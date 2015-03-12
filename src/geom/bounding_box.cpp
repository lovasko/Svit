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
	intersect_helper (float _origin, float _direction, float _min, float _max,
	    float* _t_near, float* _t_far)
	{
		if (_direction == 0.0f)
		{
			if (_origin < _min || _origin > _max)
				return boost::optional<std::tuple<float, float>>();
		}
		else
		{
			float t1 = (_min - _origin) / _direction;	
			float t2 = (_max - _origin) / _direction;	

			if (t1 > t2)
				std::swap(t1, t2);

			if (t1 > *_t_near)
				*_t_near = t1;

			if (t2 > *_t_far)
				*_t_far = t2;

			if (*_t_near > *_t_far || *_t_far < 0.0f)
				return false;
		}

		return true;
	}

	boost::optional<std::tuple<float, float>>
	BoundingBox::intersect (Ray& _ray)
	{
		float t_near = std::numeric_limits<float>::min();
		float t_far = std::numeric_limits<float>::max();

		if (intersect_helper(_ray.origin.x, _ray.direction.x, min.x, max.x, &t_near, 
		    &t_far) &&
		    intersect_helper(_ray.origin.y, _ray.direction.y, min.y, max.y, &t_near, 
		    &t_far) &&
		    intersect_helper(_ray.origin.z, _ray.direction.z, min.z, max.z, &t_near, 
		    &t_far))
			return boost::optional<std::tuple<float, float>>(std::make_tuple(t_near,
			    t_far));
		else
			return boost::optional<std::tuple<float, float>>();
	}

	bool
	BoundingBox::contains (Point3& _point)
	{
		return (_point.x > min.x && _point.x < max.x &&
			      _point.y > min.y && _point.y < max.y &&
			      _point.z > min.z && _point.z < max.z);
	}
}

