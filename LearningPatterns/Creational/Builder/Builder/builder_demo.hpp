#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <memory>

class Car
{
public:
    Car()
    {
        std::cout << "Car() created\n";
    }

    void display()
    {
        std::cout << "display() Car info:\n" << body.str();
    }

public:
    std::stringstream body;
};

class Manual
{
public:
    Manual()
    {
        std::cout << "Manual() created\n";
    }

    void display()
    {
        std::cout << "display() Manual info:\n" << body.str();
    }

public:
    std::stringstream body;
};

class Builder
{
public:
    virtual void reset() = 0;
    virtual void setSeats(size_t number) = 0;
    virtual void setEngine(const std::string& engine) = 0;
    virtual void setTripComputer(const std::string& tripComputer) = 0;
    virtual void setGPS(const std::string& gps) = 0;
};

class CarBuilder : public Builder
{
public:
    CarBuilder()
    {
        std::cout << "CarBuilder() created\n";
    }

    ~CarBuilder()
    {
        std::cout << "~CarBuilder() destroyed\n";
    }

    void reset() override
    {
        m_car = std::make_shared<Car>();
    }

    void setSeats(size_t number) override
    {
        m_car->body << "Seats: " << number << "\n";
    }

    void setEngine(const std::string& engine) override
    {
        m_car->body << "Engine: " << engine << "\n";
    }

    void setTripComputer(const std::string& tripComputer) override
    {
        m_car->body << "Trip Computer: " << tripComputer << "\n";
    }
    
    void setGPS(const std::string& gps) override
    {
        m_car->body << "GPS: " << gps << "\n";
    }

    std::shared_ptr<Car>& getResult()
    {
        return m_car;
    }

private:
    std::shared_ptr<Car> m_car;
};

class CarManualBuilder : public Builder
{
public:
    CarManualBuilder()
    {
        std::cout << "CarManualBuilder() created\n";
    }

    ~CarManualBuilder()
    {
        std::cout << "~CarManualBuilder() destroyed\n";
    }

    void reset() override
    {
        m_manual = std::make_shared<Manual>();
    }

    void setSeats(size_t number) override
    {
        m_manual->body << "Seats: " << number << "\n";
    }

    void setEngine(const std::string& engine) override
    {
        m_manual->body << "Engine: " << engine << "\n";
    }

    void setTripComputer(const std::string& tripComputer) override
    {
        m_manual->body << "Trip Computer: " << tripComputer << "\n";
    }

    void setGPS(const std::string& gps) override
    {
        m_manual->body << "GPS: " << gps << "\n";
    }

    std::shared_ptr<Manual>& getResult()
    {
        return m_manual;
    }

private:
    std::shared_ptr<Manual> m_manual;
};

class Director
{
public:
    Director()
    {
        std::cout << "Director() created\n";
    }

    bool makeSportsCar(Builder& builder)
    {
        bool productReady = false;

        builder.reset();
        builder.setSeats(2);
        builder.setEngine("Sports Engine");
        builder.setTripComputer("SC Trip Computer v1");
        builder.setGPS("SC GPS v2");
        productReady = true;

        return productReady;
    }

    bool makeSUV(Builder& builder)
    {
        bool productReady = false;

        builder.reset();
        builder.setSeats(4);
        builder.setEngine("SUV Engine");
        builder.setTripComputer("SUV Trip Computer v2");
        builder.setGPS("SUV GPS v1");
        productReady = true;

        return productReady;
    }
};
