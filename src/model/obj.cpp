#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <sstream>
#include <vector>

#include "model/obj.h"
#include "node/solid/triangle.h"

namespace Svit
{
	ObjModel::ObjModel ()
	{
	}

	std::string
	ObjModel::remove_commentary (std::string& _line)
	{
		return _line.substr(0, _line.find('#'));
	}

	ObjInstruction
	ObjModel::get_instruction (std::string& _line)
	{
		if (_line.empty())                       return OBJ_INSTR_NONE;
		if (_line.compare(0, 2, "v ") == 0)      return OBJ_INSTR_VERTEX;
		if (_line.compare(0, 3, "vn ") == 0)     return OBJ_INSTR_NORMALVERTEX;
		if (_line.compare(0, 3, "vt ") == 0)     return OBJ_INSTR_TEXVERTEX;
		if (_line.compare(0, 2, "f ") == 0)      return OBJ_INSTR_FACE;
		if (_line.compare(0, 7, "usemtl ") == 0) return OBJ_INSTR_MATERIAL;
		if (_line.compare(0, 7, "mtllib ") == 0) return OBJ_INSTR_MATERIALLIBRARY;

		return OBJ_INSTR_INVALID;
	}

	bool
	ObjModel::parse_vertex (std::string& _line)
	{
		std::vector<std::string> line_parts;
		std::string pure_line = _line.substr(2);

		boost::trim(pure_line);
		boost::split(line_parts, pure_line, boost::is_any_of(" "));

		if (line_parts.size() < 3 || line_parts.size() > 4)
		{
			std::cerr << "Not enough line parts in '" << pure_line << "'"
			          << std::endl;
			return false;
		}

		for (unsigned int i = 0; i < line_parts.size(); i++)
			boost::trim(line_parts[i]);

		float x, y, z, w;

		if (line_parts.size() == 3)
		{
			try
			{
				x = std::stof(line_parts[0]);
				y = std::stof(line_parts[1]);
				z = std::stof(line_parts[2]);
			}
			catch (const std::invalid_argument& invalid_argument)
			{
				std::cerr << "Invalid argument while parsing '" << pure_line << "'" 
				          << std::endl;
				return false;
			}
			catch (const std::out_of_range& out_of_range)
			{
				std::cerr << "Out of range in '" << pure_line << "'" << std::endl;
				return false;
			}

			vertices.push_back(Point3(x, y, z));
			return true;
		}

		if (line_parts.size() == 4)
		{
			x = std::stof(line_parts[0]);
			y = std::stof(line_parts[1]);
			z = std::stof(line_parts[2]);
			w = std::stof(line_parts[3]);

			if (w == 0.0f)
			{
				std::cerr << "Last line part is 0.0 in '" << pure_line << "'"
				          << std::endl;
				return false;
			}

			vertices.push_back(Point3(x/w, y/w, z/w));
			return true;
		}

		return false;
	}

	bool
	ObjModel::parse_normal_vertex (std::string& _line)
	{
		std::vector<std::string> line_parts;
		std::string pure_line = _line.substr(3);

		boost::trim(pure_line);
		boost::split(line_parts, pure_line, boost::is_any_of(" "));

		if (line_parts.size() < 3 || line_parts.size() > 4)
		{
			std::cerr << "Wrong line parts count is '" << line_parts.size() << "'"
			          << std::endl;
			return false;
		}

		for (unsigned int i = 0; i < line_parts.size(); i++)
			boost::trim(line_parts[i]);

		float x, y, z, w;

		if (line_parts.size() == 3)
		{
			x = std::stof(line_parts[0]);
			y = std::stof(line_parts[1]);
			z = std::stof(line_parts[2]);

			normals.push_back(Point3(x, y, z));
			return true;
		}

		if (line_parts.size() == 4)
		{
			x = std::stof(line_parts[0]);
			y = std::stof(line_parts[1]);
			z = std::stof(line_parts[2]);
			w = std::stof(line_parts[3]);

			if (w == 0.0f)
			{
				std::cerr << "Last line part is 0.0 in '" << pure_line << "'"
				          << std::endl;
				return false;
			}

			normals.push_back(Point3(x/w, y/w, z/w));
			return true;
		}

		return false;
	}

