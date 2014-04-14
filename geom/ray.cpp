#include "ray.h"

namespace Svit
{
	Ray::Ray (Vector3d& origin, Vector3d& direction)
	{
		_origin = origin;
		_direction = direction;
	}

	Vector3d Ray::operator() (float time)
	{
		return _origin + _direction * time;
	}
}

