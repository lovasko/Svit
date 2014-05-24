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
	
	boost::optional<Intersection>
	SimpleGroup::intersect (Ray& _ray, float _best)
	{
		float best = _best;
		boost::optional<Intersection> result;

		for (auto node : nodes)
		{
			boost::optional<Intersection> i = node->intersect(_ray, best);
			if (i)
			{
				best = i->t;
				result = i;
			}
		}

		return result;
	}
}

