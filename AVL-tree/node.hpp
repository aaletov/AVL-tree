#ifndef NODE_HPP
#define NODE_HPP

#include <algorithm>

namespace node
{
	template < class Key, class T >
	struct node_t
	{
		node_t* left_;
		node_t* right_;
		// Высота правого - высота левого
		std::pair< Key, T > pair_;
	};
}

#endif