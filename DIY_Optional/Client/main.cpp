#include <iostream>
#include <diy_optional.hpp>

#include "tests.hpp"

int main()
{
    tests::integer();
    tests::floating();
    tests::strings();
    tests::nullPointers();

    return 0;
}
