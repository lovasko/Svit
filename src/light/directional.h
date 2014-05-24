#ifndef SVIT_DIRECTIONAL_LIGHT
#define SVIT_DIRECTIONAL_LIGHT

#include "light/light.h"
#include "geom/vector.h"

namespace Svit
{
	class DirectionalLight : public Light
	{
		private:
			Vector3 norm_neg_direction;
			Vector3 color;

		public:
			DirectionalLight (Vector3 _direction, Vector3 _color);

		 	LightHit 
			get_light_hit (Point3 _point);

			Vector3
			get_intensity (LightHit _hit);
	};
}

#endif

