#ifndef LTEXTUREDPOLYGONPROGRAM2D_H_INCLUDED
#define LTEXTUREDPOLYGONPROGRAM2D_H_INCLUDED

#include "BSShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include <iostream>
#include "BSValues.h"



class BSTexturedPolygonProgram2D : public BSShaderProgram
{
public:

	BSTexturedPolygonProgram2D();

	bool loadProgram();

	void loadShaderAttributesLocation(GLint &theAttribute, std::string theShaderAttributeText);
	void loadShaderUniformsLocation(GLint &theUniform, std::string theShaderUniformText);
};


#endif // LTEXTUREDPOLYGONPROGRAM2D_H_INCLUDED
