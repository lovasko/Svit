#include "material/mirror.h"

namespace Svit
{
	MirrorMaterial::MirrorMaterial (float _eta, float _kappa)
	{
		eta = _eta;
		kappa = _kappa;
		e2k2 = eta * eta + kappa * kappa;
	}

	Vector3
	MirrorMaterial::get_reflectance (Point3 _point, Vector3 _normal, Vector3 _in, 
		Vector3 _out)
	{
		float cos_theta = _normal % _in;
		float cos_theta_2 = powf(cos_theta, 2.0f);

		float parallel = (e2k2 * cos_theta_2 - 2.0f * eta * cos_theta + 1.0f) / 
		                 (e2k2 * cos_theta_2 + 2.0f * eta * cos_theta + 1.0f);
		float perpendicular = (e2k2 - 2.0f * eta * cos_theta + cos_theta_2) / 
		                      (e2k2 + 2.0f * eta * cos_theta + cos_theta_2);

		float value = (parallel + perpendicular) * 0.5f;
		return Vector3(value, value, value);
	}
}

