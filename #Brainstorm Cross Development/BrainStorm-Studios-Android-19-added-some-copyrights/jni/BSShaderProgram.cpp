/*
 * Some of the code from this class was taken from the Lazy-Foo tutorials, so all copyrights reserved to Lazy-Foo. There was no point in changing or adding
 * the code, because the only thing it does is some error checking and some shader compiling.
 */
#include "BSShaderProgram.h"
#include "BSValues.h"
#include <fstream>

BSShaderProgram::BSShaderProgram()
{
	BSProgramID = 0;
}

BSShaderProgram::~BSShaderProgram()
{
    //Free program if it exists
    freeProgram();
}

void BSShaderProgram::freeProgram()
{
    //Delete program
    glDeleteProgram( BSProgramID );
}

bool BSShaderProgram::bind()
{
	//Use shader
	glUseProgram( BSProgramID );

	//Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        LOGE("Could not create program.");
        //printf( "Error binding shader! %s\n", gluErrorString( error ) );
		printProgramLog( BSProgramID );
        return false;
    }

	return true;
}

void BSShaderProgram::unbind()
{
    //Use default program
	glUseProgram( 0 );
}

GLuint BSShaderProgram::getProgramID()
{
	return BSProgramID;
}

void BSShaderProgram::printProgramLog( GLuint program )
{
	/*
	//Make sure name is shader
	if( glIsProgram( program ) )
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

		//Allocate string
		char* infoLog = new char[ maxLength ];

		//Get info log
		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
	        //LOGE("Could not create program.");
			//Print Log
	        LOGE( "%s\n", infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		LOGE("Name %d is not a program\n", program);
		//printf( "Name %d is not a program\n", program );
	}
	*/
}

void BSShaderProgram::printShaderLog( GLuint shader )
{
/*	//Make sure name is shader
	if( glIsShader( shader ) )
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

		//Allocate string
		char* infoLog = new char[ maxLength ];

		//Get info log
		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			LOGE("%s\n", infoLog );
			//printf( "%s\n", infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		LOGE( "Name %d is not a shader\n", shader );
		//printf( "Name %d is not a shader\n", shader );
	}
	*/
}



GLuint BSShaderProgram::loadShader(GLenum shaderType, const char* pSource)
{
    GLuint shaderID = glCreateShader(shaderType);
    if (shaderID)
    {
        glShaderSource(shaderID, 1, &pSource, NULL);
        glCompileShader(shaderID);
        GLint compiled = 0;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char* buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shaderID, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shaderID);
                shaderID = 0;
            }
        }
    }
    return shaderID;
}
