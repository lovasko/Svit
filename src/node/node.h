#ifndef SVIT_NODE
#define SVIT_NODE

#include "geom/bounding_box.h"
#include "geom/ray.h"
#include "node/intersection.h"

#include <list>
#include <iostream>
#include <boost/optional.hpp>

namespace Svit
{
	class Node
	{
		public:
			BoundingBox bounding_box;

			virtual boost::optional<Intersection>
			intersect (Ray& _ray, float _best) = 0;
	};
}

#endif

