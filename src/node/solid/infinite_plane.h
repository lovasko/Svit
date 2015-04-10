#ifndef SVIT_INFINITE_PLANE
#define SVIT_INFINITE_PLANE

#include "node/solid/solid.h"
#include "node/node.h"
#include "geom/point.h"
#include "geom/vector.h"
#include "geom/ray.h"

namespace Svit
{
	class InfinitePlane : public Solid
	{
		private:
			Point3 point;
			Vector3 normal;

		public:
			InfinitePlane (Point3 _point, Vector3 _normal)
				: point(_point), normal(_normal)
			{ }

			bool
			intersect (Ray& _ray, Intersection& _isect) const override;

			void
			complete_intersection (Intersection& _isect) const override;

			void
			dump (const char *_name, unsigned int _level = 0);
	};
}

#endif

