#ifndef SVIT_GROUP
#define SVIT_GROUP

#include "node/node.h"

namespace Svit
{
	class Group : public Node
	{
		public:
			virtual void
			add (Node *_node) = 0;

			virtual void
			finish () = 0;
	};
}

#endif

