#ifndef SVIT_MATERIAL
#define SVIT_MATERIAL

#include "geom/vector.h"
#include "geom/point.h"

namespace Svit
{
	class Material
	{
		public:
			virtual Vector3
			get_reflectance (Point3 _point, Vector3 _normal, Vector3 _in, 
			    Vector3 _out) = 0;
	};
}

#endif

