#ifndef SVIT_NODE
#define SVIT_NODE

#include <string>

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
			intersect (Ray& _ray, Intersection& _isect) const = 0;

			virtual void
			dump (std::string _name, unsigned int _level = 0) const = 0;
	};
}

#endif

