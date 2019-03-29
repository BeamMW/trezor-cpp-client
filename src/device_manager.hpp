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
  using MessageCallback = std::function<void(const Message &)>;

  DeviceManager()
  {
    m_worker.setGlobalPopCallback(
        [&](const std::string &session_pop, const Call &call) {
          if (MessageType::MessageType_ButtonRequest == call.type)
          {
            m_worker.push(session_pop, [&](const std::string &session) {
              return m_client.call(session, pack_message(ButtonAck()));
            });
          }
          else
          {
            auto released = m_client.release(session_pop);
            if (released.session == m_session)
              m_session = "null";

            switch (call.type)
            {
            case MessageType_Failure:
              execute_callback<MessageType_Failure, Failure>(call);
              break;
            case MessageType_BeamOwnerKey:
              execute_callback<MessageType_BeamOwnerKey, BeamOwnerKey>(call);
              break;
            default:
              print_call_response(call);
              break;
            }
          }
        });
  }

  ~DeviceManager()
  {
    if (m_call_thread.joinable())
      m_call_thread.join();
  }

  void init(const Enumerate &enumerate) throw()
  {
    if (enumerate.session != "null")
      throw std::runtime_error("device already occupied, complete the previous session first");

    m_path = enumerate.path;
    m_session = enumerate.session;
    m_is_real = enumerate.vendor && enumerate.product;
  }

  void call_BeamGetOwnerKey(bool show_display, MessageCallback callback)
  {
    m_callbacks[MessageType_BeamOwnerKey] = callback;

    BeamGetOwnerKey message;
    message.set_show_display(show_display);
    call(pack_message(message));
  }

  void set_callback(int type, MessageCallback callback)
  {
    m_callbacks[type] = callback;
  }

protected:
  template <int Type, typename MessageType>
  void execute_callback(const Call &call)
  {
    auto callback = m_callbacks.find(Type);
    if (callback != m_callbacks.end())
    {
      callback->second(call.to_message<MessageType>());
    }
  }

  void call(std::string message) throw()
  {
    if (m_session != "null")
      throw std::runtime_error("previous session must be completed");

    if (m_call_thread.joinable())
      m_call_thread.join();

    m_call_thread = std::thread([&, message]() {
      auto acquired = m_client.acquire(m_path, m_session);

      if (acquired.error.empty())
      {
        m_session = acquired.session;
        m_worker.push(m_session, [&, message](const std::string &session) {
          return m_client.call(session, message);
        });
      }
    });
  }

private:
  Client m_client;
  WorkingQueue<Call, std::string> m_worker;
  std::thread m_call_thread;

  std::unordered_map<int, MessageCallback> m_callbacks;
  std::string m_path = "null";
  std::string m_session = "null";
  bool m_is_real = false;
};
