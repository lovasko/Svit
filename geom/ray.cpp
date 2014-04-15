#include "ray.h"
#include "operations.h"

namespace Svit
{
	template <typename Scalar>
	Ray<Scalar>::Ray (Vector<Scalar>& origin, Vector<Scalar>& direction)
	{
		_origin = origin;
		_direction = direction;
	}

	template <typename Scalar>
	Point<Scalar> 
	Ray<Scalar>::operator() (Scalar time) const
	{
		return _origin + _direction * time;
	}
}

