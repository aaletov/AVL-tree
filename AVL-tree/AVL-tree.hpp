#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

template < typename T >
class AVL_tree
{
public:
	AVL_tree();
	bool search(T& key) const;
	bool insert(T& key);
	bool delete(T& key);

private:

};

#endif