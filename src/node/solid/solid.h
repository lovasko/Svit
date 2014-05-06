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
			/*
			void 
			add_intersection (float _t, Point3 _point, Solid *who)
			{
				Intersection i;
				i.t = _t;
				i.node = who;
				i.point = _point;

				result.push_back(i);
			}
			*/

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

