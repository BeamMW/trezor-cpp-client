#pragma once

#include <atomic>
#include <functional>
#include <string>
#include <thread>
#include <tuple>
#include "queue.h"
#include "models/call.hpp"

typedef std::function<Call(const std::string &session, const std::string &message)> InQueueCallback;
typedef std::function<void(std::string session, const Call &call)> PopCallback;
typedef std::tuple<std::string, std::string, InQueueCallback> InQueueItem;

class CallQueue : public Queue<InQueueItem>
{
  public:
    CallQueue()
        : m_thread(&CallQueue::_threadMain, this),
          m_popCallback(nullptr),
          m_PauseMillis(0),
          m_pushLock(false)
    {
    }

    ~CallQueue()
    {
        m_alive.clear();
        if (m_thread.joinable())
        {
            m_thread.join();
        }
    }

    void lockPush()
    {
        m_pushLock = true;
    }

    void unlockPush()
    {
        m_pushLock = false;
    }

    void push(const std::string &session, const std::string &message, InQueueCallback callback)
    {
        if (!m_pushLock)
        {
            if (!replase(session, message, callback))
            {
                Queue::push(std::make_tuple(session, message, callback));
            }
        }
    }

    void remove(const std::string &session)
    {
        std::unique_lock<std::mutex> mlock(m_mutex);

        m_deque.erase(
            std::remove_if(m_deque.begin(), m_deque.end(), [&](const InQueueItem &item) {
                return std::get<0>(item) == session;
            }),
            m_deque.end());
    }

    bool replase(const std::string &old_session, const std::string &old_message, InQueueCallback newCallback)
    {
        std::unique_lock<std::mutex> mlock(m_mutex);

        auto it = std::find_if(m_deque.begin(), m_deque.end(), [&](const InQueueItem &item) {
            return std::get<0>(item) == old_session && std::get<1>(item) == old_message;
        });

        if (it != m_deque.end())
        {
            std::get<2>(*it) = newCallback;
            return true;
        }
        return false;
    }

    void setPopCallback(PopCallback callback)
    {
        m_popCallback = callback;
    }

    void setPause(unsigned long millis)
    {
        m_PauseMillis = millis;
    }

  private:
    void _threadMain()
    {
        while (m_alive.test_and_set())
        {
            InQueueItem item;
            if (pop(item))
            {
                auto result = std::move(std::get<2>(item)(std::get<0>(item), std::get<1>(item)));
                if (m_popCallback)
                {
                    m_popCallback(std::get<0>(item), result);
                }
            }

            if (m_PauseMillis)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(m_PauseMillis));
            }
        }
    }

    std::atomic_flag m_alive = {1};
    std::thread m_thread;
    PopCallback m_popCallback;
    std::atomic<unsigned long> m_PauseMillis;

    std::atomic<bool> m_pushLock;
};