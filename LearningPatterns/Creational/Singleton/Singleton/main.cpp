#include <iostream>
#include <string>
#include <cstdint>

#include "singleton_demo.hpp"

int main()
{
    for (uint8_t i = 0; i < 10; i++)
    {
        std::cout << "Doing query. Response: " << Database::getInstance().query("SELECT * FROM table" + std::to_string(i)) << "\n";
    }

    std::cout << "Notice that connect() was called only once\n";

    return 0;
}