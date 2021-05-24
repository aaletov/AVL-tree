#include "test-functions.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

std::function< int() > getGenerator()
{
	static bool wasInvoked = false;
	static auto generator = []()
	{
		return rand();
	};
	if (!wasInvoked)
	{
		srand(time(0));
		wasInvoked = true;
	}
	return generator;
}

AVL_tree< int, int, std::function< bool(int, int) > > makeRandIntTree(size_t size)
{
	std::function< int() > gen = getGenerator();
	auto intTree = IntTree(std::less< int >());
	int elem;
	for (int i = 0; i < size; i++)
	{
		elem = gen();
		intTree.insertPair({ elem, elem });
	}
	return intTree;\
}

struct test_node_t
{
	IntCompare comparator_;
	bool res_;
	test_node_t(IntCompare comparator) :
		comparator_(comparator),
		res_(true)
	{}
	void operator()(node::node_t< int, int >* p)
	{
		bool res = true;
		if (p == nullptr)
		{
			throw - 1;
		}
		if (p->left_ != nullptr)
		{
			res &= comparator_(getKey(p->left_), getKey(p));
		}
		if (p->right_ != nullptr)
		{
			res &= comparator_(getKey(p), getKey(p->right_));
		}
		res_ &= res;
	}
};

bool testSort(IntTree intTree, IntCompare comparator)
{
	bool res = true;
	auto testNode = [res, comparator](node::node_t< int, int >* p) mutable
	{
		if (p == nullptr)
		{
			throw - 1;
		}
		if (p->left_ != nullptr)
		{
			res &= comparator(getKey(p->left_), getKey(p));
		}
		if (p->right_ != nullptr)
		{
			res &= comparator(getKey(p), getKey(p->right_));
		}
	};
	intTree.inorderRecursiveTraversal(testNode);
	return res;
}

bool testBalance(IntTree intTree)
{
	bool res = true;
	auto testNode = [res](node::node_t< int, int >* p) mutable
	{
		res &= (std::abs(node::getHeight(p->left_) - node::getHeight(p->right_)) <= 2);
	};
	intTree.inorderRecursiveTraversal(testNode);
	return res;
}