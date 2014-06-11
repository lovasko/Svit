#include "node/instance.h"

namespace Svit
{
	Instance::Instance (Node *_node)
	{
		node = _node;
	}

	boost::optional<Intersection>
	Instance::intersect (Ray& _ray, float _best)
	{
		Ray new_ray(_ray.origin * matrix, ~(_ray.direction * matrix));

		float original_length = length(_ray.direction);
		float new_length = length(new_ray.direction);
		float factor = new_length / original_length;

		boost::optional<Intersection intersection = node->intersect(new_ray);
		if (intersection)
		{
			float t = intersection.t / factor;
			if (t > 0.0f && t < _best)
			{
				boost::optional<Intersection> result;
				result.t = t;
				result.node = node;
				result.point = _ray(t);
			}
			else
				return boost::optional<Intersection>();
		}
		else
			return boost::optional<Intersection>();
	}

	void
	Instance::combine (Matrix& _transformation)
	{
		matrix = _transformation * matrix;
	}

	void
	Instance::recompute_inverse ()
	{
		inverse = !matrix;
	}

	void
	Instance::reset ()
	{
		matrix = Matrix::identity();
	}

	void 
	Instance::translate (Vector3& _translation)
	{
		Matrix translation_matrix(
			Vector4(1.0f, 0.0f, 0.0f, _translation.x),
			Vector4(0.0f, 1.0f, 0.0f, _translation.y),
			Vector4(0.0f, 0.0f, 1.0f, _translation.z),
			Vector4(0.0f, 0.0f, 0.0f, 1.0f));

		combine(translation_matrix);
		recompute_inverse();
	}

	void 
	Instance::rotate (Vector3& _axis, float _angle)
	{
		Vector3 unit = ~_axis;		
		float s = sinf(_angle);
		float c = cosf(_angle);
		float i = (1.0f - c);
		float l = unit.x;
		float m = unit.y;
		float n = unit.z;
		float ms = m*s;
		float ns = n*s;
		float ls = l*s;
		float nni = n*n*i;
		float lli = l*l*i;
		float mmi = m*m*i;
		float nmi = n*m*i;
		float lmi = l*m*i;
		float lni = l*n*i;

		Matrix rotation_matrix(
			Vector4(lli + c,  lmi - ns, lni + ms, 0.0f),
			Vector4(lmi + ns, mmi + c,  nmi - ls, 0.0f),
			Vector4(lni - ms, nmi + ls, nni + c,  0.0f),
			Vector4(0.0f,     0.0f,     0.0f,     1.0f));

		combine(rotation_matrix);
		recompute_inverse();
	}

	void 
	Instance::scale (float _scale)
	{
		scale(Vector4(_scale));
	}

	void 
	Instance::scale (Vector3& _scale)
	{
		Matrix scaling_matrix(
			Vector4(_scale.x, 0.0f, 0.0f, 0.0f),
			Vector4(0.0f, _scale.y, 0.0f, 0.0f),
			Vector4(0.0f, 0.0f, _scale.z, 0.0f),
			Vector4(0.0f, 0.0f, 0.0f,     1.0f));

		combine(scaling_matrix);
		recompute_inverse();
	}

	void 
	Instance::set_matrix (Matrix& _matrix)
	{
		matrix = _matrix;
		recompute_inverse();
	}
}

