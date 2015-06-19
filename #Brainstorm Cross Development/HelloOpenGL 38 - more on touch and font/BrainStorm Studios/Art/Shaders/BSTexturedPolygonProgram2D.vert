//Transformation Matrices
uniform mat4 BSProjectionMatrix;
uniform mat4 BSModelViewMatrix;


uniform float CameraExtremeLeft, CameraExtremeRight, CameraExtremeUp, CameraExtremeDown;
uniform float PlayerCoordinatesX, PlayerCoordinatesY;
uniform float MoveCameraX, MoveCameraY, ScaleSize;
uniform float isDark;

uniform float MouseX, MouseY, theWidthOfSquare, theHeightOfSquare, AflaRestulWidthOfSquare, AflaRestulHeightOfSquare;
uniform float isTheSquare;
uniform float TheScaleX, TheScaleY;

uniform float RotationAngle;
uniform float cosRotation;
uniform float isRotated;
uniform float isText;
uniform float isCircle;

uniform float CircleRadius;

uniform float isFlake;



#if __VERSION__ >= 130

//Vertex position attribute
in vec2 BSVertexPosition2D;

//Texture coordinate attribute
in vec2 BSTextureCoordinates;

//The coordinates for the text render, xy-vector coordinates, zw-texture coordinates
in vec4 textRenderCoord;

out vec2 texCoord;

out float isTextGLFS;
out float isCircleGLFS;
out float isDarkGLFS;

//isTheSquare o sa il folosesc in frag shader sa vad daca randez culoare sau textura
out float IsTheSquareForFrag;
out vec2 newCoord;
out float CircleRadiusGLFS;

out float ScaleSizeGLFS;

out float isFlakeGLFS;

#else

//Vertex position attribute
attribute vec2 BSVertexPosition2D;

//Texture coordinate attribute
attribute vec2 BSTextureCoordinates;

//The coordinates for the text render, xy-vector coordinates, zw-texture coordinates
attribute vec4 textRenderCoord;

varying vec2 texCoord;
varying float IsTheSquareForFrag;

varying float isTextGLFS;
varying float isCircleGLFS;
varying float isDarkGLFS;
varying vec2 newCoord;
varying float CircleRadiusGLFS;

varying float ScaleSizeGLFS;
varying float isFlakeGLFS;

#endif

void main()
{
	isDarkGLFS = isDark;

	isFlakeGLFS = isFlake;

	isTextGLFS = isText;
	isCircleGLFS = isCircle;
	ScaleSizeGLFS = ScaleSize;

	CircleRadiusGLFS = CircleRadius / 2.0;

	//Process texCoord
	IsTheSquareForFrag = isTheSquare;

	float moveTheCameraX = 0.0, moveTheCameraY = 0.0;

	float newX = BSVertexPosition2D.x, newY = BSVertexPosition2D.y;

/*
	if(BSVertexPosition2D.x < 0.0)
	{
		newX -= TheScaleX / 2.0;
	}
	else
		if(BSVertexPosition2D.x > 0.0)
		{
			newX += TheScaleX / 2.0;
		}


	if(BSVertexPosition2D.y < 0.0)
	{
		newY -= TheScaleY / 2.0;
	}
	else
		if(BSVertexPosition2D.y > 0.0)
		{
			newY += TheScaleY / 2.0;
		}*/

	//daca nu randeaza patratul de la coordonatele mouseului
	if(isTheSquare == 0.0 && isText == 0.0)
	{
		//daca se alfa in partea de stanga jos a ecranului
		if(PlayerCoordinatesX <= CameraExtremeLeft)
		{
			moveTheCameraX = 0.0;
		}
		else
			//daca se misca pe orizontala, dar nu a ajuns la final
			if(PlayerCoordinatesX > CameraExtremeLeft && PlayerCoordinatesX < CameraExtremeRight)
			{
				moveTheCameraX = CameraExtremeLeft - PlayerCoordinatesX;
			}
			else
				//se misca pe orizontala si a ajuns la final
				if(PlayerCoordinatesX > CameraExtremeRight)
				{
					moveTheCameraX = -CameraExtremeRight + CameraExtremeLeft;
				}

		if(PlayerCoordinatesY <= CameraExtremeDown)
		{
			moveTheCameraY = 0.0;
		}
		else
			//se misca pe verticala, dar nu a ajuns la final
			if(PlayerCoordinatesY > CameraExtremeDown && PlayerCoordinatesY < CameraExtremeUp)
			{
				moveTheCameraY = CameraExtremeDown - PlayerCoordinatesY;
			}
			else
				//se misca pe verticala si a ajuns la final
				if(PlayerCoordinatesY > CameraExtremeUp)
				{
					moveTheCameraY = -CameraExtremeUp + CameraExtremeDown;
				}


		//rotate the body if it needs it
		vec2 nouaPoz = BSVertexPosition2D;
		//nouaPoz.x = newX;
		//nouaPoz.y = newY;
		if(isRotated == 1.0)
		{
			nouaPoz.x = BSVertexPosition2D.x * cos(cosRotation) - BSVertexPosition2D.y * sin(cosRotation);
			nouaPoz.y = BSVertexPosition2D.y * sin(cosRotation) + BSVertexPosition2D.y * cos(cosRotation);
		}
		gl_Position = BSProjectionMatrix * BSModelViewMatrix * vec4( (nouaPoz.x  + moveTheCameraX) * ScaleSize,
																	(nouaPoz.y + moveTheCameraY) * ScaleSize, 0.0, 1.0 );
		newCoord = BSVertexPosition2D;
		texCoord = BSTextureCoordinates;
	}
	else
		if(isText == 1.0)
		{
			gl_Position = BSProjectionMatrix * BSModelViewMatrix * vec4(textRenderCoord.x * ScaleSize,
																		textRenderCoord.y * ScaleSize, 0.0, 1.0);
			texCoord = textRenderCoord.zw;

			//texCoord = textRenderCoord.zw;
			//gl_Position = BSProjectionMatrix * BSModelViewMatrix * vec4( (textRenderCoord.x  ) ,
			//														(textRenderCoord.y ) , 0.0, 1.0 );
		}
		else
			if(isTheSquare == 1.0)
			{

/*
				float variabilaImpartireX = 0, variabilaImpartireY = 0.0;

				variabilaImpartireX = theWidthOfSquare;
				variabilaImpartireY = theHeightOfSquare;

				int XX;
					XX = int ( (-BSVertexPosition2D.x + MouseX) / variabilaImpartireX);
					XX *= int (variabilaImpartireX) * ScaleSize;

				int YY;
					YY = int ( (-BSVertexPosition2D.y + MouseY) / variabilaImpartireY);
					YY *= int (variabilaImpartireY) * ScaleSize;




				int pos1 = int (BSVertexPosition2D.x * ScaleSize);// - XX * ScaleSize;
				int pos2 = int (BSVertexPosition2D.y * ScaleSize);// - YY * ScaleSize;
				gl_Position = BSProjectionMatrix * BSModelViewMatrix * vec4( (pos1), (pos2), 0.0, 1.0 );

*/
			}

	texCoord = BSTextureCoordinates;
}
