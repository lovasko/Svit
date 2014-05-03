#include "renderer/serial/serial.h"

#include <iostream>

namespace Svit
{
	Image
	SerialRenderer::render (World& _world, Settings& _settings, Engine& _engine,
	    SuperSampling& _super_sampling)
	{
		int whole_x = _settings.whole_area.size.x;
		int whole_y = _settings.whole_area.size.y;

		Image result(_settings.area.size);
		SuperSampling *super_sampling = _super_sampling.copy();

		for (int x = _settings.area.start.x; 
		         x < _settings.area.start.x + _settings.area.size.x; 
		         x++)
		for (int y = _settings.area.start.y; 
		         y < _settings.area.start.y + _settings.area.size.y; 
		         y++)
		{
			for (unsigned int i = 0; i < _settings.max_sample_count; i++)
			{
				Vector2 sample = super_sampling->next_sample(x, y);

				float nx = compute_normalized_coordinate((float)x + sample.x, whole_x);
				float ny = compute_normalized_coordinate((float)y + sample.y, whole_y);

				Ray ray = _world.camera->get_ray(nx, ny);
				Vector3 rgb = _engine.get_color(ray, _world);

				super_sampling->add_result(rgb);

				if (i % _settings.adaptive_sample_step == 0)
					if (super_sampling->adaptive)
						if (super_sampling->enough())
							break;
			}

			Vector3 final_rgb = super_sampling->final_result();

			int ix = x - _settings.area.start.x; 
			int iy = y - _settings.area.start.y; 
			result(ix, iy) = final_rgb;
		}

		delete super_sampling;		

		return result;
	}
}

