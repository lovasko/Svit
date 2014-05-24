#include "light/directional.h"

#include <limits>

namespace Svit
{
	DirectionalLight::DirectionalLight (Vector3 _direction, Vector3 _color)
	{
		norm_neg_direction = ~!_direction;		
		color = _color;
	}

	LightHit 
	DirectionalLight::get_light_hit (Point3 _point)
	{
		LightHit light_hit;
		light_hit.direction = norm_neg_direction;
		light_hit.distance = std::numeric_limits<float>::max();

		return light_hit; 
	}

	Vector3
	DirectionalLight::get_intensity (LightHit _hit)
	{
		(void) _hit;
		return color;			
	}
}

