#include "engine/ray_casting.h"

namespace Svit
{
	Vector3
	RayCastingEngine::get_color (Ray& _ray, World& _world)
	{
		std::list<Intersection> intersections = _world.scene->intersect(_ray);
		boost::optional<Intersection> best = get_best_intersection(intersections);

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

