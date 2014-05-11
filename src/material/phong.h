#ifndef SVIT_PHONG_MATERIAL
#define SVIT_PHONG_MATERIAL

#include "material/material.h"
#include "texture/texture.h"

namespace Svit
{
	class PhongMaterial : public Material
	{
		private:
			std::unique_ptr<Texture> texture;
			float exp;
				
		public:
			PhongMaterial (std::unique_ptr<Texture> _texture, 
			    float _exp);

			Vector3
			get_reflectance (Point3 _point, Vector3 _normal, Vector3 _in, 
			    Vector3 _out);
	};
}

#endif

