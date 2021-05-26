#include <boost/test/unit_test.hpp>
#include "functions.hpp"

BOOST_AUTO_TEST_SUITE(test_word_oper)

BOOST_AUTO_TEST_CASE(test_format)
{
	std::vector< std::string > toFormat
	{
		"word:",
		"word-",
		"word.",
		"word,",
		"word;",
		"word(",
		"word)",
		"word\'",
		"word\"",
		":word",
		"-word",
		".word",
		",word",
		";word",
		"(word",
		")word",
		"\'word",
		"wo\'rd",
		"\"word"
	};
	bool res = true;
	auto tester = [&res](std::string word) mutable
	{
		formatWord(word);
		res &= (word == "word");
	};
	std::for_each(toFormat.begin(), toFormat.end(), tester);
	BOOST_REQUIRE(res);
}

BOOST_AUTO_TEST_SUITE_END()
