#ifndef SVIT_NODE
#define SVIT_NODE

#include "geom/ray.h"
#include "material/material.h"

#include <list>
#include <iostream>

namespace Svit
{
	struct Intersection;

	class Node
	{
		public:
			virtual void
			set_material (std::unique_ptr<Material> _material) = 0;

			virtual std::list<Intersection>
			intersect (Ray& _ray) = 0;

			// TODO = 0;
			virtual void
			complete_intersection(Intersection *_intersection) 
			{ 
				std::cout << "toto by sa nemalo stat" << std::endl;
			}
	};

	class Solid;

	struct Intersection
	{
		Solid *node;	
		float t;
		Vector3 normal;
		Point3 point;
	};
}

#endif

