#define BOOST_TEST_MODULE AVL_TREE
#include <set>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <boost/test/included/unit_test.hpp>
#include "functions.hpp"
#include "interface.hpp"
#include "test-functions.hpp"


BOOST_AUTO_TEST_SUITE(test_int)

BOOST_AUTO_TEST_CASE(test_nothrow_tree_insertion)
{
	std::cout << "Testing no throws while inserting into int tree\n";
	std::function< int() > generator = getGenerator();
	size_t size = std::abs(generator()) * 1 + 11;
	std::cout << "Making tree of size " << size << '\n';
	BOOST_REQUIRE_NO_THROW(makeRandIntTree(size));
}

BOOST_AUTO_TEST_CASE(test_tree_sort)
{
	std::cout << "Testing sort of int tree\n";
	std::function< int() > generator = getGenerator();
	size_t size = std::abs(generator()) * 1 + 11;
	std::cout << "Making tree of size " << size << '\n';
	IntTree intTree = makeRandIntTree(size);
	BOOST_REQUIRE(testSort(intTree));
}

BOOST_AUTO_TEST_CASE(test_tree_balance)
{
	std::cout << "Testing balance of int tree\n";
	std::function< int() > generator = getGenerator();
	size_t size = std::abs(generator()) * 1 + 11;
	std::cout << "Making tree of size " << size << '\n';
	IntTree intTree = makeRandIntTree(size);
	BOOST_REQUIRE(testBalance(intTree));
}

BOOST_AUTO_TEST_CASE(test_root_deleting)
{
	std::cout << "Testing root deleting\n";
	std::function< int() > generator = getGenerator();
	size_t size = std::abs(generator()) * 1 + 11;
	std::cout << "Making tree of size " << size << '\n';
	IntTree intTree = makeRandIntTree(size);
	int rootKey = node::getKey(intTree.getRoot());
	BOOST_REQUIRE_NO_THROW(intTree.deleteKey(rootKey));
	BOOST_REQUIRE(!intTree.recursiveSearchKey(rootKey));
}

BOOST_AUTO_TEST_CASE(test_uniqueness)
{
	std::cout << "Testing uniqueness\n";
	std::function< int() > generator = getGenerator();
	size_t size = std::abs(generator()) * 1 + 11;
	IntTree intTree = makeRandIntTree(size);
	std::vector< std::pair< int, int > > treeVector;
	auto inserter = [treeVector](node::node_t< int, int >* p) mutable
	{
		treeVector.push_back(p->pair_);
		return true;
	};
	intTree.inorderRecursiveTraversal(inserter);
	std::set< std::pair< int, int > > treeSet(treeVector.begin(), treeVector.end());
	BOOST_REQUIRE(treeVector.size() == treeSet.size());
}

BOOST_AUTO_TEST_CASE(test_double_delete)
{
	std::cout << "Testing double delete\n";
	std::function< int() > generator = getGenerator();
	size_t size = std::abs(generator()) * 1 + 11;
	std::vector< std::pair< int, int > > vals;
	int val;
	for (size_t i = 0; i < size; i++)
	{
		val = generator();
		vals.push_back({ val, val });
	}
	std::cout << "Making tree of size " << size << '\n';
	IntTree intTree;
	for (std::pair< int, int > pair : vals)
	{
		intTree.insertPair(pair);
	}
	intTree.deleteKey(std::get< 0 >(vals[3]));
	BOOST_REQUIRE_NO_THROW(intTree.deleteKey(std::get< 0 >(vals[3])));
}

BOOST_AUTO_TEST_CASE(test_delete)
{
	bool res = true;
	std::cout << "Testing delete\n";
	std::function< int() > generator = getGenerator();
	size_t size = std::abs(generator()) * 1 + 11;
	std::vector< std::pair< int, int > > vals;
	int val;
	for (size_t i = 0; i < size; i++)
	{
		val = generator();
		vals.push_back({ val, val });
	}
	std::cout << "Making tree of size " << size << '\n';
	IntTree intTree;
	for (std::pair< int, int > pair : vals)
	{
		intTree.insertPair(pair);
	}
	std::cout << "Deleting\n";
	for (size_t i = 0; i < size / 10; i++)
	{
		size_t toDelete = size + 1;
		while (toDelete >= size)
		{
			toDelete = generator() / 10000;
		}
		intTree.deleteKey(std::get< 0 >(vals[toDelete]));
		res &= testSort(intTree);
		res &= testBalance(intTree);
		res &= !intTree.recursiveSearchKey(std::get< 0 >(vals[toDelete]));
	}
	BOOST_REQUIRE(res);
}

BOOST_AUTO_TEST_CASE(test_format)
{
	std::vector< std::string > toFormat
	{
		"word:",
		"word",
		"word.",
		"word,",
		"word;",
		"Word;",
		"wOrd;",
		"worD;",
		"word(",
		"word)",
		"word\'",
		"word\"",
		":word",
		"word",
		".word",
		",word",
		";word",
		"(word",
		")word",
		"\'word",
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

BOOST_AUTO_TEST_CASE(test_filter)
{
	std::vector< std::string > wrong
	{
		"foejfioj3",
		"DWOI5J5OiO",
		"a^fefe&&&"
	};
	std::vector< std::string > correct
	{
		"Awooo`",
		"wo`wowoo",
		"re-eeee",
		"qwiodj"
	};
	BOOST_REQUIRE(!std::any_of(wrong.begin(), wrong.end(), filterWord));
	BOOST_REQUIRE(std::all_of(correct.begin(), correct.end(), filterWord));
}

BOOST_AUTO_TEST_CASE(test_interface)
{
	std::locale::global(std::locale("Russian"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Testing interface\n";
	std::stringstream ss;
	std::vector< std::string > commands
	{
		"add poz",
		"print 1",
		"search poz",
		"delete poz",
		"print 1",
		"add поз",
		"print 1",
		"search поз",
		"delete поз",
		"print 1",
		"read text.txt",
		"print 5",
		"search I",
		"read text_2.txt",
		"print 5",
		"search I",
		"search текст",
		"add текст",
		"print 1",
		"delete текст",
		"print 1",
		"quit"
	};
	std::copy(commands.begin(), commands.end(), std::ostream_iterator<std::string>(ss, "\n"));
	Dictionary dict;
	Interface inter(dict, ss, std::cout);
	BOOST_REQUIRE_NO_THROW(inter.start());
}

BOOST_AUTO_TEST_SUITE_END()