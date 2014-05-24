#include "engine/ray_casting.h"

#include <numeric>

namespace Svit
{
	Vector3
	RayCastingEngine::get_color (Ray& _ray, World& _world)
	{
		boost::optional<Intersection> best = _world.scene->intersect(_ray,
		    std::numeric_limits<float>::max());

		if (best)
		{
			Intersection i = *best;
			best->node->complete_intersection(&i);

			return i.node->material->get_reflectance(i.point, i.normal,
			    _ray.direction, !_ray.direction);
		}
		else
			return Vector3();
	}
}

