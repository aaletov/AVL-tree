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
	void inorderRecursiveTraversal(Callable callback);

private:
	struct node_t
	{
		node_t* left_;
		node_t* right_;
		// ������ ������� - ������ ������
		int bal_;
		T key_;
	};
	template < class Callable >
	static void inorderRecursiveTraversal(node_t* p, Callable callback);
	static node_t* recursiveSearchNode(node_t* p, T& key);
	//  ����� ����� ��������
	static void doRRrotation(node_t* p);
	// ����� ������ ��������
	static void doLLrotation(node_t* p);
	// ������� ������ ��������
	static void doLRrotation(node_t* p);
	// ������� ����� ��������
	static void doRLrotation(node_t* p);
	static void print(node_t* p);
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
void AVL_tree< T, Compare >::inorderRecursiveTraversal(Callable callback)
{
	AVL_tree< T, Compare >::inorderRecursiveTraversal(this->root_, callback);
}

template < class T, class Compare >
static AVL_tree< T, Compare >::node_t* AVL_tree< T, Compare >::recursiveSearchNode(AVL_tree< T, Compare >::node_t* p, T& key)
{
	if (p == nullptr || key == p->key_)
	{
		return p;
	}
	if (Compare(key, p->key_))
	{
		return AVL_tree< T, Compare >::recursiveSearch(p->left_, key);
	}
	else
	{
		return AVL_tree< T, Compare >::recursiveSearch(p->right_, key);
	}
}

template < class T, class Compare >
template < class Callable >
static void AVL_tree< T, Compare >::inorderRecursiveTraversal(node_t* p, Callable callback)
{
	assert(p != nullptr);
	AVL_tree< T, Compare >::inorderRecursiveTraversal(node->left_, callback);
	callback(p);
	AVL_tree< T, Compare >::inorderRecursiveTraversal(node->right_, callback);
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