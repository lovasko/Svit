#include "camera/perspective.h"
#include "engine/cosine_debugger.h"
/* #include "engine/ray_casting.h" */
/* #include "engine/ray_tracing.h" */
#include "geom/rect.h"
#include "geom/vector.h"
#include "geom/point.h"
#include "image/image.h"
#include "node/instance.h"
#include "node/group/simple.h"
#include "node/solid/sphere.h"
/* #include "node/solid/infinite_plane.h" */
/* #include "node/solid/disc.h" */
/* #include "node/solid/triangle.h" */
#include "renderer/settings.h"
#include "renderer/serial/serial.h"
/* #include "renderer/parallel/parallel.h" */
#include "supersampling/random.h"
/* #include "trajectory/bspline.h" */
#include "world/world.h"
/* #include "material/lambertian.h" */
/* #include "material/phong.h" */
/* #include "material/mirror.h" */
/* #include "texture/constant.h" */
/* #include "texture/checkerboard.h" */
/* #include "texture/perlin_noise.h" */
/* #include "texture/wood_perlin_noise.h" */
/* #include "texture/marble_perlin_noise.h" */
/* #include "light/point.h" */
/* #include "light/directional.h" */
/* #include "light/ambient.h" */
/* #include "model/obj.h" */

#include <iostream>
#include <sstream>
#include <cmath>
#include <thread>
#include <memory>

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
	Sphere spehre(Point3(0.0, 0.0, 0.0), 1.0);
	PerspectiveCamera camera(
		Point3(0.0, 0.75, -5.5),
		Vector3(0.0, -0.1, 1.0),
		Vector3(0.0, 1.0, 0.0),
		Rectangle(Point2i(0, 0), Vector2i(128, 72)).get_aspect_ratio(),
		M_PI/2.0f);

	/* ObjModel cow; */
	/* SimpleGroup cow_group; */
	/* if (cow.load("cow.obj")) */
	/* 	cow.add_to_group(cow_group); */
	/* else */
	/* 	std::cout << "cow load not" << std::endl; */

	/* Instance i1(&cow_group); */
	/* /1* Instance i2(&sphere); *1/ */
	/* /1* Instance i3(&sphere); *1/ */
	/* /1* Instance i4(&sphere); *1/ */

	/* i1.rotate(Vector3(1.0f, 0.0f, 0.0f), M_PI/2.0f); */
	/* i1.rotate(Vector3(0.0f, 0.0f, 1.0f), M_PI); */
	/* i1.rotate(Vector3(0.0f, 1.0f, 0.0f), -M_PI/4.0f); */
	/* i1.translate(Vector3(-2.5f, -1.8f, 0.0f)); */
	/* /1* i1.translate(Vector3(1.0f, 0.0f, 0.0f)); *1/ */
	/* /1* i2.translate(Vector3(-1.0f, 0.0f, 0.0f)); *1/ */
	/* /1* i3.translate(Vector3(0.0f, 1.0f, 0.0f)); *1/ */
	/* /1* i4.translate(Vector3(-0.6f, 0.0f, 0.0f)); *1/ */

	/* scene.add(&i1); */
	/* /1* scene.add(&i2); *1/ */
	/* /1* scene.add(&i3); *1/ */
	/* /1* scene.add(&i4); *1/ */

	World world;
	world.scene = &scene;
	world.camera = &camera;

	Image image = renderer.render(world, settings, engine, super_sampling);
	image.write(std::string("cow.png"));

	return 0;
}

