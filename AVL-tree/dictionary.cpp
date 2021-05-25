#include "dictionary.hpp"

Dictionary::Dictionary()
{
	dictComparator_ = [](std::string lword, std::string rword)
	{
		return std::lexicographical_compare(lword.begin(), lword.end(), rword.begin(), rword.end());
	};
	tree_ = tree_type(dictComparator_);
}

bool Dictionary::insert(std::pair< std::string, int > pair)
{
	return tree_.insertPair(pair);
}

bool Dictionary::search(std::string key)
{
	return tree_.recursiveSearchKey(key);
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
	Dictionary::value_type max{"", 0};
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

Dictionary::value_type Dictionary::getPredecessorByValue(std::string key)
{
	Dictionary::value_type keyPair = tree_.getPairByKey(key);
	Dictionary::value_type predecessor{ "", 0 };
	auto predecessorFinder = [keyPair, &predecessor](node::node_t< std::string, int >* p) mutable
	{
		if (std::get< 1 >(p->pair_) < std::get< 1 >(keyPair) && std::get< 1 >(p->pair_) > std::get< 1 >(predecessor))
		{
			predecessor = p->pair_;
		}
		return true;
	};
	tree_.inorderRecursiveTraversal(predecessorFinder);
	return predecessor;
}