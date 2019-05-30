#pragma once

#include <string>
#include <unordered_map>
#include "client.hpp"
#include "models/models.hpp"
#include "queue/working_queue.h"
#include "utils.hpp"

#include "debug.hpp"

class DeviceManager
{
public:
  using MessageCallback = std::function<void(const Message &, std::string, size_t)>;

  DeviceManager()
  {
    m_worker_queue.setGlobalPopCallback(
        [&](const std::string &session_pop, const Call &call) {
          using namespace hw::trezor::messages;
          if (MessageType_ButtonRequest == call.type)
          {
            m_worker_queue.push(session_pop, [&](const std::string &session) {
              return m_client.call(session, pack_message(ButtonAck()));
            });
          }
          else
          {
            auto released = m_client.release(session_pop);
            if (released.session == m_session)
              m_session = "null";

            handle_response(call, released.session);

            m_request_queue.unlockPop();
          }
        });
  }

  void init(const Enumerate &enumerate)
  {
    if (enumerate.session != "null")
      throw std::runtime_error("device already occupied, complete the previous session first");

    m_path = enumerate.path;
    m_session = enumerate.session;
    m_is_real = enumerate.vendor && enumerate.product;
  }

  void call_Ping(std::string text, bool button_protection, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    Ping message;
    message.set_message(text);
    message.set_button_protection(button_protection);
    call(pack_message(message), MessageType_Success, callback);
  }

  void call_BeamGetOwnerKey(bool show_display, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamGetOwnerKey message;
    message.set_show_display(show_display);
    call(pack_message(message), MessageType_BeamOwnerKey, callback);
  }

  void call_BeamGenerateNonce(uint8_t slot, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamGenerateNonce message;
    message.set_slot(slot);
    call(pack_message(message), MessageType_BeamPublicKey, callback);
  }

  void call_BeamGetNoncePublic(uint8_t slot, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamGetNoncePublic message;
    message.set_slot(slot);
    call(pack_message(message), MessageType_BeamPublicKey, callback);
  }

  void call_BeamGenerateKey(uint64_t idx, uint32_t type, uint32_t subIdx, uint64_t value, bool isCoinKey, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamGenerateKey message;
    auto kidv = message.mutable_kidv();
    kidv->set_idx(idx);
    kidv->set_type(type);
    kidv->set_sub_idx(subIdx);
    kidv->set_value(value);
    message.set_allocated_kidv(kidv);
    message.set_is_coin_key(isCoinKey);
    call(pack_message(message), MessageType_BeamPublicKey, callback);
    message.release_kidv();
  }

  void callback_Failure(MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    auto key = std::make_pair(MessageType_Failure, GLOBAL_SESSION_ID);
    m_callbacks[key] = callback;
  }

  void callback_Success(MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    auto key = std::make_pair(MessageType_Success, GLOBAL_SESSION_ID);
    m_callbacks[key] = callback;
  }

protected:
  void handle_response(const Call &call, const std::string &session)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;
    
    switch (call.type)
    {
    case MessageType_Failure:
      execute_callback<Failure>(call, GLOBAL_SESSION_ID);
      break;
    case MessageType_Success:
      if (!execute_callback<Success>(call, session))
        execute_callback<Success>(call, GLOBAL_SESSION_ID);
      break;
    case MessageType_BeamOwnerKey:
      execute_callback<BeamOwnerKey>(call, session);
      break;
    case MessageType_BeamPublicKey:
      execute_callback<BeamPublicKey>(call, session);
      break;
    case INTERNAL_ERROR:
    {
      print_call_response(call);

      m_session = "null";
      m_request_queue.clear();
      m_worker_queue.clear();

      Failure error;
      error.set_message(call.error);
      execute_callback(error, MessageType_Failure, GLOBAL_SESSION_ID);
      break;
    }
    default:
      break;
    }
  }

  bool execute_callback(const Message &msg, int type, const std::string &session)
  {
    auto key = std::make_pair(type, session);
    auto callback = m_callbacks.find(key);
    if (callback != m_callbacks.end())
    {
      callback->second(msg, session, m_request_queue.size());
      return true;
    }
    return false;
  }

  template <typename MessageType>
  bool execute_callback(const Call &call, const std::string &session)
  {
    return execute_callback(call.to_message<MessageType>(), call.type, session);
  }

  void call(std::string message, int type, MessageCallback callback) throw()
  {
    m_request_queue.push(m_request_queue.size(), [&, message, type, callback](size_t size) {
      if (m_session != "null")
      {
        throw std::runtime_error("previous session must be completed");
        // return false; //TODO: decide which better (throw or return false)
      }

      auto acquired = m_client.acquire(m_path, m_session);
      if (acquired.error.empty())
      {
        m_session = acquired.session;
        if (callback) {
          auto key = std::make_pair(type, m_session);
          m_callbacks[key] = callback;
        }
        m_worker_queue.push(m_session, [&, message](const std::string &session) {
          return m_client.call(session, message);
        });

        m_request_queue.lockPop();
      }
      return true;
    });
  }

private:
  const std::string GLOBAL_SESSION_ID = "global";

  Client m_client;
  WorkingQueue<Call, std::string> m_worker_queue;
  WorkingQueue<bool, size_t> m_request_queue;

  std::unordered_map<std::pair<int, std::string>, MessageCallback, pair_hash> m_callbacks;
  std::string m_path = "null";
  std::string m_session = "null";
  bool m_is_real = false;
};
