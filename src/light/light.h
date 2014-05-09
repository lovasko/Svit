#ifndef SVIT_LIGHT
#define SVIT_LIGHT

#include "geom/vector.h"
#include "geom/point.h"

namespace Svit
{
	struct LightHit
	{
		Vector3 direction;
		float distance;
	};

	class Light 
	{
		public:
			virtual LightHit 
			get_light_hit (Point3 _point) = 0;

			virtual Vector3
			get_intensity (LightHit _hit) = 0;
	};
}

#endif

