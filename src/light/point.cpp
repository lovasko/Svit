#include "light/point.h"

#include <cmath>

namespace Svit
{
	PointLight::PointLight(Point3 _position, Vector3 _color)
	{
		position = _position;
		color = _color;
	}
	
	LightHit 
	PointLight::get_light_hit (Point3 _point)
	{
		Vector3 direction = position - _point;

		LightHit light_hit;
		light_hit.direction = ~direction; 
		light_hit.distance = direction % direction;

		return light_hit;
	}

	Vector3
	PointLight::get_intensity (LightHit _hit)
	{
		return color; // powf(_hit.distance, 2.0f);
	}
}

