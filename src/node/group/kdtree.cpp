#include "node/group/kdtree.h"

#include <stack>

namespace Svit
{
	void
	KDTree::add (Node* _node)
	{
		nodes.push_back(_node);
		// TODO extend some bounding box?
	}

	void
	KDTree::finish ()
	{
		std::stack<KDTree::Node*> node_stack;

		root.depth = 0;
		root.split_axis = KDTree::X;
		root.bounding_box = get_bounds();
		root.set_primitives(primitives);

		node_stack.push(&root);
		while (!stack.empty())
		{
			KDTreeNode node = stack.pop();			

			// check for terminating due to depth
			if (node.depth >= max_depth)
				continue;

			// check for terminating due to number of primitives
			if (node.primitive_count <= min_primitives)
				continue;

			float split_coordinate = 0.0;
			switch (node.split_axis)
			{
				case X:
					split_coordinate = (node.bounding_box.min.x + 
					                    node.bounding_box.max.x) / 2.0f;
				break;

				case Y:
					split_coordinate = (node.bounding_box.min.y + 
					                    node.bounding_box.max.y) / 2.0f;
				break;

				case Z:
					split_coordinate = (node.bounding_box.min.z + 
					                    node.bounding_box.max.z) / 2.0f;
				break;
			}
			
			PointPair pair = get_border_points(node, split_coordinate);

			Point first_min = node.get_bounding_box().get_min();
			Point first_max = pair.get_first();
			Point second_min = pair.get_second();
			Point second_max = node.get_bounding_box().get_max();

			KDTree::Node* left = new KDTree::Node();  
			KDTree::Node* right = new KDTree::Node();  

			left.split_axis = next_axis(node.split_axis);
			right.split_axis = next_axis(node.split_axis);

			left.depth = node.depth + 1;
			right.depth = node.depth + 1;

			left.bounding_box(first_min, first_max);
			right.bounding_box(second_min, second_max);

			for (final Primitive primitive : node.get_primitives())
			{
				float min_coord = 0.0f;
				float max_coord = 0.0f;

				switch (node.split_axis)
				{
					case X:
						min_coord = primitive.get_bounds().min.x;
						max_coord = primitive.get_bounds().max.x;
					break;

					case Y:
						min_coord = primitive.get_bounds().min.y;
						max_coord = primitive.get_bounds().max.y;
					break;

					case Z:
						min_coord = primitive.get_bounds().min.z;
						max_coord = primitive.get_bounds().max.z;
					break;
				}

				if (min_coord < split_coordinate)
					left.add_primitive(primitive);	

				if (max_coord > split_coordinate)
					right.add_primitive(primitive);	
			}

			if (left.has_any_primitives())
			{
				stack.push(left);	
				node.set_left(left);
			}

			if (right.has_any_primitives())
			{
				stack.push(right);	
				node.set_right(right);
			}
		}
	}

	boost::optional<Intersection>
	KDTree::intersect (Ray& _ray, float _best)
	{
		if (!root.bounding_box.intersect(_ray))
			return boost::optional<Intersection>();

		float best = _best;
		Intersection* best_intersection = nullptr;

		std::stack<KDTree::Node*> node_stack;
		node_stack.push(&root);

		while (!stack.empty())
		{
			KDTree::Node* node = node_stack.pop();
			if (node->is_leaf())
			{
				for (auto scene_node : node->nodes)
				{
					if (!scene_node->bounding_box.intersect(_ray))
						continue;

					boost::optional<Intersection> intersection = scene_node->intersect(
						_ray, best);
					if (intersection)
					{
						if (scene_node->bounding_box.contains(intersection->point))
						{
							best = intersection.t;
							best_intersection = &intersection; 
						}
					}
				}
			}
			else
			{
				if (node->left && node->left->bounding_box.intersect(_ray))
					stack.push(node->left);		

				if (node->right && node->right->bounding_box->intersect(_ray))
					stack.push(node->right);		
			}
		}

		if (best_intersection)
			return boost::optional<Intersection>(*best_intersection);
		else
			return boost::optional<Intersection>();
		}
	}
}

