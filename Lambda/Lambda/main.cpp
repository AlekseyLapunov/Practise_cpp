#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
struct A
{
    T payload;

    A(T val) : payload(val)
    {
        std::cout << "A()\n";
    }

    A(A& other) : payload(other.payload)
    {
        std::cout << "Copy A()\n";
    }

    ~A()
    {
        std::cout << "~A()\n";
    }

    friend std::ostream& operator<< (std::ostream& ost, const A& obj)
    {
        return ost << obj.payload;
    }
};


int main()
{
    {
        A<int> a(5);

        // Capture by copy
        auto lambdaCaptCopy = [a]() { std::cout << "Value: " << a << "\n"; };

        // Capture by reference
        auto lambdaCaptRef = [&a]() { std::cout << "Value: " << a << "\n"; };

        lambdaCaptCopy();
        lambdaCaptRef();
    }

    const std::vector<float> vec = { 2.0f, 95.0f, -20.0f, -1.0f, 77.0f };
    auto res = std::find_if(vec.begin(), vec.end(), [](float val) { return ((int)val % 2) == 0; });

    std::cout << "*res = " << *res << '\n';

    return 0;
}
