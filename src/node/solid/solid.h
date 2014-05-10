#ifndef SVIT_SOLID
#define SVIT_SOLID

#include "node/node.h"

#include <list>
#include <memory>

namespace Svit
{
	class Solid : public Node
	{
		public:
		  std::unique_ptr<Material> material;

			void
			set_material (std::unique_ptr<Material> _material)
			{
				material = std::move(_material);	
			}

			std::list<Intersection>
			fail ()
			{
				std::list<Intersection> empty;
				return empty;
			}

			// TODO virtual!
			void
			complete_intersection(Intersection *_intersection) 
			{ 
				std::cout << "aspon ze takto" << std::endl;
			}
	};
}

#endif

