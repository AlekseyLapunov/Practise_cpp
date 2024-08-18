#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace diy
{
    class thread_pool
    {
    public:
        thread_pool(size_t numThreads)
        {
            for (size_t i = 0; i < numThreads; i++)
            {
                m_workers.emplace_back([this]()
                {
                    while (true)
                    {
                        std::unique_lock<std::mutex> ul(m_mutex);

                        m_cv.wait(ul, [this]() { return m_stopFlag || !m_tasks.empty(); });

                        if (m_stopFlag && m_tasks.empty())
                            return;

                        auto task = std::move(m_tasks.front());
                        m_tasks.pop();

                        ul.unlock();

                        task();
                    }
                });
            }
        }

        ~thread_pool()
        {
            std::unique_lock<std::mutex> ul(m_mutex);
            m_stopFlag = true;
            ul.unlock();
            m_cv.notify_all();

            for (std::thread& worker : m_workers)
                if (worker.joinable())
                    worker.join();
        }

    public:
        void enqueueTask(std::function<void()>&& task)
        {
            std::unique_lock<std::mutex> ul(m_mutex);

            m_tasks.emplace(std::forward<std::function<void()>>(task));

            ul.unlock();

            m_cv.notify_one();
        }

    private:
        std::vector<std::thread> m_workers;
        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::queue<std::function<void()>> m_tasks;

        bool m_stopFlag = false;
    };

} // namespace diy