#include "light/spot.h"

namespace Svit
{
	SpotLight::SpotLight (Point3 _position, Vector3 _direction, Vector3 _color,
	    float _angle, float _exp)
	{
		position = _position;
		direction = ~_direction;
		color = _color;
		cos_cut_off = cos(_angle);
		exp = _exp;
	}
	
	LightHit 
	SpotLight::get_light_hit (Point3 _point)
	{
		Vector3 direction = _point - position;

		LightHit light_hit;
		light_hit.direction = direction; 
		light_hit.distance = direction % direction;

		return light_hit;
	}

	Vector3
	SpotLight::get_intensity (LightHit _hit)
	{
		float cos_angle = (~_hit.direction) % direction;
		if (cos_angle < 0.0 || cos_angle > cos_cut_off)
			return Vector3();
		else
		{
			float angular_strength = powf(cos_angle, exp);
			float distance_weakness = powf(_hit.distance, 2.0f);

			return color * (angular_strength / distance_weakness);
		}
	}
}

