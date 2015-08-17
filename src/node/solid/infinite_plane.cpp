#include <iostream>
#include <string>

#include "node/solid/infinite_plane.h"

namespace Svit
{
	InfinitePlane::InfinitePlane (Point3 _point, Vector3 _normal)
	 : point(_point), normal(_normal)
	{
	}

	bool
	InfinitePlane::intersect (Ray& _ray, Intersection& _isect) const
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
	InfinitePlane::complete_intersection (Intersection& _isect) const
	{
		_isect.normal = normal;
	}

	void
	InfinitePlane::dump (std::string _name, unsigned int _level) const
	{
		std::cout << std::string(_level*2, ' ')
		          << _name
		          << " = InfinitePlane"
		          << std::endl;

		point.dump("point", _level+1);
		normal.dump("normal", _level+1);
	}
}

