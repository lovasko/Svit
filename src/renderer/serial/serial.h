#ifndef SVIT_RENDERER_SERIAL_SERIAL_H
#define SVIT_RENDERER_SERIAL_SERIAL_H

#include "engine/engine.h"
#include "image/image.h"
#include "renderer/renderer.h"
#include "renderer/settings.h"
#include "world/world.h"

namespace Svit
{
	class SerialRenderer : public Renderer
	{
		public:
			Image
			render (World& _world,
			        Settings& _settings,
			        Engine& _engine,
			        SuperSampling& _super_sampling) const override;
	};
}

#endif

