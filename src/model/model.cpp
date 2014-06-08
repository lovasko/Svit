#include "model.h"

namespace Svit
{
	virtual void
	Model::add_to_group (Group& group)
	{
		for (auto solid : solids)
			group.add(solid);
	}
}

