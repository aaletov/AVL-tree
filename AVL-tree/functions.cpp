#include "functions.hpp"
#include <vector>
#include <locale>
#include <algorithm>
#include <functional>

bool dictComparator(std::string lword, std::string rword)
{
	return std::lexicographical_compare(lword.begin(), lword.end(), rword.begin(), rword.end());
}

void formatWord(std::string& word)
{
	const std::vector< std::string > PUNCT{ ":", ".", ",", ";", "(", ")", "\'", "\"" };
	auto eraser = [&word](const std::string& punct) mutable
	{
		size_t pos = word.find(punct);
		if ((pos == 0) || ((word.size() != 0) && (pos == (word.size() - 1))))
		{
			word.erase(pos, 1);
		}
	};
	std::locale loc;
	auto myLower = [&loc](char& c) mutable
	{
		c = std::tolower(c, loc);
	};
	std::for_each(PUNCT.begin(), PUNCT.end(), eraser);
	std::for_each(word.begin(), word.end(), myLower);
}

bool filterWord(const std::string& word)
{
	const std::vector< char > INNER{ '`', '-' };
	std::locale loc;
	auto myAlpha = [&loc, INNER](char c)
	{
		bool isInner = std::find(INNER.begin(), INNER.end(), c) != INNER.end();
		return std::isalpha(c, loc) || isInner;
	};
	return std::all_of(word.begin(), word.end(), myAlpha);
}