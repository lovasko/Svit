#include "node/solid/disc.h"

namespace Svit
{
	Disc::Disc (Point3 _point, Vector3 _normal, float _radius)
	{
		point = _point;
		normal = _normal;
		radius = _radius;
		radius2 = radius * radius;
	}

	bool
	Disc::intersect (Ray& _ray, Intersection& _isect)
	{
		float angle = normal % _ray.direction;

		if (angle == 0.0)
			return false;

		float t = -(normal % (_ray.origin - point))/angle;
		if (t < _isect.t && t > 0.0f)
		{
			Point3 hit_point = _ray(t);
			Vector3 difference = hit_point - point;

			if (difference % difference > radius2)
				return false;

			_isect.t = t;
			_isect.point = _ray(t);
			_isect.solid = this;
			return true;
		}
		else
			return false;
	}

	void
	Disc::complete_intersection (Intersection& _isect)
	{
		_isect.normal = normal;
	}

	void
	Disc::dump (const char *_name, unsigned int _level)
	{
		std::cout << std::string(' ', _level*2) << _name << " = Disc" << std::endl;
		point.dump("point", _level+1);
		normal.dump("normal", _level+1);
		std::cout << std::string(' ', (_level+1)*2)  << "radius = " << radius <<
		    std::endl;
	}
}

