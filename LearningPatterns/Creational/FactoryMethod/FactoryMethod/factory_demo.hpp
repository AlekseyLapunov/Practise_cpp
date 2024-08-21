#pragma once

#include <iostream>

// Interface
class Button
{
public:
    virtual void render()
    {
        std::cout << "class Button, render()\n";
    }

    virtual void onClick()
    {
        std::cout << "class Button, onClick()\n";
    }
};

class WindowsButton : public Button
{
public:
    void render() override
    {
        std::cout << "class WindowsButton, render()\n";
    }
   
    void onClick() override
    {
        std::cout << "class WindowsButton, onClick()\n";
    }
};

class WebButton : public Button
{
public:
    void render() override
    {
        std::cout << "class WebButton, render()\n";
    }

    void onClick() override
    {
        std::cout << "class WebButton, onClick()\n";
    }
};

// This can be Interface
class Dialog
{
private:
    Button* b;

    virtual Button* createButton() = 0; // Factory Method

public:
    void render()
    {
        if (b != nullptr)
            return;

        b = this->createButton();
        b->onClick();
        b->render();
    }

    virtual ~Dialog()
    {
        delete b;
    }
};

class WindowsDialog : public Dialog
{
private:
    Button* createButton() override // Factory Method
    {
        std::cout << "class WindowsDialog, createButton() -> WindowsButton\n";
        return new WindowsButton;
    }
};

class WebDialog : public Dialog
{
private:
    Button* createButton() override // Factory Method
    {
        std::cout << "class WebDialog, createButton() -> WebButton\n";
        return new WebButton;
    }
};
