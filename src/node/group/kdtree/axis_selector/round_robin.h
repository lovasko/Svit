#ifndef SVIT_KDTREE_ROUND_ROBIN
#define SVIT_KDTREE_ROUND_ROBIN

#include "geom/axis.h"
#include "node/group/kdtree/axis_selector/axis_selector.h"

namespace Svit
{
	class RoundRobinAxisSelector : public AxisSelector
	{
		public:
			Axis
			next (Axis _current) override;
	};
}

#endif

