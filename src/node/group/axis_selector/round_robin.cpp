#include "node/group/axis_selector/round_robin.h"

namespace Svit
{
	Axis
	RoundRobinAxisSelector::next (Axis _current, BoundingBox _bounding_box)
	{
		(void) _bounding_box;

		switch (_current)
		{
			case Axis::X:
				return Axis::Y;

			case Axis::Y:
				return Axis::Z;

			case Axis::Z:
				return Axis::X;

			default:
				return Axis::X;
		}
	}
}

