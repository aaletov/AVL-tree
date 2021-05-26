#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <map>
#include <utility>
#include <iostream>
#include "node.hpp"
#include "node-operations.hpp"

template < class Key, class T, bool (*comparator)(Key, Key) >
class AVL_tree
{
public:
	using comp_type = bool(*)(Key, Key);
	AVL_tree();
	// copy constructor
	AVL_tree(const AVL_tree& tree);
	// move constructor
	AVL_tree(AVL_tree&& tree);
	// copy assigment
	AVL_tree& operator=(const AVL_tree& tree);
	// move assigment
	AVL_tree& operator=(AVL_tree&& tree);
	~AVL_tree();
	bool recursiveSearchKey(Key key) const;
	bool iterativeSearchKey(Key key) const;
	bool insertPair(std::pair< Key, T > pair);
	bool deleteKey(Key key);
	void inorderRecursiveTraversal(std::function< bool(node::node_t< Key, T >*) > callback) const;
	std::pair< Key, T >& getPairByKey(Key key);
	std::pair< Key, T >& getPairByVal(T val);
	node::node_t< Key, T >* getRoot();
	auto getComparator() -> bool(*)(Key, Key)
	{
		return this->comparator_;
	}

private:
	friend void swap(AVL_tree& lhs, AVL_tree& rhs)
	{
		std::swap(lhs.root_, rhs.root_);
	}
	comp_type comparator_;
	node::node_t< Key, T >* root_;
};

template < class Key, class T, bool (*comparator)(Key, Key) >
AVL_tree< Key, T, comparator >::AVL_tree() :
	comparator_(comparator),
	root_(nullptr)
{}

template < class Key, class T, bool (*comparator)(Key, Key)  >
AVL_tree< Key, T, comparator >::AVL_tree(const AVL_tree< Key, T, comparator >& tree)
{
	auto inserter = [this](node::node_t< Key, T >* p) mutable
	{
		this->insertPair(p->pair_);
		return true;
	};
	tree.inorderRecursiveTraversal(inserter);
}

template < class Key, class T, bool (*comparator)(Key, Key)  >
AVL_tree< Key, T, comparator >::AVL_tree(AVL_tree< Key, T, comparator >&& tree) :
	AVL_tree< Key, T, comparator >()
{
	swap(*this, tree);
}

template < class Key, class T, bool (*comparator)(Key, Key)  >
AVL_tree< Key, T, comparator >& AVL_tree< Key, T, comparator >::operator=(const AVL_tree< Key, T, comparator >& tree)
{
	AVL_tree< Key, T, comparator > temp(tree);
	swap(*this, temp);
	return *this;
}

template < class Key, class T, bool (*comparator)(Key, Key) >
AVL_tree< Key, T, comparator >& AVL_tree< Key, T, comparator >::operator=(AVL_tree< Key, T, comparator >&& tree)
{
	swap(tree, *this);
	return *this;
}

template < class Key, class T, bool (*comparator)(Key, Key) >
AVL_tree< Key, T, comparator >::~AVL_tree()
{
	std::function< bool(node::node_t< Key, T >*) > deleter = [](node::node_t< Key, T >* p) mutable
	{
		delete p;
		return true;
	};
	node::levelOrderWalk(root_, deleter);
}

template < class Key, class T, bool (*comparator)(Key, Key) >
bool AVL_tree< Key, T, comparator >::recursiveSearchKey(Key key) const
{
	return recursiveSearchNode(this->root_, key, comparator_) != nullptr;
}

template < class Key, class T, bool (*comparator)(Key, Key) >
bool AVL_tree< Key, T, comparator >::iterativeSearchKey(Key key) const
{
	return iterativeSearchNode(this->root_, key, comparator_) != nullptr;
}

template < class Key, class T, bool (*comparator)(Key, Key) >
bool AVL_tree< Key, T, comparator >::insertPair(std::pair< Key, T > pair)
{
	if (root_ == nullptr)
	{
		root_ = new node::node_t< Key, T >{ nullptr, nullptr, pair };
		return true;
	}
	else
	{
		return node::insertPair(root_, root_, pair, comparator_);
	}
}

template < class Key, class T, bool (*comparator)(Key, Key) >
bool AVL_tree< Key, T, comparator >::deleteKey(Key key)
{
	return node::deleteKey(root_, key, comparator_);
}

template < class Key, class T, bool (*comparator)(Key, Key) >
void AVL_tree< Key, T, comparator >::inorderRecursiveTraversal(std::function< bool(node::node_t< Key, T >*) > callback) const
{
	node::inorderRecursiveTraversal(this->root_, callback);
}

template < class Key, class T, bool (*comparator)(Key, Key) >
std::pair< Key, T >& AVL_tree< Key, T, comparator >::getPairByKey(Key key)
{
	return node::iterativeSearchNode(root_, key, comparator_)->pair_;
}

template < class Key, class T, bool (*comparator)(Key, Key) >
std::pair< Key, T >& AVL_tree< Key, T, comparator >::getPairByVal(T val)
{
	node::node_t< Key, T >* toFind;
	auto searcher = [toFind, val](node::node_t< Key, T >* p) mutable
	{
		if (std::get< 1 >(p->pair_) == val)
		{
			toFind = p;
			return false;
		}
		return true;
	};
	return toFind->pair_;
}

template < class Key, class T, bool (*comparator)(Key, Key) >
node::node_t< Key, T >* AVL_tree< Key, T, comparator >::getRoot()
{
	return root_;
}

#endif