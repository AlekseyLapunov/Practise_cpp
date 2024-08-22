#include <iostream>

#include "abstract_factory_demo.hpp"

namespace Config
{
    enum class OS { Windows, Linux };
}

int main()
{
    Config::OS os = Config::OS::Windows;

    FactoryGUI* factory;

    switch (os)
    {
    case Config::OS::Windows:
        factory = new FactoryWin;
        break;
    case Config::OS::Linux:
        factory = new FactoryLinux;
        break;
    default:
        return 1;
    }

    Application app(factory);

    app.createUI();
    app.paint();

    delete factory;

    return 0;
}