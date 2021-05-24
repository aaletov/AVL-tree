#define BOOST_TEST_MODULE AVL
#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "test-functions.hpp"

BOOST_AUTO_TEST_SUITE(test_int)

BOOST_AUTO_TEST_CASE(test_nothrow_tree_insertion)
{
	std::cout << "Testing no throws while inserting into int tree\n";
	size_t size = std::abs(getGenerator()()) * 1 + 11;
	std::cout << "Making tree of size " << size;
	BOOST_REQUIRE_NO_THROW(makeRandIntTree(size));
}

BOOST_AUTO_TEST_CASE(test_tree_sort)
{
	std::cout << "Testing sort of int tree\n";
	size_t size = std::abs(getGenerator()()) * 1 + 11;
	std::cout << "Making tree of size " << size;
	IntTree intTree = makeRandIntTree(size);
	BOOST_REQUIRE(testSort(intTree, std::less< int >()));
}

BOOST_AUTO_TEST_CASE(test_tree_balance)
{
	std::cout << "Testing balance of int tree\n";
	size_t size = std::abs(getGenerator()()) * 1 + 11;
	std::cout << "Making tree of size " << size;
	IntTree intTree = makeRandIntTree(size);
	BOOST_REQUIRE(testBalance(intTree));
}

BOOST_AUTO_TEST_SUITE_END()