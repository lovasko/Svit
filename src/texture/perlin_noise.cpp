#include "texture/perlin_noise.h"
#include "math/interpolation.h"
#include "geom/operations.h"

#include <cstdio>

namespace Svit
{
	float
	PerlinNoiseTexture::noise (int _x, int _y, int _z)
	{
		int n = _x + _y * 57 + _z * 997;
		n = (n << 13) ^ n;

		return 
			(1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) 
			    / 1073741824.0f);
	}

	float
	PerlinNoiseTexture::noise_3D (Point3 _point)
	{
		int ix, iy, iz;
		float dx, dy, dz;

		decompose_float(_point.x, &ix, &dx);
		decompose_float(_point.y, &iy, &dy);
		decompose_float(_point.z, &iz, &dz);

		ix < 0 ? dx = 1.0f - dx : dx = dx;
		iy < 0 ? dy = 1.0f - dy : dy = dy;
		iz < 0 ? dz = 1.0f - dz : dz = dz;

		float w000 = noise(ix,   iy,   iz);
		float w100 = noise(ix+1, iy,   iz);
		float w010 = noise(ix,   iy+1, iz);
		float w110 = noise(ix+1, iy+1, iz);
		float w001 = noise(ix,   iy,   iz+1); 
		float w101 = noise(ix+1, iy,   iz+1); 
		float w011 = noise(ix,   iy+1, iz+1); 
		float w111 = noise(ix+1, iy+1, iz+1);

		float result = lerp_3D<float>(w000, w100, w010, w110, w001, w101, w011, w111, 
		    dx, dy, dz);

		return result;
	}

	PerlinNoiseTexture::PerlinNoiseTexture (Vector3 _black, Vector3 _white)
	{
		black = _black;
		white = _white;
		octave_count = 0;
	}

	void
	PerlinNoiseTexture::add_octave (float _amplitude, float _frequency)
	{
		amplitudes.push_back(_amplitude);
		frequencies.push_back(_frequency);
		octave_count++;
	}

	Vector3
	PerlinNoiseTexture::get_color (Point3 _point)
	{
		float sum = 0.0;
		for (unsigned int i = 0; i < octave_count; i++)
			sum += noise_3D(_point * frequencies[i]) * amplitudes[i];

		sum = (sum + 1.0f) / 2.0f;

		return lerp_1D<float>(black, white, sum);
	}
}

