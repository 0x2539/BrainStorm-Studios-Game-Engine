//Texture Color
uniform vec4 BSTextureColor;

//Texture Unit
uniform sampler2D BSTextureUnit;

//for the text rendering
uniform sampler2D tex;

const float blurSize = 1.0/100.0;
const float weightSum = 70.0 + 2.0 * (1.0 + 8.0 + 28.0 + 56.0);


#if __VERSION__ >= 130

//Texture coordinate
in vec2 texCoord;
in float isTextGLFS;
in float IsTheSquareForFrag;
in float isCircleGLFS;
in float isDarkGLFS;
in vec2 newCoord;
in float CircleRadiusGLFS;
in float isGlowingGLFS;

in float ScaleSizeGLFS;

//Final color
out vec4 gl_FragColor;
in vec2 v_blurTexCoords2[14];

out float isFlakeGLFS;
#else

//Texture coordinate
varying vec2 texCoord;
varying float IsTheSquareForFrag;
varying float isTextGLFS;
varying float isCircleGLFS;
varying float isDarkGLFS;
varying vec2 newCoord;
varying float CircleRadiusGLFS;
varying float isGlowingGLFS;

varying vec2 v_blurTexCoords2[14];

varying float ScaleSizeGLFS;

varying float isFlakeGLFS;
#endif

void main()
{
	//Set fragment
	//daca nu este nici o culoare atunci randez textura

	if(isTextGLFS == 0.0)
	{
		if(isCircleGLFS == 0.0)
		{
			//if(texture2D( BSTextureUnit, texCoord ) != 0)
			{
				gl_FragColor = texture2D( BSTextureUnit, texCoord ) * BSTextureColor;
			}
			//else
				//daca este o culoare, randez culoarea si nu textura
			{
			//	gl_FragColor = BSTextureColor;
			}
		}
		else
			if(isCircleGLFS == 1.0)
			{
				if(isDarkGLFS == 0.0 && isFlakeGLFS == 0.0)
				{
					float border = 0.0 * ScaleSizeGLFS;
					float radius = CircleRadiusGLFS * ScaleSizeGLFS;
					vec4 color0 = vec4(0.0, 0.0, 0.0, 1.0);
					vec4 color1 = vec4(1.0, 1.0, 1.0, 1.0);

					vec2 m = newCoord * ScaleSizeGLFS;
					float dist = radius - sqrt(m.x * m.x + m.y * m.y);

					float t = 0.0;

					if (dist > border)
					{
						t = 1.0;
					}
					else
						if (dist > 0.0)
						{
							t = dist / border;
						}

					//if(texture2D( BSTextureUnit, texCoord ) != 0)
					{
						gl_FragColor = t * texture2D( BSTextureUnit, texCoord ) * BSTextureColor;
					}
					//else
					{
						//gl_FragColor = t * BSTextureColor;
					}

				}
				else
					if(isDarkGLFS == 1.0)
					{
						float radius = float (CircleRadiusGLFS * ScaleSizeGLFS);

						vec2 m = newCoord * ScaleSizeGLFS;
						float dist = float (radius - sqrt(m.x * m.x + m.y * m.y));

						float t = 0.0;

						if (float(dist / radius) <= 1.0)
						{
							t = float (1.0 - float(dist / radius));
						}

						vec4 newColor = BSTextureColor;
						newColor.a = t;

						//if(texture2D( BSTextureUnit, texCoord ) != 0)
						{
							//BSTextureColor.a = t;
							gl_FragColor = texture2D( BSTextureUnit, texCoord ) * newColor;//BSTextureColor;
						}
						//else
						{
							//BSTextureColor.a = t;
							//gl_FragColor = BSTextureColor;
						}
					}
					else
						if(isFlakeGLFS == 1.0)
						{
							float radius = CircleRadiusGLFS * ScaleSizeGLFS;

							vec2 m = newCoord * ScaleSizeGLFS;
							float dist = radius - sqrt(m.x * m.x + m.y * m.y);

							float t = 0.0;

							if (float(dist / radius) <= 1.0)
							{
								t = float(dist / radius);
							}

							t = float(t / 4.0);

						vec4 newColor = BSTextureColor;
						newColor.a = t;

							//if(texture2D( BSTextureUnit, texCoord ) != 0)
							{
								//BSTextureColor.a = t;
								gl_FragColor = texture2D( BSTextureUnit, texCoord ) * newColor;//BSTextureColor;
							}
							//else
							{
								//BSTextureColor.a *= t;
								//gl_FragColor = BSTextureColor;
							}

						}
			}
	}
	else
	{
		gl_FragColor = BSTextureColor;
		//gl_FragColor = texture2D( tex, texCoord ) * BSTextureColor;
		//gl_FragColor = texture2D( tex, texCoord ) * BSTextureColor;
		//gl_FragColor = vec4(1, 1, 1, texture2D(tex, texCoord).a) * BSTextureColor;
	}
}
