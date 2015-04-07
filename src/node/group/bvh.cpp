#include <iterator>
#include <queue>
#include <stack>
#include <utility>

#include "node/group/bvh.h"

namespace Svit
{
	BVH::BVH (AxisSelector* _axis_selector,
	          SplitStrategy* _split_strategy,
	          unsigned int _max_bucket_size,
	          unsigned int _max_depth)
	: axis_selector(_axis_selector),
	  split_strategy(_split_strategy),
	  max_bucket_size(_max_bucket_size),
	  max_depth(_max_depth)
	{
	}

	bool
	BVH::intersect (Ray& _ray, Intersection& _isect)
	{
		std::stack<BVHNode*> s;
		s.push(&root);

		bool found = false;

		while (!s.empty())
		{
			BVHNode* bvhnode = s.top();
			s.pop();

			float t_near;
			float t_far;
			if (!bvhnode->bounding_box.intersect(_ray, &t_near, &t_far))
				continue;

			if (bvhnode->is_leaf)
			{
				for (unsigned int i = bvhnode->left_idx; i < bvhnode->right_idx; i++)
				{
					if (nodes[i]->intersect(_ray, _isect))
						found = true;
				}
			}
			else
			{
				if (bvhnode->left != nullptr)
					s.push(bvhnode->left);

				if (bvhnode->right != nullptr)
					s.push(bvhnode->right);
			}
		}

		return found;
	}

	void
	BVH::add (Node* _node)
	{
		nodes.push_back(_node);
		bounding_box.extend(_node->bounding_box);
	}

	void
	BVH::init_inner_node (BVHNode* _bvhnode,
	                      Axis _parent_split_axis,
	                      unsigned int _left_idx,
	                      unsigned int _right_idx)
	{
		_bvhnode->is_leaf = false;

		BoundingBox box;
		for (unsigned int i = _left_idx; i < _right_idx; i++)
			box.extend(nodes[i]->bounding_box);
		_bvhnode->bounding_box = box;

		_bvhnode->split_axis = axis_selector->next(_parent_split_axis, box);
	}

	void
	BVH::build (unsigned int _left_idx,
	            unsigned int _right_idx,
	            BVHNode* _bvhnode,
	            unsigned int _depth)
	{
		if (_right_idx - _left_idx <= max_bucket_size || _depth >= max_depth)
		{
			_bvhnode->is_leaf = true;
			_bvhnode->left_idx = _left_idx;
			_bvhnode->right_idx = _right_idx;
			_bvhnode->left = nullptr;
			_bvhnode->right = nullptr;
		}
		else
		{
			float split_coord = split_strategy->get_coordinate(_bvhnode->split_axis, 
			                                                   _bvhnode->bounding_box);
			Axis split_axis = _bvhnode->split_axis;

			auto split_it = std::partition(nodes.begin() + _left_idx,
			                               nodes.begin() + (_right_idx-1),
				[&split_coord, &split_axis](Node* __node) -> bool
				{
					return (__node->bounding_box.centroid()[split_axis] < split_coord);
				});

			unsigned int split_idx = std::distance(nodes.begin(), split_it);

			if (split_idx != _left_idx)
			{
				BVHNode* left_node = new BVHNode();
				left_node->left = left_node->right = nullptr;

				init_inner_node(left_node, _bvhnode->split_axis, _left_idx, split_idx);
				_bvhnode->left = left_node;
				build(_left_idx, split_idx, left_node, _depth+1);
			}

			if (split_idx != _right_idx)
			{
				BVHNode* right_node = new BVHNode();
				right_node->left = right_node->right = nullptr;

				init_inner_node(right_node, _bvhnode->split_axis, split_idx, _right_idx);
				_bvhnode->right = right_node;
				build(split_idx, _right_idx, right_node, _depth+1);
			}
		}
	}

	void
	BVH::finish ()
	{
		root.is_leaf = false;
		root.bounding_box = bounding_box;
		root.split_axis = axis_selector->next(Axis::Z, bounding_box);

		build(0, nodes.size(), &root, 0);
		cut();
	}

	void
	BVH::cut ()
	{
		std::stack<BVHNode*> s;

		/* TODO root might be one-childed */
		s.push(&root);

		BVHNode* to_delete = nullptr;
		while (!s.empty())
		{
			auto bvhnode = s.top();
			s.pop();

			if (bvhnode->left->left == nullptr)
			{
				to_delete = bvhnode->left;
				bvhnode->left = bvhnode->left->right;
				delete to_delete;
			}

			if (bvhnode->left->right == nullptr)
			{
				to_delete = bvhnode->left;
				bvhnode->left = bvhnode->left->left;
				delete to_delete;
			}

			if (bvhnode->right->right == nullptr)
			{
				to_delete = bvhnode->right;
				bvhnode->right = bvhnode->right->left;
				delete to_delete;
			}

			if (bvhnode->right->left == nullptr)
			{
				to_delete = bvhnode->right;
				bvhnode->right = bvhnode->right->right;
				delete to_delete;
			}
		}
	}

	void
	BVH::dump (std::string _name)
	{
		/* queue entry */
		struct qe
		{
			BVHNode* bvhnode;
			unsigned int level;

			qe (BVHNode* _bvhnode, unsigned int _level)
			{
				bvhnode = _bvhnode;
				level = _level;
			}
		};

		std::stack<struct qe*> q;
		q.push(new qe(&root, 0));

		while (!q.empty())
		{
			struct qe* e = q.top();
			q.pop();

			BVHNode* bvhnode = e->bvhnode;
			unsigned int level = e->level;

			std::string indent(level*2, ' ');
			std::cout << indent 
			          << "* "
			          << (bvhnode->is_leaf ? std::to_string(bvhnode->right_idx - bvhnode->left_idx) : std::string(""))
			          << std::endl;

			if (bvhnode->left != nullptr)
				q.push(new qe(bvhnode->left, level+1));

			if (bvhnode->right != nullptr)
				q.push(new qe(bvhnode->right, level+1));
		}
	}
}

