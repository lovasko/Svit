#ifndef SVIT_X86_POINT
#define SVIT_X86_POINT

#include "geom/optimization/x86/general.h"
#include "geom/point.h"

	template<>
	class Svit::Point<float>
	{
		public:
			union
			{
				struct 
				{
					float x, y, z, w;
				};
				__m128 v;
			};

			inline Point (float _x = 0.0, float _y = 0.0, float _z = 0.0, float _w = 0.0)
			{
				v = _mm_setr_ps(_x, _y, _z, _w);
			}

			inline Point (__m128 other)
			{ 
				v = other;
			}

			inline void
			dump (const char *name, unsigned int level = 0)
			{
				std::string indentation(level*2, ' ');
				std::cout << std::setprecision(10) << std::fixed;
				std::cout << indentation << name << " = SSEPoint (" << x << ", " << y <<
				    ", " << z << ", " << w << ")" << std::endl;
			}
	};

#endif

