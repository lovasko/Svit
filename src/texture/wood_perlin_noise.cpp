#include "texture/wood_perlin_noise.h"
#include "math/interpolation.h"
#include "geom/operations.h"

namespace Svit
{
	WoodPerlinNoiseTexture::WoodPerlinNoiseTexture (float _param)
	{
		param = _param;
	}

	Vector3
	WoodPerlinNoiseTexture::get_color (Point3 _point)
	{
		float sum = 0.0;
		float discard;
		for (unsigned int i = 0; i < octave_count; i++)
			sum += modff(noise_3D(_point * frequencies[i]) * amplitudes[i] * param,
			    &discard);

		sum = (sum + 1.0f) / 2.0f;

		return lerp_1D<float>(black, white, sum);
	}
}

