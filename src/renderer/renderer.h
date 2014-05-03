#ifndef SVIT_RENDERER
#define SVIT_RENDERER

#include "image/image.h"
#include "world/world.h"
#include "engine/engine.h"
#include "renderer/settings.h"
#include "supersampling/supersampling.h"

namespace Svit
{
	class Renderer
	{
		public:
			virtual Image
			render (World& _world, Settings& _settings, Engine& _engine,
			SuperSampling& _super_sampling) = 0;

			float 
			compute_normalized_coordinate (float value, float max_value)
			{
				return (((value + 0.5f)/max_value)*2.0f)-1.0f;
			}
	};
}

#endif

