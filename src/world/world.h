#ifndef SVIT_WORLD
#define SVIT_WORLD

#include "camera/camera.h"
#include "node/node.h"
#include "light/light.h"

#include <vector>
#include <memory>

namespace Svit
{
	struct World
	{
		Node *scene;
		Camera *camera;
		std::vector<std::unique_ptr<Light>> lights;

		void
		add_light (std::unique_ptr<Light> _light)
		{
			lights.push_back(std::move(_light));	
		}
	};
}

#endif

