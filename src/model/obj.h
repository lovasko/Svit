#ifndef SVIT_MODEL_OBJ_H
#define SVIT_MODEL_OBJ_H

#include <vector>

#include "geom/point.h"
#include "geom/vector.h"
#include "model/model.h"

namespace Svit
{
	enum ObjInstruction
	{
		OBJ_INSTR_NONE = 100, 
		OBJ_INSTR_INVALID, 
		OBJ_INSTR_VERTEX, 
		OBJ_INSTR_TEXVERTEX, 
		OBJ_INSTR_NORMALVERTEX, 
		OBJ_INSTR_PARAMVERTEX, 
		OBJ_INSTR_CURVEVERTEX, 
		OBJ_INSTR_DEGREE, 
		OBJ_INSTR_BASISMATRIX, 
		OBJ_INSTR_STEP, 
		OBJ_INSTR_POINT, 
		OBJ_INSTR_LINE, 
		OBJ_INSTR_FACE,
		OBJ_INSTR_CURVE, 
		OBJ_INSTR_CURVE2, 
		OBJ_INSTR_SURFACE, 
		OBJ_INSTR_CURVEPARAMETER, 
		OBJ_INSTR_CURVETRIM, 
		OBJ_INSTR_CURVEHOLE, 
		OBJ_INSTR_CURVESPECIALCURVE, 
		OBJ_INSTR_CURVESPECIALPOINT, 
		OBJ_INSTR_CURVEEND, 
		OBJ_INSTR_CONNECT, 
		OBJ_INSTR_GROUP, 
		OBJ_INSTR_SMOOTH, 
		OBJ_INSTR_MERGINGGROUP, 
		OBJ_INSTR_OBJECT, 
		OBJ_INSTR_BEVEL, 
		OBJ_INSTR_COLORINTERPOLATION, 
		OBJ_INSTR_DISSOLVEINTERPOLATION, 
		OBJ_INSTR_LOD, 
		OBJ_INSTR_MATERIAL, 
		OBJ_INSTR_MATERIALLIBRARY, 
		OBJ_INSTR_SHADOW, 
		OBJ_INSTR_TRACE, 
		OBJ_INSTR_APPROXCURVE, 
		OBJ_INSTR_APPROXSURFACE 
	};

	class ObjModel : public Model
	{
		private:
			std::vector<Point3> normals;
			std::vector<Point2> tex_coords;
			std::vector<std::string> material_libraries;

			std::string
			remove_commentary (std::string &_line);

			ObjInstruction
			get_instruction (std::string& _line);

			bool
			parse_vertex (std::string& _line);

			bool
			parse_normal_vertex (std::string& _line);

			bool
			parse_tex_vertex (std::string& _line);

			bool
			parse_face (std::string& _line);

			bool
			parse_material_library (std::string& _line);

		public:
			std::vector<Point3> vertices;

			ObjModel ();

			bool
			load (std::string _filename);
	};
}

#endif

