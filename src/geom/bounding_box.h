#ifndef SVIT_BOUNDING_BOX
#define SVIT_BOUNDING_BOX

#include "geom/point.h"
#include "geom/ray.h"

#include <tuple>
#include <boost/optional.hpp>

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
			 : size_type(BOUNDED), min(_min), max(_max)
			{ }

			BoundingBox (SizeType _size_type)
			 : size_type(_size_type), min(Point3()), max(Point3())
			{ }

			void
			extend (Point3& _point);

			void
			extend (BoundingBox& _bounding_box);

			boost::optional<std::tuple<float, float>>
			intersect (Ray& _ray);

			bool
			contains (Point3& _point);
	};
}

#endif

