#include "renderer/parallel/parallel.h"
#include "renderer/serial/serial.h"

#include <thread>
#include <future>
#include <vector>
#include <utility>
#include <boost/optional.hpp>
#include <iostream>

namespace Svit
{
	Tiles
	ParallelRenderer::worker (TaskDispatcher& _task_dispatcher, World& _world, 
	    Settings& _settings, Engine& _engine, SuperSampling& _super_sampling)
	{
		Tiles result;
		SerialRenderer serial_renderer;
		Settings settings = _settings;
		
		while (1)
		{
			boost::optional<Task> optional_task = _task_dispatcher.get_task();
			if (!optional_task)
				break;

			Task task = optional_task.get();
			settings.area = task;

			Image rendered_image = serial_renderer.render(_world, settings, _engine,
			    _super_sampling);

			Tile tile;
			tile.task = task;
			tile.image = rendered_image;
			result.push_back(tile);
		}

		return result;
	}

	Image
	ParallelRenderer::render (World& _world, Settings& _settings, Engine&
	    _engine, SuperSampling& _super_sampling)
	{
		TaskDispatcher task_dispatcher(_settings);
		std::vector<std::future<Tiles>> futures(0);

		for (unsigned i = 0; i < _settings.max_thread_count; i++)
		{
			// TODO can this be done better? it must be possible
			futures.push_back(std::async(std::launch::async, [this, &task_dispatcher,
			    &_world, &_settings, &_engine, &_super_sampling] () { 
					return worker(task_dispatcher, _world, _settings, _engine,
					_super_sampling); }));
		}

		for (unsigned i = 0; i < futures.size(); i++)
		{
			futures[i].wait();
		}

		Image final_image(_settings.area.size);
		for (unsigned i = 0; i < futures.size(); i++)
		{
			Tiles tiles = futures[i].get();
			for (unsigned j = 0; j < tiles.size(); j++)
			{
				final_image.paste(tiles[j].task.start, tiles[j].image);
			}
		}

		return final_image;
	}
}

