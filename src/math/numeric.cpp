#include "math/numeric.h"

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
}

