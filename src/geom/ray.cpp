#include "geom/ray.h"

namespace Svit
{
	Ray::Ray ()
	{ } 

	Ray::Ray (Point3 const& _origin, Vector3 const& _direction)
		: origin(_origin), direction(_direction)
	{ }

	Point3 
	Ray::operator() (float _time) const
	{
		return origin + direction * _time;
	}

	void
	Ray::dump (const char* _name, unsigned int _level) const
	{
		std::string indentation(_level*2, ' ');
		std::cout << indentation << _name << " = Ray" << std::endl;
		origin.dump("origin", _level+1);
		direction.dump("direction", _level+1);
	}
}

