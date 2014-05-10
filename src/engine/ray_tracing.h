#ifndef SVIT_ENGINE_RAY_TRACING
#define SVIT_ENGINE_RAY_TRACING

#include "engine/engine.h"

namespace Svit
{
	class RayTracingEngine : public Engine
	{
		public:
			Vector3
			get_color (Ray& ray, World& _world);
	};
}

#endif

