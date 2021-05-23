#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <map>
#include <iostream>

template < class Key, class T, class Compare >
class AVL_tree
{
public:
	AVL_tree(Compare comparator);
	~AVL_tree();
	friend std::ostream& operator<<(std::ostream& os, const AVL_tree& tree);
	bool recursiveSearchKey(Key key) const;
	bool iterativeSearchKey(Key key) const;
	bool insertPair(std::pair< Key, T > pair);
	bool deleteKey(Key key);
	template < class Callable >
	void inorderRecursiveTraversal(Callable callback);

private:
	Compare comparator_;
	node_t< Key, T >* root_;
};

template < class Key, class T, class Compare >
AVL_tree< Key, T, Compare >::AVL_tree(Compare comparator) :
	comparator_(comparator)
{}

template < class Key, class T, class Compare >
AVL_tree< Key, T, Compare >::~AVL_tree()
{

}

template < class Key, class T, class Compare >
std::ostream& operator<<(std::ostream& os, const AVL_tree< Key, T, Compare >& tree)
{
	print(root_, std::cout, 7);
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
	return insertPair(this->root_, pair, comparator_);
}

template < class Key, class T, class Compare >
bool AVL_tree< Key, T, Compare >::deleteKey(Key key)
{

}

template < class Key, class T, class Compare >
template < class Callable >
void AVL_tree< Key, T, Compare >::inorderRecursiveTraversal(Callable callback)
{
	inorderRecursiveTraversal(this->root_, callback);
}

#endif