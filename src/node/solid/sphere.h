#ifndef SVIT_SPHERE
#define SVIT_SPHERE

#include "node/solid/solid.h"
#include "geom/point.h"

namespace Svit
{
	class Sphere : public Solid
	{
		private:
			Point3 center;
			float radius;

		public:
			Sphere (Point3 _center, float _radius);

			bool
			intersect (Ray& _ray, Intersection& _isect) const override;

			void
			complete_intersection (Intersection& _isect) const override;

			void
			dump (const char *_name, unsigned int _level = 0) override;
	};
}

#endif

