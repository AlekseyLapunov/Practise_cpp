#pragma once

#include <iostream>
#include <string>

class Database
{
public:
    static Database& getInstance()
    {
        static Database m_instance;

        return m_instance;
    }

public:
    std::string query(const std::string& query)
    {
        std::cout << "query() " << query << "\n";

        return "ok";
    }

private:
    static Database m_instance;

private:
    void connect()
    {
        std::cout << "connect() Database connected\n";
    }

private:
    Database()
    {
        connect();
    }

    Database(const Database& other) {}
    Database& operator=(const Database& other) {}
    Database(Database&& other) noexcept {}
    Database& operator=(Database&& other) noexcept {}
};