#include "renderer/parallel/task_dispatcher.h"

#include <cmath>
#include <stdio.h>

namespace Svit
{
	TaskDispatcher::TaskDispatcher (Settings& _settings)
	{
		int tile_w = _settings.tile_size.x;
		int tile_h = _settings.tile_size.y;
		int w = _settings.area.size.x;
		int h = _settings.area.size.y;
		int end_x = 0;
		int end_y = 0;

		for (int x = 0; x < w; x += tile_w)
		for (int y = 0; y < h; y += tile_h)
		{
			if (x + tile_w >= w)
				end_x = w;
			else
				end_x = x + tile_w;

			if (y + tile_h >= h)
				end_y = h;
			else
				end_y = y + tile_h;

			Task task;
			task.start = Point2i(x, y);
			task.size = Vector2i(end_x - x, end_y - y);
			tasks.push_back(task);
		}

		index = 0;
	}

	bool
	TaskDispatcher::get_task (Task* _task)
	{
		std::lock_guard<std::mutex> guard(mutex);

		if (index != tasks.size())
		{
			*_task = tasks[index++];
			return true;
		}
		else
			return false;
	}
}

