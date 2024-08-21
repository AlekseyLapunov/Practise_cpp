#include <iostream>
#include <string>

#include "factory_demo.hpp"

namespace Config
{
    enum class OS { Windows, Web };
}

int main()
{
    Dialog* dialog;

    Config::OS currentOS = Config::OS::Web;

    switch (currentOS)
    {
    case Config::OS::Windows:
        dialog = new WindowsDialog;
        break;
    case Config::OS::Web:
        dialog = new WebDialog;
        break;
    default:
        return 1;
    }

    dialog->render();

    delete dialog;

    return 0;
}