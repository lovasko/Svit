#ifndef SVIT_VECTOR
#define SVIT_VECTOR

namespace Svit
{
	template <typename Scalar>
	class Vector 
	{
		public:
			Vector () {}

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

			Scalar x, y, z, w;
	};

	typedef Vector<float> Vector4;
	typedef Vector<float> Vector3;
	typedef Vector<float> Vector2;
	typedef Vector<int> Vector2i;
}

#endif

