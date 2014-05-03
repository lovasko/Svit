#include "bspline.h"

#include <assert.h>
#include <cmath>

#define ONE_SIXTH (1.0f/6.0f)

namespace Svit
{
	BSplineTrajectory::BSplineTrajectory (bool _closed)
	{
		closed = _closed;	
	}

	Point3
	BSplineTrajectory::evaluate (float _t)
	{
		assert(!(points.size() < 2 || !closed && points.size() < 4));
		float t = _t;
		float nu, uu;
		float coef;
		Point3 p;
		Point3 result;

		int base = std::floor(t);
		t -= (float)base;

		if (closed) 
			base--;

		p = get_point(base); 
		nu = 1.0f - t;
		coef = ONE_SIXTH * nu * nu * nu;
		for (int i = 0; i < 3; i++)
			result[i] = coef * p[i];

		p = get_point(base+1);
		uu = t * t;
		coef = ONE_SIXTH * (3.0f * uu * (t - 2.0f) + 4.0f);
		for (int i = 0; i < 3; i++)
			result[i] += coef * p[i];

		p = get_point(base+2);
		coef = ONE_SIXTH * (3.0f * t * (t * nu + 1.0f) + 1.0f);
		for (int i = 0; i < 3; i++)
			result[i] += coef * p[i];

		p = get_point(base+3);
		coef = ONE_SIXTH * uu * t;
		for (int i = 0; i < 3; i++)
			result[i] += coef * p[i];

		return result;
	}
}

