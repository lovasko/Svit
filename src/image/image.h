#ifndef SVIT_IMAGE
#define SVIT_IMAGE

#include "geom/vector.h"
#include "geom/point.h"

#include <vector>
#include <string>

namespace Svit
{
	class Image
	{
		private:
			std::vector<Vector3> data;

		public:
			Vector2i size;

			Vector3& 
			operator() (int x, int y);

			void
			resize (Vector2i _size);

			Image ();

			Image (Vector2i& _size);

			void
			paste (Point2i start, Image& source);

			int 
			write (std::string filename);
	};
}

#endif

