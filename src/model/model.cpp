#include "model/model.h"

namespace Svit
{
	void
	Model::add_to_group (Group& _group)
	{
		for (auto solid : solids)
			_group.add(solid);
	}
}

