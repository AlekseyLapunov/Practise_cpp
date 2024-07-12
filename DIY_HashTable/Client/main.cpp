#include <iostream>
#include <diy_hashtable.hpp>
#include <string>
#include <sstream>

size_t hashFunction(std::string&& key)
{
	if (key.empty())
		return 0;

	return (size_t)(key.at(key.length() - 1)) - (size_t)('a');
}

bool keyValidator(std::string&& key)
{
	return (key.length() > 0 && key.length() <= 10);
}

int main()
{
	diy::hash_table<std::string, 26, hashFunction, keyValidator> hTable;

	std::cout << "Expecting words sequence with commands.\n";
	std::cout << "Example: Aapple Aorange Achicken Dapple\n";
	std::cout << "         ^--A is for \"Add\"  and  ^--D is for \"Delete\"\n";
	
	std::string input;
	getline(std::cin, input);
	std::stringstream sstream(input);

	if (input.empty())
	{
		std::cout << "Caught empty input string";
		return 0;
	}

	while (sstream.good())
	{
		std::string word;
		sstream >> word;
		std::string key = word.substr(1);

		if (word[0] == 'A')
		{
			hTable.insert(std::forward<std::string&&>(key));
		}
		else if (word[0] == 'D')
		{
			hTable.remove(std::forward<std::string&&>(key));
		}
	}

	hTable.print();

	return 0;
}


