#pragma once

#include <iostream>
#include <cstdint>

class Device
{
public:
    virtual bool isEnabled() = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual uint8_t getVolume() = 0;
    virtual void setVolume(uint8_t volume) = 0;
    virtual uint8_t getChannel() = 0;
    virtual void setChannel(uint8_t channel) = 0;

protected:
    bool m_isEnabled = false;
    uint8_t m_volume = 0;
    uint8_t m_channel = 0;

public:
    const uint8_t maxVolume = 10;
    const uint8_t maxChannels = 10;
};

class Radio : public Device
{
public:
    bool isEnabled() override
    {
        return m_isEnabled;
    }

    void enable() override
    {
        std::cout << "Radio: enable()\n";
        m_isEnabled = true;
    }

    void disable() override
    {
        std::cout << "Radio: disable()\n";
        m_isEnabled = true;
    }

    uint8_t getVolume() override
    {
        return m_volume;
    }

    void setVolume(uint8_t volume) override
    {
        m_volume = volume;

        std::cout << "Radio: setVolume(...) {" << (int)m_volume << "}\n";
    }

    uint8_t getChannel() override
    {
        return m_channel;
    }

    void setChannel(uint8_t channel) override
    {
        m_channel = channel;

        std::cout << "Radio: setChannel(...) {" << (int)m_channel << "}\n";
    }
};

class Tv : public Device
{
public:
    bool isEnabled() override
    {
        return m_isEnabled;
    }

    void enable() override
    {
        std::cout << "Tv: enable()\n";
        m_isEnabled = true;
    }

    void disable() override
    {
        std::cout << "Tv: disable()\n";
        m_isEnabled = true;
    }

    uint8_t getVolume() override
    {
        return m_volume;
    }

    void setVolume(uint8_t volume) override
    {
        m_volume = volume;

        std::cout << "Tv: setVolume(...) {" << (int)m_volume << "}\n";
    }

    uint8_t getChannel() override
    {
        return m_channel;
    }

    void setChannel(uint8_t channel) override
    {
        m_channel = channel;

        std::cout << "Tv: setChannel(...) {" << (int)m_channel << "}\n";
    }
};

class Remote
{
public:
    Remote(Device& device)
    {
        m_device = &device;
    }

public:
    enum class Control { Up, Down };

    void togglePower()
    {
        if (m_device->isEnabled())
            m_device->disable();
        else
            m_device->enable();
    }

    void scrollVolume(Control word)
    {
        if (!m_device->isEnabled())
            return;

        uint8_t volume = m_device->getVolume();

        switch (word)
        {
        case Remote::Control::Up:
            volume += volume < m_device->maxVolume ? 1 : 0;
            break;
        case Remote::Control::Down:
            volume -= volume > 0 ? 1 : 0;
            break;
        default:
            return;
        }

        m_device->setVolume(volume);
    }

    void scrollChannel(Control word)
    {
        if (!m_device->isEnabled())
            return;

        uint8_t channel = m_device->getChannel();

        switch (word)
        {
        case Remote::Control::Up:
            channel += channel < m_device->maxChannels ? 1 : 0;
            break;
        case Remote::Control::Down:
            channel -= channel > 0 ? 1 : 0;
            break;
        default:
            return;
        }

        m_device->setChannel(channel);
    }

protected:
    Device* m_device;
};

class AdvancedRemote : public Remote
{
public:
    AdvancedRemote(Device& device) : Remote(device)
    {}

    void mute()
    {
        if (!m_device->isEnabled())
            return;

        m_device->setVolume(0);
    }
};
