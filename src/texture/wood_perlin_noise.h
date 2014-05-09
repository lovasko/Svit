#ifndef SVIT_WOOD_PERLIN_NOISE_TEXTURE
#define SVIT_WOOD_PERLIN_NOISE_TEXTURE

#include "texture/perlin_noise.h"

namespace Svit
{
	class WoodPerlinNoiseTexture : protected PerlinNoiseTexture
	{
		private: 
			float param;

		public:
			WoodPerlinNoiseTexture (float _param = 20.0);	

			Vector3
			get_color (Point3 _point);
	};
}

#endif

