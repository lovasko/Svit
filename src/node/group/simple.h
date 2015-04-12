#ifndef SVIT_SIMPLE_GROUP
#define SVIT_SIMPLE_GROUP

#include "node/group/group.h"
#include "geom/ray.h"

#include <list>

namespace Svit
{
	class SimpleGroup : public Group
	{
		private:
			std::list<Node*> nodes;

		public:
			bool
			intersect (Ray& _ray, Intersection& _isect) const override;

			void
			dump (std::string _name, unsigned int _level = 0) const override;

			void
			add (Node* _node) override;

			void
			finish () override;
	};
}

#endif

