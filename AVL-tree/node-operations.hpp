#ifndef NODE_OPERATIONS_HPP
#define NODE_OPERATIONS_HPP

#include <cmath>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <climits>
#include "node.hpp"
#include "functions.hpp"

namespace node
{
	template < class Key, class T, class Callable >
	void inorderRecursiveTraversal(node_t< Key, T >* p, Callable callback);
	template < class Key, class T, class Compare >
	node_t< Key, T >* recursiveSearchNode(node_t< Key, T >* p, Key key, Compare comparator);
	template < class Key, class T, class Compare >
	node_t< Key, T >* iterativeSearchNode(node_t< Key, T >* p, Key key, Compare comparator);
	template < class Key, class T, class Compare >
	node_t< Key, T >* iterativeSearchParent(node_t< Key, T >* p, Key key, Compare comparator);
	template < class Key, class T, class Compare >
	bool insertPair(node_t< Key, T >* root, node_t< Key, T >* p, std::pair< Key, T > pair, Compare comparator);
	template < class Key, class T, class Compare >
	bool deleteKey(node_t< Key, T >* p, Key key, Compare comparator);
	template < class Key, class T, class Compare >
	void deleteNode(node_t< Key, T >* p, node_t< Key, T >* toDelete, Compare comparator);
	template < class Key, class T >
	void balance(node_t< Key, T >* p);
	template < class Key, class T >
	int getHeight(node_t< Key, T >* p);
	// Малое левое вращение
	template < class Key, class T >
	void doRRrotation(node_t< Key, T >* p);
	// Малое правое вращение
	template < class Key, class T >
	void doLLrotation(node_t< Key, T >* p);
	// Большое правое вращение
	template < class Key, class T >
	void doLRrotation(node_t< Key, T >* p);
	// Большое левое вращение
	template < class Key, class T >
	void doRLrotation(node_t< Key, T >* p);
	template < class Key, class T >
	void print(node_t< Key, T >* p, std::ostream& out, int CELL_SIZE);
	template < class Key, class T >
	Key getKey(node_t< Key, T >* p);
}

template < class Key, class T, class Callable >
void node::inorderRecursiveTraversal(node::node_t< Key, T >* p, Callable callback)
{
	assert(p != nullptr);
	inorderRecursiveTraversal(p->left_, callback);
	callback(p);
	inorderRecursiveTraversal(p->right_, callback);
}

template < class Key, class T, class Compare >
node::node_t< Key, T >* node::recursiveSearchNode(node::node_t< Key, T >* p, Key key, Compare comparator)
{
	if (p == nullptr || key == getKey(p))
	{
		return p;
	}
	if (comparator(key, getKey(p)))
	{
		return recursiveSearchNode(p->left_, key);
	}
	else
	{
		return recursiveSearchNode(p->right_, key);
	}
}

template < class Key, class T, class Compare >
node::node_t< Key, T >* node::iterativeSearchNode(node::node_t< Key, T >* p, Key key, Compare comparator)
{
	while (p != nullptr && key != getKey(p))
	{
		if (comparator(key, getKey(p)))
		{
			p = p->left_;
		}
		else
		{
			p = p->right_;
		}
	}
	return p;
}

template < class Key, class T, class Compare >
node::node_t< Key, T >* node::iterativeSearchParent(node::node_t< Key, T >* p, Key key, Compare comparator)
{
	if (getKey(p) == key)
	{
		return nullptr;
	}
	while (true)
	{
		if (comparator(key, getKey(p)) && p->left_ == nullptr)
		{
			break;
		}
		if (!comparator(key, getKey(p)) && p->right_ == nullptr)
		{
			break;
		}
		if (comparator(key, getKey(p)))
		{
			p = p->left_;
		}
		else
		{
			p = p->right_;
		}
	}
	return p;
}

