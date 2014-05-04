#ifndef SVIT_POINT
#define SVIT_POINT

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <assert.h>

namespace Svit
{
	template <typename Scalar>
	class Point
	{
		public:
			Point () 
				: x(0), y(0), z(0), w(0)
			{}

			Point (Scalar _x, Scalar _y)
				: x(_x), y(_y), z(0), w(0)
			{ }

			Point (Scalar _x, Scalar _y, Scalar _z)
				: x(_x), y(_y), z(_z), w(0)
			{ }

			Point (Scalar _x, Scalar _y, Scalar _z, Scalar _w)
				: x(_x), y(_y), z(_z), w(_w)
			{ }

			void
			dump (const char *name, unsigned int level = 0)
			{
				std::string indentation(level*2, ' ');
				std::cout << std::setprecision(10) << std::fixed;
				std::cout << indentation << name << " = Point (" << x << ", " << y <<
				    ", " << z << ", " << w << ")" << std::endl;
			}

			Scalar& 
			operator[](const int nth)
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

			Scalar x, y, z, w;
	};

	typedef Point<float> Point4;
	typedef Point<float> Point3;
	typedef Point<float> Point2;
	typedef Point<int> Point2i;

}

#if defined(USE_SSE) && defined(__SSE__)
	#include "geom/optimization/x86/point.h"
#endif

#endif

