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
	settings.whole_area = Rectangle(Point2i(0, 0), Vector2i(1280, 720));
	settings.area = Rectangle(Point2i(0, 0), Vector2i(1280, 720));
	settings.max_thread_count = std::thread::hardware_concurrency();
	settings.tile_size = Vector2i(10, 10);
	settings.max_sample_count = 1;
	settings.adaptive_sample_step = 10;

	CosineDebuggerEngine engine;
	SerialRenderer renderer;
	RandomSuperSampling super_sampling(true);

	SimpleGroup scene;
	Sphere sphere(Point3(0.0, 0.0, 0.0), 1.0);
	PerspectiveCamera camera(
		Point3(0.0, 0.75, -5.5),
		Vector3(0.0, 0.0, 1.0),
		Vector3(0.0, 1.0, 0.0),
		Rectangle(Point2i(0, 0), Vector2i(128, 72)).get_aspect_ratio(),
		M_PI/2.0f);

	ObjModel cow_model;
	cow_model.load("simplecow.obj");

	KDTree cow(new RoundRobinAxisSelector(), new CentreSplitStrategy(), 20, 3);
	cow_model.add_to_group(cow);
	cow.finish();

	cow.root.bounding_box.max.dump("cow bb min");
	cow.root.bounding_box.min.dump("cow bb max");

	/* KDTree spheres(new RoundRobinAxisSelector(), new CentreSplitStrategy(), 20, 100); */
	/* for (unsigned int i = 0; i < 6; i++) */
	/* 	spheres.add(new Sphere(Point3((float)i/5.0f*10.0f, 0.0f, 0.0f), 1.0f)); */

	/* spheres.finish(); */
	/* scene.add(&spheres); */

	scene.add(&cow);
	/* scene.add(&sphere); */

	World world;
	world.scene = &scene;
	world.camera = &camera;

	Image image = renderer.render(world, settings, engine, super_sampling);
	image.write_png(std::string("coww.png"));

	return 0;
}

