#ifndef SVIT_MODEL
#define SVIT_MODEL

#include "node/solid/solid.h"
#include "node/group/group.h"

#include <string>

namespace Svit
{
	class Model
	{
		public:
			std::list<Solid*> solids;

			virtual bool
			load (std::string _filename) = 0;

			virtual void
			add_to_group (Group& group);
	};
}

#endif

