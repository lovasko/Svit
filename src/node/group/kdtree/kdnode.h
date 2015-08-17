#ifndef SVIT_KDTREE_KDNODE
#define SVIT_KDTREE_KDNODE

#include <vector>

#include "geom/axis.h"
#include "geom/bounding_box.h"
#include "node/node.h"

namespace Svit
{
	class KDNode
	{
		public:
			KDNode* left;
			KDNode* right;
			std::vector<Node*> nodes;
			BoundingBox bounding_box;
			Axis split_axis;
			unsigned int depth;

			KDNode ();

			bool
			is_leaf () const;
	};
}

#endif

