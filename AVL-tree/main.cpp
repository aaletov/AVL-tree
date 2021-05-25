#include <iostream>
#include <fstream>
#include <vector>
#include "dictionary.hpp"

int main()
{
	setlocale(LC_ALL, "Russian");
	const std::vector< std::string > NOT_WORDS{ "-", ",", ".", ":" };
	Dictionary dict;
	long long unsigned counter = 0;
	std::ifstream fs;
	fs.open("..\\tolstoi.txt");
	if (!fs.is_open())
	{
		return -2;
	}
	std::string word;
	while (!(fs.eof() || fs.fail()))
	{

		fs >> word;
		if (std::find(NOT_WORDS.begin(), NOT_WORDS.end(), word) != NOT_WORDS.end())
		{
			continue;
		}
		counter++;
		if (counter % 10000 == 0)
		{
			std::cout << "Read " << counter / 10000 <<  "0000\n";
			Dictionary::value_type max1 = dict.getMaxByValue();
			std::cout << std::get< 0 >(max1) << ' ' << std::get< 1 >(max1) << '\n';
		}
		if (dict.search(word))
		{
			dict.incrKey(word);
		}
		else
		{
			dict.insert({ word, 1 });
		}
	}
	fs.close();
	std::cout << "End of file\n";
	Dictionary::value_type max1 = dict.getMaxByValue();
	Dictionary::value_type max2 = dict.getPredecessorByValue(std::get< 0 >(max1));
	Dictionary::value_type max3 = dict.getPredecessorByValue(std::get< 0 >(max2));
	std::cout << std::get< 0 >(max1) << ' ' << std::get< 1 >(max1) << '\n';
	std::cout << std::get< 0 >(max2) << ' ' << std::get< 1 >(max2) << '\n';
	std::cout << std::get< 0 >(max3) << ' ' << std::get< 1 >(max3) << '\n';
}