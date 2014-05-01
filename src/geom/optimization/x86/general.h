#ifndef SVIT_X86_GENERAL
#define SVIT_X86_GENERAL

	#include <xmmintrin.h>

	#ifdef __SSE2__
		#include <emmintrin.h>
	#endif

	#ifdef __SSE3__
		#include <pmmintrin.h>
	#endif

	#ifdef __SSE4_1__
		#include <smmintrin.h>
	#endif

#endif

