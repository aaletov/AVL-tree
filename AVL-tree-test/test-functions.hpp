#ifndef TEST_FUNCTIONS_HPP
#define TEST_FUNCTIONS_HPP

#include <functional>
#include "../AVL-tree/AVL-tree.hpp"

using IntTree = AVL_tree< int, int, std::function< bool(int, int) > >;
using IntCompare = std::function< bool(int, int) >;

std::function< int() > getGenerator();
AVL_tree< int, int, std::function< bool(int, int) > > makeRandIntTree(size_t size);
bool testSort(IntTree intTree, IntCompare comparator);
bool testBalance(IntTree intTree);

#endif