#pragma once

#include <string>
#include <unordered_map>
#include "utils.hpp"
#include "client.hpp"
#include "queue/working_queue.h"
#include "models/models.hpp"
#include "debug.hpp"

class BaseDeviceManager
{
public:
  using MessageCallback = std::function<void(const Message &, std::string, size_t)>;
  BaseDeviceManager();
  virtual ~BaseDeviceManager() = 0;
  void init(const Enumerate &enumerate);
  void callback_Failure(MessageCallback callback);
  void callback_Success(MessageCallback callback);

protected:
  const std::string GLOBAL_SESSION_ID = "global";

  virtual void handle_custom_response(const Call &call, const std::string &session) = 0;
  bool execute_callback(const Message &msg, int type, const std::string &session);
  template <typename MessageType>
  bool execute_callback(const Call &call, const std::string &session);
  void call(std::string message, int type, MessageCallback callback) throw();

private:
  Client m_client;
  WorkingQueue<Call, std::string> m_worker_queue;
  WorkingQueue<bool, size_t> m_request_queue;

  std::unordered_map<std::pair<int, std::string>, MessageCallback, pair_hash> m_callbacks;
  std::string m_path = "null";
  std::string m_session = "null";
  bool m_is_real = false;
  
  void handle_response(const Call &call, const std::string &session);
};

inline BaseDeviceManager::BaseDeviceManager()
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

inline BaseDeviceManager::~BaseDeviceManager()
{
}

inline void BaseDeviceManager::init(const Enumerate &enumerate)
{
  if (enumerate.session != "null")
    throw std::runtime_error("device already occupied, complete the previous session first");

  m_path = enumerate.path;
  m_session = enumerate.session;
  m_is_real = enumerate.vendor && enumerate.product;
}

inline void BaseDeviceManager::callback_Failure(MessageCallback callback)
{
  using namespace hw::trezor::messages;
  auto key = std::make_pair(MessageType_Failure, GLOBAL_SESSION_ID);
  m_callbacks[key] = callback;
}

inline void BaseDeviceManager::callback_Success(MessageCallback callback)
{
  using namespace hw::trezor::messages;
  auto key = std::make_pair(MessageType_Success, GLOBAL_SESSION_ID);
  m_callbacks[key] = callback;
}

inline bool BaseDeviceManager::execute_callback(const Message &msg, int type, const std::string &session)
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
bool BaseDeviceManager::execute_callback(const Call &call, const std::string &session)
{
  return execute_callback(call.to_message<MessageType>(), call.type, session);
}

inline void BaseDeviceManager::call(std::string message, int type, MessageCallback callback) throw()
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
      if (callback)
      {
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

inline void BaseDeviceManager::handle_response(const Call &call, const std::string &session)
{
  using namespace hw::trezor::messages;

  switch (call.type)
  {
  case MessageType_Failure:
    if (!execute_callback<Failure>(call, session))
      execute_callback<Failure>(call, GLOBAL_SESSION_ID);
    break;
  case MessageType_Success:
    if (!execute_callback<Success>(call, session))
      execute_callback<Success>(call, GLOBAL_SESSION_ID);
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
    handle_custom_response(call, session);
    break;
  }
}
