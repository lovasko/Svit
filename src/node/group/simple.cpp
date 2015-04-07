#include "node/group/simple.h"

namespace Svit
{
	void 
	SimpleGroup::add (Node *_node)
	{
		nodes.push_back(_node);
	}

	bool
	SimpleGroup::intersect (Ray& _ray, Intersection& _isect)
	{
		bool found = false;

		for (auto node : nodes)
			found = node->intersect(_ray, _isect) || found;

		return found;
	}
}

