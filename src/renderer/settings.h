#ifndef SVIT_ENGINE_SETTINGS
#define SVIT_ENGINE_SETTINGS

#include "geom/vector.h"
#include "geom/rect.h"

namespace Svit
{
	struct Settings
	{
		Rectangle whole_area;
		Rectangle area;
		Vector2i tile_size;
		unsigned int max_thread_count;
		unsigned int sample_count;
	};
}

#endif

