#include <iostream>
#include <thread>
#include <mutex>
#include <cstdint>

int64_t gBalance = 0;

std::mutex m;

// Only Reading the common Resource is not considered as Critical section.
// If there is at least one Writing operation applied to the common Resource, it is now a Critical section.

// Thread and Process Syncronization usually comes in a form of semaphore and mutex use. 

void addMoney(int64_t val)
{
    std::unique_lock<std::mutex> ul(m);
    gBalance += val; // Critical section, possible race condition without mutex lock
}

int main()
{
    std::thread t1(addMoney, 100);
    std::thread t2(addMoney, 200);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    std::cout << "Bank balance: " << gBalance << "\n";

    return 0;
}