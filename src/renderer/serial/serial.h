#ifndef SVIT_SERIAL_RENDERER
#define SVIT_SERIAL_RENDERER

#include "renderer/renderer.h"
#include "image/image.h"
#include "world/world.h"
#include "engine/engine.h"
#include "renderer/settings.h"

namespace Svit
{
	class SerialRenderer : public Renderer
	{
		public:
			Image
			render (World& _world, Settings& _settings, Engine& _engine);
	};
}

#endif

