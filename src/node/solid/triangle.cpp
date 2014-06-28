#include "node/solid/triangle.h"

namespace Svit
{
	Triangle::Triangle (Point3 _p1, Point3 _p2, Point3 _p3)
	  : p1(_p1), p2(_p2), p3(_p3)
	{
		Vector3 e1 = p2 - p1;
		Vector3 e2 = p3 - p1;
		normal = ~(~e1 & ~e2);
	}

	boost::optional<Intersection>
	intersect (Ray& _ray, float _best)
	{
		float d = _ray.direction % normal;
		if (d == 0.0f)
			return boost::optional<Intersection>();

		float a = (_ray.origin - p1) % normal;
		float t = -a/d;
		if (t < 0.0001f || t > _best)
			return boost::optional<Intersection>();

		Point3 surface_point = _ray(t);

		Vector3 e1 = p2 - p1;
		Vector3 e2 = p3 - p1;
		Vector3 u  = e1 & e2;
		float area = sqrtf(u % u);

		Vector3 e11 = surface_point - p1;
		Vector3 e12 = p3 - p1;
		Vector3 u1  = e11 & e12;
		float area1 = sqrtf(u1 % u1);

		Vector3 e21 = p2 - surface_point;
		Vector3 e22 = p3 - surface_point;
		Vector3 u2  = e21 & e22;
		float area2 = sqrtf(u2 % u2);

		Vector3 e31 = p2 - p1;
		Vector3 e32 = surface_point - p1;
		Vector3 u3 =  e31 % e32;
		float area3 = sqrtf(u3 % u3);

		float lambda1 = area1 / area;
		float lambda2 = area2 / area;
		float lambda3 = area3 / area;

		float dotuu1 = u % u1;
		float dotuu2 = u % u2;
		float dotuu3 = u % u3;

		if (dotuu1 < 0.0f || dotuu2 < 0.0f || dotuu3 < 0.0f) 
			return boost::optional<Intersection>();

		// Point3 barycentric_point(lambda1, lambda2, lambda3);

		Intersection intersection;
		intersection.t = t;
		intersection.point = surface_point;
		intersection.node = this;

		boost::optional<Intersection> result(intersection);
		return result;
	}

	void
	Triangle::complete_intersection (Intersection *_intersection)
	{
		_intersection->normal = normal;
	}

	void
	Triangle::dump (const char *_name, unsigned int _level = 0);
	{
		std::cout << std::string(' ', _level*2) << _name << " = Triangle" << 
		    std::endl;

		p1.dump("p1", _level+1);
		p1.dump("p2", _level+1);
		p1.dump("p3", _level+1);
	}
}

