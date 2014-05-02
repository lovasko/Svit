#ifndef SVIT_PERSPECTIVE_CAMERA
#define SVIT_PERSPECTIVE_CAMERA

#include "camera/camera.h"
#include "geom/vector.h"
#include "geom/point.h"
#include "geom/rect.h"
#include "geom/operations.h"

#include <cmath>

namespace Svit
{
	class PerspectiveCamera : public Camera
	{
		private:
			Point3 position;
			Vector3 forward;
			Vector3 up;
			Vector3 grid_width;
			Vector3 grid_height;
			float horizontal_angle;
			float aspect_ratio;

			void 
			recompute ();

		public:
			PerspectiveCamera (Point3 _position, Vector3 _forward, Vector3 _up, 
			    float _aspect_ratio, float _horizontal_angle);

			Ray
			get_ray (float _x, float _y);

			void
			look_at (Point3 _dest);
	};
}

#endif

