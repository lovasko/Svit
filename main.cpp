#include <iostream>

#include "geom/ray.h"
#include "image/image.h"
#include "image/formats.h"

using namespace Svit;

int 
main (void)
{
	Vector<int> size(200, 100);
	Image<RGB8Format> image(size);

	std::cout << image(1, 10).x << std::endl;

	return 0;
}
