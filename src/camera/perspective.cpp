#include "camera/perspective.h"

namespace Svit
{
	PerspectiveCamera::PerspectiveCamera (Point3 _position, Vector3 _forward, 
	    Vector3 _up, Rectangle _area, float _horizontal_angle)
		: position(_position), 
			forward(~_forward), 
			up(~_up), 
			horizontal_angle(_horizontal_angle)
	{
		set_area(_area);
		recompute();
	}

	void 
	PerspectiveCamera::recompute ()
	{
		Vector3 left = ~(forward & up);
		float half_width = 1.0f / tan(horizontal_angle / 2.0);
		float half_height = half_width / area.get_aspect_ratio();

		grid_width = left * -half_width;
		grid_height = up * -half_height;
	}

	Ray
	PerspectiveCamera::get_ray (float _x, float _y)
	{
		Ray ray;
		ray.origin = position;
		ray.direction = ~(forward + (grid_width * _x) + (grid_height * _y));

		return ray;
	}

	void
	PerspectiveCamera::look_at (Point3 _dest)
	{
		forward = ~(_dest - position);
		recompute();
	}
}

