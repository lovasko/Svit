#include "material/phong.h"

#include <cmath>

namespace Svit
{
	PhongMaterial::PhongMaterial (std::unique_ptr<Texture> _texture, float _exp)
	{
		texture = std::move(_texture);
		exp = _exp;
	}

	Vector3
	PhongMaterial::get_reflectance (Point3 _point, Vector3 _normal, Vector3 _in, 
	    Vector3 _out)
	{
		Vector3 ideal_reflection = (_normal * 2.0f * (_normal % _in)) - _in;
		float cos_angle = ~ideal_reflection % _out;

		if (cos_angle < 0.0f)
			return Vector3();
		else
		{
			float power = powf(cos_angle, exp);
			float intensity = power * (exp + 2.0f) / M_PI_2;

			return texture->get_color(_point) * intensity;
		}
	}
}

