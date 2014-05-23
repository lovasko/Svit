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

	std::list<Intersection>
	Disc::intersect (Ray& _ray)
	{
		std::list<Intersection> result;

		float angle = normal % _ray.direction;

		if (angle == 0.0)
			return fail();

		float t = -(normal % (_ray.origin - point))/angle;

		Point3 hit_point = _ray(t);
		Vector3 difference = hit_point - point;

		if (difference % difference > radius2)
			return fail();	

		Intersection intersection;
		intersection.t = t;
		intersection.point = _ray(t);
		intersection.node = this;
		result.push_back(intersection);

		return result;
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

