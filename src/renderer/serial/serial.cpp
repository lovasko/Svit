#include "renderer/serial/serial.h"

#include <iostream>

namespace Svit
{
	Image
	SerialRenderer::render (World& _world, Settings& _settings, Engine& _engine)
	{
		Image result(_settings.area.size);

		for (int x = _settings.area.start.x; 
		         x < _settings.area.start.x + _settings.area.size.x; 
		         x++)
		for (int y = _settings.area.start.y; 
		         y < _settings.area.start.y + _settings.area.size.y; 
		         y++)
		{
			float nx = compute_normalized_coordinate(x, _settings.whole_area.size.x);
			float ny = compute_normalized_coordinate(y, _settings.whole_area.size.y);

			Ray ray = _world.camera->get_ray(nx, ny);
			RGB rgb = _engine.get_color(ray, _world);

			int ix = x - _settings.area.start.x; 
			int iy = y - _settings.area.start.y; 
			result(ix, iy) = rgb;
		}

		return result;
	}
}

