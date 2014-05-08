#ifndef SVIT_POINT_LIGHT
#define SVIT_POINT_LIGHT

#include "light/light.h"
#include "geom/point.h"

namespace Svit
{
	class PointLight : public Light
	{
		private:
			Point3 position;
			Vector3 color;

		public:
			PointLight(Point3 _position, Vector3 _color);
			
		 	LightHit 
			get_light_hit (Point3 _point);

			Vector3
			get_intensity (LightHit _hit);
	};
}

#endif

