#ifndef SVIT_MATH
#define SVIT_MATH

#include "geom/vector.h"

namespace Svit
{
	template <typename Scalar>
	Vector<Scalar>
	lerp_1D (Vector<Scalar>& _a, Vector<Scalar>& _b, Scalar _v)
	{
		return (_a + ((_b - _a) * _v));	
	}

	template <typename Scalar>
	Scalar
	lerp_1D (Scalar _a, Scalar _b, Scalar _v)
	{
		return (_a + ((_b - _a) * _v));	
	}

	template <typename Scalar>
	Scalar
	lerp_3D (Scalar _w000, Scalar _w100, Scalar _w010, Scalar _w110,
	    Scalar _w001, Scalar _w101, Scalar _w011, Scalar _w111,
	    Scalar _xv, Scalar _yv, Scalar _zv) 
	{
		Scalar w00 = lerp_1D<Scalar>(_w000, _w100, _xv);
		Scalar w01 = lerp_1D<Scalar>(_w001, _w101, _xv);
		Scalar w10 = lerp_1D<Scalar>(_w010, _w110, _xv);
		Scalar w11 = lerp_1D<Scalar>(_w011, _w111, _xv);

		Scalar w0 = lerp_1D<Scalar>(w00, w10, _yv);
		Scalar w1 = lerp_1D<Scalar>(w01, w11, _yv);

		Scalar result = lerp_1D<Scalar>(w0, w1, _zv);
		return result;
	}
}

#endif

