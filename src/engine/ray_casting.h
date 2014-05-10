#ifndef SVIT_RAY_CASTING_ENGINE
#define SVIT_RAY_CASTING_ENGINE

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

