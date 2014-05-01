#include "node/solid/infinite_plane.h"

#include <iostream>

namespace Svit
{
	std::list<Intersection>
	InfinitePlane::intersect (Ray& _ray)
	{
		result.clear();
		float angle = normal % _ray.direction;

		if (angle == 0.0)
			return fail();

		float t = -(normal % (_ray.origin - point))/angle;

		add_intersection(t, _ray(t), this);
		return result;
	}

	void
	InfinitePlane::complete_intersection (Intersection *_intersection)
	{
		_intersection->normal = normal;
	}
}

