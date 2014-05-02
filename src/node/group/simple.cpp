#include "node/group/simple.h"

namespace Svit
{
	void 
	SimpleGroup::add (Node& _node)
	{
		nodes.push_back(&_node);
	}
	
	std::list<Intersection>
	SimpleGroup::intersect (Ray& _ray)
	{
		std::list<Intersection> result;

		std::list<Node*>::iterator it;
		for (it = nodes.begin(); it != nodes.end(); it++)
		{
			Node *node = *it;
			std::list<Intersection> node_result = node->intersect(_ray);
			result.splice(result.end(), node_result);
		}

		return result;
	}
}

