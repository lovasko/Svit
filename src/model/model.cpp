#include "model.h"

namespace Svit
{
	void
	Model::add_to_group (Group& group)
	{
		for (auto solid : solids)
			group.add(solid);
	}
}

