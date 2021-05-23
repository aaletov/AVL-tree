#ifndef NODE_OPERATIONS_HPP
#define NODE_OPERATIONS_HPP

#include <cmath>
#include "node.hpp"
#include "functions.hpp"

template < class Key, class T, class Callable >
void inorderRecursiveTraversal(node_t< Key, T >* p, Callable callback);
template < class Key, class T, class Compare >
node_t< Key, T >* recursiveSearchNode(node_t< Key, T >* p, Key key, Compare comparator);
template < class Key, class T, class Compare >
node_t< Key, T >* iterativeSearchNode(node_t< Key, T >* p, Key key, Compare comparator);
template < class Key, class T, class Compare >
node_t< Key, T >* iterativeSearchParent(node_t< Key, T >* p, Key key, Compare comparator);
template < class Key, class T, class Compare >
bool insertPair(node_t< Key, T >* p, std::pair< Key, T > pair, Compare comparator);
template < class Key, class T, class Compare >
bool deleteKey(node_t< Key, T >* p, Key key, Compare comparator);
template < class Key, class T >
void deleteNode(node_t< Key, T >* p, node_t< Key, T >* toDelete);
template < class Key, class T >
int balance(node_t< Key, T >* p);
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
void print(node_t< Key, T >* p);


template < class Key, class T, class Callable >
void inorderRecursiveTraversal(node_t< Key, T >* p, Callable callback)
{
	assert(p != nullptr);
	inorderRecursiveTraversal(p->left_, callback);
	callback(p);
	inorderRecursiveTraversal(p->right_, callback);
}

template < class Key, class T, class Compare >
node_t< Key, T >* recursiveSearchNode(node_t< Key, T >* p, Key key, Compare comparator)
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
node_t< Key, T >* iterativeSearchNode(node_t< Key, T >* p, Key key, Compare comparator)
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
node_t< Key, T >* iterativeSearchParent(node_t< Key, T >* p, Key key, Compare comparator)
{
	if (getKey(p) == key)
	{
		return nullptr;
	}
	while (true)
	{
		if (key == getKey(p->left_) || key == getKey(p->right_))
		{
			break;
		}
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
bool insertPair(node_t< Key, T >* p, std::pair< Key, T > pair, Compare comparator)
{
	node_t< Key, T > resP = iterativeSearchParent(p, getKey(pair));
	{
		bool isLeftCorrectParrent = (comparator(getKey(pair), getKey(resP))) && (resP->left_ == nullptr);
		bool isRightCorrectParrent = (!comparator(getKey(pair), getKey(resP))) && (resP->right_ == nullptr);
		assert(isLeftCorrectParrent || isRightCorrectParrent);
	}
	// Проход по пути поиска, пока не убедимся, что ключа в дереве нет
	if (getKey(pair) = getKey(resP->left_) || getKey(pair) = getKey(resP->right_))
	{
		return false;
	}
	// Вставка
	if (comparator(getKey(pair), getKey(resP)))
	{
		resP->left_ = node_t< Key, T >{ nullptr, nullptr, 0, pair };
	}
	else
	{
		resP->right_ = node_t< Key, T >{ nullptr, nullptr, 0, pair };
	}
	// Возвращаемся
	while (resP != nullptr)
	{
		balance(resP);
		resP = iterativeSearchParent(getKey(resP));
	}
}

template < class Key, class T, class Compare >
bool deleteKey(node_t< Key, T >* p, Key key, Compare comparator)
{
	node< Key, T > toDelete = recursiveSearchNode(p, key, comparator);
	if (toDelete == nullptr)
	{
		return false;
	}
	deleteNode(p, toDelete);
	return true;
}

template < class Key, class T >
void deleteNode(node_t< Key, T >* p, node_t< Key, T >* toDelete)
{
	assert(p != nullptr);

}

template < class Key, class T >
void balance(node_t< Key, T >* p)
{
	assert(p != nullptr);
	if (p->left_ == nullptr || p->right_ == nullptr)
	{
		return;
	}
	node_t< Key, T > b;
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
int getHeight(node_t< Key, T >* p)
{
	if (p->left_ == nullptr || p->right_ == nullptr)
	{
		return 1;
	}
	int leftHeight = getHeight(p->left_);
	int rightHeight = getHeight(p->right_);
	return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

// Малое левое вращение
template < class Key, class T >
void doRRrotation(node_t< Key, T >* p)
{
	assert(p != nullptr);
	assert(p->right_ != nullptr);
	node_t* p1 = p->right_;
	p->right_ = p1->left_;
	p1->left_ = p;
}

// Малое правое вращение
template < class Key, class T >
void doLLrotation(node_t< Key, T >* p)
{
	assert(p != nullptr);
	assert(p->left_ != nullptr);
	node_t* p1 = p->left_;
	p->left_ = p1->right_;
	p1->right_ = p;
}

// Большое правое вращение
template < class Key, class T >
void doLRrotation(node_t< Key, T >* p)
{
	assert(p != nullptr);
	assert(p->left_ != nullptr);
	assert(p->left_->right_ != nullptr);
	node_t* p1 = p->left_;
	node_t* p2 = p1->right_;
	p1->right_ = p2->left_;
	p2->left_ = p1;
	p->left_ = p2->right_;
	p2->right_ = p;
}

// Большое левое вращение
template < class Key, class T >
void doRLrotation(node_t< Key, T >* p)
{
	assert(p != nullptr);
	assert(p->right_ != nullptr);
	asster(p->right_->left_ != nullptr);
	node_t* p1 = p->right_;
	node_t* p2 = p1->left_;
	p1->left_ = p2->right_;
	p2->right_ = p1;
	p->right_ = p2->left_;
	p2->left_ = p;
}

template < class Key, class T >
void print(node_t< Key, T >* p, std::ostream& out, int CELL_SIZE)
{
	if (p == nullptr)
	{
		out << "Tree is empty" << '\n';
		return;
	}
	node_t< Key, T >* node = p;
	if (CELL_SIZE <= 0)
	{
		CELL_SIZE = trunc(log10(INT_MAX)) + 1 + 1 + 2;
	}

	int currCellSize = CELL_SIZE * pow(2, (getHeight(p) - 1));
	int leftSpace;
	int rightSpace;
	//int level = 0;
	int currCellsCount = 1;
	int currDequeSize;
	std::deque< node_t< Key, T >* > deque;

	deque.push_back(node);
	while (containsValues(deque))
	{
		currDequeSize = deque.size();
		if (deque[0] != p)
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
			printNode(out, deque[i], currCellSize);
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
Key getKey(node_t< Key, T >* p)
{
	return std::get<0>(p->pair_);
}

#endif