#include "texture/costant.h"

namespace Svit 
{
	ConstantTexture::ConstantTexture (Vector3 _color)
	{
		color = _color;
	}

	Vector3
	ConstantTexture::get_color (Point3 _point)
	{
		(void) _point;
		return color;
	}
}

