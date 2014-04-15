#ifndef SVIT_IMAGE
#define SVIT_IMAGE

#include <assert.h>
#include <vector>
#include "../geom/vector.h"

namespace Svit
{
	template <typename Format>
	class Image
	{
		private:
			std::vector<typename Format::data_type> data;
			Vector<int> size;

		public:
			typename Format::data_type& 
			operator() (int x, int y)
			{
				assert(x >= 0 && y >= 0);
				return data[y * size.y + x];
			}

			Image (Vector<int>& _size)
			 : size(_size)
			{
				data.resize(size.x * size.y);

				for (int x = 0; x < size.x; x++)
				for (int y = 0; y < size.y; y++)
					(*this)(x, y) = Format::zero();
			}

			int 
			write (std::string filename)
			{
				for (int i = 0; i < data.size(); i++)
				{
					std::cout << data[i] << std::endl;
				}
			}
	};
}

#endif

