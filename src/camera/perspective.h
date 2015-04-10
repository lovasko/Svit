#ifndef SVIT_CAMERA_PERSPECTIVE_H
#define SVIT_CAMERA_PERSPECTIVE_H

#include "camera/camera.h"
#include "geom/point.h"
#include "geom/rectangle.h"
#include "geom/vector.h"

namespace Svit
{
	class PerspectiveCamera : public Camera
	{
		private:
			Vector3 grid_width;
			Vector3 grid_height;
			float horizontal_angle;
			float aspect_ratio;

			void 
			recompute ();

		public:
			Point3 position;
			Vector3 up;
			Vector3 forward;

			PerspectiveCamera (Point3 _position,
			                   Vector3 _forward,
			                   Vector3 _up,
			                   float _aspect_ratio,
			                   float _horizontal_angle);

			Ray
			get_ray (float _x, float _y) const override;
	};
}

#endif

