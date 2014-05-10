#include "supersampling/random.h"

namespace Svit
{
	RandomSuperSampling::RandomSuperSampling (bool _adaptive)
	{
		adaptive = _adaptive;
		std::random_device rd;
		generator.seed(rd());
	}

	Vector2
	RandomSuperSampling::next_sample (int _x, int _y)
	{
		(void) _x;
		(void) _y;

		float x = 0.5f - distribution(generator);
		float y = 0.5f - distribution(generator);

		return Vector2(x, y);
	}

	void
	RandomSuperSampling::add_result (Vector3 _result)
	{
		results.push_back(_result);	
	}

	bool
	RandomSuperSampling::enough ()
	{
		return false;	
	}

	Vector3	
	RandomSuperSampling::final_result ()
	{
		Vector3 result;

		for (unsigned int i = 0; i < results.size(); i++)
		{
			result += results[i];
		}
		result /= (float)results.size();

		results.clear();
		return result;
	}
}

