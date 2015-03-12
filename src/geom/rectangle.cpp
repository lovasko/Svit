#include <stdexcept>

#include "geom/rectangle.h"

namespace Svit
{
	Rectangle::Rectangle ()
	{ }

	Rectangle::Rectangle (Point2i _start, Vector2i _size)
		: start(_start), size(_size)
	{ }

	int
	Rectangle::get_area ()
	{
		return size.x * size.y;
	}

	float
	Rectangle::get_aspect_ratio ()
	{
		if (size.y == 0)
			throw std::runtime_error("Rectangle height is zero");

		return (float)size.x/(float)size.y;
	}

	void
	Rectangle::dump (const char* _name, unsigned int _level)
	{
		std::string indentation(_level*2, ' ');	
		std::cout << indentation << _name << " = Rectangle" << std::endl;
		start.dump("start", _level+1);
		size.dump("size", _level+1);
	}
}

