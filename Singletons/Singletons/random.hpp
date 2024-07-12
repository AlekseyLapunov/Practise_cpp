#pragma once

#include <iostream>
#include <string>

class Random
{
public:
	static Random& instance()
	{
		static Random m_instance;

		return m_instance;
	}

	static float value()
	{
		return instance()._value();
	}

private:
	float _value() { return m_value; }

private:
	static Random m_instance;

	float m_value { 0.0f };

private:
	Random() {}
	Random(const Random& other) {}
	Random& operator=(const Random& other) {}
	Random(Random&& other) noexcept {}
	Random& operator=(Random&& other) noexcept {}
};