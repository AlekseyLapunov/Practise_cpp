#include <iostream>
#include <memory>

#include "prototype_demo.hpp"

int main()
{
    UiElementsRegistry reg;

    std::unique_ptr<UiElement> button = std::make_unique<Button>("red", 1, 1, "Press");
    std::unique_ptr<UiElement> checkbox = std::make_unique<Checkbox>("blue", 100, 150, false);

    reg.add(button.get());
    reg.add(checkbox.get());

    UiElement& elem1 = reg.getByColor("red");
    elem1.info();

    UiElement& elem2 = reg.getByColor("blue");
    elem2.info();

    UiElement& elem3 = reg.getById(0);
    elem3.info();

    UiElement& elem4 = reg.getById(1);
    elem4.info();

    return 0;
}