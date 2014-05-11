#ifndef SVIT_MIRROR_MATERIAL
#define SVIT_MIRROR_MATERIAL

#include "material/material.h"

namespace Svit
{
	class MirrorMaterial : public Material
	{
		private: 	
			float eta;
			float kappa;
			float e2k2;
		public:
			MirrorMaterial (float _eta, float _kappa);

			Vector3
			get_reflectance (Point3 _point, Vector3 _normal, Vector3 _in, 
				Vector3 _out);
	};
}

#endif

