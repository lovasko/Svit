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

		void
		dump (const char *name, unsigned int level = 0)
		{
			std::string indentation(level*2, ' ');	
			std::cout << indentation << name << " = Rectangle" << std::endl;
			start.dump("start", level+1);
			size.dump("size", level+1);
		}
	};
}

#endif

