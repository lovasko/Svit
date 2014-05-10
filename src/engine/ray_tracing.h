#ifndef SVIT_RAY_TRACING_ENGINE
#define SVIT_RAY_TRACING_ENGINE

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

