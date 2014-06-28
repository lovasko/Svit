#ifndef SVIT_GEOM_OPERATIONS
#define SVIT_GEOM_OPERATIONS

#include "geom/vector.h"
#include "geom/point.h"
#include "geom/matrix.h"

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
	operator/(const Vector<Scalar>& v, Scalar s)
	{
		return Vector<Scalar>(
			v.x / s,
			v.y / s,
			v.z / s,
			v.w / s);
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

	// TODO make this operation also with x86 optimizations
	template <typename Scalar> 
	Vector<Scalar> 
	operator*(const Vector<Scalar>& a, const Vector<Scalar>& b)
	{
		return Vector<Scalar>(
			a.x * b.x,
			a.y * b.y,
			a.z * b.z,
			a.w * b.w);
	}

	template <typename Scalar>
	Vector<Scalar>
	operator-(const Vector<Scalar>& a, const Vector<Scalar>& b)
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

	template <typename Scalar>
	Vector<Scalar>& 
	operator/=(Vector<Scalar>& v, Scalar s) 
	{
		v.x /= s;
		v.y /= s; 
		v.z /= s;
		v.w /= s;
		
		return v;
	}

	template <typename Scalar>
	Matrix<Scalar>
	operator* (Matrix<Scalar>& _a, Matrix<Scalar>& _b)
	{
		Scalar m[16];
		Matrix<Scalar> t = _b.transpose();

		m[0]  = _a.a%t.a; m[1]  = _a.a%t.b; m[2]  = _a.a%t.c; m[3]  = _a.a%t.d;
		m[4]  = _a.b%t.a; m[5]  = _a.b%t.b; m[6]  = _a.b%t.c; m[7]  = _a.b%t.d;
		m[8]  = _a.c%t.a; m[9]  = _a.c%t.b; m[10] = _a.c%t.c; m[11] = _a.c%t.d;
		m[12] = _a.d%t.a; m[13] = _a.d%t.b; m[14] = _a.d%t.c; m[15] = _a.d%t.d;

		return Matrix<Scalar>(
			Vector<Scalar>(m[0],  m[1],  m[2],  m[3]),
			Vector<Scalar>(m[4],  m[5],  m[6],  m[7]),
			Vector<Scalar>(m[8],  m[9],  m[10], m[11]),
			Vector<Scalar>(m[12], m[13], m[14], m[15]));
	}

	template <typename Scalar>
	Matrix<Scalar>
	operator* (Matrix<Scalar>& _matrix, Scalar _f)
	{
		return Matrix<Scalar>(
			_matrix.a * _f, 
			_matrix.b * _f, 
			_matrix.c * _f, 
			_matrix.d * _f);
	}

	template <typename Scalar>
	Vector<Scalar>
	operator* (Matrix<Scalar>& _matrix, Vector<Scalar>& _vector)
	{
		return Vector<Scalar>(
			_matrix.a % _vector,
			_matrix.b % _vector,
			_matrix.c % _vector,
			_matrix.d % _vector);
	}

	template <typename Scalar>
	Matrix<Scalar>
	operator! (Matrix<Scalar>& _m)
	{
		Scalar det = _m.determinant();
		if (det == 0.0f)
			return Matrix<Scalar>();

		Scalar m[16];
		m[0]  = _m.a.x; m[1]  = _m.a.y; m[2]  = _m.a.z; m[3]  = _m.a.w;
		m[4]  = _m.b.x; m[5]  = _m.b.y; m[6]  = _m.b.z; m[7]  = _m.b.w;
		m[8]  = _m.c.x; m[9]  = _m.c.y; m[10] = _m.c.z; m[11] = _m.c.w;
		m[12] = _m.d.x; m[13] = _m.d.y; m[14] = _m.d.z; m[15] = _m.d.w;

		Scalar result[16];
		result[0] = m[5]  * m[10] * m[15] -
		            m[5]  * m[11] * m[14] -
		            m[9]  * m[6]  * m[15] +
		            m[9]  * m[7]  * m[14] +
		            m[13] * m[6]  * m[11] -
		            m[13] * m[7]  * m[10];

		result[4] = -m[4]  * m[10] * m[15] +
		             m[4]  * m[11] * m[14] +
		             m[8]  * m[6]  * m[15] -
		             m[8]  * m[7]  * m[14] -
		             m[12] * m[6]  * m[11] +
		             m[12] * m[7]  * m[10];

		result[8] = m[4]  * m[9]  * m[15] -
		            m[4]  * m[11] * m[13] -
		            m[8]  * m[5]  * m[15] +
		            m[8]  * m[7]  * m[13] +
		            m[12] * m[5]  * m[11] -
		            m[12] * m[7]  * m[9];

		result[12] = -m[4]  * m[9]  * m[14] +
		              m[4]  * m[10] * m[13] +
		              m[8]  * m[5]  * m[14] -
		              m[8]  * m[6]  * m[13] -
		              m[12] * m[5]  * m[10] +
		              m[12] * m[6]  * m[9];

		result[1] = -m[1]  * m[10] * m[15] +
		             m[1]  * m[11] * m[14] +
		             m[9]  * m[2]  * m[15] -
		             m[9]  * m[3]  * m[14] -
		             m[13] * m[2]  * m[11] +
		             m[13] * m[3]  * m[10];

		result[5] = m[0]  * m[10] * m[15] -
		            m[0]  * m[11] * m[14] -
		            m[8]  * m[2]  * m[15] +
		            m[8]  * m[3]  * m[14] +
		            m[12] * m[2]  * m[11] -
		            m[12] * m[3]  * m[10];

		result[9] = -m[0]  * m[9]  * m[15] +
		             m[0]  * m[11] * m[13] +
		             m[8]  * m[1]  * m[15] -
		             m[8]  * m[3]  * m[13] -
		             m[12] * m[1]  * m[11] +
		             m[12] * m[3]  * m[9];

		result[13] = m[0]  * m[9]  * m[14] -
		             m[0]  * m[10] * m[13] -
		             m[8]  * m[1]  * m[14] +
		             m[8]  * m[2]  * m[13] +
		             m[12] * m[1]  * m[10] -
		             m[12] * m[2]  * m[9];

		result[2] = m[1]  * m[6] * m[15] -
		            m[1]  * m[7] * m[14] -
		            m[5]  * m[2] * m[15] +
		            m[5]  * m[3] * m[14] +
		            m[13] * m[2] * m[7] -
		            m[13] * m[3] * m[6];

		result[6] = -m[0] *  m[6] * m[15] +
		             m[0] *  m[7] * m[14] +
		             m[4] *  m[2] * m[15] -
		             m[4] *  m[3] * m[14] -
		             m[12] * m[2] * m[7] +
		             m[12] * m[3] * m[6];

		result[10] = m[0]  * m[5] * m[15] -
		             m[0]  * m[7] * m[13] -
		             m[4]  * m[1] * m[15] +
		             m[4]  * m[3] * m[13] +
		             m[12] * m[1] * m[7] -
		             m[12] * m[3] * m[5];

		result[14] = -m[0] *  m[5] * m[14] +
		              m[0] *  m[6] * m[13] +
		              m[4] *  m[1] * m[14] -
		              m[4] *  m[2] * m[13] -
		              m[12] * m[1] * m[6] +
		              m[12] * m[2] * m[5];

		result[3] = -m[1] * m[6] * m[11] +
		             m[1] * m[7] * m[10] +
		             m[5] * m[2] * m[11] -
		             m[5] * m[3] * m[10] -
		             m[9] * m[2] * m[7] +
		             m[9] * m[3] * m[6];

		result[7] = m[0] * m[6] * m[11] -
		            m[0] * m[7] * m[10] -
		            m[4] * m[2] * m[11] +
		            m[4] * m[3] * m[10] +
		            m[8] * m[2] * m[7] -
		            m[8] * m[3] * m[6];

		result[11] = -m[0] * m[5] * m[11] +
		              m[0] * m[7] * m[9] +
		              m[4] * m[1] * m[11] -
		              m[4] * m[3] * m[9] -
		              m[8] * m[1] * m[7] +
		              m[8] * m[3] * m[5];

		result[15] = m[0] * m[5] * m[10] -
		             m[0] * m[6] * m[9] -
		             m[4] * m[1] * m[10] +
		             m[4] * m[2] * m[9] +
		             m[8] * m[1] * m[6] -
		             m[8] * m[2] * m[5];

		Matrix<Scalar> helper(
			Vector<Scalar>(result[0],  result[1],  result[2],  result[3]),
			Vector<Scalar>(result[4],  result[5],  result[6],  result[7]),
			Vector<Scalar>(result[8],  result[9],  result[10], result[11]),
			Vector<Scalar>(result[12], result[13], result[14], result[15]));

		return helper * (1.0f/det);
	}

}

#endif

