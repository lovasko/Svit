#ifndef SVIT_GEOM_VECTOR_H
#define SVIT_GEOM_VECTOR_H

#include <assert.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

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
			operator[] (int nth) const
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

			Scalar
			max_component3 () const
			{
				return std::max(x, std::max(y, z));
			}

			Scalar
			max_component4 () const
			{
				return std::max(x, std::max(y, std::max(z, w)));
			}

			void
			dump (std::string _name, unsigned int _level = 0) const
			{
				std::cout << std::setprecision(10)
				          << std::fixed
				          << std::string(_level*2, ' ')
				          << _name
				          << " = Vector ("
				          << x
				          << ", "
				          << y
				          << ", "
				          << z
				          << ", "
				          << w
				          << ")"
				          << std::endl;
			}

			Scalar x, y, z, w;
	};

	typedef Vector<float> Vector4;
	typedef Vector<float> Vector3;
	typedef Vector<float> Vector2;
	typedef Vector<int> Vector2i;
	typedef Vector<int> Vector3i;
}

#if defined(USE_SSE) && defined(__SSE__)
	#include "geom/optimization/x86/vector.h"
#endif

#if defined(USE_SSE) && defined(__SSE__)
	#include "geom/optimization/x86/operations.h"
#endif

#include "geom/operations.h"

#endif

