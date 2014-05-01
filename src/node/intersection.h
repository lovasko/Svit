#ifndef SVIT_INTERSECTION
#define SVIT_INTERSECTION

#include "node/node.h"
#include "geom/vector.h"
#include "geom/point.h"

#include <iostream>
#include <iomanip>

namespace Svit
{
	struct Intersection
	{
		Node *node;	
		float t;
		Vector3 normal;
		Point3 point;

		void
		dump (const char *name, unsigned int level = 0)
		{
			std::string indentation(level*2, ' ');
			std::cout << indentation << name << " = Intersection (t = " << t << ")"
			    << std::endl;
			normal.dump("normal", level+1);
			point.dump("point", level+1);
		}

		// TODO add cast to bool to enable put Intersection into "if ()"
	};
}

#endif

