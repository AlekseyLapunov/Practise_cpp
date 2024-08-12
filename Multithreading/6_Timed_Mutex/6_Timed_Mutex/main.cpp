#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int gMyAmount = 0;
std::timed_mutex m;

void increment(int threadIdx)
{
    if (m.try_lock_for(std::chrono::seconds(2)))
    {
        ++gMyAmount;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "Thread " << threadIdx << " Entered\n";

        m.unlock();
    }
    else
    {
        std::cout << "Thread " << threadIdx << " Couldn't Enter\n";
    }
}

int main()
{
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);
    
    if (t1.joinable())
        t1.join();
    if (t2.joinable())
        t2.join();

    std::cout << "gMyAmount = " << gMyAmount << "\n";

    return 0;
}