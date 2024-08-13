#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;
long gBalance = 0;

void addMoney(int money)
{
    std::unique_lock<std::mutex> sl(m);

    gBalance += money;

    std::cout << "Amount " << money << " added; current balance: " << gBalance << "\n";

    cv.notify_one(); // notify the "waiters"
}

void withdrawMoney(int money)
{
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul, [money]() // here it is waiting for awakening by notify
    {
            return (gBalance != 0); // still be waiting if this is false even if this thread awakened via notify by some other thread
    });

    if (gBalance < money)
    {
        std::cout << "Money can't be deducted because current balance is less than " << money << "\n";
        return;
    }

    gBalance -= money;

    std::cout << "Amount " << money << " deducted; current balance is " << gBalance << "\n";
}

int main()
{
    while (true)
    {
        std::thread t1(withdrawMoney, 500);
        std::thread t2(addMoney, 500);

        if (t1.joinable())
            t1.join();

        if (t2.joinable())
            t2.join();

        std::cout << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}