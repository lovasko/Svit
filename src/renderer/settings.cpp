#include "renderer/settings.h"

namespace Svit
{
	void
	Settings::dump (const char* _name, unsigned int _level)
	{
		std::string indentation(_level*2, ' ');
		std::cout << indentation << _name << " = Settings" << std::endl;
		area.dump("area", _level+1);
		tile_size.dump("tile size", _level+1);
		// TODO sample_count and max_thread_count
	}
}

