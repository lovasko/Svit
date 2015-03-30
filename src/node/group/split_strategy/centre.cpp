#include "node/group/kdtree/split_strategy/centre.h"

namespace Svit
{
	float
	CentreSplitStrategy::get_coordinate (Axis _axis, BoundingBox _bounding_box)
	{
		_bounding_box.min.dump("bb-min");
		_bounding_box.max.dump("bb-max");

		switch (_axis)
		{
			case Axis::X:
				return (_bounding_box.min.x + _bounding_box.max.x) / 2.0f;

			case Axis::Y:
				return (_bounding_box.min.y + _bounding_box.max.y) / 2.0f;

			case Axis::Z:
				return (_bounding_box.min.z + _bounding_box.max.z) / 2.0f;

			default:
				printf("wat\n");
				return -2.7f;
		}
	}
}

