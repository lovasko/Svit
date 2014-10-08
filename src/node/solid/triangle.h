#ifndef SVIT_TRIANGLE
#define SVIT_TRIANGLE

#include "node/solid/solid.h"
#include "geom/point.h"
#include "geom/vector.h"

#include <list>

namespace Svit
{
	class Triangle : public Solid
	{
		private:
			Vector3 normal;			
			Vector3 e1;
			Vector3 e2;

		public:
			Point3 p1;
			Point3 p2;
			Point3 p3;

			Triangle (Point3 _p1, Point3 _p2, Point3 _p3);

			boost::optional<Intersection>
			intersect (Ray& _ray, float _best);

			void
			complete_intersection (Intersection *_intersection);

			void
			dump (const char *_name, unsigned int _level = 0);
	};
}

#endif

