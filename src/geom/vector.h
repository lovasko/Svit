#ifndef SVIT_VECTOR
#define SVIT_VECTOR

#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace Svit
{
	template <typename Scalar>
	class Vector 
	{
		public:
			Vector () 
				: x(0), y(0), z(0), w(0)
			{}

			Vector (Scalar _x, Scalar _y)
				: x(_x), y(_y), z(0), w(0)
			{ }

			Vector (Scalar _x, Scalar _y, Scalar _z)
				: x(_x), y(_y), z(_z), w(0)
			{ }

			Vector (Scalar _x, Scalar _y, Scalar _z, Scalar _w)
				: x(_x), y(_y), z(_z), w(_w)
			{ }

			Vector (const Vector& other)
				: x(other.x), y(other.y), z(other.z), w(other.w)
			{ }

			Scalar& 
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

			void
			dump (const char *name, unsigned int level = 0)
			{
				std::string indentation(level*2, ' ');
				std::cout << std::setprecision(10) << std::fixed;
				std::cout << indentation << name << " = Vector (" << x << ", " << y <<
				    ", " << z << ", " << w << ")" << std::endl;
			}

			Scalar x, y, z, w;
	};

	typedef Vector<float> Vector4;
	typedef Vector<float> Vector3;
	typedef Vector<float> Vector2;
	typedef Vector<int> Vector2i;

	#if defined(USE_SSE) && defined(__SSE__)
		#include "geom/optimization/x86/vector.h"
	#endif
}

#endif

