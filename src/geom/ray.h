#ifndef SVIT_RAY
#define SVIT_RAY

#include "geom/vector.h"
#include "geom/operations.h"
#include "geom/point.h"

namespace Svit
{
	class Ray
	{
		public:
			Point3 origin;
			Vector3 direction;

			Ray () { } 

			Ray (Point3& _origin, Vector3& _direction)
				: origin(_origin), direction(_direction)
			{ }

			Point3 
			operator() (float _time) const
			{
				return origin + direction * _time;
			}

			void
			dump (const char *name, unsigned int level = 0)
			{
				std::string indentation(level*2, ' ');
				std::cout << indentation << name << " = Ray" << std::endl;
				origin.dump("origin", level+1);
				direction.dump("direction", level+1);
			}
	};
}

#endif

