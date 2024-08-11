#include <iostream>
#include <thread>

void func(int x)
{
    while (x-- > 0)
        std::cout << x << "\n";
}

int main()
{
    {
        std::cout << "\t#1. Function pointer\n";
        std::thread t(func, 11);

        if (t.joinable())
            t.join();
    }

    {
        std::cout << "\t#2 Lambda expression\n";
        auto lamb = [](int x) 
        {
            while (x-- > 0)
                std::cout << x << "\n";
        };

        std::thread t(lamb, 11);
        if (t.joinable())
            t.join();
    }

    {
        std::cout << "\t#3 Functor (Function object)\n";
        struct Base
        {
            void operator() (int x)
            {
                while (x-- > 0)
                    std::cout << x << "\n";
            }
        };

        std::thread t(Base(), 11);
        if (t.joinable())
            t.join();
    }

    {
        std::cout << "\t#4 Non-static member function\n";
        struct Base
        {
            void run(int x)
            {
                while (x-- > 0)
                    std::cout << x << "\n";
            }
        };

        Base obj;

        std::thread t(&Base::run, &obj, 11);
        if (t.joinable())
            t.join();
    }

    {
        std::cout << "\t#5 Static member function\n";
        struct Base
        {
            static void run(int x)
            {
                while (x-- > 0)
                    std::cout << x << "\n";
            }
        };

        std::thread t(&Base::run, 11);
        if (t.joinable())
            t.join();
    }

    return 0;
}
