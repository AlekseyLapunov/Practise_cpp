#include <iostream>
#include <cstdint>
#include <chrono>
#include <string>
#include <sstream>
#include <set> // we need to show that there are exactly N unique threads

#include <diy_thread_pool.hpp>

std::string threadIdToString()
{
    auto id = std::this_thread::get_id();
    std::stringstream ss;
    ss << id;
    return ss.str();
}

void inline showSet(std::set<std::string>& memo)
{
    std::cout << "showSet() printing set:\n";
    for (auto& entry : memo)
    {
        std::cout << "Thread ID#" << entry << "\n";
    }
}

int main()
{
    const size_t threadsCount = 5;
    std::set<std::string> memoThreadsIds;

    {
        diy::thread_pool threadPool(threadsCount);

        std::cout << "main() diy::thread_pool created\n";


        std::cout << "main() enqueuing some tasks\n";

        const uint8_t tasksCount = 15;

        for (uint8_t i = 0; i < tasksCount; i++)
            threadPool.enqueueTask([i, &memoThreadsIds]()
            {
                std::string threadId = threadIdToString();
                std::cout << "Task " << (int)i << " is being executed by thread ID#" << threadId << "\n";

                memoThreadsIds.insert(threadId);

                std::this_thread::sleep_for(std::chrono::seconds(1)); // for demonstration purpose only
            });
    }

    showSet(memoThreadsIds);

    std::cout << "memoThreadsIds.size()"
        << (memoThreadsIds.size() == threadsCount ? " == " : " != ")
        << "threadsCount\n";

    return 0;
}