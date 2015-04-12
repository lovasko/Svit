#include <iostream>

#include "node/group/simple.h"

namespace Svit
{
	void 
	SimpleGroup::add (Node *_node)
	{
		nodes.push_back(_node);
	}

	bool
	SimpleGroup::intersect (Ray& _ray, Intersection& _isect) const
	{
		bool found = false;

		for (auto node : nodes)
			found = node->intersect(_ray, _isect) || found;

		return found;
	}

	void
	SimpleGroup::dump (std::string _name, unsigned int _level) const
	{
		std::cout << std::string(_level*2, ' ')
		          << _name
		          << " = Group::Simple "
		          << "("
		          << nodes.size()
		          << ")"
		          << std::endl;

		for (auto node : nodes)
			node->dump("_", _level+1);
	}

	void
	SimpleGroup::finish ()
	{
	}
}

