#include "node/group/split_strategy/centre.h"

namespace Svit
{
	float
	CentreSplitStrategy::get_coordinate (Axis _axis, BoundingBox _bounding_box)
	{
		return _bounding_box.centroid()[_axis];
	}
}

