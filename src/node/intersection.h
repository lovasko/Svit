#ifndef SVIT_INTERSECTION
#define SVIT_INTERSECTION

#include "geom/point.h"
#include "geom/vector.h"

namespace Svit
{
	class Solid;

	struct Intersection
	{
		const Solid* solid;
		float t;
		Vector3 normal;
		Point3 point;
	};
}

#endif

