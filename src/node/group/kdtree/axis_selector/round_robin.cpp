#include "node/group/kdtree/axis_selector/round_robin.h"

namespace Svit
{
	Axis
	RoundRobinAxisSelector::next (Axis _current)
	{
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

