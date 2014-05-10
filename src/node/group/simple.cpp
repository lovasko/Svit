#include "node/group/simple.h"

namespace Svit
{
	void 
	SimpleGroup::add (Node& _node)
	{
		nodes.push_back(&_node);
	}

	void
	SimpleGroup::set_material (std::unique_ptr<Material> _material)
	{
		// TODO solve this problem:
		// unique_ptr does not allow to share the pointer we do not want to make
		// copy for each group member just imagine a huge model with 300k
		// triangles, sharing the same material with copying is insane. 
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

