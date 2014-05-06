#ifndef SVIT_RAY_CASTING
#define SVIT_RAY_CASTING

#include "engine/engine.h"

namespace Svit
{
	class RayCastingEngine : public Engine
	{
		public:
			Vector3
			get_color (Ray& ray, World& _world);
	};
}

#endif

