#ifndef SVIT_INSTANCE
#define SVIT_INSTANCE

#include "geom/matrix.h"
#include "node/node.h"

namespace Svit
{
	class Instance : public Node
	{
		private:
			Node *node;
			mutable Matrix44 matrix;
			mutable Matrix44 inverse;

			void
			combine (Matrix44& _transformation);

			void
			recompute_inverse ();

		public:
			Instance (Node *_node);

			bool
			intersect (Ray& _ray, Intersection& _isect) const override;

			void
			dump (std::string _name, unsigned int _level = 0) const override;

			void
			reset ();

			void
			translate (Vector3 const& _translation);

			void
			rotate (Vector3 const& _axis, float _angle);

			void
			scale (Vector3 const& _scale);

			void
			scale (float _scale);

			void 
			set_matrix (Matrix44& _matrix);
	};
}

#endif

