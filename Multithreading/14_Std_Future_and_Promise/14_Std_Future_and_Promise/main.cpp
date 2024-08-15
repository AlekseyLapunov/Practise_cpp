#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <cstdint>

void countOddSum(std::promise<uint64_t>&& oddSumPromise, uint64_t start, uint64_t end)
{
    std::cout << "| Thread: started counting\n";

    uint64_t oddSum = 0;

    for (uint64_t i = start; i <= end; i++)
        oddSum += i % 2 != 0 ? i : 0;

    oddSumPromise.set_value(oddSum); // setting the value

    std::cout << "| Thread: finished counting\n";
}

int main()
{
    const uint64_t start = 0;
    const uint64_t end = 1900000000;

    std::promise<uint64_t> oddSum; // promise is like a setter...
    std::future<uint64_t> oddSumFuture = oddSum.get_future(); // ...and future is like a getter

    std::cout << "Creating thread\n";
    std::thread t(countOddSum, std::move(oddSum), start, end);

    std::cout << "Waiting for result\n";
    // Main execution thread will wait for result until it is ready to be claimed
    std::cout << "oddSum = " << oddSumFuture.get() << "\n"; // getting the value

    std::cout << "Joining thread\n";
    if (t.joinable())
        t.join();
    
    return 0;
}