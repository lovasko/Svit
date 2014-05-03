#ifndef SVIT_BSPLINE
#define SVIT_BSPLINE

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

