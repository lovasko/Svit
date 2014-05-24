#ifndef SVIT_AMBIENT_LIGHT
#define SVIT_AMBIENT_LIGHT

#include "light/light.h"
#include "geom/vector.h"

namespace Svit
{
	class AmbientLight : public Light
	{
		private:
			Vector3 color;

		public:
			AmbientLight (Vector3 _color);

		 	LightHit 
			get_light_hit (Point3 _point);

			Vector3
			get_intensity (LightHit _hit);
	};
}

#endif

