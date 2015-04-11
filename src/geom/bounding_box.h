#ifndef SVIT_GEOM_BOUNDING_BOX_H
#define SVIT_GEOM_BOUNDING_BOX_H

#include "geom/point.h"
#include "geom/ray.h"

namespace Svit
{
	enum SizeType
	{
		EMPTY,
		BOUNDED,
		FULL
	};

	class BoundingBox
	{
		public:
			Point3 min;
			Point3 max;
			SizeType size_type;

			BoundingBox ();

			BoundingBox (Point3 _min, Point3 _max);

			BoundingBox (SizeType _size_type);

			void
			extend (Point3& _point);

			void
			extend (BoundingBox& _bounding_box);

			bool
			intersect (Ray& _ray, float* _t_near, float* _t_max) const;

			bool
			contains (Point3& _point) const;

			Point3
			centroid () const;

			void
			dump (std::string _name, unsigned int _level = 0) const;
	};
}

#endif

