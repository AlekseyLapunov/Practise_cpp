#include <iostream>
#include <thread>
#include <semaphore>
#include <deque>

std::binary_semaphore signalToProducer {1},
                      signalToConsumer {0};

std::deque<int32_t> gCommonBuffer;
const uint32_t gMaxBufferSize = 5;

void producer(int32_t value)
{
    while (value)
    {
        signalToProducer.acquire();

        std::cout << "producer() Producing: ";

        for (uint32_t i = 0; i < gMaxBufferSize; i++)
        {
            gCommonBuffer.push_back(value);

            std::cout << value << " ";

            value--;

            std::this_thread::sleep_for(std::chrono::milliseconds(150)); // for demonstration purpose only
        }

        std::cout << "\n";

        signalToConsumer.release();
    }

    std::cout << "producer() Nothing left to produce\n";
}

void consumer()
{
    bool breakOnEmpty = false;

    while (true)
    {
        signalToConsumer.acquire();

        std::cout << "consumer() Consuming: ";
        for (uint32_t i = 0; i < gMaxBufferSize; i++)
        {
            int32_t value = gCommonBuffer.back();

            std::cout << value << " ";

            gCommonBuffer.pop_back();

            if (!breakOnEmpty)
                breakOnEmpty = (value == 1);

            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // for demonstration purpose only
        }

        std::cout << "\n";

        signalToProducer.release();

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