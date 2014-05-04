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
#include "trajectory/bspline.h"
#include "world/world.h"

#include <iostream>
#include <sstream>
#include <cmath>
#include <thread>

using namespace Svit;

int 
main (void)
{
	Settings settings;
	settings.whole_area = Rectangle(Point2i(0, 0), Vector2i(1280, 720));
	settings.area = Rectangle(Point2i(0, 0), Vector2i(1280, 720));
	settings.max_thread_count = std::thread::hardware_concurrency();
	settings.tile_size = Vector2i(100, 100);
	settings.max_sample_count = 4;
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
	ParallelRenderer renderer;
	//SerialRenderer renderer;
	RandomSuperSampling super_sampling(true);


	BSplineTrajectory trajectory(true);
	trajectory.add_point(Point3(0.0f, 0.0f, 0.0f));
	trajectory.add_point(Point3(-3.0f, 3.0f, 3.0f));
	trajectory.add_point(Point3(0.0f, 6.0f, 6.0f));
	trajectory.add_point(Point3(3.0f, 3.0f, 3.0f));

	unsigned int FPS = 25;
	float animation_length = 10.0;

	unsigned int frame_count = FPS * (int)(animation_length);
	for (int frame = 0; frame < frame_count; frame++) 
	{
		camera.position = trajectory.evaluate(4.0f / (float)frame_count *
		    (float)frame) + Vector3(0.0, -0.25, -3.0);
		camera.look_at(Point3(0.0, 0.0, 3.0));

		Point3 now = trajectory.evaluate(4.0f / (float)frame_count *
		    (float)frame) + Vector3(0.0, -0.25, -3.0);

		Point3 next = trajectory.evaluate(4.0f / (float)frame_count *
		    (((float)frame) + 0.0001f)) + Vector3(0.0, -0.25, -3.0);

		Vector3 left = ~(next - now);
		camera.up = left & camera.forward;

		camera.position.dump("position");
		camera.forward.dump("forward");
		camera.up.dump("up");

		Image image = renderer.render(world, settings, engine, super_sampling);

		std::ostringstream ss;
		ss << std::setw(3) << std::setfill('0') << frame;
	  std::string frame_string(ss.str());

		image.write(std::string("output") + frame_string + std::string(".png"));

		std::cout << "Frame " << frame << "/" << frame_count << " done." <<
		    std::endl;
	}

	return 0;
}
