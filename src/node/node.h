#ifndef SVIT_NODE
#define SVIT_NODE

#include "geom/ray.h"

#include <list>
#include <iostream>

namespace Svit
{
	class Intersection;

	class Node
	{
		public:
			virtual std::list<Intersection>
			intersect (Ray& _ray) = 0;

			// TODO = 0;
			virtual void
			complete_intersection(Intersection *_intersection) 
			{ 
				std::cout << "toto by sa nemalo stat" << std::endl;
			}
	};
}

#endif

