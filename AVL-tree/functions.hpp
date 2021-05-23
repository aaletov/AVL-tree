#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <iomanip>
#include <deque>
#include "node.hpp"

template < class Key, class T >
void printNode(std::ostream& out, node_t< Key, T >* p, int cellSize);
template < class Key, class T >
bool containsValues(std::deque<T*>& deque);

template < class Key, class T >
void printNode(std::ostream& out, node_t< Key, T >* p, int cellSize)
{
    out << std::setw(cellSize) << std::internal << '(' << std::get< 0 >(p->pair_) << ')';
}

template <typename T>
bool containsValues(std::deque<T*>& deque)
{
    bool x = false;
    for (int i = 0; i < deque.size(); i++)
    {
        x = x || deque[i] != nullptr;
        if (x)
        {
            break;
        }
    }
    return x;
}

#endif