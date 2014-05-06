#ifndef SVIT_CONSTANT_TEXTURE
#define SVIT_CONSTANT_TEXTURE

#include "texture/texture.h"

namespace Svit
{
	class ConstantTexture : public Texture
	{
		private:
			Vector3 color;
		public:
			ConstantTexture (Vector3 _color);

			Vector3
			get_color (Point3 _point);
	};
}

#endif

