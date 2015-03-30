#ifndef SVIT_KDTREE_AXIS_SELECTOR
#define SVIT_KDTREE_AXIS_SELECTOR

#include "geom/axis.h" 

namespace Svit
{
	class AxisSelector
	{
		public:
			virtual Axis
			next (Axis _current) = 0;
	};
}

#endif

