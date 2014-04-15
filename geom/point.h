#ifndef SVIT_POINT
#define SVIT_POINT

namespace Svit
{
	template <typename Scalar>
	class Point
	{
		public:
			Point(Scalar _x, Scalar _y)
				: x(_x), y(_y), z(0), w(0)
			{ }

			Point(Scalar _x, Scalar _y, Scalar _z)
				: x(_x), y(_y), z(_z), w(0)
			{ }

			Point(Scalar _x, Scalar _y, Scalar _z, Scalar _w)
				: x(_x), y(_y), z(_z), w(_w)
			{ }

			Scalar x, y, z, w;
	};
}

#endif

