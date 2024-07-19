#include <iostream>

#include <diy_vector.hpp>

#include "tests.hpp"

int main()
{
    tests::init();
    tests::print();
    tests::rangeBasedPrint();
    tests::iteratorPrint();

    return 0;
}