#include "light/directional.h"

namespace Svit
{
	DirectionalLight::DirectionalLight (Vector3 _direction, Vector3 _color)
	{
		direction = _direction;		
		color = _color;
	}

	LightHit 
	DirectionalLight::get_light_hit (Point3 _point)
	{
		LightHit light_hit;
		light_hit.direction = direction;
		light_hit.distance = FLT_MAX;

		return light_hit; 
	}

	Vector3
	DirectionalLight::get_intensity (LightHit _hit)
	{
		return color;			
	}
}

