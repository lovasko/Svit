#ifndef SVIT_RAY
#define SVIT_RAY

#include "vector.h"
#include "point.h"

namespace Svit
{
	template <typename Scalar>
	class Ray
	{
		public:
			Point<Scalar> origin;
			Vector<Scalar> direction;

			Ray (Vector<Scalar>& _origin, Vector<Scalar>& _direction)
			{
				origin = _origin;
				direction = _direction;
			}

			Point<Scalar> operator() (Scalar _time) const
			{
				return origin + direction * _time;
			}
	};
}

#endif

