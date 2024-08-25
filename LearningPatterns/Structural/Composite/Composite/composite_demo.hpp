#pragma once

#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <utility>

namespace ImageEditor
{

    class Graphic
    {
    public:
        Graphic() : m_id(idCounter()++) {}
        Graphic(const Graphic& other) : m_id(other.m_id) {}
        virtual ~Graphic() {}

    public:
        virtual void move(int32_t x, int32_t y) = 0;
        virtual void draw() = 0;

        size_t id() const
        {
            return m_id;
        }

    private:
        const size_t m_id;

    private:
        static size_t& idCounter()
        {
            static size_t g_idCounter = 0;
            return g_idCounter;
        }
        static size_t g_idCounter;
    };

    class CompoundGraphic : public Graphic
    {
    public:
        CompoundGraphic() : Graphic() {}
        ~CompoundGraphic() {}

    public:
        void add(const Graphic& obj)
        {
            // ...imagine that we have proper tree-wise components adding
        }

        void remove(size_t id)
        {
            // ...imagine that we have proper tree-wise components removing
        }

    public:
        void move(int32_t x, int32_t y) override
        {
            for (auto& child : m_children)
            {
                child.second->move(x, y);
                std::cout << "CompoundGraphic: move() " << x << " " << y << "\n";
            }
        }

        void draw() override
        {
            for (auto& child : m_children)
            {
                child.second->draw();
                std::cout << "CompoundGraphic: draw()\n";
            }
        }

    private:
        std::unordered_map<size_t, Graphic*> m_children;
    };

    class Dot : public Graphic
    {
    public:
        Dot(int32_t x, int32_t y) : m_x(x), m_y(y)
        {}

        virtual ~Dot() {}

        void move(int32_t x, int32_t y) override
        {
            m_x = x;
            m_y = y;

            std::cout << "Dot: move() " << m_x << " " << m_y << "\n";
        }

        virtual void draw() override
        {
            std::cout << "Dot: draw()\n";
        }

    protected:
        int m_x;
        int m_y;
    };

    class Circle : public Dot
    {
    public:
        Circle(int32_t x, int32_t y, uint32_t radius) : Dot(x, y), m_radius(radius)
        {}

        ~Circle() {}

        void draw() override
        {
            std::cout << "Circle: draw()\n";
        }

    private:
        uint32_t m_radius;
    };

} // namespace ImageEditor
