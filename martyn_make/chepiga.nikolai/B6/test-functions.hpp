#ifndef TEST_FUNCTIONS_HPP
#define TEST_FUNCTIONS_HPP

#include <functional>
#include "AVL-tree.hpp"
#include "int-comp.hpp"

using IntTree = AVL_tree< int, int, intComparator >;
std::function< int() > getGenerator();
AVL_tree< int, int, intComparator > makeRandIntTree(size_t size);
bool testSort(IntTree& intTree);
bool testBalance(IntTree& intTree);

#endif
