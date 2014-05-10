#include "math/numeric.h"

#include <limits>

namespace Svit
{
	void
	decompose_float (float _float, int *_integral, float *_fractional, 
	    bool _abs)
	{
		float fractional;	
		float integral;

		fractional = modff(_float, &integral);			
		
		if (_abs)
			fractional = fabs(fractional);

		*_integral = (int)floor(_float);
		*_fractional = fractional;
	}

	bool
	around_zero (float _float)
	{
		if (_float > 0.0 && _float < std::numeric_limits<float>::epsilon())
			return true;
		else
			return false;
	}
}

