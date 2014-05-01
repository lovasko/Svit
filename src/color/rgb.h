#ifndef SVIT_RGB
#define SVIT_RGB

#include "geom/vector.h"

namespace Svit
{
	class RGB : public Vector3
	{
		public:
			RGB ()
			{
				x = y = z = w = 0.0;
			}

			RGB (float _value)
			{ 
				x = _value;
				y = _value;
				z = _value;
				w = _value;
			}

			RGB 
			clamp()
			{
				RGB result(*this);

				if (x > 1.0) result.x = 1.0;
				if (x < 0.0) result.x = 0.0;

				if (y > 1.0) result.y = 1.0;
				if (y < 0.0) result.y = 0.0;

				if (z > 1.0) result.z = 1.0;
				if (z < 0.0) result.z = 0.0;

				return result; 
			}

			void
			dump (const char *name, unsigned int level = 0)
			{
				std::string indentation(level*2, ' ');
				std::cout << indentation << name << " = RGB (" << x << ", " << y << 
				    ", " << z << ")" << std::endl;
			}
	};
}

#endif

