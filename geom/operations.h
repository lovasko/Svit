#ifndef SVIT_GEOM_OPERATIONS
#define SVIT_GEOM_OPERATIONS

#include "vector.h"
#include "point.h"

namespace Svit
{
	template <typename Scalar> 
	Vector<Scalar> 
	operator+(const Vector<Scalar>& a, const Vector<Scalar>& b)
	{
		return Vector<Scalar>(
			a.x + b.x,
			a.y + b.y,
			a.z + b.z,
			a.w + b.w);
	}

	template <typename Scalar> 
	Vector<Scalar> 
	operator*(const Vector<Scalar>& v, Scalar s)
	{
		return Vector<Scalar>(
			v._x * s,
			v._y * s,
			v._z * s,
			v._w * s);
	}

	template <typename Scalar> 
	Vector<Scalar> 
	operator*(Scalar s, const Vector<Scalar>& v)
	{
		return Vector<Scalar>(
			v._x * s,
			v._y * s,
			v._z * s,
			v._w * s);
	}

	template <typename Scalar> 
	Point<Scalar> 
	operator+(const Point<Scalar>& p, const Vector<Scalar>& v)
	{
		return Point<Scalar>(
			p._x + v._x,
			p._y + v._y,
			p._z + v._z,
			p._w + v._w);
	}
}

#endif

