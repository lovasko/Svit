#ifndef SVIT_TEXTURE
#define SVIT_TEXTURE

#include "geom/vector.h"
#include "geom/point.h"

namespace Svit
{
	class Texture
	{
		public:
			virtual Vector3
			get_color (Point3 _point) = 0;
	};
}

#endif

