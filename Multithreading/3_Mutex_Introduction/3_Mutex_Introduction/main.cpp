#include <iostream>
#include <thread>
#include <mutex>

int gMyAmount = 0;

std::mutex m;

// Obviously this is not efficient but it is a trivial example of mutex using
void addMoney()
{
    m.lock();

    for (size_t i = 0; i < 120000; i++)
        ++gMyAmount;

    m.unlock();
}

int main()
{
    std::thread t1(addMoney);
    std::thread t2(addMoney);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    // Without mutex locks output is 120000 when it should be 240000 (due to race conditions)
    std::cout << "gMyAmount: " << gMyAmount << "\n";

    return 0;
}