#ifndef SVIT_WORLD
#define SVIT_WORLD

#include "camera/camera.h"
#include "node/node.h"

namespace Svit
{
	struct World
	{
		Node *scene;
		Camera *camera;
	};
}

#endif

