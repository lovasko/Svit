#include "node/group/kdtree/kdnode.h"

namespace Svit
{
	KDNode::KDNode ()
	{
		left = nullptr;
		right = nullptr;
		split_axis = Axis::X;
	}

	bool
	KDNode::is_leaf () const
	{
		return (left == nullptr && right == nullptr);
	}
}

