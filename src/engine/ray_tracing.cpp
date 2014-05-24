#include "engine/ray_tracing.h"
#include "light/light.h"
#include "math/numeric.h"

#include <numeric>

namespace Svit
{
	Vector3
	RayTracingEngine::get_color (Ray& _ray, World& _world)
	{
		boost::optional<Intersection> best = _world.scene->intersect(_ray,
		    std::numeric_limits<float>::max());

		if (best)
		{
			Intersection i = *best;
			best->node->complete_intersection(&i);

			Vector3 light_component(0.0, 0.0, 0.0);
			for (auto &light : _world.lights)
			{
				LightHit light_hit = light->get_light_hit(i.point);

				/* float sgn1 = ~light_hit.direction % ~i.normal; */
				/* float sgn2 = ~!_ray.direction % ~i.normal; */
				/* if ((sgn1 < 0.0f && sgn2 > 0.0f) || */ 
				/*     (sgn1 > 0.0f && sgn2 < 0.0f)) */ 
				/* 	continue; */

				Point3 shadow_point = i.point + (light_hit.direction * 0.0001f);
				Ray shadow_ray(shadow_point, light_hit.direction);

				boost::optional<Intersection> shadow =
				    _world.scene->intersect(shadow_ray, light_hit.distance - 0.0001f);

				if (shadow)
					continue;

				light_component += light->get_intensity(light_hit);
			}

			Vector3 material_component = i.node->material->get_reflectance(i.point, 
			    i.normal, _ray.direction, !_ray.direction);

			return material_component * light_component;
		}
		else
			return Vector3();
	}
}

