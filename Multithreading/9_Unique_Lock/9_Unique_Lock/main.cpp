#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;
int gBuffer = 0;

void task(const char* threadNumber, int loopFor)
{
    // std::defer_lock   -> do not acquire ownership of the mutex;
    // std::try_to_lock  -> try to acquire ownership of the mutex without blocking;
    // std::adopt_lock   -> assume the calling thread already has ownership of the mutex.
    std::unique_lock<std::mutex> lock(m/*, std::defer_lock*/);

    for (int i = 0; i < loopFor; ++i)
        gBuffer++;

    std::cout << threadNumber << "has completed the task\n";
}

int main()
{
    const int loopFor = 10000;

    std::thread t1(task, "T1 ", loopFor);
    std::thread t2(task, "T2 ", loopFor);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    std::cout << "gBuffer  = " << gBuffer     << "\n";
    std::cout << "expected = " << loopFor*2   << "\n";

    return 0;
}