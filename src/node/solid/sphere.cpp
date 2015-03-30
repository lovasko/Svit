#include "node/solid/sphere.h"

namespace Svit
{
	Sphere::Sphere (Point3 _center, float _radius)
		: center(_center), radius(_radius)
	{ 
		Point3 min = center - Vector3(radius, radius, radius);
		Point3 max = center + Vector3(radius, radius, radius);

		bounding_box.extend(min);
		bounding_box.extend(max);
	}

	boost::optional<Intersection>
	Sphere::intersect (Ray& _ray, float _best)
	{
		Vector3 ray_origin_vector = _ray.origin - Point3(0,0,0);
		Vector3 sphere_center_vector = center - Point3(0,0,0);

		float A = _ray.direction % _ray.direction;
		float B = 2.0f * (_ray.direction % ray_origin_vector) 
		        - 2.0f * (sphere_center_vector % _ray.direction);
		float C = (ray_origin_vector % ray_origin_vector)
		        - 2.0f * (sphere_center_vector % ray_origin_vector)
						+ (sphere_center_vector % sphere_center_vector)
						- radius * radius;

		float t = 1.0f;

		if (A == 0.0f)
		{
			t = - C / B;
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
		else
		{
			float discriminant = B * B - 4.0f * A * C;

			if (discriminant < 0.0f)
				return boost::optional<Intersection>();

			float t1 = ( - B + sqrt(discriminant)) / (2 * A);
			float t2 = ( - B - sqrt(discriminant)) / (2 * A);

			bool t1_valid = t1 < _best && t1 >= 0.0001f;
			bool t2_valid = t2 < _best && t2 >= 0.0001f;

			if (!t1_valid && !t2_valid) return boost::optional<Intersection>();
			if ( t1_valid &&  t2_valid) t = fmin(t1, t2);
			if (!t1_valid &&  t2_valid) t = t2;
			if ( t1_valid && !t2_valid) t = t1;
	
			Intersection intersection;
			intersection.t = t;
			intersection.point = _ray(t);
			intersection.node = this;

			boost::optional<Intersection> result(intersection);
			return result;
		}
	}

	void
	Sphere::complete_intersection (Intersection *_intersection)
	{
		_intersection->normal = ~(_intersection->point - center);
	}

	void
	Sphere::dump (const char *_name, unsigned int _level)
	{
		std::cout << std::string(' ', _level*2) << _name << " = Sphere" <<
		    std::endl;
		center.dump("center", _level+1);
		std::cout << std::string(' ', (_level+1)*2)  << "radius = " << radius <<
		    std::endl;
	}
}

