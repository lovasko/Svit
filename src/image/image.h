#ifndef SVIT_IMAGE_IMAGE_H
#define SVIT_IMAGE_IMAGE_H

#include <string>
#include <vector>

#include "geom/point.h"
#include "geom/vector.h"

namespace Svit
{
	class Image
	{
		private:
			std::vector<Vector3> data;

		public:
			Vector2i size;

			Vector3& 
			operator() (int _x, int _y);

			void
			resize (Vector2i _size);

			Image ();

			Image (Vector2i& _size);

			void
			paste (Point2i _start, Image& _source);

			int 
			write (std::string _filename);
	};
}

#endif

