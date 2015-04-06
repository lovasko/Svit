#ifndef SVIT_ZERO_SUPERSAMPLING
#define SVIT_ZERO_SUPERSAMPLING

namespace Svit
{
	class ZeroSuperSampling : public SuperSampling
	{
		public:
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

