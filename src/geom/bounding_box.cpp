#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>

#include "geom/bounding_box.h"

namespace Svit
{
	void
	BoundingBox::extend (Point3& _point)
	{
		switch (size_type)
		{
			case EMPTY:
				min = _point;
				max = _point;
				size_type = BOUNDED;
			break;

			case BOUNDED:
			{
				float min_x = fmin(min.x, _point.x);
				float min_y = fmin(min.y, _point.y);
				float min_z = fmin(min.z, _point.z);
				min = Point3(min_x, min_y, min_z);

				float max_x = fmax(max.x, _point.x);
				float max_y = fmax(max.y, _point.y);
				float max_z = fmax(max.z, _point.z);
				max = Point3(max_x, max_y, max_z);
			}
			break;

			case FULL:
			default:
			break;
		}
	}

	void
	BoundingBox::extend (BoundingBox& _bounding_box)
	{
		switch (size_type)
		{
			case EMPTY:
				switch (_bounding_box.size_type)
				{
					case FULL:
						size_type = FULL;
					break;

					case BOUNDED:
						min = _bounding_box.min;
						max = _bounding_box.max;
						size_type = BOUNDED;
					break;

					case EMPTY:
					default:
					break;
				}

			case BOUNDED:
				switch (_bounding_box.size_type)
				{
					case FULL:
						size_type = FULL;
					break;

					case BOUNDED:
						extend(_bounding_box.min);
						extend(_bounding_box.max);
					break;

					case EMPTY:
					default:
					break;
				}

			case FULL:
			default:
			break;
		}
	}

	bool
	BoundingBox::intersect (Ray& _ray, float* _t_near, float* _t_far)
	{
		float t0 = std::numeric_limits<float>::min();
		float t1 = std::numeric_limits<float>::max();

		for (int i = 0; i < 3; ++i)
		{
			float inv_ray_dir = 1.0f / _ray.direction[i];
			float t_near = (min[i] - _ray.origin[i]) * inv_ray_dir;
			float t_far  = (max[i] - _ray.origin[i]) * inv_ray_dir;

			if (tNear > tFar)
				std::swap(tNear, tFar);

			t0 = tNear > t0 ? tNear : t0;
			t1 = tFar  < t1 ? tFar  : t1;

			if (t0 > t1)
				 return false;
		}

		*_t_near = t0;
		*_t_far = t1;
		return true;
	}

	bool
	BoundingBox::contains (Point3& _point)
	{
		return (_point.x > min.x && _point.x < max.x &&
			      _point.y > min.y && _point.y < max.y &&
			      _point.z > min.z && _point.z < max.z);
	}

	Point3
	BoundingBox::centroid ()
	{
		return (min + max) / 2.0f;
	}

	void
	BoundingBox::dump (std::string _name, unsigned int _level)
	{
		std::cout << std::string(' ', _level*2)
		          << _name
		          << " = BoundingBox"
		          << std::endl;

		min.dump("min", _level+1);
		max.dump("max", _level+1);
	}
}

