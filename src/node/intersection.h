#ifndef SVIT_INTERSECTION
#define SVIT_INTERSECTION

#include "geom/point.h"
#include "geom/vector.h"

namespace Svit
{
	class Solid;

	struct Intersection
	{
		Solid* node;	
		float t;
		Vector3 normal;
		Point3 point;
	};
}

#endif
