#ifndef SVIT_ENGINE_COSINE_DEBUGGER_H
#define SVIT_ENGINE_COSINE_DEBUGGER_H

#include "engine/engine.h"

namespace Svit
{
	class CosineDebuggerEngine : public Engine
	{
		public:
			Vector3
			get_color (Ray& _ray, World& _world) const override;
	};
}

#endif

