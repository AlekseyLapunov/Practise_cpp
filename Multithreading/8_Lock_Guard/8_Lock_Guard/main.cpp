#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;
int gBuffer = 0;

void task(const char* threadNumber, int loopFor)
{
    //m.lock();
    // We can use std::lock_guard instead.

    std::lock_guard<std::mutex> lock(m);

    for (int i = 0; i < loopFor; ++i)
    {
        gBuffer++;
        std::cout << threadNumber << gBuffer << "\n";
    }

    //m.unlock();
}

int main()
{
    std::thread t1(task, "T1 ", 10);
    std::thread t2(task, "T2 ", 10);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    return 0;
}