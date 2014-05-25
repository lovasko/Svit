#include "camera/perspective.h"
#include "engine/cosine_debugger.h"
#include "engine/ray_casting.h"
#include "engine/ray_tracing.h"
#include "geom/rect.h"
#include "geom/vector.h"
#include "geom/point.h"
#include "image/image.h"
#include "node/group/simple.h"
#include "node/solid/sphere.h"
#include "node/solid/infinite_plane.h"
#include "node/solid/disc.h"
#include "renderer/settings.h"
#include "renderer/serial/serial.h"
#include "renderer/parallel/parallel.h"
#include "supersampling/random.h"
#include "trajectory/bspline.h"
#include "world/world.h"
#include "material/lambertian.h"
#include "material/phong.h"
#include "material/mirror.h"
#include "texture/constant.h"
#include "texture/checkerboard.h"
#include "texture/perlin_noise.h"
#include "texture/wood_perlin_noise.h"
#include "texture/marble_perlin_noise.h"
#include "light/point.h"
#include "light/directional.h"
#include "light/ambient.h"

#include <iostream>
#include <sstream>
#include <cmath>
#include <thread>
#include <memory>

using namespace Svit;

World
get_wood_world ()
{
	SimpleGroup *scene = new SimpleGroup();

	InfinitePlane *plane = new InfinitePlane(Point3(0.0, 0.02, 0.0), 
	    Vector3(0.0, 1.0, 0.0));
	std::unique_ptr<Texture> checker_texture(new CheckerboardTexture(Vector3(0.5f, 
	    0.5f, 0.5f), Vector3(1.0, 1.0, 1.0), 0.25));
	std::unique_ptr<Material> plane_material(new LambertianMaterial(
	    std::move(checker_texture)));
	plane->set_material(std::move(plane_material));

	Sphere *sphere = new Sphere(Point3(-0.9, 0.35, 0.0), 0.35);
	WoodPerlinNoiseTexture *wood_texture = new WoodPerlinNoiseTexture(
			Vector3(149.0f/255.0f, 69.0f/255.0f, 53.0f/255.0f), Vector3(237.0f/255.0f,
			201.0f/255.0f, 175.0f/255.0f));
	wood_texture->add_octave(1.0, 3.0);
	std::unique_ptr<Texture> wood_sphere_tex(wood_texture);
	std::unique_ptr<Material> sphere_material(new LambertianMaterial(
	    std::move(wood_sphere_tex)));
	sphere->set_material(std::move(sphere_material));

	scene->add(plane);
	scene->add(sphere);

	PerspectiveCamera *camera = new PerspectiveCamera(
		Point3(0.0, 0.75, -2.0),
		Vector3(0.0, -0.1, 1.0),
		Vector3(0.0, 1.0, 0.0),
		Rectangle(Point2i(0, 0), Vector2i(1280, 720)).get_aspect_ratio(),
		M_PI/2.0);

	World world;
	world.scene = scene;
	world.camera = camera;

	std::unique_ptr<Light> ambient_light(new AmbientLight(
	    Vector3(1.0f, 1.0f, 1.0f)));
	world.add_light(std::move(ambient_light));

	std::unique_ptr<Light> point_light(new PointLight(Point3(0.0, 1.5, 0.0),
	   Vector3(1.0f, 1.0f, 1.0f) * 3.0f));
	world.add_light(std::move(point_light));

	return world;
}

World
get_marble_world ()
{
	SimpleGroup *scene = new SimpleGroup();

	InfinitePlane *plane = new InfinitePlane(Point3(0.0, 0.02, 0.0), 
	    Vector3(0.0, 1.0, 0.0));
	std::unique_ptr<Texture> checker_texture(new CheckerboardTexture(Vector3(0.5f, 
	    0.5f, 0.5f), Vector3(1.0, 1.0, 1.0), 4.25));
	std::unique_ptr<Material> plane_material(new LambertianMaterial(
	    std::move(checker_texture)));
	plane->set_material(std::move(plane_material));

	MarblePerlinNoiseTexture *marble_texture = new MarblePerlinNoiseTexture(
			Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f));
	for (int i = 1; i < 1024; i*=2)
		marble_texture->add_octave(1.0f/(float)i, (float)i);

	std::unique_ptr<Texture> marble_sphere_tex(marble_texture);
	std::unique_ptr<Material> marble_sphere_mat(new LambertianMaterial(
	    std::move(marble_sphere_tex)));
	Sphere *sphere = new Sphere(Point3(12.8, 15.35, 2.0), 15.35);
	sphere->set_material(std::move(marble_sphere_mat));

	scene->add(plane);
	scene->add(sphere);

	PerspectiveCamera *camera = new PerspectiveCamera(
		Point3(0.0, 24.75, -47.0),
		Vector3(0.0, -0.1, 1.0),
		Vector3(0.0, 1.0, 0.0),
		Rectangle(Point2i(0, 0), Vector2i(1280, 720)).get_aspect_ratio(),
		M_PI/2.0);

	World world;
	world.scene = scene;
	world.camera = camera;

	std::unique_ptr<Light> ambient_light(new AmbientLight(
	    Vector3(1.0f, 1.0f, 1.0f) * 3.0f));
	world.add_light(std::move(ambient_light));

	return world;
}

int 
main (void)
{
	Settings settings;
	settings.whole_area = Rectangle(Point2i(0, 0), Vector2i(1280, 720));
	settings.area = Rectangle(Point2i(0, 0), Vector2i(1280, 720));
	settings.max_thread_count = std::thread::hardware_concurrency();
	settings.tile_size = Vector2i(100, 100);
	settings.max_sample_count = 4;
	settings.adaptive_sample_step = 1000;

	RayTracingEngine engine;
	ParallelRenderer renderer;
	RandomSuperSampling super_sampling(true);

	World marble_world = get_marble_world();
	World wood_world = get_wood_world();

	Image marble_image = renderer.render(marble_world, settings, engine, 
	    super_sampling);
	marble_image.write(std::string("marble_output.png"));

	Image wood_image = renderer.render(wood_world, settings, engine, 
	    super_sampling);
	wood_image.write(std::string("wood_output.png"));

	return 0;
}

