#ifndef SVIT_RECT
#define SVIT_RECT 

#include "geom/vector.h"
#include "geom/point.h"

#include <stdexcept>

namespace Svit
{
	struct Rectangle
	{
		Point2i start;
		Vector2i size;

		Rectangle () { } 

		Rectangle (Point2i _start, Vector2i _size)
			: start(_start), size(_size)
		{ }

		int
		get_area ()
		{
			return size.x * size.y;
		}

		float
		get_aspect_ratio ()
		{
			if (size.y == 0)
				throw std::runtime_error("Rectangle height is zero");

			return (float)size.x/(float)size.y;
		}
	};
}

#endif

