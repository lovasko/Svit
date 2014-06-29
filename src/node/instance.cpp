#include "node/instance.h"

namespace Svit
{
	Instance::Instance (Node *_node)
	{
		node = _node;
		matrix = Matrix44::identity();
		recompute_inverse();
	}

	boost::optional<Intersection>
	Instance::intersect (Ray& _ray, float _best)
	{
		_ray.origin.w = 1.0f;
		_ray.direction.w = 0.0f;
		Ray new_ray(inverse * _ray.origin, ~(inverse * _ray.direction));

		new_ray.origin.w = 0.0f;
		boost::optional<Intersection> node_intersection = node->intersect(new_ray, 
		    _best);

		if (node_intersection)
		{
			Point3 hit_point = matrix * node_intersection->point;
			Intersection intersection;
			intersection.t = node_intersection->t;
			intersection.node = node_intersection->node;
			intersection.point = hit_point;

			boost::optional<Intersection> result(intersection);
			return result;
		}
		else
			return boost::optional<Intersection>();
	}

	void
	Instance::set_material (std::unique_ptr<Material> _material)
	{
	
	}

	void
	Instance::combine (Matrix44& _transformation)
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
		matrix = Matrix44::identity();
	}

	void 
	Instance::translate (Vector3 const& _translation)
	{
		Matrix44 translation_matrix(
			Vector4(1.0f, 0.0f, 0.0f, _translation.x),
			Vector4(0.0f, 1.0f, 0.0f, _translation.y),
			Vector4(0.0f, 0.0f, 1.0f, _translation.z),
			Vector4(0.0f, 0.0f, 0.0f, 1.0f));

		combine(translation_matrix);
		recompute_inverse();
	}

	void 
	Instance::rotate (Vector3 const& _axis, float _angle)
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

		Matrix44 rotation_matrix(
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
	Instance::scale (Vector3 const& _scale)
	{
		Matrix44 scaling_matrix(
			Vector4(_scale.x, 0.0f, 0.0f, 0.0f),
			Vector4(0.0f, _scale.y, 0.0f, 0.0f),
			Vector4(0.0f, 0.0f, _scale.z, 0.0f),
			Vector4(0.0f, 0.0f, 0.0f,     1.0f));

		combine(scaling_matrix);
		recompute_inverse();
	}

	void 
	Instance::set_matrix (Matrix44& _matrix)
	{
		matrix = _matrix;
		recompute_inverse();
	}
}

