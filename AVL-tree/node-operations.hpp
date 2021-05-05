#ifndef NODE_OPERATIONS_HPP
#define NODE_OPERATIONS_HPP

#include "node.hpp"

template < class Key, class T, class Callable >
void inorderRecursiveTraversal(node_t< Key, T >* p, Callable callback);
template < class Key, class T >
node_t< Key, T >* recursiveSearchNode(node_t< Key, T >* p, Key key);
template < class Key, class T, class Compare >
node_t< Key, T >* iterativeSearchNode(node_t< Key, T >* p, Key key);
template < class Key, class T, class Compare >
node_t< Key, T >* iterativeSearchParent(node_t< Key, T >* p, Key key);
template < class Key, class T >
bool insertPair(node_t< Key, T > p, std::pair< Key, T > pair);
template < class Key, class T >
void updateBalance(node_t< Key, T >* p);
template < class Key, class T >
int balance(node_t< Key, T >* p);
template < class Key, class T >
void getHeight(node_t< Key, T >* p);
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
	inorderRecursiveTraversal(node->left_, callback);
	callback(p);
	inorderRecursiveTraversal(node->right_, callback);
}

template < class Key, class T >
node_t< Key, T >* recursiveSearchNode(node_t< Key, T >* p, Key key)
{
	if (p == nullptr || key == getKey(p))
	{
		return p;
	}
	if (Compare(key, getKey(p)))
	{
		return AVL_tree< Key, T, Compare >::recursiveSearch(p->left_, key);
	}
	else
	{
		return AVL_tree< Key, T, Compare >::recursiveSearch(p->right_, key);
	}
}

template < class Key, class T, class Compare >
node_t< Key, T >* iterativeSearchNode(node_t< Key, T >* p, Key key)
{
	while (p != nullptr && key != getKey(p))
	{
		if (Compare(key, getKey(p)))
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
node_t< Key, T >* iterativeSearchParent(node_t< Key, T >* p, Key key)
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
		if (Compare(key, getKey(p)) && p->left_ == nullptr)
		{
			break;
		}
		if (!Compare(key, getKey(p)) && p->right_ == nullptr)
		{
			break;
		}
		if (Compare(key, getKey(p)))
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
bool insertPair(node_t< Key, T > p, std::pair< Key, T > pair)
{
	node_t< Key, T > resP = iterativeSearchParent(p, getKey(pair));
	{
		bool isLeftCorrectParrent = (Compare(getKey(pair), getKey(resP))) && (resP->left_ == nullptr);
		bool isRightCorrectParrent = (!Compare(getKey(pair), getKey(resP))) && (resP->right_ == nullptr);
		assert(isLeftCorrectParrent || isRightCorrectParrent);
	}
	// Проход по пути поиска, пока не убедимся, что ключа в дереве нет
	if (getKey(pair) = getKey(resP->left_) || getKey(pair) = getKey(resP->right_))
	{
		return false;
	}
	// Вставка
	if (Compare(getKey(pair), getKey(resP)))
	{
		resP->left_ = node_t< Key, T >{ nullptr, nullptr, 0, pair };
		resP->bal_--;
	}
	else
	{
		resP->right_ = node_t< Key, T >{ nullptr, nullptr, 0, pair };
		resP->bal_++;
	}
	// Возвращаемся
	resP = iterativeSearchParent(getKey(resP));
	updateBalance(resp);
	while (resP != nullptr)
	{
		resP = iterativeSearchParent(getKey(resP));
		updateBalance(p);
		balance(resp);
	}
}

template < class Key, class T >
void updateBalance(node_t< Key, T >* p)
{
	p->bal_ = getHeight(p->right_) - getHeight(p->left_);
}

template < class Key, class T >
void balance(node_t< Key, T >* p)
{

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
	//
	p->bal_ = 0;
}

// Малое правое вращение
template < class Key, class T >
void doLLrotation(node_t< Key, T >* p)
{
	assert(root != nullptr);
	assert(root->left_ != nullptr);
	node_t* p1 = p->left_;
	p->left_ = p1->right_;
	p1->right_ = p;
	//
	p->bal_ = 0;
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
	//
	p->bal = (p2->bal == -1) ? 1 : 0;
	p1->bal = (p2->bal == 1) ? -1 : 0;
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
	//
	p->bal_ = (p2->bal_ == 1) ? -1 : 0;
	p1->bal_ = (p2->bal == -1) ? 1 : 0;
}

template < class Key, class T >
void print(node_t< Key, T >* p)
{

}

template < class Key, class T >
Key getKey(node_t< Key, T >* p)
{
	return std::get<0>(p->pair_);
}

#endif