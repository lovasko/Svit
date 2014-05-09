#ifndef SVIT_MATH_NUMERIC
#define SVIT_MATH_NUMERIC

#include <cmath>

namespace Svit
{
	void
	decompose_float (float _float, int *_integral, float *_fractional, 
	    bool _abs = true);
}

#endif

