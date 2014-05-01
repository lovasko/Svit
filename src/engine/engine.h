#ifndef SVIT_ENGINE
#define SVIT_ENGINE

#include "geom/ray.h"
#include "world/world.h"
#include "color/rgb.h"
#include "node/intersection.h"

#include <list>
#include <boost/optional.hpp>

namespace Svit
{
	class Engine
	{
		public:
			virtual RGB
			get_color (Ray& _ray, World& _world) = 0;

			boost::optional<Intersection>
			get_best_intersection (std::list<Intersection>& _intersections)
			{
				if (_intersections.empty())
					return boost::optional<Intersection>();

				std::list<Intersection>::iterator it, best;

				for (best = _intersections.begin(); best != _intersections.end(); best++)
				{
					if (best->t > 0.0)
						break;
				}

				if (best == _intersections.end())
					return boost::optional<Intersection>();

				for (it = _intersections.begin(); it != _intersections.end(); it++)
				{
					if (it->t <= 0.0 || it->t >= best->t)
						continue;

					best = it;
				}

				//if (true || found)
					return boost::optional<Intersection>(*best);
				//else
				//	return boost::optional<Intersection>();
			}
	};
}

#endif

