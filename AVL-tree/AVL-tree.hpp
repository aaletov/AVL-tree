#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <algorithm>
#include <iostream>
#include "tree-operations.hpp"

template < class T, class Compare = std::less< T > >
class AVL_tree
{
public:
	AVL_tree();
	~AVL_tree();
	friend std::ostream& operator<<(std::ostream& os, const AVL_tree& tree);
	bool searchKey(T& key) const;
	bool insertKey(T& key);
	bool deleteKey(T& key);
	template < class Callable >
	void inorderTraversal(Callable callback);

private:
	struct node_t
	{
		node_t* left_;
		node_t* right_;
		int bal_;
		T key_;
		int count_;
	};
	static void doRRrotation(node_t* root);
	static void doLLrotation(node_t* root);
	static void doLRrotation(node_t* root);
	static void doRLrotation(node_t* root);
	static void print(node_t* root);
	node_t* root_;

};

template < class T, class Compare >
AVL_tree< T, Compare >::AVL_tree()
{

}

template < class T, class Compare >
AVL_tree< T, Compare >::~AVL_tree()
{

}

template < class T, class Compare >
std::ostream& operator<<(std::ostream& os, const AVL_tree< T, Compare >& tree)
{

}

template < class T, class Compare >
bool AVL_tree< T, Compare >::searchKey(T& key) const
{

}

template < class T, class Compare >
bool AVL_tree< T, Compare >::insertKey(T& key)
{

}

template < class T, class Compare >
bool AVL_tree< T, Compare >::deleteKey(T& key)
{

}

template < class T, class Compare >
template < class Callable >
void AVL_tree< T, Compare >::inorderTraversal(Callable callback)
{

}

template < class T, class Compare >
static void AVL_tree< T, Compare >::doRRrotation(node_t* root)
{

}

template < class T, class Compare >
static void AVL_tree< T, Compare >::doLLrotation(node_t* root)
{

}

template < class T, class Compare >
static void AVL_tree< T, Compare >::doLRrotation(node_t* root)
{

}

template < class T, class Compare >
static void AVL_tree< T, Compare >::doRLrotation(node_t* root)
{

}

template < class T, class Compare >
static void AVL_tree< T, Compare >::print(node_t* root)
{

}

#endif