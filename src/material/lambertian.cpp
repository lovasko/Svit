#include "material/lambertian.h"
#include "geom/operations.h"

#include <cmath>

namespace Svit
{
	LambertianMaterial::LambertianMaterial (std::unique_ptr<Texture> _texture,
	    bool _simple)
	{
		texture = std::move(_texture);	
		simple = _simple;
	}

	Vector3
	LambertianMaterial::get_reflectance (Point3 _point, Vector3 _normal, 
	    Vector3 _in, Vector3 _out)
	{
		if (simple)
			return texture->get_color(_point);
		else
		{
			float cosine = _in % _normal;
			float lambert_law = fabs(cosine); 

			return texture->get_color(_point) * (lambert_law * (float)M_1_PI);
		}
	}
}

