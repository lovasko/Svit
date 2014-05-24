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
#include "light/point.h"
#include "light/directional.h"
#include "light/ambient.h"

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
	settings.tile_size = Vector2i(100, 100);
	settings.max_sample_count = 750;
	settings.adaptive_sample_step = 1000;

	SimpleGroup scene;

	InfinitePlane infinite_plane(Point3(0.0, 0.02, 0.0), Vector3(0.0, 1.0, 0.0));
	CheckerboardTexture *checker = new CheckerboardTexture(Vector3(0.5f, 0.5f,
	    0.5f), Vector3(1.0, 1.0, 1.0), 0.25);

	std::unique_ptr<Texture> ct(checker);
	std::unique_ptr<Material> mat(new LambertianMaterial(std::move(ct)));
	infinite_plane.set_material(std::move(mat));
scene.add(infinite_plane);

	WoodPerlinNoiseTexture *wood_texture = new WoodPerlinNoiseTexture(
			Vector3(149.0f/255.0f, 69.0f/255.0f, 53.0f/255.0f), Vector3(237.0f/255.0f,
			201.0f/255.0f, 175.0f/255.0f));
	wood_texture->add_octave(1.0, 3.0);

	ConstantTexture *white_texture = new ConstantTexture(Vector3(1.0, 1.0, 1.0));

	std::unique_ptr<Texture> wood_sphere_tex(wood_texture);
	std::unique_ptr<Material> wood_sphere_mat(new LambertianMaterial(
	    std::move(wood_sphere_tex)));
	Sphere wood_sphere(Point3(-0.9, 0.35, 0.0), 0.35);
	wood_sphere.set_material(std::move(wood_sphere_mat));
	scene.add(wood_sphere);

	std::unique_ptr<Material> mirror_material(new MirrorMaterial(0.0f, 20.0f));
	Sphere mirror_sphere(Point3(0.0f, 0.35f, 2.0f), 0.35f);
	mirror_sphere.set_material(std::move(mirror_material));
	//scene.add(mirror_sphere);

	PerspectiveCamera camera(
		Point3(0.0, 0.75, -2.0),
		Vector3(0.0, 0.0, 1.0),
		Vector3(0.0, 1.0, 0.0),
		settings.whole_area.get_aspect_ratio(),
		M_PI/2.0);

	World world;
	world.scene = &scene;
	world.camera = &camera;

	std::unique_ptr<Light> light1(new PointLight(Point3(0.0, 1.5, 0.0),
	   Vector3(1.0f, 1.0f, 1.0f) * 3.0f));
	world.add_light(std::move(light1));

	std::unique_ptr<Light> ambient_light(new AmbientLight(
	    Vector3(1.0f, 1.0f, 1.0f)));
	world.add_light(std::move(ambient_light));

	/* std::unique_ptr<Light> light2(new DirectionalLight(Vector3(0.0, -1.0, 1.0), */
	/*     Vector3(3.0, 3.0, 3.0) * 0.1f)); */
	/* world.add_light(std::move(light2)); */

	RayTracingEngine engine;
	ParallelRenderer renderer;
	RandomSuperSampling super_sampling(true);

	Image image = renderer.render(world, settings, engine, super_sampling);
	image.write(std::string("output.png"));

	return 0;
}

