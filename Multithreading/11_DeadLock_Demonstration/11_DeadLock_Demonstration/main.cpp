#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
std::mutex m2;

// Deadlock happen here because double-lock will result in waiting for mutex is available to lock;
// so we have two waiting threads for mutex to be unlocked.

void task1()
{
    m1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m2.lock();
    std::cout << "Critical section of task1\n";
    m1.unlock();
    m2.unlock();
}

void task2()
{
    m2.lock(); // Possible solution is to change this to m1.lock()...
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m1.lock(); // ...and change this to m2.lock() respectively.
    std::cout << "Critical section of task2\n";
    m2.unlock();
    m1.unlock();
}

int main()
{
    std::thread t1(task1);
    std::thread t2(task2);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    return 0;
}