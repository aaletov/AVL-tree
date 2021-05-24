#ifndef NODE_OPERATIONS_HPP
#define NODE_OPERATIONS_HPP

#include <cmath>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <climits>
#include "node.hpp"

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
	bool insertPair(node_t< Key, T >* root, node_t< Key, T >*& p, std::pair< Key, T > pair, Compare comparator);
	template < class Key, class T, class Compare >
	bool deleteKey(node_t< Key, T >* p, Key key, Compare comparator);
	template < class Key, class T, class Compare >
	void deleteNode(node_t< Key, T >*& toDelete, Compare comparator);
	template < class Key, class T >
	void balance(node_t< Key, T >*& p);
	template < class Key, class T >
	int getHeight(node_t< Key, T >* p);
	// ����� ����� ��������
	template < class Key, class T >
	void doRRrotation(node_t< Key, T >*& p);
	// ����� ������ ��������
	template < class Key, class T >
	void doLLrotation(node_t< Key, T >*& p);
	// ������� ������ ��������
	template < class Key, class T >
	void doLRrotation(node_t< Key, T >*& p);
	// ������� ����� ��������
	template < class Key, class T >
	void doRLrotation(node_t< Key, T >*& p);
	template < class Key, class T >
	Key getKey(node_t< Key, T >* p);
}

template < class Key, class T, class Callable >
void node::inorderRecursiveTraversal(node::node_t< Key, T >* p, Callable callback)
{
	if (p == nullptr)
	{
		return;
	}
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
		return recursiveSearchNode(p->left_, key, comparator);
	}
	else
	{
		return recursiveSearchNode(p->right_, key, comparator);
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
bool node::insertPair(node::node_t< Key, T >* root, node::node_t< Key, T >*& p, std::pair< Key, T > pair, Compare comparator)
{
	bool res;
	// ������ �� ���� ������
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
		// �������
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
	// �������
	balance(p);
	return res;
}

template < class Key, class T, class Compare >
bool node::deleteKey(node::node_t< Key, T >* p, Key key, Compare comparator)
{
	bool res;
	// ������ �� ���� ������
	if (p != nullptr)
	{
		// ��������
		if (p->right_ != nullptr)
		{
			if (key == getKey(p->right_))
			{
				res = true;
				deleteNode(p->right_, comparator);
			}
			else if (!comparator(key, getKey(p)))
			{
				res = deleteKey(p->right_, key, comparator);
			}

		}
		if (p->left_ != nullptr)
		{
			if (key == getKey(p->left_))
			{
				res = true;
				deleteNode(p->left_, comparator);
			}
			else if (comparator(key, getKey(p)))
			{
				res = deleteKey(p->left_, key, comparator);
			}
		}


	}
	else
	{
		return false;
	}
	// �������
	balance(p);
	return res;
}

template < class Key, class T, class Compare >
void node::deleteNode(node::node_t< Key, T >*& p, Compare comparator)
{
	assert(p != nullptr);
	node::node_t< Key, T >*& left = p->left_;
	node::node_t< Key, T >*& right = p->right_;
	if (left == nullptr && right == nullptr)
	{
		delete p;
		p = nullptr;
	}
	else if (left == nullptr && right != nullptr)
	{
		delete p;
		p = right;
	}
	else if (left != nullptr && right == nullptr)
	{
		delete p;
		p = left;
	}
	else
	{
		node::node_t< Key, T >* minRight = right;
		while (minRight->left_ != nullptr)
		{
			minRight = minRight->left_;
		}
		std::pair< Key, T > minRightPair = minRight->pair_;
		deleteKey(p, getKey(minRight), comparator);
		node::node_t< Key, T >* tempLeft = left;
		node::node_t< Key, T >* tempRight = right;
		delete p;
		p = new node::node_t< Key, T >{ tempLeft, tempRight, minRightPair };
	}
}

template < class Key, class T >
void node::balance(node::node_t< Key, T >*& p)
{
	assert(p != nullptr);
	if (p->left_ == nullptr && p->right_ == nullptr)
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
	if (p == nullptr)
	{
		return 0;
	}
	int left = 1;
	int right = 1;
	if (p->left_ != nullptr)
	{
		left += getHeight(p->left_);
	}
	if (p->right_ != nullptr)
	{
		right += getHeight(p->right_);
	}
	return (left > right) ? left : right;
}

// ����� ����� ��������
template < class Key, class T >
void node::doRRrotation(node::node_t< Key, T >*& p)
{
	assert(p != nullptr);
	assert(p->right_ != nullptr);
	node::node_t< Key, T >* p1 = p->right_;
	p->right_ = p1->left_;
	p1->left_ = p;
	p = p1; //
}

// ����� ������ ��������
template < class Key, class T >
void node::doLLrotation(node::node_t< Key, T >*& p)
{
	assert(p != nullptr);
	assert(p->left_ != nullptr);
	node::node_t< Key, T >* p1 = p->left_;
	p->left_ = p1->right_;
	p1->right_ = p;
	p = p1; //
}

// ������� ������ ��������
template < class Key, class T >
void node::doLRrotation(node::node_t< Key, T >*& p)
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
	p = p2; //
}

// ������� ����� ��������
template < class Key, class T >
void node::doRLrotation(node::node_t< Key, T >*& p)
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
	p = p2; //
}

template < class Key, class T >
Key node::getKey(node::node_t< Key, T >* p)
{
	return std::get<0>(p->pair_);
}

#endif