#include <Eigen/Core>
#include <iostream>

#include "geom/ray.h"

int 
main (void)
{
	Eigen::Vector3d d(1.0, 0.0, 1.0);
	Eigen::Vector3d o(0.0, 0.0, 0.0);

	Svit::Ray ray(o, d);
	std::cout << ray(0.5) << std::endl;
	return 0;
}
