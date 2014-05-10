#include "engine/ray_tracing.h"
#include "light/light.h"
#include "math/numeric.h"

namespace Svit
{
	Vector3
	RayTracingEngine::get_color (Ray& _ray, World& _world)
	{
		std::list<Intersection> intersections = _world.scene->intersect(_ray);
		boost::optional<Intersection> best = get_best_intersection(intersections);

		if (best)
		{
			Intersection i = *best;
			best->node->complete_intersection(&i);

			Vector3 light_component(0.0, 0.0, 0.0);
			for (auto &light : _world.lights)
			{
				LightHit light_hit = light->get_light_hit(i.point);
				Vector3 norm_hit_dir = ~light_hit.direction;
				Vector3 neg_norm_hit_dir = !norm_hit_dir;

				Ray shadow_ray(i.point, neg_norm_hit_dir);

				std::list<Intersection> shadow_intersections =
				    _world.scene->intersect(shadow_ray);

				boost::optional<Intersection> shadow_best =
				    get_best_intersection(shadow_intersections);

				float sgn1 = neg_norm_hit_dir % i.normal;
				float sgn2 = !_ray.direction % i.normal;
				if ((sgn1 < 0.0 && sgn2 > 0.0) || 
				    (sgn1 > 0.0 && sgn2 < 0.0)) 
					continue;

				if (shadow_best && shadow_best->t < light_hit.distance)
					continue;

				light_component += light->get_intensity(light_hit);
			}

			Vector3 material_component = i.node->material->get_reflectance(i.point, 
			    i.normal, _ray.direction, !_ray.direction);

			return material_component + light_component;
		}
		else
			return Vector3();
	}
}

