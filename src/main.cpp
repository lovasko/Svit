#include "camera/perspective.h"
#include "engine/cosine_debugger.h"
#include "geom/rect.h"
#include "geom/vector.h"
#include "geom/point.h"
#include "image/image.h"
#include "node/group/simple.h"
#include "node/solid/sphere.h"
#include "node/solid/infinite_plane.h"
#include "renderer/settings.h"
#include "renderer/serial/serial.h"
#include "renderer/parallel/parallel.h"
#include "supersampling/random.h"
#include "world/world.h"

#include <iostream>
#include <cmath>

using namespace Svit;

int 
main (void)
{
	Settings settings;
	settings.whole_area = Rectangle(Point2i(0, 0), Vector2i(1280, 720));
	settings.area = Rectangle(Point2i(0, 0), Vector2i(1280, 720));
	settings.max_thread_count = 4;
	settings.tile_size = Vector2i(100, 100);
	settings.max_sample_count = 20;
	settings.adaptive_sample_step = 2;

	SimpleGroup scene;

	InfinitePlane infinite_plane(Point3(0.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0));
	scene.add(infinite_plane);

	Sphere* spheres[100];
	int i = 0;

	for (float x = -3.0; x < 3.0; x += 0.5)
	for (float z = 0.0; z < 6.0; z += 0.5)
	{
		spheres[i] = new Sphere(Point3(x, 0.5, z), (float)(rand() % 15)/100.0);
		scene.add(*spheres[i]);
		i++;
	}

	PerspectiveCamera camera(
		Point3(0.0, 0.75, -2.0),
		Vector3(0.0, 0.0, 1.0),
		Vector3(0.0, 1.0, 0.0),
		settings.whole_area.get_aspect_ratio(),
		M_PI/2.0);

	World world;
	world.scene = &scene;
	world.camera = &camera;

	CosineDebuggerEngine engine;
	//ParallelRenderer renderer;
	SerialRenderer renderer;
	RandomSuperSampling super_sampling(true);

	Image image = renderer.render(world, settings, engine, super_sampling);
	image.write(std::string("output.png"));

	return 0;
}
