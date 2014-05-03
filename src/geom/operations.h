// TODO rename this file to ops.h
#ifndef SVIT_GEOM_OPERATIONS
#define SVIT_GEOM_OPERATIONS

#include "geom/vector.h"
#include "geom/point.h"

#include <cmath>

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
			v.x * s,
			v.y * s,
			v.z * s,
			v.w * s);
	}

	template <typename Scalar> 
	Vector<Scalar> 
	operator*(Scalar s, const Vector<Scalar>& v)
	{
		return Vector<Scalar>(
			v.x * s,
			v.y * s,
			v.z * s,
			v.w * s);
	}

	template <typename Scalar> 
	Point<Scalar> 
	operator+(const Point<Scalar>& p, const Vector<Scalar>& v)
	{
		return Point<Scalar>(
			p.x + v.x,
			p.y + v.y,
			p.z + v.z,
			p.w + v.w);
	}

	template <typename Scalar>
	Vector<Scalar>
	operator-(const Point<Scalar>& a, const Point<Scalar>& b)
	{
		return Vector<Scalar>(
			a.x - b.x, 
			a.y - b.y, 
			a.z - b.z, 
			a.w - b.w);
	}

	template <typename Scalar>
	Vector<Scalar>
	operator&(const Vector<Scalar>& a, const Vector<Scalar>& b)
	{
		double new_x;
		double new_y;
		double new_z;

		new_x = a.y * b.z - a.z * b.y;  
		new_y = a.z * b.x - a.x * b.z; 
		new_z = a.x * b.y - a.y * b.x; 

		return Vector<Scalar>(new_x, new_y, new_z, 0.0);
	}

	template <typename Scalar>
	Scalar
	operator%(const Vector<Scalar>& a, const Vector<Scalar>& b)
	{
		return a.x * b.x
		     + a.y * b.y
		     + a.z * b.z
		     + a.w * b.w;
	}

	template <typename Scalar>
	Vector<Scalar>
	operator!(const Vector<Scalar>& a)
	{
		return Vector<Scalar>(-a.x, -a.y, -a.z, -a.w);
	}

	template <typename Scalar>
	Vector<Scalar>
	operator~(const Vector<Scalar>& a)
	{
		float length = sqrt(a % a);
		return Vector<Scalar>(a.x/length, a.y/length, a.z/length, a.w/length);
	}

	template <typename Scalar>
	Vector<Scalar>& 
	operator+=(Vector<Scalar>& a, const Vector<Scalar>& b) 
	{
		a.x += b.x; 
		a.y += b.y; 
		a.z += b.z;
		a.w += b.w;

		return a;
	}

	#ifdef __SSE__
		#include "geom/optimization/x86/operations.h"
	#endif
}

#endif

