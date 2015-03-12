#include "engine/engine.h"

namespace Svit
{
	boost::optional<Intersection>
	Engine::get_best_intersection (std::list<Intersection>& _intersections)
	{
		if (_intersections.empty())
			return boost::optional<Intersection>();

		std::list<Intersection>::iterator it, best;

		for (best = _intersections.begin(); 
				 best != _intersections.end(); 
				 best++)
		{
			if (best->t > 0.0001f)
				break;
		}

		if (best == _intersections.end())
			return boost::optional<Intersection>();

		for (it = _intersections.begin(); it != _intersections.end(); it++)
		{
			if (it->t <= 0.0f || it->t >= best->t)
				continue;

			best = it;
		}

		return boost::optional<Intersection>(*best);
	}
}

