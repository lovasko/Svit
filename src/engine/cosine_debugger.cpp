#include <cmath>
#include <numeric>

#include "engine/cosine_debugger.h"

namespace Svit
{
	Vector3
	CosineDebuggerEngine::get_color (Ray& _ray, World& _world)
	{
		boost::optional<Intersection> best = _world.scene->intersect(_ray,
		    std::numeric_limits<float>::max());

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

