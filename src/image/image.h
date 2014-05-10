#ifndef SVIT_IMAGE
#define SVIT_IMAGE

#include "geom/vector.h"
#include "geom/point.h"

#include <assert.h>
#include <vector>
#include <string>
#include <iostream>
#include <png.h>

// TODO split to image.cpp and image.h

namespace Svit
{
	class Image
	{
		private:
			std::vector<Vector3> data;

		public:
			Vector2i size;

			Vector3& 
			operator() (int x, int y)
			{
				assert(x >= 0 && y >= 0);
				return data[x * size.y + y];
			}

			void
			resize (Vector2i _size)
			{
				data.resize(_size.x * _size.y);
				size = _size;
			}

			Image ()
			{
				data.resize(0);
				size = Vector2i(0, 0);
			}

			Image (Vector2i& _size)
				: size(_size)
			{
				data.resize(size.x * size.y);

				for (int x = 0; x < size.x; x++)
				for (int y = 0; y < size.y; y++)
					(*this)(x, y) = Vector3(1.0, 0.7, 0.0);
			}

			void
			paste (Point2i start, Image& source)
			{
				assert(start.x + source.size.x <= size.x);
				assert(start.y + source.size.y <= size.y);

				for (int x = start.x; x < start.x + source.size.x; x++) 	
				for (int y = start.y; y < start.y + source.size.y; y++) 	
				{
					(*this)(x, y) = source(x - start.x, y - start.y);
				}
			}

			int 
			write (std::string filename)
			{
				FILE *file = fopen(filename.c_str(), "wb");
				png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, 
				    NULL, NULL);
				png_infop info = png_create_info_struct(png);

				png_init_io(png, file);

				png_set_IHDR(png, info, size.x, size.y, 8, PNG_COLOR_TYPE_RGB,
				    PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, 
				    PNG_FILTER_TYPE_BASE);

				png_text text;
				char key[] = "Created with";
				char value[] = "Path Tracer Svit";
				text.compression = PNG_TEXT_COMPRESSION_NONE;
				text.key = key;
				text.text = value;
				png_set_text(png, info, &text, 1);

				png_write_info(png, info);

				size_t row_size = size.x * 3;
				png_bytep row = (png_bytep)malloc(row_size * sizeof(png_byte));

				for (unsigned y = 0; y < size.y; y++)
				{
					for (unsigned x = 0; x < size.x; x++)
					{
						Vector3& rgb = (*this)(x, y);
						row[x*3 + 0] = (png_byte)((rgb.x > 1.0 ? 1.0 : rgb.x) * 255.0); 
						row[x*3 + 1] = (png_byte)((rgb.y > 1.0 ? 1.0 : rgb.y) * 255.0); 
						row[x*3 + 2] = (png_byte)((rgb.z > 1.0 ? 1.0 : rgb.z) * 255.0); 
					}

					png_write_row(png, row);
				}

				png_write_end(png, NULL);
				fclose(file);
				png_free_data(png, info, PNG_FREE_ALL, -1);
				png_destroy_write_struct(&png, (png_infopp)NULL);
				free(row);

				return 0;
			}
	};
}

#endif

