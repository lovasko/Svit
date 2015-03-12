#ifndef SVIT_RENDERER_SETTINGS_H
#define SVIT_RENDERER_SETTINGS_H

#include "geom/rectangle.h"
#include "geom/vector.h"

namespace Svit
{
	class Settings
	{
		public:
			Rectangle whole_area;
			Rectangle area;
			Vector2i tile_size;
			unsigned int max_thread_count;
			unsigned int max_sample_count;
			unsigned int adaptive_sample_step;

			void
			dump (const char* _name, unsigned int _level = 0);
	};
}

#endif

