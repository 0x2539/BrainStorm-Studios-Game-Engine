#include "BSTexturedPolygonProgram2D.h"


static const char gVertexShader[] =
		"uniform mat4 BSProjectionMatrix;\n"
				"uniform mat4 BSModelViewMatrix;\n"
				"uniform float ScaleSize;\n"
				"uniform float isDark;\n"
				"uniform float RotationAngle;\n"
				"uniform float isCircle;\n"
				"uniform float CircleRadius;\n"
				"uniform float isFlake;\n"
				"#if __VERSION__ >= 130\n"
				"in vec3 BSVertexPosition3D;\n"
				"in vec2 BSTextureCoordinates;\n"
				"out vec2 textureCoordinates;\n"
				"out float isCircleGLFS;\n"
				"out float isDarkGLFS;\n"
				"out vec3 bodyCoordinates;\n"
				"out float CircleRadiusGLFS;\n"
				"out float ScaleSizeGLFS;\n"
				"out float isFlakeGLFS;\n"
				"#else\n"
				"attribute vec3 BSVertexPosition3D;\n"
				"attribute vec2 BSTextureCoordinates;\n"
				"varying vec2 textureCoordinates;\n"
				"varying float isCircleGLFS;\n"
				"varying float isDarkGLFS;\n"
				"varying vec3 bodyCoordinates;\n"
				"varying float CircleRadiusGLFS;\n"
				"varying float ScaleSizeGLFS;\n"
				"varying float isFlakeGLFS;\n"
				"#endif\n"
				"void main()\n"
				"{\n"
				"isDarkGLFS = isDark;\n"
				"isFlakeGLFS = isFlake;\n"
				"isCircleGLFS = isCircle;\n"
				"ScaleSizeGLFS = ScaleSize;\n"
				"CircleRadiusGLFS = CircleRadius / 2.0;\n"
				"gl_Position = BSProjectionMatrix * BSModelViewMatrix * vec4( BSVertexPosition3D.x, BSVertexPosition3D.y, 0.0, 1.0 );\n"
				"bodyCoordinates = BSVertexPosition3D;\n"
				"textureCoordinates = BSTextureCoordinates;\n"
				"}\n";

static const char gFragmentShader[] =
				"precision mediump float;\n"
				"uniform vec4 BSTextureColor;\n"
				"uniform sampler2D BSTextureUnit;\n"
				"#if __VERSION__ >= 130\n"
				"in vec2 textureCoordinates;\n"
				"in float isCircleGLFS;\n"
				"in float isDarkGLFS;\n"
				"in vec3 bodyCoordinates;\n"
				"in float CircleRadiusGLFS;\n"
				"in float ScaleSizeGLFS;\n"
				"out vec4 gl_FragColor;\n"
				"out float isFlakeGLFS;\n"
				"#else\n"
				"varying vec2 textureCoordinates;\n"
				"varying float isCircleGLFS;\n"
				"varying float isDarkGLFS;\n"
				"varying vec3 bodyCoordinates;\n"
				"varying float CircleRadiusGLFS;\n"
				"varying float ScaleSizeGLFS;\n"
				"varying float isFlakeGLFS;\n"
				"#endif\n"
				"void main()\n"
				"{\n"
				"if(isCircleGLFS == 0.0)\n"
				"{\n"
				"gl_FragColor = texture2D( BSTextureUnit, textureCoordinates ) * BSTextureColor;\n"
				"}\n"
				"else\n"
				"if(isCircleGLFS != 0.0)\n"
				"{\n"
				"if(isDarkGLFS == 0.0 && isFlakeGLFS == 0.0)\n"
				"{\n"
				"float border = 0.0 ;\n"
				"float radius = CircleRadiusGLFS ;\n"
				"vec3 m = bodyCoordinates ;\n"
				"float dist = radius - sqrt(m.x * m.x + m.y * m.y);\n"
				"float t = 0.0;\n"
				"if (dist > border)\n"
				"{\n"
				"t = 1.0;\n"
				"}\n"
				"else\n"
				"if (dist > 0.0)\n"
				"{\n"
				"t = dist / border;\n"
				"}\n"
				"gl_FragColor = t * texture2D( BSTextureUnit, textureCoordinates ) * BSTextureColor;\n"
				"}\n"
				"else\n"
				"if(isDarkGLFS != 0.0)\n"
				"{\n"
				"float radius = float (CircleRadiusGLFS * 32.0);\n"
				"vec3 m = bodyCoordinates * 32.0;\n"
				"float dist = float (radius - sqrt(m.x * m.x + m.y * m.y));\n"
				"float t = 0.0;\n"
				"if (float(dist / radius) <= 1.0)\n"
				"{\n"
				"t = float (1.0 - float(dist / radius));\n"
				"}\n"
				"vec4 color = BSTextureColor;\n"
				"color.a = t;\n"
				"gl_FragColor = texture2D( BSTextureUnit, textureCoordinates ) * color;\n"
				"}\n"
				"else\n"
				"if(isFlakeGLFS != 0.0)\n"
				"{\n"
				"float radius = CircleRadiusGLFS * 32.0;\n"
				"vec3 m = bodyCoordinates * 32.0;\n"
				"float dist = radius - sqrt(m.x * m.x + m.y * m.y);\n"
				"float t = 0.0;\n"
				"if (float(dist / radius) <= 1.0)\n"
				"{\n"
				"t = float(dist / radius);\n"
				"}\n"
				"t = float(t / 4.0);\n"
				"vec4 color = BSTextureColor;\n"
				"color.a = t;\n"
				"gl_FragColor = texture2D( BSTextureUnit, textureCoordinates ) * color;\n"
				"}\n"
				"}\n"
				"}\n";


BSTexturedPolygonProgram2D::BSTexturedPolygonProgram2D()
{
}

bool BSTexturedPolygonProgram2D::loadProgram()
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, gVertexShader);
    if (!vertexShader)
    {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, gFragmentShader);
    if (!pixelShader)
    {
        return 0;
    }

    BSProgramID = glCreateProgram();
    if (BSProgramID)
    {
        glAttachShader(BSProgramID, vertexShader);
        checkGlError("glAttachShaderVertex");
        glAttachShader(BSProgramID, pixelShader);
        checkGlError("glAttachShaderPixel");
        glLinkProgram(BSProgramID);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(BSProgramID, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(BSProgramID, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = (char*) malloc(bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(BSProgramID, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(BSProgramID);
            BSProgramID = 0;
            return false;
        }
    }

	/*//Generate program
	BSProgramID = glCreateProgram();

	//Load vertex shader
	GLuint vertexShader = loadShader(gFragmentShader, GL_VERTEX_SHADER );

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
*/
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



void BSTexturedPolygonProgram2D::loadShaderAttributesLocation(GLuint &theAttribute, std::string theShaderAttributeText)
{
	theAttribute = glGetAttribLocation( BSProgramID, theShaderAttributeText.c_str() );
	if( theAttribute == -1 )
	{
		printf( "%s is not a valid glsl program variable (attribute, maybe not used)!\n", theShaderAttributeText.c_str() );
	}
}

void BSTexturedPolygonProgram2D::loadShaderUniformsLocation(GLuint &theUniform, std::string theShaderUniformText)
{
	theUniform = glGetUniformLocation( BSProgramID, theShaderUniformText.c_str() );
	if( theUniform == -1 )
	{
		printf( "%s is not a valid glsl program variable (uniform, maybe not used)!\n", theShaderUniformText.c_str() );
	}
}
