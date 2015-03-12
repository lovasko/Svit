#ifndef SVIT_WORLD_WORLD_H
#define SVIT_WORLD_WORLD_H

#include <memory>
#include <vector>

#include "camera/camera.h"
#include "node/node.h"

namespace Svit
{
	class World
	{
		public:
			Node* scene;
			Camera* camera;
	};
}

#endif

