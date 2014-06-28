#ifndef SVIT_MATRIX
#define SVIT_MATRIX

#include "geom/vector.h"

namespace Svit
{
	template <typename Scalar>
	class Matrix
	{
		public:
			Vector<Scalar> a;
			Vector<Scalar> b;
			Vector<Scalar> c;
			Vector<Scalar> d;

			Matrix (Vector<Scalar> const& _a, Vector<Scalar> const& _b,
			    Vector<Scalar> const& _c, Vector<Scalar> const& _d) 
			  : a(_a), b(_b), c(_c), d(_d)
			{ }

			Matrix () { }

			void
			dump (const char *_name, unsigned int _level = 0)
			{
				std::string indentation(_level*2, ' ');
				std::cout << std::setprecision(10) << std::fixed;
				std::cout << indentation << _name << " = Matrix (" << std::endl;
				a.dump("a", _level+1);
				b.dump("b", _level+1);
				c.dump("c", _level+1);
				d.dump("d", _level+1);
				std::cout << indentation << ")";
			}

			Matrix<Scalar>
			transpose ()
			{
				Vector<Scalar> na(a.x, b.x, c.x, d.x);				
				Vector<Scalar> nb(a.y, b.y, c.y, d.y);				
				Vector<Scalar> nc(a.z, b.z, c.z, d.z);				
				Vector<Scalar> nd(a.w, b.w, c.w, d.w);				
				Matrix<Scalar> m(na, nb, nc, nd);

				return m;
			}

			static Matrix<Scalar>
			identity ()
			{
				Vector<Scalar> a(1.0f, 0.0f, 0.0f, 0.0f);
				Vector<Scalar> b(0.0f, 1.0f, 0.0f, 0.0f);
				Vector<Scalar> c(0.0f, 0.0f, 1.0f, 0.0f);
				Vector<Scalar> d(0.0f, 0.0f, 0.0f, 1.0f);
				Matrix<Scalar> m(a, b, c, d);

				return m;
			}

			Scalar	
			determinant ()
			{
				Scalar m[16];

				m[0] = a.x;
				m[1] = a.y;
				m[2] = a.z;
				m[3] = a.w;

				m[4] = b.x;
				m[5] = b.y;
				m[6] = b.z;
				m[7] = b.w;

				m[8] =  c.x;
				m[9] =  c.y;
				m[10] = c.z;
				m[11] = c.w;

				m[12] = d.x;
				m[13] = d.y;
				m[14] = d.z;
				m[15] = d.w;

				return
					m[12] * m[9] * m[6]  * m[3]  - m[8] * m[13] * m[6]  * m[3]  -
					m[12] * m[5] * m[10] * m[3]  + m[4] * m[13] * m[10] * m[3]  +
					m[8]  * m[5] * m[14] * m[3]  - m[4] * m[9]  * m[14] * m[3]  -
					m[12] * m[9] * m[2]  * m[7]  + m[8] * m[13] * m[2]  * m[7]  +
					m[12] * m[1] * m[10] * m[7]  - m[0] * m[13] * m[10] * m[7]  -
					m[8]  * m[1] * m[14] * m[7]  + m[0] * m[9]  * m[14] * m[7]  +
					m[12] * m[5] * m[2]  * m[11] - m[4] * m[13] * m[2]  * m[11] -
					m[12] * m[1] * m[6]  * m[11] + m[0] * m[13] * m[6]  * m[11] +
					m[4]  * m[1] * m[14] * m[11] - m[0] * m[5]  * m[14] * m[11] -
					m[8]  * m[5] * m[2]  * m[15] + m[4] * m[9]  * m[2]  * m[15] +
					m[8]  * m[1] * m[6]  * m[15] - m[0] * m[9]  * m[6]  * m[15] -
					m[4]  * m[1] * m[10] * m[15] + m[0] * m[5]  * m[10] * m[15];
			}
	};

	typedef Matrix<float> Matrix44;
}

#endif

