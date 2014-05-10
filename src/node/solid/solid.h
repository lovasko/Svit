#ifndef SVIT_SOLID
#define SVIT_SOLID

#include "node/node.h"
#include "node/intersection.h"

#include <list>

namespace Svit
{
	class Solid : public Node
	{
		public:
			std::list<Intersection>
			fail ()
			{
				std::list<Intersection> empty;
				return empty;
			}

			// TODO virtual!
			void
			complete_intersection(Intersection *_intersection) 
			{ 
				std::cout << "aspon ze takto" << std::endl;
			}
	};
}

#endif

