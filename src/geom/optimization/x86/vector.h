#ifndef SVIT_GEOM_OPTIMIZATION_X86_VECTOR_H
#define SVIT_GEOM_OPTIMIZATION_X86_VECTOR_H

#include <stdexcept>
#include <iostream>
#include <iomanip>

#include <assert.h>

#include "geom/optimization/x86/general.h"

namespace Svit
{
	template<>
	class Vector<float>
	{
		public:
			union
			{
				struct 
				{
					float x;
					float y;
					float z;
					float w;
				};
				__m128 v;
			};

			inline Vector (float _x = 0.0, float _y = 0.0, float _z = 0.0, float _w = 0.0)
			{ 
				v = _mm_setr_ps(_x, _y, _z, _w);
			}

			inline Vector (const Vector& other)
			{ 
				v = other.v;
			}

			inline Vector (__m128 other)
			{ 
				v = other;
			}

			inline float& 
			operator[](int nth)
			{
				assert(nth >= 0 && nth <= 3);
				switch (nth)
				{
					case 0:
						return x;

					case 1:
						return y;

					case 2:
						return z;

					case 3:
						return w;
				}

				throw std::runtime_error("Bad index");
			}

			inline void
			dump (const char *name, unsigned int level = 0)
			{
				std::string indentation(level*2, ' ');
				std::cout << std::setprecision(10) << std::fixed;
				std::cout << indentation << name << " = SSE Vector (" << x << ", " << 
						y << ", " << z << ", " << w << ")" << std::endl;
			}
	};
}

#endif

