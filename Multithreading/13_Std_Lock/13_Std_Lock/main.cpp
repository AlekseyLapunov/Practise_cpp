
// * std::lock(m1, m2, ..., mn)
// ^ all arguments are locked via a sequence of calls to: lock(), try_lock() or unlock() on each argument;
// ^ will try to not cause a deadlock;
// ^ it is a blocking call.

// Examples:
//
// #1 No deadlock
//      Thread 1                Thread 2
//      std::lock(m1, m2);      std::lock(m1, m2);
// Explanation: locking and unlocking mutexes in the same order basically will not cause deadlock situation.
// 
// #2 No deadlock
//      Thread 1                Thread 2
//      std::lock(m1, m2);      std::lock(m2, m1);
// Explanation: t1 will try to lock m1 and wait till m2 be awailable to lock;
//              at the same time t2 will try to lock m2 and wait till m1 be awailable to lock;
//              deadlock will not happen because t1 will unlock m1 at the moment t2 will try to acquire it;
//              respectivly t2 will unlock m2 so t1 will not wait forever.
// 
// #3 Possible deadlock
//      Thread 1                Thread 2
//      std::lock(m1, m2);      std::lock(m3, m4);
//      std::lock(m3, m4);      std::lock(m1, m2);

#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1, m2;

void taskA(int loopFor, int increment, uint64_t& commonBalance)
{
    for (int i = 0; i < loopFor; ++i)
    {
        std::lock(m1, m2); // The order is no matter here

        // Uncomment these two lines and comment std::lock line to see the deadlock
        //m1.lock();
        //m2.lock();

        commonBalance += increment;

        m1.unlock(); // * The order is no matter here
        m2.unlock(); // ^
    }
}

void taskB(int loopFor, int increment, uint64_t& commonBalance)
{
    for (int i = 0; i < loopFor; ++i)
    {
        std::lock(m2, m1); // The order is no matter here

        // Uncomment these two lines and comment std::lock line to see the deadlock
        //m2.lock();
        //m1.lock();

        commonBalance += increment;

        m2.unlock(); // * The order is no matter here
        m1.unlock(); // ^
    }
}

int main()
{
    const int loopForT1 = 1000000;
    const int loopForT2 = 1500000;
    const int increment = 6;

    uint64_t commonBalance = 0;

    std::thread t1(taskA, loopForT1, increment, std::ref(commonBalance));
    std::thread t2(taskB, loopForT2, increment, std::ref(commonBalance));

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    int expectedResult = increment*(loopForT1 + loopForT2);

    std::cout << "realResult"
              << ((commonBalance == expectedResult) ? "\t==\t" : "\t!=\t")
              << "expectedResult\n";

    std::cout << "realResult\t==\t" << commonBalance << "\n";
    std::cout << "expectedResult\t==\t" << expectedResult << "\n";

    return 0;
}