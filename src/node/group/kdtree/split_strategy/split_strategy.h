#ifndef SVIT_KDTREE_SPLIT_STRATEGY
#define SVIT_KDTREE_SPLIT_STRATEGY

#include "geom/axis.h"
#include "geom/bounding_box.h"

namespace Svit
{
	class SplitStrategy
	{
		public:
			virtual float
			get_coordinate (Axis _axis, BoundingBox _bounding_box) = 0;
	};
}

#endif