	bool
	ObjModel::parse_tex_vertex (std::string& _line)
	{
		std::cout << _line << std::endl;
		std::vector<std::string> line_parts;
		std::string pure_line = _line.substr(3);

		boost::trim(pure_line);
		boost::split(line_parts, pure_line, boost::is_any_of(" "));

		if (line_parts.size() != 2)
		{
			std::cerr << "Wrong line parts count in '" << pure_line << "'" 
			          << std::endl;
			return false;
		}

		float u, v;

		u = std::stof(line_parts[0]);
		v = std::stof(line_parts[1]);
		tex_coords.push_back(Point2(u, v));

		return true;
	}

	bool
	ObjModel::parse_face (std::string& _line)
	{
		std::vector<std::string> line_parts;
		std::string pure_line = _line.substr(2);

		boost::trim(pure_line);
		boost::split(line_parts, pure_line, boost::is_any_of(" "),
		    boost::token_compress_on);

		if (line_parts.size() < 3)
		{
			std::cerr << "Not enough elements while parsing face '" << _line << "'"
			          << std::endl;
			return false;
		}

		for (unsigned int i = 0; i < line_parts.size(); i++)
			boost::trim(line_parts[i]);

		bool missing[3];
		missing[0] = missing[1] = missing[2] = false;

		Vector3i *face_data = new Vector3i[line_parts.size()];
		for (unsigned int i = 0; i < line_parts.size(); i++)
		{
			std::vector<std::string> vertex_parts;
			boost::split(vertex_parts, line_parts[i], boost::is_any_of("/"));

			if (vertex_parts.size() < 1 || vertex_parts.size() > 3)
			{
				std::cerr << "Not enough vertex parts in '" << line_parts[i] << "'"
				          << std::endl;
				return false;
			}

			if (vertex_parts.size() == 1)
			{
				face_data[i].x = std::stoi(vertex_parts[0]);
				missing[1] = true;
				missing[2] = true;
			}

			if (vertex_parts.size() == 2)
			{
				face_data[i].x = std::stoi(vertex_parts[0]);
				face_data[i].y = std::stoi(vertex_parts[1]);
				missing[2] = true;
			}

			if (vertex_parts.size() == 3)
			{
				face_data[i].x = std::stoi(vertex_parts[0]);

				if (vertex_parts[1].empty())
					missing[1] = true;
				else
					face_data[i].y = std::stoi(vertex_parts[1]);

				face_data[i].z = std::stoi(vertex_parts[2]);
			}

			if (!missing[0] && face_data[i].x < 0)
				face_data[i].x += vertices.size();

			if (!missing[1] && face_data[i].y < 0)
				face_data[i].y += normals.size();

			if (!missing[2] && face_data[i].z < 0)
				face_data[i].z += tex_coords.size();

			if (!missing[0])
				face_data[i].x--;

			if (!missing[1])
				face_data[i].y--;

			if (!missing[2])
				face_data[i].z--;
		}

		for (unsigned int i = 1; i < line_parts.size() - 1; i++)
		{
			Point3 p1 = vertices[face_data[0].x];
			Point3 p2 = vertices[face_data[i + 0].x];
			Point3 p3 = vertices[face_data[i + 1].x];

			Triangle *triangle = new Triangle(p1, p2, p3);
			solids.push_back(triangle);
		}

		return true;
	}

	bool
	ObjModel::parse_material_library (std::string& _line)
	{
		material_libraries.push_back(_line.substr(7));
		return true;
	}
	
	bool
	ObjModel::load (std::string _filename)
	{
		std::ifstream input(_filename, std::ifstream::in);
		if (!input)
		{
			std::cerr << "Unable to open the file '" << _filename << "'" 
			          << std::endl;
			return false;
		}

		std::string line;
		while (std::getline(input, line))
		{
			line = remove_commentary(line);	
			boost::trim(line);

			ObjInstruction instruction = get_instruction(line);
			switch (instruction)
			{
				case OBJ_INSTR_NONE:
				break;

				case OBJ_INSTR_VERTEX:
					if (!parse_vertex(line))
						return false;
				break;

				case OBJ_INSTR_NORMALVERTEX:
					if (!parse_normal_vertex(line))
						return false;
				break;

				case OBJ_INSTR_TEXVERTEX:
					if (!parse_tex_vertex(line))
						return false;
				break;

				case OBJ_INSTR_FACE:
					if (!parse_face(line))
						return false;
				break;

				case OBJ_INSTR_MATERIALLIBRARY:
					if (!parse_material_library(line))
						return false;
				break;

				case OBJ_INSTR_MATERIAL:
				break;

				case OBJ_INSTR_INVALID:
				default:
					return false;
				break;
			}
		}

		return true;
	}
}

