#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <map>
#include <iostream>
#include "node.hpp"
#include "node-operations.hpp"

template < class Key, class T, class Compare >
class AVL_tree
{
public:
	AVL_tree(Compare comparator);
	~AVL_tree();
	bool recursiveSearchKey(Key key) const;
	bool iterativeSearchKey(Key key) const;
	bool insertPair(std::pair< Key, T > pair);
	bool deleteKey(Key key);
	template < class Callable >
	void inorderRecursiveTraversal(Callable callback);
	node::node_t< Key, T >* getRoot();

private:
	Compare comparator_;
	node::node_t< Key, T >* root_;
};

template < class Key, class T, class Compare >
AVL_tree< Key, T, Compare >::AVL_tree(Compare comparator) :
	comparator_(comparator),
	root_(nullptr)
{}

template < class Key, class T, class Compare >
AVL_tree< Key, T, Compare >::~AVL_tree()
{

}

template < class Key, class T, class Compare >
bool AVL_tree< Key, T, Compare >::recursiveSearchKey(Key key) const
{
	return recursiveSearchNode(this->root_, key, comparator_) != nullptr;
}

template < class Key, class T, class Compare >
bool AVL_tree< Key, T, Compare >::iterativeSearchKey(Key key) const
{
	return iterativeSearchNode(this->root_, key, comparator_) != nullptr;
}

template < class Key, class T, class Compare >
bool AVL_tree< Key, T, Compare >::insertPair(std::pair< Key, T > pair)
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

template < class Key, class T, class Compare >
bool AVL_tree< Key, T, Compare >::deleteKey(Key key)
{
	return node::deleteKey(root_, key, comparator_);
}

template < class Key, class T, class Compare >
template < class Callable >
void AVL_tree< Key, T, Compare >::inorderRecursiveTraversal(Callable callback)
{
	inorderRecursiveTraversal(this->root_, callback);
}

template < class Key, class T, class Compare >
node::node_t< Key, T >* AVL_tree< Key, T, Compare >::getRoot()
{
	return root_;
}

#endif