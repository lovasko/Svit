#include "renderer/renderer.h"

namespace Svit
{
	float 
	Renderer::compute_normalized_coordinate (float _value, float _max_value)
	{
		return (((_value + 0.5f)/_max_value)*2.0f)-1.0f;
	}
}

