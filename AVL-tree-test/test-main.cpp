#define BOOST_TEST_MODULE TEST_AVL
#include <iostream>
#include <set>
#include <boost/test/included/unit_test.hpp>
#include "..\AVL-tree\print-int.hpp"
#include "test-functions.hpp"

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
	bool res = true;
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
	bool res = true;
	std::cout << "Testing double delete\n";
	std::function< int() > generator = getGenerator();
	size_t size = std::abs(generator()) * 1 + 11;
	std::vector< std::pair< int, int > > vals;
	int val;
	for (int i = 0; i < size; i++)
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
	intTree.deleteKey(std::get< 0 >(vals[3]));
}

BOOST_AUTO_TEST_CASE(test_delete)
{
	bool res = true;
	std::cout << "Testing delete\n";
	std::function< int() > generator = getGenerator();
	size_t size = std::abs(generator()) * 1 + 11;
	std::vector< std::pair< int, int > > vals;
	int val;
	for (int i = 0; i < size; i++)
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
	for (int i = 0; i < size / 10; i++)
	{
		int toDelete = size + 1;
		while (toDelete >= size)
		{
			toDelete = generator();
		}
		intTree.deleteKey(std::get< 0 >(vals[toDelete]));
		res &= testSort(intTree);
		res &= testBalance(intTree);
		res &= !intTree.recursiveSearchKey(std::get< 0 >(vals[toDelete]));
	}
	BOOST_REQUIRE(res);
}

BOOST_AUTO_TEST_SUITE_END()
