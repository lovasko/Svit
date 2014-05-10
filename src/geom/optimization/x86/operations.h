#ifndef SVIT_X86_OPERATIONS
#define SVIT_X86_OPERATIONS

#include "geom/optimization/x86/general.h"
#include "geom/optimization/x86/vector.h"

namespace Svit
{
	inline Vector<float> 
	operator+(const Vector<float>& a, const Vector<float>& b)
	{
		return Vector<float>(_mm_add_ps(a.v, b.v));
	}

	inline Vector<float> 
	operator*(const Vector<float>& v, float s)
	{
		return Vector<float>(_mm_mul_ps(v.v, _mm_set1_ps(s)));
	}

	inline Vector<float> 
	operator*(float s, const Vector<float>& v)
	{
		return Vector<float>(_mm_mul_ps(v.v, _mm_set1_ps(s)));
	}

	inline Vector<float>
	operator-(const Vector<float>& a, const Vector<float>& b)
	{
		return Vector<float>(_mm_sub_ps(a.v, b.v));
	}

	inline Vector<float>
	operator&(const Vector<float>& a, const Vector<float>& b)
	{
		__m128 t1 = _mm_shuffle_ps(a.v, a.v, 0xc9);
		__m128 t2 = _mm_shuffle_ps(a.v, a.v, 0xd2);
		__m128 t3 = _mm_shuffle_ps(b.v, b.v, 0xd2);
		__m128 t4 = _mm_shuffle_ps(b.v, b.v, 0xc9);
		__m128 t5 = _mm_mul_ps(t1, t3);
		__m128 t6 = _mm_mul_ps(t2, t4);

		return Vector<float>(_mm_sub_ps(t5, t6));
	}

	inline float
	operator%(const Vector<float>& a, const Vector<float>& b)
	{
		#if defined(__SSE4_1__)
			__m128 dp = _mm_dp_ps(a.v, b.v, 0xff);
		#elif defined(__SSE3__)
			__m128 t1 = _mm_mul_ps(a.v, b.v);
			__m128 t2 = _mm_hadd_ps(t1, t1);
			__m128 dp = _mm_hadd_ps(t2, t2);
		#else
			__m128 t1 = _mm_mul_ps(a.v, b.v);
			__m128 t2 = _mm_shuffle_ps(t1, t1, 0x93);
			__m128 t3 = _mm_add_ps(t1, t2);
			__m128 t4 = _mm_shuffle_ps(t3, t3, 0x4e);
			__m128 dp = _mm_add_ps(t3, t4);
		#endif

		float result[4];
		_mm_store_ps(result, dp);

		return result[0];
	}

	inline Vector<float>
	operator!(const Vector<float>& v)
	{
		// TODO optimization: the _mm -1.0f can be prepared before for all calls
		return Vector<float>(_mm_mul_ps(v.v, _mm_set1_ps(1.0f)));
	}

	inline Vector<float>
	operator~(const Vector<float>& v)
	{
		__m128 dot = _mm_set1_ps(v % v);
		return Vector<float>(_mm_div_ps(v.v, _mm_sqrt_ps(dot)));
	}
}

#endif

