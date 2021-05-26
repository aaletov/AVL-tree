#include "functions.hpp"
#include <vector>
#include <algorithm>
#include <iostream> //

bool dictComparator(std::string lword, std::string rword)
{
	return std::lexicographical_compare(lword.begin(), lword.end(), rword.begin(), rword.end());
}

void formatWord(std::string& word)
{
	const std::vector< std::string > PUNCT{ ":", "-", ".", ",", ";", "(", ")", "\'", "\"" };
	auto eraser = [&word](const std::string& punct) mutable
	{
		size_t pos = word.find(punct);
		if (pos != std::string::npos)
		{
			word.erase(pos, 1);
		}
	};
	std::for_each(PUNCT.begin(), PUNCT.end(), eraser);
}

bool filterWord(const std::string& word)
{
	return true;
}