#include <iostream>
#include <chrono>
#include <cstdint>
#include <thread>

uint64_t oddSumVal = 0, evenSumVal = 0;

void oddSum(uint64_t start, uint64_t end)
{
    for (uint64_t i = start; i <= end; i++)
        oddSumVal += (i % 2 != 0) ? i : 0;
}

void evenSum(uint64_t start, uint64_t end)
{
    for (uint64_t i = start; i <= end; i++)
        evenSumVal += (i % 2 == 0) ? i : 0;
}

int main()
{
    uint64_t start = 0, end = 1900000000;

    auto timeStart = std::chrono::high_resolution_clock::now();

    /*
    // Single-threaded implementation (1600 ms)
    oddSum(start, end);  // "costly" function #1
    evenSum(start, end); // "costly" function #2
    */

    // Two-threaded implementation (822 ms)
    std::thread t1(oddSum, start, end);
    std::thread t2(evenSum, start, end);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    auto timeEnd = std::chrono::high_resolution_clock::now();

    std::cout << "oddSumVal = " << oddSumVal << "\n";
    std::cout << "evenSumVal = " << evenSumVal << "\n";

    std::cout << "Elapsed Time = "
        << std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count()/1000
        << " ms\n";

    return 0;
}