template < class Key, class T, class Compare >
bool node::insertPair(node::node_t< Key, T >* root, node::node_t< Key, T >* p, std::pair< Key, T > pair, Compare comparator)
{
	bool res;
	// Проход по пути поиска
	if (p != nullptr)
	{
		if (std::get< 0 >(pair) == getKey(p))
		{
			return false;
		}
		else if (comparator(std::get< 0 >(pair), getKey(p)))
		{
			res = insertPair(root, p->left_, pair, comparator);
		}
		else
		{
			res = insertPair(root, p->right_, pair, comparator);
		}
	}
	else
	{
		// Вставка
		node::node_t< Key, T >* parent = iterativeSearchParent(root, std::get< 0 >(pair), comparator);
		if (comparator(std::get< 0 >(pair), getKey(parent)))
		{
			parent->left_ = new node::node_t< Key, T >{ nullptr, nullptr, pair };
		}
		else
		{
			parent->right_ = new node::node_t< Key, T >{ nullptr, nullptr, pair };
		}
		return true;
	}
	// Возврат
	balance(p);
	return res;
}

template < class Key, class T, class Compare >
bool node::deleteKey(node::node_t< Key, T >* p, Key key, Compare comparator)
{
	bool res;
	// Проход по пути поиска
	if (p != nullptr)
	{
		// Удаление
		if (key == getKey(p->right_))
		{
			res = true;
			deleteNode(p, p->right_, comparator);
		}
		else if (key == getKey(p->left_))
		{
			res = true;
			deleteNode(p, p->left_, comparator);
		}
		else if (comparator(key, getKey(p)))
		{
			res = deleteKey(p->left_, key, comparator);
		}
		else
		{
			res = deleteKey(p->right_, key, comparator);
		}
	}
	else
	{
		return false;
	}
	// Возврат
	balance(p);
	return res;
}

template < class Key, class T, class Compare >
void node::deleteNode(node::node_t< Key, T >* root, node::node_t< Key, T >* node, Compare comparator)
{
	assert(root != nullptr && node != nullptr);
	node::node_t< Key, T >* p = iterativeSearchParent(root, getKey(node), comparator);
	node::node_t< Key, T >* left = node->left_;
	node::node_t< Key, T >* right = node->right_;
	if (node == root)
	{
		node::node_t< Key, T >* minRight = right;
		while (minRight->left_ != nullptr)
		{
			minRight = minRight->left_;
		}
		std::pair< Key, T > minRightPair = minRight->key_;
		if (minRight == right)
		{
			right = nullptr;
		}
		minRight = nullptr;
		deleteKey(root, std::get< 0 >(minRightPair), comparator);
		root = new node::node_t< Key, T >{ left, right, minRightPair };
		if (left != nullptr)
		{
			left->p_ = root;
		}
		if (right != nullptr)
		{
			right->p_ = root;
		}
		delete node;
		return;
	}
	if (left == nullptr && right == nullptr)
	{
		if (p->left_ == node)
		{
			delete node;
			p->left_ = nullptr;
		}
		else
		{
			delete node;
			p->right_ = nullptr;
		}
	}
	else if (left == nullptr && right != nullptr)
	{
		if (p->left_ == node)
		{
			delete node;
			p->left_ = right;
		}
		else
		{
			delete node;
			p->right_ = right;
		}
	}
	else if (left != nullptr && right == nullptr)
	{
		if (p->left_ == node)
		{
			delete node;
			p->left_ = left;
		}
		else
		{
			delete node;
			p->right_ = left;
		}
	}
	else
	{
		node::node_t< Key, T >* minRight = right;
		while (minRight->left_ != nullptr)
		{
			minRight = minRight->left_;
		}
		std::pair< Key, T > minRightPair = minRight->key_;
		if (minRight == right)
		{
			right = nullptr;
		}
		minRight = nullptr;
		deleteKey(root, std::get< 0 >(minRightPair), comparator);
		if (p->left_ == node)
		{
			p->left_ = new node::node_t< Key, T >{ left, right, minRightPair };
			left->p_ = p->left_;
		}
		else
		{
			p->right_ = new node::node_t< Key, T >{ left, right, minRightPair };
			left->p_ = p->right_;
		}
		delete node;
	}
}

