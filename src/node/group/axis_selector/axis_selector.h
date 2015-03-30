#ifndef SVIT_AXIS_SELECTOR
#define SVIT_AXIS_SELECTOR

#include "geom/axis.h" 
#include "geom/bounding_box.h" 

namespace Svit
{
	class AxisSelector
	{
		public:
			virtual Axis
			next (Axis _current, BoundingBox _bounding_box) = 0;
	};
}

#endif

