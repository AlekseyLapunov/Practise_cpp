#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex m; // can be locked multiple times by same thread;
                        // using of recursive mutex brings overhead to the system,
                        // so it's should be avoided if possible
int buffer = 0;

void recursion(char c, int loopFor)
{
    if (loopFor < 0) // End recursion condition
        return;

    m.lock();
    std::cout << c << " locked\n";

    std::cout << c << " " << buffer++ << "\n";

    recursion(c, --loopFor);

    m.unlock();
    std::cout << c << " unlocked\n";
}

int main()
{
    std::thread t1(recursion, 'a', 10);
    std::thread t2(recursion, 'b', 10);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();

    return 0;
}