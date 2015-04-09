#include "node/solid/infinite_plane.h"

#include <iostream>
#include <string>

namespace Svit
{
	bool
	InfinitePlane::intersect (Ray& _ray, Intersection& _isect)
	{
		float angle = normal % _ray.direction;

		if (angle == 0.0)
			return false;

		float t = -(normal % (_ray.origin - point))/angle;
		if (t < _isect.t && t > 0.0f)
		{
			_isect.t = t;
			_isect.point = _ray(t);
			_isect.solid = this;
			return true;
		}
		else
			return false;
	}

	void
	InfinitePlane::complete_intersection (Intersection& _isect)
	{
		_isect.normal = normal;
	}

	void
	InfinitePlane::dump (const char *_name, unsigned int _level)
	{
		std::cout << std::string(' ', _level*2)
		          << _name
		          << " = InfinitePlane"
		          << std::endl;

		point.dump("point", _level+1);
		normal.dump("normal", _level+1);
	}
}

