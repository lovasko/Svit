#ifndef SVIT_GEOM_BOUNDING_BOX_H
#define SVIT_GEOM_BOUNDING_BOX_H

#include <boost/optional.hpp>
#include <tuple>

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

			BoundingBox ()
			 : size_type(EMPTY)
			{ }

			BoundingBox (Point3 _min, Point3 _max)
			 : min(_min), max(_max), size_type(BOUNDED)
			{ }

			BoundingBox (SizeType _size_type)
			 : min(Point3()), max(Point3()), size_type(_size_type)
			{ }

			void
			extend (Point3& _point);

			void
			extend (BoundingBox& _bounding_box);

			bool
			intersect (Ray& _ray, float* _t_near, float* _t_max);

			bool
			contains (Point3& _point);

			Point3
			centroid ();

			void
			dump (std::string _name, unsigned int _level = 0);
	};
}

#endif

