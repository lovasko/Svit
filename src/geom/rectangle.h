#ifndef SVIT_GEOM_RECTANGLE_H
#define SVIT_GEOM_RECTANGLE_H

#include "geom/point.h"
#include "geom/vector.h"

namespace Svit
{
	class Rectangle
	{
		public:
			Point2i start;
			Vector2i size;

			Rectangle ();

			Rectangle (Point2i _start, Vector2i _size);

			int
			get_area () const;

			float
			get_aspect_ratio () const;

			void
			dump (const char* _name, unsigned int _level = 0) const;
	};
}

#endif

