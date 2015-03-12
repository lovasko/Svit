#ifndef SVIT_GEOM_OPTIMIZATION_X86_GENERAL_H
#define SVIT_GEOM_OPTIMIZATION_X86_GENERAL_H

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

