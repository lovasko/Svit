#ifndef SVIT_LAMBERTIAN_MATERIAL
#define SVIT_LAMBERTIAN_MATERIAL

#include "texture/texture.h"
#include "material/material.h"

#include <memory>

namespace Svit
{
	class LambertianMaterial : public Material
	{
		private:
			std::unique_ptr<Texture> texture;
			bool simple;
				
		public:
			LambertianMaterial (std::unique_ptr<Texture> _texture, 
			    bool _simple = false);

			Vector3
			get_reflectance (Point3 _point, Vector3 _normal, Vector3 _in, 
			    Vector3 _out);
	};
}

#endif

