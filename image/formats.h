#ifndef SVIT_IMAGE_FORMATS
#define SVIT_IMAGE_FORMATS

#include "../geom/vector.h"

namespace Svit
{
	class RGB8Format
	{
		public:
			typedef Vector<float> data_type;

			static data_type zero ()
			{
				return Vector<float>(0.0, 0.0, 0.0);
			}
	};

	class RGBA8Format
	{
		public:
			typedef Vector<float> data_type;

			static data_type zero ()
			{
				return Vector<float>(0.0, 0.0, 0.0, 1.0);
			}
	};
}

#endif

