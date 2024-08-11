#include <iostream>
#include <chrono>
#include <thread>

void run(int count)
{
    while (count-- > 0)
        std::cout << "run()\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "task run() finished\n";
}

int main()
{
    {
        std::cout << "\tJoin block\n";

        std::thread t(run, 10);

        std::cout << "main() before join\n";

        if (t.joinable())
            t.join();

        if (t.joinable())
            t.join(); // double join will fail the program without if-statement guard containing joinable check

        std::cout << "main() after join\n";
    }
    
    {
        std::cout << "\tDetach block\n";

        std::thread t(run, 10);

        std::cout << "main() before detach\n";

        if (t.joinable())
            t.detach(); // main thread will not wait for task in "t" thread be complete
                        // detach does not terminate the thread

        if (t.joinable())
            t.detach(); // double detach will also fail the program without joinable check

        std::cout << "main() after detach\n";

        std::this_thread::sleep_for(std::chrono::seconds(5)); // stub main thread wait
    }

    return 0;
}