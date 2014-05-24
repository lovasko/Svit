#ifndef SVIT_SIMPLE_GROUP
#define SVIT_SIMPLE_GROUP

#include "node/group/group.h"
#include "geom/ray.h"

#include <list>

namespace Svit
{
	class SimpleGroup : public Group
	{
		private:
			std::list<Node*> nodes;

		public:
			boost::optional<Intersection>
			intersect (Ray& _ray, float _best);

			void
			set_material (std::unique_ptr<Material> _material);

			void
			add (Node& _node);

			void
			finish () { }
	};
}

#endif

