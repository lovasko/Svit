#ifndef SVIT_SOLID
#define SVIT_SOLID

#include "node/node.h"

namespace Svit
{
	class Solid : public Node
	{
		public:
			virtual void
			complete_intersection (Intersection& _isect) const = 0;
	};
}

#endif

