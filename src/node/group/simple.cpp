#include "node/group/simple.h"

namespace Svit
{
	void 
	SimpleGroup::add (Node *_node)
	{
		nodes.push_back(_node);
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

