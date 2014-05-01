#ifndef SVIT_RENDERER
#define SVIT_RENDERER

#include "image/image.h"
#include "world/world.h"
#include "engine/engine.h"
#include "renderer/settings.h"

// TODO write move constructor 

namespace Svit
{
	class Renderer
	{
		public:
			virtual Image
			render (World& _world, Settings& _settings, Engine& _engine) = 0;

			float 
			compute_normalized_coordinate (int value, int max_value)
			{
				return ((((float)value + 0.5f)/(float)max_value)*2.0f)-1.0f;
			}
	};
}

#endif

