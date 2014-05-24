#include "node/solid/infinite_plane.h"

#include <iostream>
#include <string>

namespace Svit
{
	boost::optional<Intersection>
	InfinitePlane::intersect (Ray& _ray, float _best)
	{
		std::list<Intersection> result;

		float angle = normal % _ray.direction;

		if (angle == 0.0)
			return boost::optional<Intersection>();

		float t = -(normal % (_ray.origin - point))/angle;
		if (t < _best && t > 0.0f)
		{
			Intersection intersection;
			intersection.t = t;
			intersection.point = _ray(t);
			intersection.node = this;

			boost::optional<Intersection> result(intersection);
			return result;
		}
		else
			return boost::optional<Intersection>();
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