template < class Key, class T >
void node::balance(node::node_t< Key, T >* p)
{
	assert(p != nullptr);
	if (p->left_ == nullptr || p->right_ == nullptr)
	{
		return;
	}
	node::node_t< Key, T >* b;
	// case 3, 4
	b = p->left_;
	if (getHeight(b) - getHeight(p->right_) == 2)
	{
		if (getHeight(b->right_) <= getHeight(b->left_))
		{
			doLLrotation(p);
		}
		else
		{
			doLRrotation(p);
		}
		return;
	}
	// case 1, 2
	b = p->right_;
	if (getHeight(b) - getHeight(p->left_) == 2)
	{
		if (getHeight(b->left_) <= getHeight(b->right_))
		{
			doRRrotation(p);
		}
		else
		{
			doRLrotation(p);
		}
	}
}

template < class Key, class T >
int node::getHeight(node::node_t< Key, T >* p)
{
	if (p->left_ == nullptr || p->right_ == nullptr)
	{
		return 1;
	}
	int leftHeight = getHeight(p->left_);
	int rightHeight = getHeight(p->right_);
	return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Малое левое вращение
template < class Key, class T >
void node::doRRrotation(node::node_t< Key, T >* p)
{
	assert(p != nullptr);
	assert(p->right_ != nullptr);
	node::node_t< Key, T >* p1 = p->right_;
	p->right_ = p1->left_;
	p1->left_ = p;
}

// Малое правое вращение
template < class Key, class T >
void node::doLLrotation(node::node_t< Key, T >* p)
{
	assert(p != nullptr);
	assert(p->left_ != nullptr);
	node::node_t< Key, T >* p1 = p->left_;
	p->left_ = p1->right_;
	p1->right_ = p;
}

// Большое правое вращение
template < class Key, class T >
void node::doLRrotation(node::node_t< Key, T >* p)
{
	assert(p != nullptr);
	assert(p->left_ != nullptr);
	assert(p->left_->right_ != nullptr);
	node::node_t< Key, T >* p1 = p->left_;
	node::node_t< Key, T >* p2 = p1->right_;
	p1->right_ = p2->left_;
	p2->left_ = p1;
	p->left_ = p2->right_;
	p2->right_ = p;
}

// Большое левое вращение
template < class Key, class T >
void node::doRLrotation(node::node_t< Key, T >* p)
{
	assert(p != nullptr);
	assert(p->right_ != nullptr);
	assert(p->right_->left_ != nullptr);
	node::node_t< Key, T >* p1 = p->right_;
	node::node_t< Key, T >* p2 = p1->left_;
	p1->left_ = p2->right_;
	p2->right_ = p1;
	p->right_ = p2->left_;
	p2->left_ = p;
}

template < class Key, class T >
void node::print(node::node_t< Key, T >* p, std::ostream& out, int CELL_SIZE)
{
	if (p == nullptr)
	{
		out << "Tree is empty" << '\n';
		return;
	}
	node::node_t< Key, T >* node = p;
	if (CELL_SIZE <= 0)
	{
		throw -1;
	}

	int currCellSize = CELL_SIZE * pow(2, (getHeight(p) - 1));
	int currCellsCount = 1;
	int currDequeSize;
	std::deque< node::node_t< Key, T >* > deque;

	deque.push_back(node);
	while (containsValues(deque))
	{
		currDequeSize = deque.size();
		if (deque[0] != p)
		{
			currCellSize /= 2;
			out << '\n';
			for (int i = 0; i < currDequeSize; i++)
			{
				out << std::setw(currCellSize) << std::internal << '|' << ' ';
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
			if (deque[i] == nullptr)
			{
				out << std::setw(currCellSize) << std::internal << '(' << ' ' << ')';
			}
			else
			{
				out << std::setw(currCellSize) << std::internal << '(' << std::get< 0 >(deque[i]->pair_) << ')';
			}
		}
		for (int i = 0; i < currDequeSize; i++)
		{
			deque.pop_front();
		}
		out << '\n';
	}
	out << '\n';
}

template < class Key, class T >
Key node::getKey(node::node_t< Key, T >* p)
{
	return std::get<0>(p->pair_);
}

#endif