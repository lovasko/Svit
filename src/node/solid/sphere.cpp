#include "node/solid/sphere.h"

namespace Svit
{
	std::list<Intersection>
	Sphere::intersect (Ray& _ray)
	{
		result.clear();

		Vector3 ray_origin_vector = _ray.origin - Point3(0,0,0);
		Vector3 sphere_center_vector = center - Point3(0,0,0);

		float A = _ray.direction % _ray.direction;
		float B = 2.0 * (_ray.direction % ray_origin_vector) 
		        - 2.0 * (sphere_center_vector % _ray.direction);
		float C = (ray_origin_vector % ray_origin_vector)
		        - 2.0 * (sphere_center_vector % ray_origin_vector)
						+ (sphere_center_vector % sphere_center_vector)
						- radius * radius;

		float t = 1.0;

		if (A == 0.0)
		{
			t = - C / B;
			add_intersection(t, _ray(t), this);
		}
		else
		{
			float discriminant = B * B - 4.0 * A * C;

			if (discriminant < 0.0)
			{
				result.clear();
				return result;
			}

			double t1 = ( - B + sqrt(discriminant)) / (2 * A);
			double t2 = ( - B - sqrt(discriminant)) / (2 * A);
			add_intersection(t1, _ray(t1), this);
			add_intersection(t2, _ray(t2), this);
		}

		return result;
	}

	void
	Sphere::complete_intersection (Intersection *_intersection)
	{
		_intersection->normal = ~(_intersection->point - center);
	}
}

