#ifndef SVIT_NODE
#define SVIT_NODE

#include "geom/bounding_box.h"
#include "geom/ray.h"
#include "node/intersection.h"

namespace Svit
{
	class Node
	{
		public:
			BoundingBox bounding_box;

			virtual bool
			intersect (Ray& _ray, Intersection& _isect) = 0;
	};
}

#endif

