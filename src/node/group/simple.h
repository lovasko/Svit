#ifndef SVIT_SIMPLE_GROUP
#define SVIT_SIMPLE_GROUP

#include "node/group/group.h"
#include "geom/ray.h"
#include "node/intersection.h"

#include <list>

namespace Svit
{
	class SimpleGroup : public Group
	{
		private:
			std::list<Node*> nodes;

		public:
			std::list<Intersection>
			intersect (Ray& _ray);

			void
			add (Node& _node);
	};
}

#endif

