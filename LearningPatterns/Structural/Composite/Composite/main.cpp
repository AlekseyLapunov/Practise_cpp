#include <iostream>
#include <memory>

#include "composite_demo.hpp"

int main()
{
    ImageEditor::CompoundGraphic root;

    ImageEditor::Dot dot(5, 4);

    root.add(dot); // pretending that we're adding dots
    root.add(dot);
    root.add(dot);
    root.add(dot);

    std::cout << root.id() << "\n";
    root.draw(); // won't actually say anything because inner container is empty

    return 0;
}