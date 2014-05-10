#ifndef SVIT_BSPLINE_TRAJECTORY
#define SVIT_BSPLINE_TRAJECTORY

#include "trajectory/trajectory.h"

namespace Svit
{
	class BSplineTrajectory : public Trajectory
	{
		public:
			BSplineTrajectory (bool _closed);

			Point3
			evaluate (float _t);
	};
}

#endif

