#ifndef PRINT_INT_HPP
#define PRINT_INT_HPP

#include <iostream>
#include <iomanip>
#include <deque>
#include <algorithm>
#include <functional>
#include "node.hpp"
#include "AVL-tree.hpp"
#include "functions.hpp"
#include "int-comp.hpp"

void printInt(AVL_tree< int, int, intComparator >& tree, std::ostream& out, int CELL_SIZE);
void printIntNode(std::ostream& out, node::node_t< int, int >* p, int cellSize);

void printInt(AVL_tree< int, int, intComparator >& tree, std::ostream& out, int CELL_SIZE)
{
    node::node_t< int, int >* root = tree.getRoot();
    if (root == nullptr)
    {
        out << "Tree is empty" << '\n';
        return;
    }
    node::node_t< int, int >* p = root;
    if (CELL_SIZE <= 0)
    {
        CELL_SIZE = trunc(log10(INT_MAX)) + 1 + 1 + 2;
    }

    int currCellSize = CELL_SIZE * pow(2, node::getHeight(root) - 1);
    int leftSpace;
    int rightSpace;
    //int level = 0;
    int currCellsCount = 1;
    int currDequeSize;
    std::deque<node::node_t< int, int >*> deque;

    deque.push_back(p);
    while (containsValues(deque))
    {
        currDequeSize = deque.size();
        if (deque[0] != root)
        {
            currCellSize /= 2;
            leftSpace = (currCellSize - 1) / 2;
            rightSpace = currCellSize - leftSpace;
            out << '\n';
            for (int i = 0; i < currDequeSize; i++)
            {
                out << std::setw(leftSpace) << '|' << std::setw(rightSpace) << ' ';
            }
            out << '\n';
        }
        for (int i = 0; i < currDequeSize; i++)
        {
            if (deque[i] == nullptr)
            {
                deque.push_back(nullptr);
                deque.push_back(nullptr);
            }
            else
            {
                deque.push_back(deque[i]->left_);
                deque.push_back(deque[i]->right_);
            }
            printIntNode(out, deque[i], currCellSize);
        }
        for (int i = 0; i < currDequeSize; i++)
        {
            deque.pop_front();
        }
        out << '\n';
    }
    out << '\n';
}

void printIntNode(std::ostream& out, node::node_t< int, int >* p, int cellSize)
{
    if (p != nullptr)
    {
        int keyLen;
        if (std::get< 0 >(p->pair_) != 0)
        {
            keyLen = trunc(log10(abs(std::get< 0 >(p->pair_)))) + 1;
        }
        else
        {
            keyLen = 1;
        }
        int leftSpace = (cellSize - keyLen - 2) / 2;
        int rightSpace = cellSize - leftSpace - keyLen;
        out << std::setw(leftSpace) << '(' << std::get< 0 >(p->pair_) << ')' << std::setw(rightSpace - 1) << ' ';
    }
    else
    {
        out << std::setw(cellSize /*- 1*/) << ' ';
    }
}

#endif