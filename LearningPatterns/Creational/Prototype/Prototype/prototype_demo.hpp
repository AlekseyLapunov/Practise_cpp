#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

class UiElement
{
public:
    UiElement() {}
    virtual ~UiElement() {}

    virtual std::unique_ptr<UiElement> clone() const = 0;
    virtual void info() const = 0;

public:
    std::string color;
    size_t x = 0;
    size_t y = 0;
};

class Button : public UiElement
{
public:
    Button(const std::string& _color, size_t _x, size_t _y, const std::string& _sign)
    {
        color = _color;
        x = _x;
        y = _y;
        sign = _sign;

        std::cout << "Button() created\n";
    }

    ~Button()
    {
        std::cout << "Button() destroyed\n";
    }

    std::unique_ptr<UiElement> clone() const override
    {
        return std::make_unique<Button>(color, x, y, sign);
    }

    void info() const override
    {
        std::cout << "Button {"
            << x << " "
            << y << " "
            << color << " "
            << sign
            << "}\n";
    }

public:
    std::string sign = "Press";
};

class Checkbox : public UiElement
{
public:
    Checkbox(const std::string& _color, size_t _x, size_t _y, bool _checked)
    {
        color = _color;
        x = _x;
        y = _y;
        checked = _checked;

        std::cout << "Checkbox() created\n";
    }

    ~Checkbox()
    {
        std::cout << "Checkbox() destroyed\n";
    }

    std::unique_ptr<UiElement> clone() const override
    {
        return std::make_unique<Checkbox>(color, x, y, checked);
    }

    void info() const override
    {
        std::cout << "Checkbox {"
            << x << " "
            << y << " "
            << color << " "
            << (checked ? "checked" : "unchecked")
            << "}\n";
    }

public:
    bool checked = false;
};

class UiElementsRegistry
{
public:
    void add(UiElement* element) 
    {
        m_items.insert({m_innerCounter++, element->clone()});
    }

    UiElement& getById(size_t id)
    {
        return *m_items.at(id).get();
    }

    UiElement& getByColor(const std::string& color)
    {
        for (auto& entry : m_items)
            if (entry.second->color == color)
                return *m_items.at(entry.first).get();
    }

private:
    std::unordered_map<size_t, std::unique_ptr<UiElement>> m_items;
    size_t m_innerCounter = 0;
};
