#include <iostream>
#include <fstream>
#include <vector>
#include "dictionary.hpp"

int main()
{
	setlocale(LC_ALL, "Russian");
	Dictionary dict;
	long long unsigned counter = 0;
	std::ifstream fs;
	fs.open("..\\text.txt");
	if (!fs.is_open())
	{
		return -2;
	}
	std::string word;
	while (!(fs.eof() || fs.fail()))
	{

		fs >> word;
		formatWord(word);
		if (!filterWord(word))
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
	Dictionary copyDict(dict);
	Dictionary::value_type max = copyDict.getMaxByValue();
	std::cout << "Max " << std::get< 0 >(max) << " \"" << std::get< 1 >(max) << "\"\n";
	copyDict.deleteKey(std::get< 0 >(max));
	for (int i = 2; i < 101; i++)
	{
		max = copyDict.getMaxByValue();
		if (max == Dictionary::npos)
		{
			std::cout << "No more words" << '\n';
			break;
		}
		std::cout << i << " place is word \"" << std::get< 0 >(max) << "\" " << std::get< 1 >(max) << " occurances\n";
		copyDict.deleteKey(std::get< 0 >(max));
	}
}