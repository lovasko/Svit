#ifndef SVIT_ENGINE_ENGINE_H
#define SVIT_ENGINE_ENGINE_H

#include <list>
#include <boost/optional.hpp>

#include "geom/ray.h"
#include "node/node.h"
#include "node/solid/solid.h"
#include "world/world.h"

namespace Svit
{
	class Engine
	{
		public:
			virtual Vector3 
			get_color (Ray& _ray, World& _world) = 0;

			boost::optional<Intersection>
			get_best_intersection (std::list<Intersection>& _intersections);
	};
}

#endif

