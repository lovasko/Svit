#ifndef SVIT_SPHERE
#define SVIT_SPHERE

#include "geom/point.h"
#include "node/solid/solid.h"

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
			dump (std::string _name, unsigned int _level = 0) const override;
	};
}

#endif

