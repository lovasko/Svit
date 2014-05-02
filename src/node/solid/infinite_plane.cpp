#include "node/solid/infinite_plane.h"

#include <iostream>

namespace Svit
{
	std::list<Intersection>
	InfinitePlane::intersect (Ray& _ray)
	{
		std::list<Intersection> result;

		float angle = normal % _ray.direction;

		if (angle == 0.0)
			return fail();

		float t = -(normal % (_ray.origin - point))/angle;

		Intersection intersection;
		intersection.t = t;
		intersection.point = _ray(t);
		intersection.node = this;
		result.push_back(intersection);

		return result;
	}

	void
	InfinitePlane::complete_intersection (Intersection *_intersection)
	{
		_intersection->normal = normal;
	}
}

