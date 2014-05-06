#ifndef SVIT_CHECKERBOARD_TEXTURE
#define SVIT_CHECKERBOARD_TEXTURE

#include "texture/texture.h"

namespace Svit
{
	class CheckerboardTexture : public Texture
	{
		private:
			Vector3 black;
			Vector3 white;
			final size;

		public:
			CheckerboardTexture (Vector3 _black, Vector3 _white, final _size);

			Vector3
			get_color (Point3 _point);
	};
}

#endif

