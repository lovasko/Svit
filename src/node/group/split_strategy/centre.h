#ifndef SVIT_KDTREE_SPLIT_STRATEGY_CENTRE
#define SVIT_KDTREE_SPLIT_STRATEGY_CENTRE

#include "node/group/kdtree/split_strategy/split_strategy.h"

namespace Svit
{
	class CentreSplitStrategy : public SplitStrategy
	{
		public:
			float
			get_coordinate (Axis _axis, BoundingBox _bounding_box) override;
	};
}

#endif

