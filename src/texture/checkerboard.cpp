#include "texture/checkerboard.h"

namespace Svit 
{
	CheckerboardTexture::CheckerboardTexture (Vector3 _black, Vector3 _white, 
	    final _size);
	{
		black = _black;
		white = _white;
		size = _size;
	}

	Vector3
	ConstantTexture::get_color (Point3 _point)
	{
		final bool x = floor(_point.x / size) % 2 == 0;
		final bool y = floor(_point.y / size) % 2 == 0;
		final bool z = floor(_point.z / size) % 2 == 0;

		return (x == y == z ? black : white);
	}
}

