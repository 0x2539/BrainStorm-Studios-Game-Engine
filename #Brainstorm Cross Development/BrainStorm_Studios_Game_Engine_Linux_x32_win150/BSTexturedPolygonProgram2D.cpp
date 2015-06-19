#include "BSTexturedPolygonProgram2D.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include <iostream>
#include "BSValues.h"

BSTexturedPolygonProgram2D::BSTexturedPolygonProgram2D()
{
//	mCameraExtremeLeft = 0, mCameraExtremeRight = 0, mCameraExtremeUp = 0, mCameraExtremeDown = 0;
//	mPlayerCoordinates = 0;
//
//	mVertexPos2DLocation = 0;
//	mTexCoordLocation = 0;
//
//	mProjectionMatrixLocation = 0;
//	mModelViewMatrixLocation = 0;
//    mTextureColorLocation = 0;
//    mTextureUnitLocation = 0;
}

bool BSTexturedPolygonProgram2D::loadProgram()
{
	//Generate program
	BSProgramID = glCreateProgram();

	//Load vertex shader
	GLuint vertexShader = loadShaderFromFile( "Shaders/BSTexturedPolygonProgram2D.glvs", GL_VERTEX_SHADER );

    //Check for errors
    if( vertexShader == 0 )
    {
        glDeleteProgram( BSProgramID );
        BSProgramID = 0;
        return false;
    }

	//Attach vertex shader to program
	glAttachShader( BSProgramID, vertexShader );


	//Create fragment shader
	GLuint fragmentShader = loadShaderFromFile( "Shaders/BSTexturedPolygonProgram2D.glfs", GL_FRAGMENT_SHADER );

    //Check for errors
    if( fragmentShader == 0 )
    {
        glDeleteProgram( BSProgramID );
        BSProgramID = 0;
        return false;
    }

	//Attach fragment shader to program
	glAttachShader( BSProgramID, fragmentShader );

	//Link program
    glLinkProgram( BSProgramID );

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv( BSProgramID, GL_LINK_STATUS, &programSuccess );
	if( programSuccess != GL_TRUE )
    {
		printf( "Error linking program %d!\n", BSProgramID );
		printProgramLog( BSProgramID );
        glDeleteProgram( BSProgramID );
        BSProgramID = 0;
        return false;
    }

	loadShaderAttributesLocation(locationBSVertexPosition3D, "BSVertexPosition3D");
	loadShaderAttributesLocation(locationBSTextureCoordinate, "BSTextureCoordinates");


    loadShaderUniformsLocation(ShaderCameraExtremeLeft, "CameraExtremeLeft");
    loadShaderUniformsLocation(ShaderCameraExtremeRight, "CameraExtremeRight");
    loadShaderUniformsLocation(ShaderCameraExtremeUp, "CameraExtremeUp");
    loadShaderUniformsLocation(ShaderCameraExtremeDown, "CameraExtremeDown");
//	ShaderCameraExtremeLeft = glGetUniformLocation(BSProgramID, "CameraExtremeLeft");
//	ShaderCameraExtremeRight = glGetUniformLocation(BSProgramID, "CameraExtremeRight");
//	ShaderCameraExtremeUp = glGetUniformLocation(BSProgramID, "CameraExtremeUp");
//	ShaderCameraExtremeDown = glGetUniformLocation(BSProgramID, "CameraExtremeDown");

    loadShaderUniformsLocation(ShaderPlayerCoordinatesX, "PlayerCoordinatesX");
    loadShaderUniformsLocation(ShaderPlayerCoordinatesY, "PlayerCoordinatesY");
//	ShaderPlayerCoordinatesX = glGetUniformLocation(BSProgramID, "PlayerCoordinatesX");
//	ShaderPlayerCoordinatesY = glGetUniformLocation(BSProgramID, "PlayerCoordinatesY");

    loadShaderUniformsLocation(ShaderScaleSize, "ScaleSize");
    loadShaderUniformsLocation(ShaderScaleOnX, "TheScaleX");
    loadShaderUniformsLocation(ShaderScaleOnY, "TheScaleY");
//	ShaderScaleSize = glGetUniformLocation(BSProgramID, "ScaleSize");
//	ShaderScaleOnX = glGetUniformLocation(BSProgramID, "TheScaleX");
//	ShaderScaleOnY = glGetUniformLocation(BSProgramID, "TheScaleY");

    loadShaderUniformsLocation(ShaderFlake, "isFlake");
    loadShaderUniformsLocation(ShaderIsCircle, "isCircle");
    loadShaderUniformsLocation(ShaderDark, "isDark");
//	ShaderFlake = glGetUniformLocation(BSProgramID, "isFlake");
//	ShaderIsCircle = glGetUniformLocation(BSProgramID, "isCircle");
//	ShaderDark = glGetUniformLocation(BSProgramID, "isDark");




    loadShaderUniformsLocation(ShaderRotationAngle, "RotationAngle");
    loadShaderUniformsLocation(ShaderCircleRadius, "CircleRadius");
//	ShaderRotationAngle = glGetUniformLocation(BSProgramID, "RotationAngle");
//	ShaderCircleRadius = glGetUniformLocation(BSProgramID, "CircleRadius");





    loadShaderUniformsLocation(locationBSTextureColor, "BSTextureColor");
    loadShaderUniformsLocation(locationBSTextureUnit, "BSTextureUnit");

    loadShaderUniformsLocation(locationBSProjectionMatrix, "BSProjectionMatrix");
    loadShaderUniformsLocation(locationBSModelViewMatrix, "BSModelViewMatrix");
//	mTextureColorLocation = glGetUniformLocation( BSProgramID, "BSTextureColor" );
//	mTextureUnitLocation = glGetUniformLocation( BSProgramID, "BSTextureUnit" );

//	mProjectionMatrixLocation = glGetUniformLocation( BSProgramID, "BSProjectionMatrix" );
//	mModelViewMatrixLocation = glGetUniformLocation( BSProgramID, "BSModelViewMatrix" );

	return true;
}



GLint BSTexturedPolygonProgram2D::loadShaderAttributesLocation(GLint &theAttribute, char theShaderAttributeText[])
{
	theAttribute = glGetAttribLocation( BSProgramID, theShaderAttributeText );
	if( theAttribute == -1 )
	{
		printf( "%s is not a valid glsl program variable (attribute, maybe not used)!\n", theShaderAttributeText );
	}
}

GLint BSTexturedPolygonProgram2D::loadShaderUniformsLocation(GLint &theUniform, char theShaderUniformText[])
{
	theUniform = glGetUniformLocation( BSProgramID, theShaderUniformText );
	if( theUniform == -1 )
	{
		printf( "%s is not a valid glsl program variable (uniform, maybe not used)!\n", theShaderUniformText );
	}
}


