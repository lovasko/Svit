#ifndef SVIT_GEOM_RAY_H
#define SVIT_GEOM_RAY_H

#include "geom/point.h"
#include "geom/vector.h"

namespace Svit
{
	class Ray
	{
		public:
			Point3 origin;
			Vector3 direction;

			Ray ();

			Ray (Point3 const& _origin, Vector3 const& _direction);

			Point3 
			operator() (float _time) const;

			void
			dump (const char *name, unsigned int level = 0);
	};
}

#endif

