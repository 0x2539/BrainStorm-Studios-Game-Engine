#ifndef LTEXTUREDPOLYGONPROGRAM2D_H_INCLUDED
#define LTEXTUREDPOLYGONPROGRAM2D_H_INCLUDED

#include "BSShaderProgram.h"
#include "glm/glm.hpp"
#include "BSValues.h"

class BSTexturedPolygonProgram2D : public BSShaderProgram
{
	public:

    BSTexturedPolygonProgram2D();

    bool loadProgram();

    GLint loadShaderAttributesLocation(GLint &theAttribute, char theShaderAttributeText[]);
    GLint loadShaderUniformsLocation(GLint &theUniform, char theShaderUniformText[]);
};


#endif // LTEXTUREDPOLYGONPROGRAM2D_H_INCLUDED
