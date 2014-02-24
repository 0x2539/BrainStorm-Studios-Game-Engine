#include "BSTexturedPolygonProgram2D.h"

BSTexturedPolygonProgram2D::BSTexturedPolygonProgram2D()
{
}

bool BSTexturedPolygonProgram2D::loadProgram()
{
	//Generate program
	BSProgramID = glCreateProgram();

	//Load vertex shader
	GLuint vertexShader = loadShaderFromFile("Shaders/BSTexturedPolygonProgram2D.glvs", GL_VERTEX_SHADER);

	//Check for errors
	if(vertexShader == 0)
	{
		glDeleteProgram(BSProgramID);
		BSProgramID = 0;
		return false;
	}

	//Attach vertex shader to program
	glAttachShader(BSProgramID, vertexShader);

	//Create fragment shader
	GLuint fragmentShader = loadShaderFromFile("Shaders/BSTexturedPolygonProgram2D.glfs", GL_FRAGMENT_SHADER);

	//Check for errors
	if(fragmentShader == 0)
	{
		glDeleteProgram(BSProgramID);
		BSProgramID = 0;
		return false;
	}

	//Attach fragment shader to program
	glAttachShader(BSProgramID, fragmentShader);

	//Link program
	glLinkProgram(BSProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(BSProgramID, GL_LINK_STATUS, &programSuccess);
	if(programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", BSProgramID);
		printProgramLog(BSProgramID);
		glDeleteProgram(BSProgramID);
		BSProgramID = 0;
		return false;
	}

	loadShaderAttributesLocation(locationBSVertexPosition3D, "BSVertexPosition3D");
	loadShaderAttributesLocation(locationBSTextureCoordinate, "BSTextureCoordinates");

	loadShaderUniformsLocation(ShaderScaleSize, "ScaleSize");

	loadShaderUniformsLocation(ShaderFlake, "isFlake");
	loadShaderUniformsLocation(ShaderIsCircle, "isCircle");
	loadShaderUniformsLocation(ShaderDark, "isDark");

	loadShaderUniformsLocation(ShaderCircleRadius, "CircleRadius");

	loadShaderUniformsLocation(locationBSTextureColor, "BSTextureColor");
	loadShaderUniformsLocation(locationBSTextureUnit, "BSTextureUnit");

	loadShaderUniformsLocation(locationBSProjectionMatrix, "BSProjectionMatrix");
	loadShaderUniformsLocation(locationBSModelViewMatrix, "BSModelViewMatrix");

	return true;
}



void BSTexturedPolygonProgram2D::loadShaderAttributesLocation(GLint &theAttribute, std::string theShaderAttributeText)
{
	theAttribute = glGetAttribLocation(BSProgramID, theShaderAttributeText.c_str());
	if(theAttribute == -1)
	{
		printf("%s is not a valid glsl program variable (attribute, maybe not used)!\n", theShaderAttributeText.c_str());
	}
}

void BSTexturedPolygonProgram2D::loadShaderUniformsLocation(GLint &theUniform, std::string theShaderUniformText)
{
	theUniform = glGetUniformLocation(BSProgramID, theShaderUniformText.c_str());
	if(theUniform == -1)
	{
		printf("%s is not a valid glsl program variable (uniform, maybe not used)!\n", theShaderUniformText.c_str());
	}
}
