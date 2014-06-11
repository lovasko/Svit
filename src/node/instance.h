#ifndef SVIT_INSTANCE
#define SVIT_INSTANCE

#include "node/node.h"
#include "geom/matrix.h"

namespace Svit
{
	class Instance : public Node
	{
		private:
			Node *node;
			Matrix matrix;
			Matrix inverse;

			void
			combine (Matrix& _transformation);

			void
			recompute_inverse ();

		public:
			Instance (Node *_node);

			boost::optional<Intersection>
			intersect (Ray& _ray, float _best);

			void
			reset ();

			void
			translate (Vector3& _translation);

			void
			rotate (Vector3& _axis, float _angle);

			void
			scale (Vector3& _scale);

			void
			scale (float _scale);
	};
}

#endif

