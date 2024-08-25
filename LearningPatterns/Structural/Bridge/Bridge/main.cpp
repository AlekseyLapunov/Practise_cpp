#include <iostream>

#include "bridge_demo.hpp"

int main()
{
    std::cout << "Radio block\n";
    {
        Radio radio;

        Remote remote(radio);

        remote.togglePower();

        for (uint8_t i = 0; i < 3; i++)
            remote.scrollChannel(Remote::Control::Up);

        remote.scrollChannel(Remote::Control::Down);

        for (uint8_t i = 0; i < 6; i++)
            remote.scrollVolume(Remote::Control::Up);

        for (uint8_t i = 0; i < 3; i++)
            remote.scrollVolume(Remote::Control::Down);
    }

    std::cout << "\nTv block\n";
    {
        Tv tv;

        AdvancedRemote remote(tv);

        remote.togglePower();

        for (uint8_t i = 0; i < 3; i++)
            remote.scrollChannel(Remote::Control::Up);

        remote.scrollChannel(Remote::Control::Down);

        for (uint8_t i = 0; i < 6; i++)
            remote.scrollVolume(Remote::Control::Up);

        for (uint8_t i = 0; i < 3; i++)
            remote.scrollVolume(Remote::Control::Down);

        remote.mute();
    }

    return 0;
}