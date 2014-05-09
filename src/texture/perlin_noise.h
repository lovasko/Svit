#ifndef SVIT_PERLIN_NOISE_TEXTURE
#define SVIT_PERLIN_NOISE_TEXTURE

#include "texture/texture.h"

#include <vector>

namespace Svit
{
	class PerlinNoiseTexture : public Texture
	{
		protected:
			Vector3 black;
			Vector3 white;
			unsigned int octave_count;
			std::vector<float> amplitudes;
			std::vector<float> frequencies;

			float
			noise (int _x, int _y, int _z);

			float
			noise_3D (Point3 _point);

		public:
			PerlinNoiseTexture (Vector3 _black, Vector3 _white);

			void
			add_octave (float _amplitude, float _frequency);

			virtual Vector3
			get_color (Point3 _point);
	};
}

#endif

