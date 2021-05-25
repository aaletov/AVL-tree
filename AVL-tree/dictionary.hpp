#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <functional>
#include "AVL-tree.hpp"

class Dictionary
{
public:
	using key_type = std::string;
	using mapped_type = int;
	using value_type = std::pair< std::string, int >;
	using tree_type = AVL_tree< std::string, int, std::function< bool(std::string, std::string) > >;
	Dictionary();
	bool insert(std::pair< std::string, int > pair);
	bool search(std::string key);
	bool deleteKey(std::string key);
	bool incrKey(std::string key);
	value_type getMaxByValue();
	value_type getPredecessorByValue(std::string key);
private:
	std::function< bool(std::string, std::string) > dictComparator_;
	tree_type tree_;
};

#endif