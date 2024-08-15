#include <iostream>
#include <thread>
#include <future>
#include <cstdint>

// * std::async manages std::promise by its own
// ^ it returns std::future which holds the result;
// ^ there are several launch policies:
// ^ 1. std::launch::async -> is for threading, is creating thread;
// ^ 2. std::launch::deffered -> not creating a thread;
// ^ 3. std::launch::async | std::launch::deffered -> compiler or OS figures out which policy is preffered. 

uint64_t oddSum(uint64_t start, uint64_t end)
{
    std::cout << "oddSum(...) ThreadID: " << std::this_thread::get_id() << "\n";

    uint64_t result = 0;

    for (uint64_t i = start; i <= end; i++)
        result += i % 2 != 0 ? i : 0;

    return result;
}

int main()
{
    uint64_t start = 0, end = 1900000000;

    std::cout << "main() ThreadID: " << std::this_thread::get_id() << "\n";

    std::future<uint64_t> oddSumVal = std::async(std::launch::deferred | std::launch::async, oddSum, start, end);

    std::cout << "Waiting for result\n";
    std::cout << "OddSumVal: " << oddSumVal.get() << "\n"; // waiting for result because it is future-get

    return 0;
}