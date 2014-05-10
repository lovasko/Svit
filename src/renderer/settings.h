#ifndef SVIT_SETTINGS
#define SVIT_SETTINGS

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
		unsigned int max_sample_count;
		unsigned int adaptive_sample_step;

		void
		dump (const char *name, unsigned int level = 0)
		{
			std::string indentation(level*2, ' ');	
			std::cout << indentation << name << " = Settings" << std::endl;
			area.dump("area", level+1);
			tile_size.dump("tile size", level+1);
			// TODO sample_count and max_thread_count
		}
	};
}

#endif

