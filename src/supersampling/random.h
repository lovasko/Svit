#ifndef SVIT_RANDOM_SUPERSAMPLING
#define SVIT_RANDOM_SUPERSAMPLING

#include "supersampling/supersampling.h"

#include <random>

namespace Svit
{
	class RandomSuperSampling : public SuperSampling
	{
		private:
			std::vector<Vector3> results;
			std::mt19937 generator;
			std::uniform_real_distribution<float> distribution;

		public:
			RandomSuperSampling (bool _adaptive);

			RandomSuperSampling (const RandomSuperSampling& other)
			{
				this->adaptive = other.adaptive;	
			}



			Vector2
			next_sample (int _x, int _y);

			void
			add_result (Vector3 _result);

			bool
			enough ();

			Vector3
			final_result ();

			SuperSampling*
			copy ()
			{
				RandomSuperSampling *c = new RandomSuperSampling(*this);
				return c;
			}
	};
}

#endif

