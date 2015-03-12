#ifndef SVIT_RENDERER_RENDERER_H
#define SVIT_RENDERER_RENDERER_H

#include "engine/engine.h"
#include "image/image.h"
#include "renderer/settings.h"
#include "supersampling/supersampling.h"
#include "world/world.h"

namespace Svit
{
	class Renderer
	{
		public:
			virtual Image
			render (World& _world, Settings& _settings, Engine& _engine,
			SuperSampling& _super_sampling) = 0;

			float 
			compute_normalized_coordinate (float _value, float _max_value);
	};
}

#endif

