#include "light/ambient.h"

namespace Svit
{
	AmbientLight::AmbientLight (Vector3 _color)
	{
		color = _color;
	}

	LightHit 
	AmbientLight::get_light_hit (Point3 _point)
	{
		(void) _point;

		LightHit light_hit;
		light_hit.direction = Vector3(0.0, 1.0, 0.0);
		light_hit.distance = 0.0f;

		return light_hit; 
	}

	Vector3
	AmbientLight::get_intensity (LightHit _hit)
	{
		(void) _hit;
		return color;			
	}
}

