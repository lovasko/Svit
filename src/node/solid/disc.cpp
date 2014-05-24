#include "node/solid/disc.h"

namespace Svit
{
	Disc::Disc (Point3 _point, Vector3 _normal, float _radius)
	{
		point = _point;
		normal = _normal;
		radius = _radius;
		radius = radius * radius;
	}

	boost::optional<Intersection>
	Disc::intersect (Ray& _ray, float _best)
	{
		float angle = normal % _ray.direction;

		if (angle == 0.0)
			return boost::optional<Intersection>();

		float t = -(normal % (_ray.origin - point))/angle;
		if (t < _best && t > 0.0f)
		{
			Point3 hit_point = _ray(t);
			Vector3 difference = hit_point - point;

			if (difference % difference > radius2)
				return boost::optional<Intersection>();	

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
	Disc::complete_intersection (Intersection *_intersection)
	{
		_intersection->normal = normal;
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

