#pragma once

#include <iostream>

class Button
{
public:
    virtual void paint() = 0;

    virtual ~Button() {};
};

class ButtonWin : public Button
{
public:
    ButtonWin()
    {
        std::cout << "ButtonWin() created\n";
    }

    void paint() override
    {
        std::cout << "ButtonWin() painted\n";
    }

    ~ButtonWin()
    {
        std::cout << "ButtonWin() destroyed\n";
    }
};

class ButtonLinux : public Button
{
public:
    ButtonLinux()
    {
        std::cout << "ButtonLinux() created\n";
    }

    void paint() override
    {
        std::cout << "ButtonLinux() painted\n";
    }

    ~ButtonLinux()
    {
        std::cout << "ButtonLinux() destroyed\n";
    }
};

class Checkbox
{
public:
    virtual void paint() = 0;

    virtual ~Checkbox() {};
};

class CheckboxWin : public Checkbox
{
public:
    CheckboxWin()
    {
        std::cout << "CheckboxWin() created\n";
    }

    void paint() override
    {
        std::cout << "CheckboxWin() painted\n";
    }

    ~CheckboxWin()
    {
        std::cout << "CheckboxWin() destroyed\n";
    }
};

class CheckboxLinux : public Checkbox
{
public:
    CheckboxLinux()
    {
        std::cout << "CheckboxLinux() created\n";
    }

    void paint() override
    {
        std::cout << "CheckboxLinux() painted\n";
    }

    ~CheckboxLinux()
    {
        std::cout << "CheckboxLinux() destroyed\n";
    }
};

class FactoryGUI
{
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
};

class FactoryWin : public FactoryGUI
{
public:
    Button* createButton() override { return new ButtonWin; }
    Checkbox* createCheckbox() override { return new CheckboxWin; }
};

class FactoryLinux : public FactoryGUI
{
public:
    Button* createButton() override { return new ButtonLinux; }
    Checkbox* createCheckbox() override { return new CheckboxLinux; }
};

class Application
{
private:
    FactoryGUI* m_factory = nullptr;
    Button* m_button = nullptr;
    Checkbox* m_checkbox = nullptr;

public:
    Application(FactoryGUI* factory) : m_factory(factory) {}

    void createUI()
    {
        m_button = m_factory->createButton();
        m_checkbox = m_factory->createCheckbox();
    }

    void paint()
    {
        if (m_button != nullptr)
            m_button->paint();
        
        if (m_checkbox != nullptr)
            m_checkbox->paint();
    }

    ~Application()
    {
        if (m_button != nullptr)
            delete m_button;

        if (m_checkbox != nullptr)
            delete m_checkbox;
    }
};