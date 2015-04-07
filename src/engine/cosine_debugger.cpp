#include <cmath>
#include <numeric>

#include "engine/cosine_debugger.h"

namespace Svit
{
	Vector3
	CosineDebuggerEngine::get_color (Ray& _ray, World& _world)
	{
		Intersection isect;
		isect.t = std::numeric_limits<float>::max();

		if (_world.scene->intersect(_ray, isect))
		{
			isect.solid->complete_intersection(&isect);
			float angle = (~_ray.direction) % (~(isect.normal));
			float color_value = fabs(angle); 
			return Vector3(color_value, color_value, color_value);
		}
		else
			return Vector3();
	}
}

