#include <cmath>

#include "camera/perspective.h"

namespace Svit
{
	PerspectiveCamera::PerspectiveCamera (Point3 _position, Vector3 _forward, 
	    Vector3 _up, float _aspect_ratio, float _horizontal_angle)
		: horizontal_angle(_horizontal_angle),
			aspect_ratio(_aspect_ratio),
			position(_position),
			up(~_up), 
			forward(~_forward)
	{
		recompute();
	}

	void 
	PerspectiveCamera::recompute ()
	{
		Vector3 left = ~(forward & up);
		float half_width = 1.0f / tan(horizontal_angle / 2.0);
		float half_height = half_width / aspect_ratio;

		grid_width = left * -half_width;
		grid_height = up * -half_height;
	}

	Ray
	PerspectiveCamera::get_ray (float _x, float _y) const
	{
		Ray ray;
		ray.origin = position;
		ray.direction = ~(forward + (grid_width * _x) + (grid_height * _y));

		return ray;
	}
}

