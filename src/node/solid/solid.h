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
			std::list<Intersection> result;

			void 
			add_intersection (float _t, Point3 _point, Solid *who)
			{
				Intersection i;
				i.t = _t;
				i.node = who;
				i.point = _point;

				result.push_back(i);
			}

			std::list<Intersection>
			fail ()
			{
				result.clear();
				return result;
			}

			void
			complete_intersection(Intersection *_intersection) 
			{ 
				std::cout << "aspon ze takto" << std::endl;
			}
	};
}

#endif

