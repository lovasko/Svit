
namespace Svit
{
	Vector2
	ZeroSuperSampling::next_sample (int _x, int _y) override;

	void
	ZeroSuperSampling::add_result (Vector3 _result) override; 

	bool
	ZeroSuperSampling::enough () override;

	Vector3 
	ZeroSuperSampling::final_result () override;

	SuperSampling*
	ZeroSuperSampling::copy () override;
}

