#ifndef SVIT_KDTREE_KDNODE
#define SVIT_KDTREE_KDNODE

#include <vector>

#include "node/node.h"
#include "geom/bounding_box.h"
#include "geom/axis.h"

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

