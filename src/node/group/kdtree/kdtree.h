#ifndef SVIT_KDTREE_KDTREE_GROUP
#define SVIT_KDTREE_KDTREE_GROUP

#include <vector>

#include "geom/axis.h"
#include "geom/ray.h"
#include "node/group/group.h"
#include "node/group/kdtree/kdnode.h"
#include "node/group/kdtree/axis_selector/axis_selector.h"
#include "node/group/kdtree/split_strategy/split_strategy.h"

namespace Svit
{
	class KDTree : public Group
	{
		private:
			AxisSelector* axis_selector;
			SplitStrategy* split_strategy;
			unsigned int max_depth;
			unsigned int min_node_count;
			/* std::vector<Node*> nodes; */

			std::tuple<Point3, Point3>
			border_points (KDTree::Node& _node, float _coordinate);
			
		public:
			KDNode root;

			KDTree (AxisSelector* _axis_selector,
			        SplitStrategy* _split_strategy,
			        unsigned int _max_depth = 20,
			        unsigned int _min_node_count = 50);

			boost::optional<Intersection>
			intersect (Ray& _ray, float _best) override;

			void
			add (Node* _node) override;

			void
			finish () override;
	};
}

#endif

