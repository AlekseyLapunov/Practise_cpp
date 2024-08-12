#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// * std::try_lock(m1, m2, ..., mn)
// ^ This try_lock implementation will lock every mutex passed as arguments

int gX = 0;
int gY = 0;

std::mutex m1, m2;

void doSomeWorkForSeconds(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void incrementXorY(int& XorY, std::mutex& m, const char* desc)
{
    for (int i = 0; i < 5; i++)
    {
        m.lock();

        ++XorY;

        std::cout << desc << XorY << "\n";

        m.unlock();

        doSomeWorkForSeconds(1);
    }
}

void consumeXandY()
{
    int useCount = 5;
    int XplusY = 0;

    while (true)
    {
        int lockResult = std::try_lock(m1, m2);

        std::cout << "lockResult = " << lockResult << "\n";

        if (lockResult == -1)
        {
            if (gX != 0 && gY != 0)
            {
                --useCount;
                XplusY += gX + gY;
                gX = 0;
                gY = 0;
                std::cout << "XplusY " << XplusY << "\n";
            }

            m1.unlock();
            m2.unlock();

            if (useCount == 0)
                break;
        }
    }
}

int main()
{
    std::thread t1(incrementXorY, std::ref(gX), std::ref(m1), "X ");
    std::thread t2(incrementXorY, std::ref(gY), std::ref(m2), "Y ");
    std::thread t3(consumeXandY);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    if (t3.joinable())
        t3.join();

    return 0;
}
