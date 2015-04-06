#ifndef SVIT_PARALLEL_RENDERER
#define SVIT_PARALLEL_RENDERER

#include "renderer/settings.h"
#include "image/image.h"
#include "renderer/parallel/task_dispatcher.h"
#include "geom/rectangle.h"
#include "world/world.h"
#include "engine/engine.h"
#include "renderer/renderer.h"

#include <vector>
#include <utility>

namespace Svit
{
	struct Tile
	{
		Task task;
		Image image;
	};

	typedef std::vector<Tile> Tiles;

	class ParallelRenderer : public Renderer
	{
		public:
			Image
			render (World& _world, Settings& _settings, Engine& _engine, 
			    SuperSampling& _super_sampling) const override;
	};
}

#endif

