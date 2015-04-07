#ifndef SVIT_BVH_GROUP
#define SVIT_BVH_GROUP

#include <vector>

#include "geom/axis.h"
#include "geom/bounding_box.h"
#include "node/group/axis_selector/axis_selector.h"
#include "node/group/group.h"
#include "node/group/split_strategy/split_strategy.h"
#include "node/node.h"

namespace Svit
{
	struct BVHNode
	{
		bool is_leaf;
		unsigned int left_idx;
		unsigned int right_idx;
		BVHNode* left;
		BVHNode* right;
		Axis split_axis;
		BoundingBox bounding_box;
	};

	class BVH : public Group
	{
		private:
			std::vector<Node*> nodes;
			BVHNode root;

			AxisSelector* axis_selector;
			SplitStrategy* split_strategy;
			unsigned int max_bucket_size;
			unsigned int max_depth;

			void
			build (unsigned int _left_idx,
			       unsigned int _right_idx,
			       BVHNode* _bvhnode,
			       unsigned int _depth);

			void
			init_inner_node (BVHNode* _bvhnode,
			                 Axis _parent_split_axis,
			                 unsigned int _offset,
			                 unsigned int _length);

			void
			cut ();

		public:
			BVH (AxisSelector* _axis_selector,
			     SplitStrategy* _split_strategy,
			     unsigned int _max_bucket_size,
			     unsigned int _max_depth);

			bool
			intersect (Ray& _ray, Intersection& _isect);

			void
			add (Node* _node) override;

			void
			finish () override;

			void
			dump (std::string _name);
	};
}

#endif

