#ifndef SVIT_RAY
#define SVIT_RAY

#include "vector.h"
#include "point.h"

namespace Svit
{
	class Ray
	{
		public:
			Point3 origin;
			Vector3 direction;

			Ray (Point3& _origin, Vector3& _direction)
				: origin(_origin), direction(_direction)
			{ }

			Point3 operator() (float time) const
			{
				return origin + direction * _time;
			}
	};
}

#endif

