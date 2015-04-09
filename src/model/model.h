#ifndef SVIT_MODEL_MODEL_H
#define SVIT_MODEL_MODEL_H

#include <list>
#include <string>

#include "node/group/group.h"
#include "node/solid/solid.h"

namespace Svit
{
	class Model
	{
		public:
			std::list<Solid*> solids;

			virtual bool
			load (std::string _filename) = 0;

			virtual void
			add_to_group (Group& _group) const;
	};
}

#endif

