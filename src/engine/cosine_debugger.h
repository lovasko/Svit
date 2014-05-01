#ifndef SVIT_COSINE_DEBUGGER_ENGINE
#define SVIT_COSINE_DEBUGGER_ENGINE

#include "engine/engine.h"

#include <list>

namespace Svit
{
	class CosineDebuggerEngine : public Engine
	{
		public:
			CosineDebuggerEngine () { }

			RGB
			get_color (Ray& _ray, World& _world);
	};
}

#endif

