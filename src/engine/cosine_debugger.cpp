#include "engine/cosine_debugger.h"
#include "geom/operations.h"

#include <cmath>
#include <iostream>

namespace Svit
{
	RGB
	CosineDebuggerEngine::get_color (Ray& _ray, World& _world)
	{
		std::list<Intersection> intersections = _world.scene->intersect(_ray);
		boost::optional<Intersection> best = get_best_intersection(intersections);

		if (best)
		{
			Intersection i = *best;
			best->node->complete_intersection(&i);
			float angle = (~_ray.direction) % (~(i.normal));
			float color_value = fabs(angle); 

			return RGB(color_value);
		}
		else
			return RGB(0.0);
	}
}

