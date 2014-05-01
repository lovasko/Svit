#include "renderer/simple.h"

#include <iostream>

namespace Svit
{
	Image
	SimpleRenderer::render (World& _world, Settings& _settings, Engine& _engine)
	{
		Image result(_settings.area.size);

		_world.camera->set_area(_settings.area);
		for (int x = _settings.area.start.x; x < _settings.area.size.x; x++)
		for (int y = _settings.area.start.y; y < _settings.area.size.y; y++)
		{
			float nx = compute_normalized_coordinate(x, _settings.area.size.x);
			float ny = compute_normalized_coordinate(y, _settings.area.size.y);

			Ray ray = _world.camera->get_ray(nx, ny);
			RGB rgb = _engine.get_color(ray, _world);
			result(x, y) = rgb;
		}

		return result;
	}
}

