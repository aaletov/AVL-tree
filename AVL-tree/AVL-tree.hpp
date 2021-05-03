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
		// Высота правого - высота левого
		int bal_;
		T key_;
		int count_;
	};
	//  Малое левое вращение
	static void doRRrotation(node_t* root);
	// Малое правое вращение
	static void doLLrotation(node_t* root);
	// Большое правое вращение
	static void doLRrotation(node_t* root);
	// Большое левое вращение
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
static void AVL_tree< T, Compare >::doRRrotation(node_t* p)
{
	assert(p != nullptr);
	assert(p->right_ != nullptr);
	node_t* p1 = p->right_;
	p->right_ = p1->left_;
	p1->left_ = p;
	//
	p->bal_ = 0;
}

template < class T, class Compare >
static void AVL_tree< T, Compare >::doLLrotation(node_t* p)
{
	assert(root != nullptr);
	assert(root->left_ != nullptr);
	node_t* p1 = p->left_;
	p->left_ = p1->right_;
	p1->right_ = p;
	//
	p->bal_ = 0;
}

template < class T, class Compare >
static void AVL_tree< T, Compare >::doLRrotation(node_t* p)
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

template < class T, class Compare >
static void AVL_tree< T, Compare >::doRLrotation(node_t* p)
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

template < class T, class Compare >
static void AVL_tree< T, Compare >::print(node_t* root)
{

}

#endif