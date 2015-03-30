#ifndef SVIT_ROUND_ROBIN_AXIS_SELECTOR
#define SVIT_ROUND_ROBIN_AXIS_SELECTOR

#include "geom/axis.h"
#include "node/group/axis_selector/axis_selector.h"

namespace Svit
{
	class RoundRobinAxisSelector : public AxisSelector
	{
		public:
			Axis
			next (Axis _current, BoundingBox _bounding_box) override;
	};
}

#endif

