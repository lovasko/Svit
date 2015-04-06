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
			next_sample (int _x, int _y) override;

			void
			add_result (Vector3 _result) override;

			bool
			enough () override;

			Vector3
			final_result () override;

			SuperSampling*
			copy () override;
	};
}

#endif

