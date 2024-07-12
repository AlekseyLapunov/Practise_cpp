#include <iostream>
#include "random.hpp"

int main()
{
    float number = Random::value();

    std::cout << number;

    return 0;
}
