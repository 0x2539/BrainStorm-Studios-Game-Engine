#ifndef LSHADERPROGRAM_H_INCLUDED
#define LSHADERPROGRAM_H_INCLUDED


#include "BSOpenGL.h"
#include <stdio.h>
#include <string>

class BSShaderProgram
{
public:
	BSShaderProgram();
	
	virtual ~BSShaderProgram();
	
	virtual bool loadProgram() = 0;
	
	virtual void freeProgram();
	
	bool bind();
	
	void unbind();
	
	GLuint getProgramID();
	
protected:
	void printProgramLog( GLuint program );
	
	void printShaderLog( GLuint shader );
	
	GLuint loadShaderFromFile( std::string path, GLenum shaderType );
	
};


#endif // LSHADERPROGRAM_H_INCLUDED
