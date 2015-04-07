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
			intersect (Ray& _ray, Intersection& _isect);

			void
			add (Node* _node);

			void
			finish () { }
	};
}

#endif

