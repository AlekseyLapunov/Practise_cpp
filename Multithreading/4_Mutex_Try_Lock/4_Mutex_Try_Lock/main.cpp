#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;

int gMoney;

void addMoney()
{
    for (size_t i = 0; i < 100000; i++)
    {
        // try_lock is not blocking so we're getting wrong answer here if is is enabled

        //if (m.try_lock())
        //{
        m.lock();
        ++gMoney;
        m.unlock();
        //}
    }
}

int main()
{
    std::thread t1(addMoney);
    std::thread t2(addMoney);

    if(t1.joinable())
        t1.join();

    if(t2.joinable())
        t2.join();

    std::cout << "gMoney: " << gMoney << "\n";

    return 0;
}