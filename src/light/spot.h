#ifndef SVIT_SPOT_LIGHT
#define SVIT_SPOT_LIGHT

#include "light/light.h"
#include "geom/vector.h"
#include "geom/point.h"

#include <cmath>

namespace Svit
{
	class SpotLight : public Light
	{
		private:
			Point3 position;
			Vector3 direction;
			Vector3 color;
			float angle;
			float exp;

		public:
			SpotLight (Point3 _position, Vector3 _direction, Vector3 _color,
			    float _angle, float _exp);
			
		 	LightHit 
			get_light_hit (Point3 _point);

			Vector3
			get_intensity (LightHit _hit);
	};
}

#endif

