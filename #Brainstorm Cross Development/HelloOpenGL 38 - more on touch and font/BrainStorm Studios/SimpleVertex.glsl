//Transformation Matrices
uniform mat4 BSProjectionMatrix;
uniform mat4 BSModelViewMatrix;


uniform float CameraExtremeLeft, CameraExtremeRight, CameraExtremeUp, CameraExtremeDown;
uniform float PlayerCoordinatesX, PlayerCoordinatesY;
uniform float ScaleSize;
uniform float isDark;

uniform float TheScaleX, TheScaleY;

uniform float RotationAngle;
uniform float isCircle;

uniform float CircleRadius;

uniform float isFlake;



#if __VERSION__ >= 130

//Vertex position attribute
in vec2 BSVertexPosition2D;

//Texture coordinate attribute
in vec2 BSTextureCoordinates;

out vec2 textureCoordinates;

out float isCircleGLFS;
out float isDarkGLFS;

out vec2 bodyCoordinates;
out float CircleRadiusGLFS;

out float ScaleSizeGLFS;

out float isFlakeGLFS;

#else

//Vertex position attribute
attribute vec2 BSVertexPosition2D;

//Texture coordinate attribute
attribute vec2 BSTextureCoordinates;


varying vec2 textureCoordinates;

varying float isCircleGLFS;
varying float isDarkGLFS;
varying vec2 bodyCoordinates;
varying float CircleRadiusGLFS;

varying float ScaleSizeGLFS;
varying float isFlakeGLFS;

#endif

void main()
{
	isDarkGLFS = isDark;
    
	isFlakeGLFS = isFlake;
    
	isCircleGLFS = isCircle;
	ScaleSizeGLFS = ScaleSize;
    
	CircleRadiusGLFS = CircleRadius / 2.0;
    
    gl_Position = BSProjectionMatrix * BSModelViewMatrix * vec4( BSVertexPosition2D.x, BSVertexPosition2D.y, 0.0, 1.0 );
    bodyCoordinates = BSVertexPosition2D;
    textureCoordinates = BSTextureCoordinates;
}
