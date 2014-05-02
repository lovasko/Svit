#ifndef SVIT_GROUP
#define SVIT_GROUP

#include "node/node.h"
#include "node/intersection.h"

namespace Svit
{
	class Group : public Node
	{
		public:
			std::list<Intersection> result;

			virtual void
			add (Node& _node) = 0;

			void
			complete_intersection (Intersection *_intersection)
			{ }
	};
}

#endif
