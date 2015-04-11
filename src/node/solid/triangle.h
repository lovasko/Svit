#ifndef SVIT_TRIANGLE
#define SVIT_TRIANGLE

#include "node/solid/solid.h"
#include "geom/point.h"
#include "geom/vector.h"

namespace Svit
{
	class Triangle : public Solid
	{
		private:
			Point3 p1;
			Vector3 e1;
			Vector3 e2;

		public:
			Triangle (Point3 _p1, Point3 _p2, Point3 _p3);

			bool
			intersect (Ray& _ray, Intersection& _isect) const override;

			void
			complete_intersection (Intersection& _isect) const override;

			void
			dump (const char *_name, unsigned int _level = 0);
	};
}

#endif

