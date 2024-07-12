#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

int main()
{
	std::vector<int> values = { 1, 2, 3, 4, 5 };

	for (size_t i = 0; i < values.size(); i++)
	{
		std::cout << values[i] << "\n";
	}

	for (const int& value : values)
		std::cout << value << "\n";

	for (std::vector<int>::iterator iter = values.begin();
		iter != values.end();
		++iter)
	{
		std::cout << *iter << "\n";
	}

	using ScoreMap = std::unordered_map<std::string, int>;
	ScoreMap map;

	map["me"] = 5;
	map["cpp"] = 2;

	for (ScoreMap::const_iterator it = map.begin(); it != map.end(); it++)
	{
		auto& key = it->first;
		auto& value = it->second;

		std::cout << key << " = " << value << "\n";
	}

	for (const auto& kv : map)
	{
		std::cout << kv.first << " = " << kv.second << "\n";
	}

	for (const auto& [key, value] : map)
	{
		std::cout << key << " = " << value << "\n";
	}

	std::cin.get();
}