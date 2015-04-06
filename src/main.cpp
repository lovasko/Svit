#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

#include "camera/perspective.h"
#include "engine/cosine_debugger.h"
#include "geom/point.h"
#include "geom/rectangle.h"
#include "geom/vector.h"
#include "image/image.h"
#include "model/obj.h"
#include "node/group/simple.h"
#include "node/group/kdtree/kdtree.h"
#include "node/group/axis_selector/round_robin.h"
#include "node/group/split_strategy/centre.h"
#include "node/group/kdtree/kdtree.h"
#include "node/group/bvh.h"
#include "node/instance.h"
#include "node/solid/disc.h"
#include "node/solid/infinite_plane.h"
#include "node/solid/sphere.h"
#include "node/solid/triangle.h"
#include "renderer/parallel/parallel.h"
#include "renderer/serial/serial.h"
#include "renderer/settings.h"
#include "supersampling/random.h"
#include "world/world.h"

using namespace Svit;

int 
main (void)
{
	Settings settings;
	settings.whole_area = Rectangle(Point2i(0, 0), Vector2i(800, 600));
	settings.area = Rectangle(Point2i(0, 0), Vector2i(800, 600));
	settings.max_thread_count = std::thread::hardware_concurrency();
	settings.tile_size = Vector2i(100, 100);
	settings.max_sample_count = 2;
	settings.adaptive_sample_step = 10;

	CosineDebuggerEngine engine;
	ParallelRenderer renderer;
	RandomSuperSampling super_sampling(true);

	PerspectiveCamera camera(
		Point3(0.0, 0.75, -4.5),
		Vector3(0.0, 0.0, 1.0),
		Vector3(0.0, 1.0, 0.0),
		Rectangle(Point2i(0, 0), Vector2i(80, 60)).get_aspect_ratio(),
		M_PI/2.0f);

	ObjModel cow_model;
	BVH cow_bvh(new RoundRobinAxisSelector(), new CentreSplitStrategy(), 520, 8);
	Instance cow(&cow_bvh);

	cow_model.load("mdl/cow.obj");
	cow_model.add_to_group(cow_bvh);
	cow_bvh.finish();
	cow.rotate(Vector3(0.0f, 0.0f, 1.0f), M_PI/4.0f);
	cow.rotate(Vector3(0.0f, 1.0f, 0.0f), M_PI/2.0f);
	cow.rotate(Vector3(0.0f, 0.0f, 1.0f), M_PI/2.0f);
	cow.rotate(Vector3(0.0f, 1.0f, 0.0f), M_PI/3.5f);
	cow.translate(Vector3(-3.5f, -2.0f, 0.0f));

	InfinitePlane plane(Point3(0.0f, -3.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	SimpleGroup scene;
	scene.add(&cow);
	scene.add(&plane);

	World world;
	world.scene = &scene;
	world.camera = &camera;

	Image image = renderer.render(world, settings, engine, super_sampling);
	image.write_png(std::string("cow.png"));

	return 0;
}

