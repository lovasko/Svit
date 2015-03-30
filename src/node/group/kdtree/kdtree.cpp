#include "node/group/kdtree/kdtree.h"
#include <stack>

namespace Svit
{
	KDTree::KDTree (AxisSelector* _axis_selector,
					SplitStrategy* _split_strategy,
					unsigned int _max_depth,
					unsigned int _min_node_count)
	{
		max_depth = _max_depth;
		min_node_count = _min_node_count;
		axis_selector = _axis_selector;
		split_strategy = _split_strategy;
	}

	void
	KDTree::add (Node* _node)
	{
		root.nodes.push_back(_node);
		root.bounding_box.extend(_node->bounding_box);
	}

	void
	KDTree::finish ()
	{
		std::stack<KDNode*> kdnode_stack;

		root.depth = 0;
		root.split_axis = axis_selector->next(Axis::X);
		root.left = nullptr;
		root.right = nullptr;

		kdnode_stack.push(&root);
		while (!kdnode_stack.empty())
		{
			KDNode* kdnode = kdnode_stack.top();
			kdnode_stack.pop();

			printf("%d\n", kdnode_stack.size());

			if (kdnode->depth >= max_depth)
				continue;

			if (kdnode->nodes.size() <= min_node_count)
				continue;

			KDNode* left = new KDNode();  
			KDNode* right = new KDNode();  

			left->depth = kdnode->depth + 1;
			right->depth = kdnode->depth + 1;

			float split_coordinate = split_strategy->get_coordinate(kdnode->split_axis, kdnode->bounding_box);
			/* printf("SPLIT COORD = %f\n", split_coordinate); */
			for (Node* node : kdnode->nodes)
			{
				float min_coord = 0.0f;
				float max_coord = 0.0f;

				switch (kdnode->split_axis)
				{
					case Axis::X:
						min_coord = node->bounding_box.min.x;
						max_coord = node->bounding_box.max.x;
					break;

					case Axis::Y:
						min_coord = node->bounding_box.min.y;
						max_coord = node->bounding_box.max.y;
					break;

					case Axis::Z:
						min_coord = node->bounding_box.min.z;
						max_coord = node->bounding_box.max.z;
					break;

					default:
						printf("wat\n");
				}

				/* printf("%f ...---... %f\n", min_coord, max_coord); */

				if (min_coord < split_coordinate)
				{
					left->nodes.push_back(node);	
					left->bounding_box.extend(node->bounding_box);
				}

				if (max_coord >= split_coordinate)
				{
					right->nodes.push_back(node);	
					right->bounding_box.extend(node->bounding_box);
				}
			}

			if (left->nodes.size() > 0)
			{
				printf("pridavam aj dolava\n");
				left->split_axis = axis_selector->next(kdnode->split_axis);
				kdnode_stack.push(left);	
				kdnode->left = left;
			}

			if (right->nodes.size() > 0)
			{
				right->split_axis = axis_selector->next(kdnode->split_axis);
				kdnode_stack.push(right);	
				kdnode->right = right;
			}
		}
		
		printf("finish finished\n");
	}

	boost::optional<Intersection>
	KDTree::intersect (Ray& _ray, float _best)
	{
		if (!root.bounding_box.intersect(_ray))
			return boost::optional<Intersection>();

		/* printf("trafili sme root\n"); */

		float best = _best;
		/* boost::optional<Intersection>* best_intersection = nullptr; */
		bool have_best = false;
		Intersection best_intersection;

		std::stack<KDNode*> kdnode_stack;
		kdnode_stack.push(&root);

		while (!kdnode_stack.empty())
		{
			KDNode* kdnode = kdnode_stack.top();
			kdnode_stack.pop();

			if (kdnode->is_leaf())
			{
				/* printf("sme v leafe!\n"); */
				for (Node* node : kdnode->nodes)
				{
					if (!node->bounding_box.intersect(_ray))
						continue;

					boost::optional<Intersection> intersection = node->intersect( _ray, best);
					if (intersection)
					{
						// TODO why is this here? shouldnt we compare bests?
						/* if (node->bounding_box.contains(intersection->point)) */
						if (intersection->t < best)
						{
							have_best = true;
							best = intersection->t;
							best_intersection = *intersection;
						}
					}
				}
			}
			else
			{
				if (kdnode->left && kdnode->left->bounding_box.intersect(_ray))
				{
					/* printf("pojdeme dolava!\n"); */
					kdnode_stack.push(kdnode->left);
				}

				if (kdnode->right && kdnode->right->bounding_box.intersect(_ray))
				{
					/* printf("pojdeme doprava!\n"); */
					kdnode_stack.push(kdnode->right);
				}
			}
		}

		/* if (best_intersection) */
		/* if (have_best) */
		/* 	printf("mame!\n"); */
		/* else */
		/* 	printf("NEMAME\n"); */

		/* if (best_intersection) */
		if (have_best)
			/* return *best_intersection; */
			return boost::optional<Intersection>(best_intersection);
		else
			return boost::optional<Intersection>();
	}
}

