#include "texture/checkerboard.h"

#include <cmath>

namespace Svit 
{
	CheckerboardTexture::CheckerboardTexture (Vector3 _black, Vector3 _white, 
	    float _size)
	{
		black = _black;
		white = _white;
		size = _size;
	}

	Vector3
	CheckerboardTexture::get_color (Point3 _point)
	{
		bool x = (int)floor(_point.x / size) % 2 == 0;
		bool y = (int)floor(_point.y / size) % 2 == 0;
		bool z = (int)floor(_point.z / size) % 2 == 0;

		return (x == y == z ? black : white);
	}
}

