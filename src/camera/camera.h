#ifndef SVIT_CAMERA_CAMERA_H
#define SVIT_CAMERA_CAMERA_H

#include "geom/point.h"
#include "geom/ray.h"
#include "geom/rectangle.h"

namespace Svit
{
	class Camera
	{
		public:
			virtual Ray 
			get_ray (float _x, float _y) const = 0;
	};
}

#endif

