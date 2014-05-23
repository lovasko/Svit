#include "node/solid/infinite_plane.h"

#include <iostream>
#include <string>

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

	void
	InfinitePlane::dump (const char *_name, unsigned int _level)
	{
		std::cout << std::string(' ', _level*2) << _name << " = Infinite Plane" <<
		    std::endl;
		point.dump("point", _level+1);
		normal.dump("normal", _level+1);
	}
}

