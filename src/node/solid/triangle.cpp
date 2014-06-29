#include "node/solid/triangle.h"

namespace Svit
{
	Triangle::Triangle (Point3 _p1, Point3 _p2, Point3 _p3)
	  : p1(_p1), p2(_p2), p3(_p3)
	{
		p1.w = 0.0f;
		p2.w = 0.0f;
		p3.w = 0.0f;

		e1 = p2 - p1;
		e2 = p3 - p1;
		normal = ~(~e1 & ~e2);
	}

	boost::optional<Intersection>
	Triangle::intersect (Ray& _ray, float _best)
	{
		Vector3 P = _ray.direction & e2;
		float det = e1 % P;
		if (det == 0.0f) 
			return boost::optional<Intersection>();
		float inv_det = 1.0f / det;

		Vector3 T = _ray.origin - p1;
		float u = (T % P) * inv_det;
		if (u < 0.f || u > 1.f) 
			return boost::optional<Intersection>();

		Vector3 Q = T & e1;
		float v = (_ray.direction % Q) * inv_det;
		if (v < 0.f || u + v  > 1.f) 
			return boost::optional<Intersection>();
																												  
		float t = (e2 % Q) * inv_det;
		if(t > 0.0f && t < _best)
		{ 
			Intersection intersection;
			intersection.t = t;
			intersection.point = _ray(t);
			intersection.node = this;

			boost::optional<Intersection> result(intersection);
			return result;
		}

		return boost::optional<Intersection>();
	}

	void
	Triangle::complete_intersection (Intersection *_intersection)
	{
		_intersection->normal = normal;
	}

	void
	Triangle::dump (const char *_name, unsigned int _level)
	{
		std::cout << std::string(' ', _level*2) << _name << " = Triangle" << 
		    std::endl;

		p1.dump("p1", _level+1);
		p2.dump("p2", _level+1);
		p3.dump("p3", _level+1);
	}
}

