#include "dictionary.hpp"
#include <climits>

const Dictionary::value_type Dictionary::npos = std::pair< std::string, int >("", 0);

bool Dictionary::insert(std::pair< std::string, int > pair)
{
	return tree_.insertPair(pair);
}

bool Dictionary::search(std::string key)
{
	return tree_.recursiveSearchKey(key);
}

int Dictionary::at(std::string key)
{
	return std::get< 1 >(tree_.getPairByKey(key));
}

bool Dictionary::deleteKey(std::string key)
{
	return tree_.deleteKey(key);
}

bool Dictionary::incrKey(std::string key)
{
	if (!tree_.recursiveSearchKey(key))
	{
		return false;
	}
	Dictionary::value_type& pair = tree_.getPairByKey(key);
	std::get< 1 >(pair)++;
	return true;
}

Dictionary::value_type Dictionary::getMaxByValue()
{
	Dictionary::value_type max = Dictionary::npos;
	auto maxFinder = [&max](node::node_t< std::string, int >* p) mutable
	{
		if (std::get< 1 >(p->pair_) > std::get< 1 >(max))
		{
			max = p->pair_;
		}
		return true;
	};
	tree_.inorderRecursiveTraversal(maxFinder);
	return max;
}

Dictionary::value_type Dictionary::getMinByValue()
{
	Dictionary::value_type min{ "", INT_MAX };
	auto minFinder = [&min](node::node_t< std::string, int >* p) mutable
	{
		if (std::get< 1 >(p->pair_) < std::get< 1 >(min))
		{
			min = p->pair_;
		}
		return true;
	};
	tree_.inorderRecursiveTraversal(minFinder);
	if (std::get< 1 >(min) == INT_MAX)
	{
		min = Dictionary::npos;
	}
	return min;
}