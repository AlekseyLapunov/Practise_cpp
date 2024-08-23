#include <iostream>
#include <memory>

#include "builder_demo.hpp"

int main()
{
    Director director;
    
    std::shared_ptr<Car> car;
    {
        std::cout << "\nBlock #1. Sports Car building\n";
        CarBuilder carBuilder;

        if (director.makeSportsCar(carBuilder))
            car = carBuilder.getResult();
        else
            return 1;
    }
    car->display();

    std::shared_ptr<Manual> manual;
    {
        std::cout << "\nBlock #2. SUV Car Manual building\n";
        CarManualBuilder carManualBuilder;

        if (director.makeSUV(carManualBuilder))
            manual = carManualBuilder.getResult();
        else
            return 1;
    }
    manual->display();

    return 0;
}