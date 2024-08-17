#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;

std::deque<int32_t> gCommonBuffer;
const uint32_t gMaxBufferSize = 25;

void producer(int32_t value)
{
    while (value)
    {
        std::unique_lock<std::mutex> locker(m); // there is the race for the mutex acquire

        cv.wait(locker, []() // waiting the notification
            {
                return gCommonBuffer.size() < gMaxBufferSize; // ...and condition meeting
            });

        gCommonBuffer.push_back(value);
        std::cout << "producer() Produced: " << value << "\n";

        value--;

        locker.unlock();
        cv.notify_one();
    }

    std::cout << "producer() Nothing left to produce\n";
}

void consumer()
{
    bool breakOnEmpty = false;

    while (true)
    {
        std::unique_lock<std::mutex> locker(m); // there is the race for the mutex acquire

        cv.wait(locker, []() // waiting the notification
            {
                return gCommonBuffer.size() > 0; // ...and condition meeting
            });

        int32_t value = gCommonBuffer.back();

        if (!breakOnEmpty)
            breakOnEmpty = (value == 1);

        gCommonBuffer.pop_back();
        std::cout << "consumer() Consumed: " << value << "\n";

        locker.unlock();
        cv.notify_one();

        if (gCommonBuffer.size() == 0 && breakOnEmpty)
            break;
    }

    std::cout << "consumer() Nothing left to consume\n";
}

int main()
{
    std::thread t1(producer, 50);
    std::thread t2(consumer);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    return 0;
}