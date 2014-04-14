#ifndef SVIT_RAY
#define SVIT_RAY

#include <Eigen/Core>

using namespace Eigen;

namespace Svit
{
	class Ray
	{
		private:
			Vector3d _origin;
			Vector3d _direction;

		public:
			Ray (Vector3d& origin, Vector3d& direction);
			Vector3d operator() (float time);
	};
}

#endif

