#ifndef SVIT_TASK_DISPATCHER
#define SVIT_TASK_DISPATCHER

#include <mutex>
#include <vector>

#include "renderer/settings.h"
#include "geom/rectangle.h"

namespace Svit
{
	typedef Rectangle Task;

	class TaskDispatcher
	{
		private:
			std::mutex mutex;
			std::vector<Task> tasks;

		public:
			TaskDispatcher (Settings& _settings);

			bool
			get_task (Task* _task);

			unsigned int index;
	};
}

#endif

