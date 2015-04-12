#include <cmath>
#include <fstream>
#include <iostream>

#include <assert.h>
#include <stdint.h>

#ifdef USE_PNG
	#include <png.h>
#endif

#include "image/image.h"

namespace Svit
{
	Vector3& 
	Image::operator() (int _x, int _y)
	{
		assert(_x >= 0 && _y >= 0);
		return data[_x * size.y + _y];
	}

	void
	Image::resize (Vector2i _size)
	{
		data.resize(_size.x * _size.y);
		size = _size;
	}

	Image::Image ()
	{
		// TODO use this::resize
		data.resize(0);
		size = Vector2i(0, 0);
	}

	Image::Image (Vector2i& _size)
		: size(_size)
	{
		data.resize(size.x * size.y);

		for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
			(*this)(x, y) = Vector3(1.0, 0.7, 0.0);
	}

	void
	Image::paste (Point2i _start, Image& _source)
	{
		assert(_start.x + _source.size.x <= size.x);
		assert(_start.y + _source.size.y <= size.y);

		for (int x = _start.x; x < _start.x + _source.size.x; x++) 	
		for (int y = _start.y; y < _start.y + _source.size.y; y++) 	
		{
			(*this)(x, y) = _source(x - _start.x, y - _start.y);
		}
	}

#ifdef USE_PNG
	int 
	Image::write_png (std::string _filename)
	{
		FILE *file = fopen(_filename.c_str(), "wb");
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

		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++)
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
#endif

	int
	Image::write_ppm (std::string _filename, unsigned int _depth)
	{
		assert(_depth == 1 || 
		       _depth == 2 ||
		       _depth == 4 ||
		       _depth == 8 ||
		       _depth == 16);

		std::ofstream ppm(_filename.c_str(), std::ofstream::out);
		unsigned int max_color;

		max_color = ((int)pow(2.0f, _depth)-1);

		ppm << "P3" << std::endl;
		ppm	<< size.x << " " << size.y << std::endl;
		ppm << max_color << std::endl;

		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++)
			{
				Vector3& rgb = (*this)(x, y);
				ppm << (int)((rgb.x > 1.0 ? 1.0 : rgb.x) * (float)max_color) << " ";
				ppm << (int)((rgb.y > 1.0 ? 1.0 : rgb.y) * (float)max_color) << " ";
				ppm << (int)((rgb.z > 1.0 ? 1.0 : rgb.z) * (float)max_color) << " ";
			}
			
			ppm << std::endl;
		}

		return 0;
	}

	int
	Image::write_rgbe (std::string _filename)
	{
		std::ofstream rgbe(_filename, std::ios::binary);

		rgbe << "#?RADIANCE" << '\n';
		rgbe << "# Svit" << '\n';
		rgbe << "FORMAT=32-bit_rle_rgbe" << '\n' << '\n';
		rgbe << "-Y " << size.y << " +X " << size.x << '\n';

		for (int y = 0; y < size.y; y++)
		for (int x = 0; x < size.x; x++)
		{
			uint8_t pixel[4] = {0, 0, 0, 0};
			Vector3& rgb = (*this)(x, y);
			float max_component = rgb.max_component3();

			if (max_component >= 1e-32f)
			{
				int exponent;
				float mantissa;

				mantissa = frexpf(max_component, &exponent) * 256.0f / max_component;
				pixel[0] = (uint8_t)(rgb.x * mantissa);
				pixel[1] = (uint8_t)(rgb.y * mantissa);
				pixel[2] = (uint8_t)(rgb.z * mantissa);
				pixel[3] = exponent;
			}

			rgbe << pixel[0] << pixel[1] << pixel[2] << pixel[3];
		}
		
		return 0;
	}

}

