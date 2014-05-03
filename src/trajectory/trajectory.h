#ifndef SVIT_TRAJECTORY
#define SVIT_TRAJECTORY

#include "geom/point.h"

#include <vector>

namespace Svit
{
	class Trajectory
	{
		public:
			std::vector<Point3> points;
			bool closed;

			virtual Point3
			evaluate (float _t) = 0;

			void
			add_point (Point3 _point)
			{
				points.push_back(_point);
			}

			Point3&
			get_point (int _index)
			{
				int index = _index;

				if (index > points.size() - 1)
					index = index % points.size();

				if (index < 0)
					index = points.size() - 1 + ((index+1) % points.size());

				return points[index];
			}
	};
}

#endif

