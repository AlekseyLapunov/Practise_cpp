#pragma once

#include <iostream>
#include <diy_vector.hpp>

namespace tests
{
    static diy::vector<int> vec;

    void init()
    {
        if (vec.size() != 0)
            return;

        vec.emplaceBack(1);
        vec.emplaceBack(2);
        vec.emplaceBack(3);
        vec.emplaceBack(4);
        vec.emplaceBack(5);
    }

    void print(std::ostream& ost = std::cout)
    {
        ost << "Printing vector:\n";
        const int size = vec.size();
        for (int i{ 0 }; i < size; i++)
            ost << "[" << i << "] " << vec[i] << "\n";
    }

    void rangeBasedPrint(std::ostream& ost = std::cout)
    {
        ost << "Printing vector (range-based for-loop):\n";
        for (auto& item : vec)
            ost << item << "\n";
    }

    void iteratorPrint(std::ostream& ost = std::cout)
    {
        ost << "Printing vector (iterator):\n";
        for (diy::vector<int>::iter it = vec.begin();
            it != vec.end();
            it++)
        {
            ost << *it << "\n";
        }
    }

}
