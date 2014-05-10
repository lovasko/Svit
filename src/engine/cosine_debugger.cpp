#include "engine/cosine_debugger.h"

#include <cmath>
#include <iostream>

namespace Svit
{
	Vector3
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

			return Vector3(color_value, color_value, color_value);
		}
		else
			return Vector3();
	}
}

