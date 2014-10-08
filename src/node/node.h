#ifndef SVIT_NODE
#define SVIT_NODE

#include "geom/ray.h"
#include "geom/bounding_box.h"
#include "material/material.h"

#include <list>
#include <iostream>
#include <boost/optional.hpp>

namespace Svit
{
	struct Intersection;

	class Node
	{
		public:
			BoundingBox bounding_box;

			virtual void
			set_material (std::unique_ptr<Material> _material) = 0;

			virtual boost::optional<Intersection>
			intersect (Ray& _ray, float _best) = 0;
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

