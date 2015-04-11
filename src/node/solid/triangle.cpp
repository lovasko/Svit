#include "node/solid/triangle.h"

namespace Svit
{
	Triangle::Triangle (Point3 _p1, Point3 _p2, Point3 _p3)
	 : p1(_p1)
	{
		p1.w = 0.0f;

		e1 = _p2 - p1;
		e2 = _p3 - p1;

		bounding_box.extend(_p1);
		bounding_box.extend(_p2);
		bounding_box.extend(_p3);
	}

	bool
	Triangle::intersect (Ray& _ray, Intersection& _isect) const
	{
		Vector3 P = _ray.direction & e2;
		float det = e1 % P;
		if (det == 0.0f) 
			return false;
		float inv_det = 1.0f / det;

		Vector3 T = _ray.origin - p1;
		float u = (T % P) * inv_det;
		if (u < 0.f || u > 1.f) 
			return false;

		Vector3 Q = T & e1;
		float v = (_ray.direction % Q) * inv_det;
		if (v < 0.f || u + v  > 1.f) 
			return false;

		float t = (e2 % Q) * inv_det;
		if(t > 0.0f && t < _isect.t)
		{ 
			_isect.t = t;
			_isect.solid = this;
			_isect.point = _ray(t);
			return true;
		}

		return false;
	}

	void
	Triangle::complete_intersection (Intersection& _isect) const
	{
		_isect.normal = ~(~e1 & ~e2);
	}

	void
	Triangle::dump (const char *_name, unsigned int _level)
	{
		std::cout << std::string(' ', _level*2)
		          << _name
		          << " = Triangle"
		          << std::endl;

		p1.dump("p1", _level+1);
		(p1 + e1).dump("p2", _level+1);
		(p1 + e2).dump("p3", _level+1);
	}
}

