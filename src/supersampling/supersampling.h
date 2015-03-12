#ifndef SVIT_SUPERSAMPLING
#define SVIT_SUPERSAMPLING

#include "geom/vector.h"
	
namespace Svit
{
	class SuperSampling
	{
		public:
			unsigned int sample_count;
			bool adaptive;

			virtual Vector2
			next_sample (int _x, int _y) = 0;

			virtual void
			add_result (Vector3 _result) = 0;

			virtual bool
			enough () = 0;

			virtual Vector3 
			final_result () = 0;

			virtual SuperSampling*
			copy () = 0;
	};
}

#endif

