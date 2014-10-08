#ifndef SVIT_KDTREE
#define SVIT_KDTREE

#include "node/group/group.h"
#include "geom/ray.h"

#include <list>

namespace Svit
{
	namespace KDTree
	{
		enum Axis
		{
			X, Y, Z;
		};

		class Node
		{
			public:
				KDTree::Node* left;
				KDTree::Node* right;
				std::list<Svit::Node*> nodes;
				BoundingBox bounding_box;
				Axis split_axis;
				unsigned int depth;

				bool
				is_leaf ()
				{
					return (left == nullptr && right == nullptr);
				}
		};
	}

	class KDTree : public Group
	{
		private:
			KDTree::Node root;
			unsigned int max_depth;
			unsigned int max_node_count;
			std::list<Node*> nodes;

			KDTree::Axis
			next_axis (KDTree::Axis _axis);

			std::tuple<Point3, Point3>
			border_points (KDTree::Node& _node, float _coordinate);
			
		public:
			KDTree (unsigned int _max_depth = 20)
			 : max_depth(_max_depth)
			{ }

			boost::optional<Intersection>
			intersect (Ray& _ray, float _best);

			void
			set_material (std::unique_ptr<Material> _material)
			{ }

			void
			add (Node* _node);

			void
			finish ();
	};
}

#endif

