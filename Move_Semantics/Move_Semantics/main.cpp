#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>

class String
{
public:
	String() = default;
	String(const char* str)
	{
		m_size = strlen(str);
		m_data = new char[m_size];
		memcpy_s(m_data, m_size, str, m_size);
		std::cout << "Constructed from const char* str.\n";
	}

	String(const String& other)
	{
		m_size = other.m_size;
		m_data = new char[m_size];
		memcpy_s(m_data, m_size, other.m_data, m_size);
		std::cout << "Copied from other.\n";
	}

	String(String&& other) noexcept
	{
		m_size = other.m_size;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_data = nullptr;
		std::cout << "Moved from other.\n";
	}

	String& operator=(String&& other) noexcept
	{
		if (this == &other)
			return *this;

		delete[] m_data;

		m_size = other.m_size;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_data = nullptr;
		std::cout << "Assign-Moved from other.\n";

		return *this;
	}

	~String()
	{
		delete[] m_data;
		std::cout << "Destroyed.\n";
	}

	friend std::ostream& operator<< (std::ostream& ost, const String& str)
	{
		for (uint32_t i = 0; i < str.m_size; i++)
			ost << str.m_data[i];
		return ost;
	}

private:
	char* m_data;
	uint32_t m_size;
};

class Entity
{
public:
	Entity(const String& name)
		: m_name(name)
	{
		std::cout << m_name << " entity created via String-copy.\n";
	}

	Entity(String&& name)
		: m_name(std::move(name))
	{
		std::cout << m_name << " entity created via String-move.\n";
	}
private:
	String m_name;
};

int main()
{
	Entity entity("Aleksey");

	String apple = "Apple";
	String dest;

	std::cout << "apple: " << apple << "\n";
	std::cout << "dest: " << dest << "\n";

	dest = std::move(apple);

	std::cout << "apple: " << apple << "\n";
	std::cout << "dest: " << dest << "\n";

	return 0;
}