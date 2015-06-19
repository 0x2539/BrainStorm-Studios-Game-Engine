#include <glew.h>
#include "BSUtilities.h"
#include "BSValues.h"
#include <iostream>
#include <fstream>
#include "BSObstacles.h"
#include "BSTexturedPolygonProgram2D.h"
#include "BSTexture.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "BSLevelMenu.h"
#include "BSXmlFiles.h"
#include "glm/gtc/type_ptr.hpp"

bool aIncarcatHarta = false;
BSObstacles *obstacle = new BSObstacles();
BSLevelMenu *theLevels = new BSLevelMenu;

//Textured polygon shader
BSTexturedPolygonProgram2D gTexturedPolygonProgram2D;

//Loaded texture
BSTexture *gOpenGLTexture = new BSTexture;
BSColorRGBA gTextureColor = { 1.f, 1.f, 1.f, 1.f };

/*int BSUtilities::OpenAlEndWithError(char* msg, int error=0)
 {
 //Display error message in console
 std::cout << msg << "\n";
 system("PAUSE");
 return error;
 }*/
typedef unsigned int DWORD;
typedef unsigned char BYTE;

int endWithError(std::string msg, int error=0)
{
    //Display error message in console
    std::cout << msg << "\n";
    return error;
}


bool BSUtilities::createOpenAlContext()
{
    //Now OpenAL needs to be initialized
    deviceOpenAL = alcOpenDevice(NULL);                                               //Open the device
    if(!deviceOpenAL) return endWithError("no sound device");
	//Error during device oening
    contextOpenAL = alcCreateContext(deviceOpenAL, NULL);                                   //Give the device a context
    alcMakeContextCurrent(contextOpenAL);                                             //Make the context the current
    if(!contextOpenAL) return endWithError("no sound context");                       //Error during context handeling
	
}

bool BSUtilities::openTheWavfile(char path[], ALuint &sourceOfSound, ALuint &bufferOfSound)
{
    //Loading of the WAVE file
    FILE *fp = NULL;                                                            //Create FILE pointer for the WAVE file
    fp=fopen(path,"rb");                                            //Open the WAVE file
    if (!fp) return endWithError("Failed to open file");                        //Could not open file
	
    //Variables to store info about the WAVE file (all of them is not needed for OpenAL)
    char type[4];
    DWORD size,chunkSize;
    short formatType,channels;
    DWORD sampleRate,avgBytesPerSec;
    short bytesPerSample,bitsPerSample;
    DWORD dataSize;
	
    //Check that the WAVE file is OK
    fread(type,sizeof(char),4,fp);                                              //Reads the first bytes in the file
    if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F')            //Should be "RIFF"
		return endWithError ("No RIFF");                                            //Not RIFF
	
    fread(&size, sizeof(DWORD),1,fp);                                           //Continue to read the file
    fread(type, sizeof(char),4,fp);                                             //Continue to read the file
    if (type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E')           //This part should be "WAVE"
		return endWithError("not WAVE");                                            //Not WAVE
	
    fread(type,sizeof(char),4,fp);                                              //Continue to read the file
    if (type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' ')           //This part should be "fmt "
		return endWithError("not fmt ");                                            //Not fmt
	
    //Now we know that the file is a acceptable WAVE file
    //Info about the WAVE data is now read and stored
    fread(&chunkSize,sizeof(DWORD),1,fp);
    fread(&formatType,sizeof(short),1,fp);
    fread(&channels,sizeof(short),1,fp);
    fread(&sampleRate,sizeof(DWORD),1,fp);
    fread(&avgBytesPerSec,sizeof(DWORD),1,fp);
    fread(&bytesPerSample,sizeof(short),1,fp);
    fread(&bitsPerSample,sizeof(short),1,fp);
	
    fread(type,sizeof(char),4,fp);
    if (type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a')           //This part should be "data"
		return endWithError("Missing DATA");                                        //not data
	
    fread(&dataSize,sizeof(DWORD),1,fp);                                        //The size of the sound data is read
	
	
    unsigned char* buf= new unsigned char[dataSize];                            //Allocate memory for the sound data
    std::cout << fread(buf,sizeof(BYTE),dataSize,fp) << " bytes loaded\n";           //Read the sound data and display the
																					 //number of bytes loaded.
																					 //Should be the same as the Data Size if OK
	
	
    ///The Sample Rate of the WAVE file
	ALuint frequency = sampleRate;
	///The audio format (bits per sample, number of channels)
	ALenum format=0;
	
	
	
	///Generate one OpenAL Buffer and link to "buffer"
	alGenBuffers(1, &bufferOfSound);
	///Generate one OpenAL Source and link to "source"
	alGenSources(1, &sourceOfSound);
	
	
	if(alGetError() != AL_NO_ERROR)
	{
		std::cout<<"error GenSource"<<'\n';
	}
	
	///Figure out the format of the WAVE file
	if(bitsPerSample == 8)
	{
		if(channels == 1)
			format = AL_FORMAT_MONO8;
		else
			if(channels == 2)
				format = AL_FORMAT_STEREO8;
	}
	else
		if(bitsPerSample == 16)
		{
			if(channels == 1)
				format = AL_FORMAT_MONO16;
			else
				if(channels == 2)
					format = AL_FORMAT_STEREO16;
		}
	
	if(!format)
	{
		std::cout<<"Wrong BitPerSample"<<'\n';
	}
	
	
	///Store the sound data in the OpenAL Buffer
	alBufferData(bufferOfSound, format, buf, dataSize, frequency);
	
	if(alGetError() != AL_NO_ERROR)
	{
		std::cout<<"Error loading ALBuffer"<<'\n';
	}
	
	///Sound setting variables
	//Position of the source sound
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
	//Velocity of the source sound
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
	//Position of the listener
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
	//Velocity of the listener
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
	//Orientation of the listener, First direction vector, then vector pointing up)
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
	
	///Listener
	//Set position of the listener
	alListenerfv(AL_POSITION,    ListenerPos);
	//Set velocity of the listener
	alListenerfv(AL_VELOCITY,    ListenerVel);
	//Set orientation of the listener
	alListenerfv(AL_ORIENTATION, ListenerOri);
	
	///Source
	//Link the buffer to the source
	alSourcei (sourceOfSound, AL_BUFFER,   bufferOfSound);
	//Set the pitch of the source
	alSourcef (sourceOfSound, AL_PITCH,    1.0f     );
	//Set the gain of the source
	alSourcef (sourceOfSound, AL_GAIN,     1.0f     );
	//Set the position of the source
	alSourcefv(sourceOfSound, AL_POSITION, SourcePos);
	//Set the velocity of the source
	alSourcefv(sourceOfSound, AL_VELOCITY, SourceVel);
	//Set if source is looping sound
	alSourcei (sourceOfSound, AL_LOOPING,  AL_FALSE );
	
	
	//Play the sound buffer linked to the source
	if(alGetError() != AL_NO_ERROR)
	{
		std::cout<<"Error playing sound"<<'\n';
	}
}

bool BSUtilities::isPlaying(ALuint theSource)
{
	ALenum state;
	
	alGetSourcei(theSource, AL_SOURCE_STATE, &state);
	
	return (state == AL_PLAYING);
}




bool BSUtilities::initAL()
{
	createOpenAlContext();
	openTheWavfile("Sounds/menu.wav", SourceSoundMusic1, BufferSoundMusic1);
	openTheWavfile("Sounds/Mus_Forest_01.wav", SourceSoundMusic2, BufferSoundMusic2);
	openTheWavfile("Sounds/Mus_Forest_03.wav", SourceSoundMusic3, BufferSoundMusic3);
	newVolumeAudio = 1.f;
	alSourcef(SourceSoundMusic1, AL_GAIN, newVolumeAudio);
	alSourcef(SourceSoundMusic2, AL_GAIN, newVolumeAudio);
	alSourcef(SourceSoundMusic3, AL_GAIN, newVolumeAudio);
	
	alSourcePlay(SourceSoundMusic1);
	muscicIndex = 1;
	
	openTheWavfile("Sounds/mb_die.wav", SourceSoundDies, BufferSoundDies);
	openTheWavfile("Sounds/mb_jump.wav", SourceSoundJump, BufferSoundJump);
	openTheWavfile("Sounds/sfx_fadeout.wav", SourceSoundBeginningGame, BufferSoundBeginningGame);
	openTheWavfile("Sounds/sfx_menu_next coin2.wav", SourceSoundCoin, BufferSoundCoin);
	openTheWavfile("Sounds/Dragon Ball Z - Super Saiyan Sound Effect.wav", SourceSoundPowerUp, BufferSoundPowerUp);
	openTheWavfile("Sounds/anim_ray_liftoff.wav", SourceSoundTeleport, BufferSoundTeleport);
	
    ALfloat Pitch = 1.5f;
    alSourcef(SourceSoundTeleport, AL_PITCH, Pitch);
}

bool BSUtilities::initGL()
{
	//Initialize GLEW
	GLenum glewError = glewInit();
	
	if( glewError != GLEW_OK )
	{
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
		return false;
	}
	//std::cout<<"pula"<<'\n';
	
	//Make sure OpenGL 2.1 is supported
	if( !GLEW_VERSION_2_1 )
	{
		printf( "OpenGL 2.1 not supported!\n" );
		return false;
	}
	
	//Set the viewport
	//	glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );
	
	//Initialize clear color
	glClearColor( 1.f, 1.f, 1.f, 1.f );
	
	//Enable texturing
	glEnable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );
	
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	
	//Check for error
	GLenum error = glGetError();
	
	if( error != GL_NO_ERROR )
	{
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		return false;
	}
	
	return true;
}

bool BSUtilities::loadGP()
{
	//Load textured shader program
	if( !gTexturedPolygonProgram2D.loadProgram() )
	{
		printf( "Unable to load textured polygon program!\n" );
		return false;
	}
	
	//Bind textured shader program
	gTexturedPolygonProgram2D.bind();
	
	//Initialize projection
	//	gTexturedPolygonProgram2D.setProjection( glm::ortho<GLfloat>( 0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 1.0, -1.0 ) );
	//BSProjectionMatrix = glm::ortho<GLfloat>( 0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 1.0, -1.0 );
	///gTexturedPolygonProgram2D.updateProjection();
	//glUniformMatrix4fv(	locationBSProjectionMatrix, 1, GL_FALSE, glm::value_ptr( BSProjectionMatrix ) );
	
    BSProjectionMatrix = glm::perspective(45.0f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 10000.0f);
	glUniformMatrix4fv(	locationBSProjectionMatrix, 1, GL_FALSE, glm::value_ptr( BSProjectionMatrix ) );
	
	
	//Initialize modelview
	///gTexturedPolygonProgram2D.setModelView( glm::mat4() );
	BSModelViewMatrix = glm::mat4();
	///gTexturedPolygonProgram2D.updateModelView();
	glUniformMatrix4fv(	locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr( BSModelViewMatrix ) );
	
	//Set texture unit
	///gTexturedPolygonProgram2D.setTextureUnit( 0 );
	glUniform1i( locationBSTextureUnit, 0 );
	
	return true;
}

bool BSUtilities::loadMedia()
{
	iData[0] = 0;
	iData[1] = 1;
	iData[2] = 2;
	iData[3] = 3;
	
	SDL_PollEvent( &event );
	
	obstacle->setTheVaoData(originalBody->vao, originalBody->vbo, originalBody->ibo, originalBody->data, 1.0f, 1.0f);
	
	gOpenGLTexture->loadTheLoadingImage();
	
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gOpenGLTexture->renderTheLoadingImage(1);
	SDL_GL_SwapBuffers();
	
	gOpenGLTexture->loadATexture("blank.png", blankTexture);
	
	
	std::cout<<"Began loading the textures..."<<'\n';
	std::cout<<'\n';
	gOpenGLTexture->loadTextures();
	std::cout<<'\n';
	std::cout<<"Finished loading the textures!"<<'\n';
	std::cout<<'\n';
	
	std::cout<<"Began loading the bodies..."<<'\n';
	std::cout<<'\n';
	obstacle->addBackgrounds();
	obstacle->setUpBodies();
	obstacle->addSnowFlakeS();///functia incarcaHarta() trebuie sa fie interogata inainte!!! pentru CameraExtremeLeft,up,right,down
	obstacle->createMouseCircles();
	obstacle->addTheTexturesOfCloudyParticles();
	obstacle->addCloudyParticles();
	gOpenGLTexture->buildRainDrops();
	loadCoinsAndDeaths();
	std::cout<<'\n';
	std::cout<<"Finished loading the bodies!"<<'\n';
	std::cout<<'\n';
	///gOpenGLTexture->initVboAndVao();
	
	std::cout<<"Began loading the chapters..."<<'\n';
	std::cout<<'\n';
	theLevels->loadChapters();
	std::cout<<'\n';
	std::cout<<"Finished loading the chapters!"<<'\n';
	std::cout<<'\n';
	gOpenGLTexture->initMenuButtons();
	
	
	///theLevels->loadLevels();
	gOpenGLTexture->initMenuLevels();
	
	
	gOpenGLTexture->initTheFont();
	std::cout<<"done utilities"<<'\n';
	return true;
}

void BSUtilities::loadCoinsAndDeaths()
{
	std::ifstream coinsAndDeaths("coinsAndDeaths");
	coinsAndDeaths>>coinsTotalNo>>deathsTotalNo;
}

void BSUtilities::update()
{
	//for (int32 i = 0; i < 6; ++i)
	{
	    if(!isTeleporting)
		{
		    world->Step((float) 1/theTimeHowFast , 8, 3); //1/60, 8, 3
														  //world.step(1/30,10,10); //performs a time step in the box2d simulation
            world->ClearForces();
            //world->DrawDebugData();
		}
	}
}

void BSUtilities::render()
{
	//	//Clear color buffer
	//	glClear( GL_COLOR_BUFFER_BIT );
	//
	//	//Reset transformations
	//	gTexturedPolygonProgram2D.setModelView( glm::mat4() );
	//
	//	//Render texture centered
	//	//gTextureColor = { 1.f, 1.f, 1.f, 1.f };
	//	//gTexturedPolygonProgram2D.setTextureColor( gTextureColor );
	//	gOpenGLTexture->renderVboAndVao();//( ( SCREEN_WIDTH  ) / 2.f, ( SCREEN_HEIGHT ) / 2.f );
	//
	//	//Update screen
	//	SDL_GL_SwapBuffers();///    glutSwapBuffers();
}

void canPressKeyAgainFunc(unsigned char key)
{
	if(canPressKeyAgain[key] == false)
	{
		//		if(keyStates[key] == false)
		{
			canPressKeyAgain[key] = true;
		}
	}
}

//void BSUtilities::keyboardHandling()
//{
//	if(canWriteInConsole == false)
//	{
//		if(keyStates[' '] == false || canPressKeyAgain[' '] == false)
//		{
//			//ButtonJump = false;
//		}
//
//		if(keyStates[' '] == true)// && canPressKeyAgain[' '] == true)
//		{
//
//			//std::cout<<canPressKeyAgain[' ']<<" "<<ButtonJump<<'\n';
//			//keyStates[key] = true;
//			//if(canPressKeyAgain[' '] == true)
//			//std::cout<<wasPressed[' ']<<" "<<keyStates[' ']<<'\n';
//			if(wasPressed[' '] == false)
//			{
//				wasPressed[' '] = true;
//				ButtonJump = true;
//			//std::cout<<wasPressed[' ']<<" "<<keyStates[' ']<<'\n';
//				//canPressKeyAgain[' '] = false;
//			}
//			else
//			{
//				ButtonJump = false;
//			}
//
//			//ButtonJump = true;
//		}
//
//		if(canMoveCamera)
//		{
//			if(keyStates['a'])
//			{
//				glTranslatef(10, 0, 0);
//			}
//			if(keyStates['d'])
//			{
//				glTranslatef(-10, 0, 0);
//			}
//			if(keyStates['w'])
//			{
//				glTranslatef(0, -10, 0);
//			}
//			if(keyStates['s'])
//			{
//				glTranslatef(0, 10, 0);
//			}
//		}
//
//		if(keyStates['f'] && canPressKeyAgain['f'])
//		{
//			if(isPaused == false)
//			{
//				if(theLevelHasFinished == false)
//				{
//					theLevelHasFinished = true;
//				}
//			}
//			canPressKeyAgain['f'] = false;
//		}
//		if(keyStates['c'])
//		{
//			clean = true;
//
//			if(clean == true)
//			{
//				clean = false;
//				theLevelHasFinished = false;
//				razaInitialaInner = 40;
//			}
//
//		}
//		if(keyStates['p'] && canPressKeyAgain['p'])
//		{
//			if(theLevelHasFinished == false)
//			{
//				if(isPaused == false)
//				{
//					isPaused = true;
//				}
//				else
//				{
//					isPaused = false;
//				}
//			}
//			canPressKeyAgain['p'] = false;
//		}
//	}
//}


bool aMutat = false;
std::string lastConsoleString = "";
void BSUtilities::controlConsoleString()
{
	if(consoleString != lastConsoleString)
	{
		if(consoleString == "incarca harta: ")
		{
			aIncarcatHarta = false;
		}
		
		aMutat = false;
		//aIncarcatHarta = false;
	}
	
	//daca nu scrie in consola, atunci poate folosi una din comenzile
	if(canWriteInConsole == false)
	{
		consoleAddObstacles();
		
		consoleMoveCamera();
		
		consoleMoveLittleBig();
		
		consoleSalveazaHarta();
		
		consoleChangeWidthHeight();
		
		consoleChangeScaleSize();
		
		consoleMoveSelectedObstacle();
		
		consoleSetUserData();
		
		consoleTeleportHero();
		
		consoleIncarcaHarta();
		
		consoleSetSelectedObstacleTexture();
		
		consoleAddSquareOrRound();
		
		consoleSetKillHeroOrNextLevel();
		
		consoleDeleteSelectedObstacleTexture();
		
		consoleDeleteSelectedObstacleColor();
		
		consoleSetSelectedObstacleColor();
		
		consoleSendObstacleToBack();
		
		consoleSetRoundObstacleRotate();
		
		consoleSaveWorldBoundaries();
		
		consoleAddCoins();
		
		consoleSaveCoins();
	}
	else
		//daca vrea sa scrie in consola, blochez toate comenzile
	{
		canMoveCamera = false;
		canAddObstacles = false;
		aSchimbatDejaMarimeaObstacolului = false;
	}
	
	lastConsoleString = consoleString;
}


void BSUtilities::consoleAddObstacles()
{
	if( consoleString == "add obstacles")
	{
		canAddObstacles = true;
	}
	else
	{
		canAddObstacles = false;
	}
}

void BSUtilities::consoleMoveCamera()
{
	if( consoleString == "move camera")
	{
		canMoveCamera = true;
	}
	else
	{
		canMoveCamera = false;
	}
}

void BSUtilities::consoleMoveSelectedObstacle()
{
	if(consoleString.find("move selected obstacle") != std::string::npos && aMutat == false)
	{
		bool moveLeft = false, moveRight = false, moveUp = false, moveDown = false;
		
		char theNewSize[10];
		int indexOfNewSize = 0, pozitivSauNegativ = 1;
		bool areNumar = false;
		
		if(consoleString.find("left") != std::string::npos)
		{
			moveLeft = true;
		}
		else
			if(consoleString.find("right") != std::string::npos)
			{
				moveRight = true;
			}
			else
				if(consoleString.find("up") != std::string::npos)
				{
					moveUp = true;
				}
				else
					if(consoleString.find("down") != std::string::npos)
					{
						moveDown = true;
					}
		
		///Caut numarul cu care o sa mut obiectul
		for(int i = 0; i < consoleString.size(); i++)
		{
			//daca e numar, sau este punctul dintr-un float, ex: 3.4
			if(isdigit(consoleString[i]) == true || (consoleString[i] == '.' && areNumar == true))
			{
				if(consoleString[i-1] == '-')
				{
					pozitivSauNegativ = -1;
				}
				
				theNewSize[indexOfNewSize] = consoleString[i];
				indexOfNewSize++;
				areNumar = true;
			}
			else
			{
				//sa retina decat primul numar
				if(indexOfNewSize != 0)
				{
					break;
				}
			}
		}
		
		if(areNumar && (selectedSquareBody || selectedRoundBody))
		{
			float variab = atof( theNewSize ), mutaX = 0, mutaY = 0;
			
			if(moveLeft)
			{
				mutaX = -1 * variab;
			}
			else
				if(moveRight)
				{
					mutaX = variab;
				}
				else
					if(moveDown)
					{
						mutaY = variab * -1;
					}
					else
						if(moveUp)
						{
							mutaY = variab;
						}
			
			if(addCircleOrSquare == 1)
			{
				selectedSquareBody->theBody->SetTransform(b2Vec2(
																 selectedSquareBody->theBody->GetPosition().x + mutaX * pozitivSauNegativ,
																 selectedSquareBody->theBody->GetPosition().y + mutaY * pozitivSauNegativ),
														  selectedSquareBody->theBody->GetAngle());
			}
			else
				if(addCircleOrSquare == -1)
				{
					selectedRoundBody->theBody->SetTransform(b2Vec2(
																	selectedRoundBody->theBody->GetPosition().x + mutaX * pozitivSauNegativ,
																	selectedRoundBody->theBody->GetPosition().y + mutaY * pozitivSauNegativ),
															 selectedRoundBody->theBody->GetAngle());
				}
			
			aMutat = true;
			
		}
	}
}

void BSUtilities::consoleChangeWidthHeight()
{
	char theNewSizeOfBody[10];
	int indexOfNewSizeOfBody = 0;
	
	int gasesteSaSchimbe = false;
	//0 - nu gaseste nici height, nici width
	//1 - a gasit sa schimbe width
	//2 - a gasit sa schimbe height
	
	//verifica daca in stringul introdus apare "change obstacle"
	if( consoleString.find("change obstacle") != std::string::npos)
	{
		//verific daca schimb width
		if( consoleString.find("width") != std::string::npos )
		{
			gasesteSaSchimbe = 1;
		}
		else
			
			//verific daca schimb height
			if(consoleString.find("height") != std::string::npos)
			{
				gasesteSaSchimbe = -1;
			}
		
		if(gasesteSaSchimbe != 0)
		{
			indexOfNewSizeOfBody = 0;
			
			for(int i = 0; i < consoleString.size(); i++)
			{
				//daca a gasit o cifra o salvez
				if(isdigit(consoleString[i]) == true || consoleString[i] == '.')
				{
					theNewSizeOfBody[indexOfNewSizeOfBody] = consoleString[i];
					indexOfNewSizeOfBody++;
				}
				else
				{
					//sa retina decat primul numar
					if(indexOfNewSizeOfBody)
					{
						break;
					}
				}
			}
			
			//std::cout<<theNewSizeOfBody<<'\n';
			//Verific daca a gasit un numar si daca nu a schimbat deja marimea lui, pentru a nu o schimba in continuu si sa umple ramul
			if(indexOfNewSizeOfBody && aSchimbatDejaMarimeaObstacolului == false)
			{
				//Set the width or height of the obstacle
				if(gasesteSaSchimbe == 1)
				{
					widthOfObstacle = atof(theNewSizeOfBody);
				}
				else
				{
					heightOfObstacle = atof(theNewSizeOfBody);
				}
				
				///Reset the circle size
				theRenderedObstacleCircle->radius = atof(theNewSizeOfBody);
				obstacle->setTheVaoData(theRenderedObstacleCircle->vao,
										theRenderedObstacleCircle->vbo,
										theRenderedObstacleCircle->ibo,
										theRenderedObstacleCircle->data,
										theRenderedObstacleCircle->radius,
										theRenderedObstacleCircle->radius);
				//				gOpenGLTexture->setTheVao(theRenderedObstacleCircle->VaoBufferOfCircle, theRenderedObstacleCircle->DataOfCircle,
				//											theRenderedObstacleCircle->vbo, theRenderedObstacleCircle->ibo);
				
				///Reset the square size
				obstacle->setTheVaoData(theRenderedObstacleSquare->vao,
										theRenderedObstacleSquare->vbo,
										theRenderedObstacleSquare->ibo,
										theRenderedObstacleSquare->data,
										widthOfObstacle, heightOfObstacle);
				//				gOpenGLTexture->setTheVao(theRenderedObstacleSquare->VaoBufferOfSquare, theRenderedObstacleSquare->DataOfSquare,
				//											theRenderedObstacleSquare->vbo, theRenderedObstacleSquare->ibo);
				
				aSchimbatDejaMarimeaObstacolului = true;
			}
			else
				if(indexOfNewSizeOfBody == 0)
				{
					aSchimbatDejaMarimeaObstacolului = false;
				}
		}
	}
}

void BSUtilities::consoleMoveLittleBig()
{
	if( consoleString == "move obstacle little")
	{
		LittleBigMoveTheObstacle = 0;
	}
	else
		if( consoleString == "move obstacle big")
		{
			LittleBigMoveTheObstacle = 1;
		}
		else
			if( consoleString == "move obstacle small")
			{
				LittleBigMoveTheObstacle = -1;
			}
}

void BSUtilities::consoleChangeScaleSize()
{
	if(consoleString.find("change scale size") != std::string::npos)
	{
		canChangeScaleSize = true;
		char theNewSize[10];
		int indexOfNewSize = 0;
		bool areNumar = false;
		
		for(int i = 0; i < consoleString.size(); i++)
		{
			if(isdigit(consoleString[i]) == true || (consoleString[i] == '.' && areNumar == true))
			{
				theNewSize[indexOfNewSize] = consoleString[i];
				indexOfNewSize++;
				areNumar = true;
			}
			else
			{
				//sa retina decat primul numar
				if(indexOfNewSize != 0)
				{
					break;
				}
			}
		}
		
		if(areNumar)
		{
			scaleSize = atof( theNewSize );
		}
		
	}
	else
		if(consoleString.find("change scale size") == std::string::npos)
		{
			canChangeScaleSize = false;
		}
}

void BSUtilities::consoleSetUserData()
{
	if(consoleString.find("set user data ") != std::string::npos && selectedSquareBody != NULL)
	{
		USERDATA* userdata = new USERDATA;
		int pauze = 0;
		std::string userDataGasit = "";
		
		for(int i = 0 ; i < consoleString.size(); i++)
		{
			if(pauze >= 3)
			{
				userDataGasit += consoleString[i];
			}
			
			if(consoleString[i] == ' ')
			{
				pauze++;
			}
		}
		
		userdata->name = userDataGasit;
		selectedSquareBody->theBody->SetUserData(userdata);
	}
	
}

void BSUtilities::consoleTeleportHero()
{
	if(consoleString.find("teleport hero") != std::string::npos)
	{
		canTeleportHero = true;
	}
	else
	{
		canTeleportHero = true;///false
	}
}

void BSUtilities::consoleIncarcaHarta()
{
	
	if(consoleString == "incarca harta ")
	{
		aIncarcatHarta = false;
	}
	else
		if(consoleString.find("incarca harta ") != std::string::npos && aIncarcatHarta == false)
		{
			int pauze = 0;
			char numeHarta[100] = "";
			std::string theNameOfMap = "Levels/";
			
			for(int i = 0 ; i < consoleString.size() ; i++)
			{
				if(pauze >= 2)
				{
					theNameOfMap += consoleString[i];
				}
				
				if(consoleString[i] == ' ')
				{
					pauze++;
				}
			}
			
			theNameOfMap += ".xml";
			
			for(int i = 0 ; i < theNameOfMap.size() ; i++)
			{
				numeHarta[i] = theNameOfMap[i];
			}
			
			///Verific daca exista nivelul
			std::ifstream ifFile(numeHarta);
			
			if(ifFile)
			{
				obstacle->destroyLevel();
				//				obstacle->destroyAllBodiesSquare();
				//				obstacle->destroyAllBodiesRound();
				obstacle->incarcaHarta(numeHarta);
			}
			else
			{
				std::cout<<"The level '"<<numeHarta<<"' doesn't exist!"<<'\n';
			}
			
			aIncarcatHarta = true;
		}
		else
			if(consoleString == "incarca harta" && aIncarcatHarta == true)
			{
				aIncarcatHarta = false;
			}
	
	//std::cout<<aIncarcatHarta<<'\n';
}

void BSUtilities::consoleSalveazaHarta()
{
	if(consoleString.find("salveaza harta ") != std::string::npos && aSalvatHarta == false)
	{
		int pauze = 0, indexNumeHarta = 0, nrOfLinesSave = 0;
		char numeHarta[100] = "", nodesName[100][100], attributesName[100][100], attributesValues[100][100];
		ListaDeCaractere *nodesForXML[1000];
		std::string theNameOfMap = "Levels/";
		
		for(int i = 0 ; i < consoleString.size() ; i++)
		{
			if(pauze >= 2)
			{
				theNameOfMap += consoleString[i];
			}
			
			if(consoleString[i] == ' ')
			{
				pauze++;
			}
		}
		
		///Creez fisierul cu nivelul
		theNameOfMap += ".xml";
		
		strcpy(numeHarta, theNameOfMap.c_str());
		
		///Salvez jucatorul
		nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
		nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
		nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
		nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
		nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
		nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "0");
		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], "playerTexture.png");
		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
		std::string theSave = BStoString(HeroInitialX);
		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
		theSave = BStoString(HeroInitialY);
		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
		theSave = BStoString(Hero_size);
		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
		theSave = BStoString(Hero_size);
		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], "hero");
		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "playerAnimation");
		
		
		
		nrOfLinesSave++;
		
		
		std::cout<<'\n'<<"Salveaza harta: "<<numeHarta<<'\n';
		//Parcurg toate corpurile si le salvez
		
		
		
		std::list<BSTheRoundBodies*>::iterator iteratorRoundBodies;
		for(iteratorRoundBodies = ListOfRoundBodies.begin(); iteratorRoundBodies != ListOfRoundBodies.end(); iteratorRoundBodies++)
		{
			//extrag userData-ul
			USERDATA *salveazaUserData = (USERDATA*)(*iteratorRoundBodies)->theBody->GetUserData();
			
			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "1");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], (*iteratorRoundBodies)->nameOfTexture.c_str());
			
			theSave = BStoString((*iteratorRoundBodies)->theBody->GetPosition().x);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
			theSave = BStoString((*iteratorRoundBodies)->theBody->GetPosition().y);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
			theSave = BStoString((*iteratorRoundBodies)->radius);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
			theSave = BStoString((*iteratorRoundBodies)->radius);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], salveazaUserData->name.c_str());
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "roundAnimation");
			
			
			if((*iteratorRoundBodies)->ObstacleFinishesLevel == true)
			{
				strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "2");
			}
			else
			{
				theSave = BStoString((*iteratorRoundBodies)->ObstacleCanKillHero);
				strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], theSave.c_str());
			}
			
			nrOfLinesSave++;
			
			delete salveazaUserData;
		}
		
		std::list<BSTheSquareBodies*>::iterator iteratorSquareBodies;
		for(iteratorSquareBodies = ListOfSquareBodies.begin(); iteratorSquareBodies != ListOfSquareBodies.end(); iteratorSquareBodies++)
		{
			USERDATA *salveazaUserData = (USERDATA*)(*iteratorSquareBodies)->theBody->GetUserData();
			
			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "0");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], (*iteratorSquareBodies)->nameOfTexture.c_str());
			
			theSave = BStoString((*iteratorSquareBodies)->theBody->GetPosition().x);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
			theSave = BStoString((*iteratorSquareBodies)->theBody->GetPosition().y);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
			theSave = BStoString((*iteratorSquareBodies)->width);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
			theSave = BStoString((*iteratorSquareBodies)->height);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], salveazaUserData->name.c_str());
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "textureAnimation");
			
			
			///Vad daca obstacolul va fi cel care il va trece pe jucator la nivelul urmator
			if((*iteratorSquareBodies)->ObstacleFinishesLevel == true)
			{
				strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "2");
			}
			else
			{
				theSave = BStoString((*iteratorSquareBodies)->ObstacleCanKillHero);
				strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], theSave.c_str());
			}
			
			
			
			nrOfLinesSave++;
			
		}
		
		std::list<BSTheMessages*>::iterator i;
		for(i = listOfMessages.begin(); i != listOfMessages.end(); i++)
		{
			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "2");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], (*i)->nameOfTextureMessage.c_str());
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
			theSave = BStoString((*i)->xCord);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
			theSave = BStoString((*i)->yCord);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], "0");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], "0");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], "message");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "messageAnimation");
			
			nrOfLinesSave++;
		}
		
		std::list<BSCoins*>::iterator iq;
		for(iq = listOfCoins.begin(); iq != listOfCoins.end(); iq++)
		{
			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "5");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], "Animations/coin.png");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
			theSave = BStoString((*iq)->xCord);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
			theSave = BStoString((*iq)->yCord);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], "1");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], "1");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], "coin");
			theSave = BStoString((*iq)->available);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], theSave.c_str());
			
			nrOfLinesSave++;
		}
		
		std::list<BSFans*>::iterator iqq;
		for(iqq = listOfFans.begin(); iqq != listOfFans.end(); iqq++)
		{
			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
			nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "6");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], "Animations/fan.png");
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
			theSave = BStoString((*iqq)->xCord);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
			theSave = BStoString((*iqq)->yCord);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
			theSave = BStoString((*iqq)->width);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
			theSave = BStoString((*iqq)->height);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
			
			theSave = BStoString((*iqq)->lenthOfPower) + " " + BStoString((*iqq)->powerX) + " " + BStoString((*iqq)->powerY);
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], theSave.c_str());
			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "none");
			
			nrOfLinesSave++;
		}
		
		BSXmlFiles *saveTheMap = new BSXmlFiles();
		strcpy(nodesName[0], "Body_Type");
		strcpy(nodesName[1], "Texture_path");
		strcpy(nodesName[2], "Kill_or_Next_Level");
		strcpy(nodesName[3], "xCoordinate");
		strcpy(nodesName[4], "yCoordinate");
		strcpy(nodesName[5], "width");
		strcpy(nodesName[6], "height");
		strcpy(nodesName[7], "userName");
		strcpy(nodesName[8], "Animation_name");
		strcpy(nodesName[9], "Index");
		
		strcpy(attributesName[0], "name");
		strcpy(attributesName[1], "boundary_Left");
		strcpy(attributesName[2], "boundary_Down");
		strcpy(attributesName[3], "boundary_Up");
		strcpy(attributesName[4], "boundary_Right");
		strcpy(attributesName[5], "script");
		
		strcpy(attributesValues[0], numeHarta);
		strcpy(attributesValues[1], BStoString(CameraExtremeLeft - SCREEN_WIDTH / 2.f / scaleSize).c_str());
		strcpy(attributesValues[2], BStoString(CameraExtremeDown - SCREEN_HEIGHT / 2.f / scaleSize).c_str());
		strcpy(attributesValues[3], BStoString(CameraExtremeUp + SCREEN_HEIGHT / 2.f / scaleSize).c_str());
		strcpy(attributesValues[4], BStoString(CameraExtremeRight + SCREEN_WIDTH / 2.f / scaleSize).c_str());
		strcpy(attributesValues[5], "0");
		
		
		saveTheMap->writeAnyXML(numeHarta, "Level", "obstacle",
								nodesName, nodesForXML,
								attributesName, attributesValues,
								10, nrOfLinesSave, 5, 5);
		delete saveTheMap, nodesForXML;
		
		
		
		aSalvatHarta = true;
	}
	else
		if(consoleString == "salveaza harta" && aSalvatHarta == true)
		{
			aSalvatHarta = false;
		}
}

void BSUtilities::consoleAddSquareOrRound()
{
	if(consoleString == "set round obstacle")
	{
		addCircleOrSquare = -1;
	}
	else
		if(consoleString == "set square obstacle")
		{
			addCircleOrSquare = 1;
		}
		else
			if(consoleString == "set round texture")
			{
				addCircleOrSquare = -2;
			}
			else
				if(consoleString == "set square texture")
				{
					addCircleOrSquare = 2;
				}
	
}

void BSUtilities::consoleSetKillHeroOrNextLevel()
{
	if(selectedRoundBody || selectedSquareBody)
	{
		if(consoleString == "set obstacle to kill hero")
		{
			if(selectedRoundBody)
			{
				USERDATA* currentUserData = (USERDATA*) selectedRoundBody->theBody->GetUserData();
				currentUserData->canKillHero = true;
				selectedRoundBody->theBody->SetUserData(currentUserData);
				selectedRoundBody->ObstacleCanKillHero = true;
			}
			else
				if(selectedSquareBody)
				{
					USERDATA* currentUserData = (USERDATA*) selectedSquareBody->theBody->GetUserData();
					currentUserData->canKillHero = true;
					selectedSquareBody->theBody->SetUserData(currentUserData);
					selectedSquareBody->ObstacleCanKillHero = true;
				}
		}
		else
			if(consoleString == "set obstacle to next level")
			{
				if(selectedRoundBody)
				{
					USERDATA* currentUserData = (USERDATA*) selectedRoundBody->theBody->GetUserData();
					currentUserData->isToNextLevel = true;
					currentUserData->canKillHero = false;
					selectedRoundBody->theBody->SetUserData(currentUserData);
					selectedRoundBody->ObstacleFinishesLevel = true;
					selectedRoundBody->ObstacleCanKillHero = false;
				}
				else
					if(selectedSquareBody)
					{
						USERDATA* currentUserData = (USERDATA*) selectedSquareBody->theBody->GetUserData();
						currentUserData->isToNextLevel = true;
						currentUserData->canKillHero = false;
						selectedSquareBody->theBody->SetUserData(currentUserData);
						selectedSquareBody->ObstacleFinishesLevel = true;
						selectedSquareBody->ObstacleCanKillHero = false;
					}
			}
			else
				if(consoleString == "set obstacle to nothing")
				{
					if(selectedRoundBody)
					{
						USERDATA* currentUserData = (USERDATA*) selectedRoundBody->theBody->GetUserData();
						currentUserData->isToNextLevel = false;
						currentUserData->canKillHero = false;
						selectedRoundBody->theBody->SetUserData(currentUserData);
						selectedRoundBody->ObstacleFinishesLevel = false;
						selectedRoundBody->ObstacleCanKillHero = false;
					}
					else
						if(selectedSquareBody)
						{
							USERDATA* currentUserData = (USERDATA*) selectedSquareBody->theBody->GetUserData();
							currentUserData->isToNextLevel = false;
							currentUserData->canKillHero = false;
							selectedSquareBody->theBody->SetUserData(currentUserData);
							selectedSquareBody->ObstacleFinishesLevel = false;
							selectedSquareBody->ObstacleCanKillHero = false;
						}
				}
	}
}

void BSUtilities::consoleSetSelectedObstacleTexture()
{
	if(consoleString.find("set selected obstacle texture: ") != std::string::npos && (selectedRoundBody || selectedSquareBody) )
	{
		char theNewTexture[100] = "";
		int indexOfNewTexture = 0, nrPauze = 0;
		//std::string nameOfTheNewTexture = "";
		
		///Caut numarul cu care o sa mut obiectul
		for(int i = 0; i < consoleString.size(); i++)
		{
			if(nrPauze >= 4)
			{
				theNewTexture[indexOfNewTexture] = consoleString[i];
				indexOfNewTexture++;
			}
			
			if(consoleString[i] == ' ')
			{
				nrPauze++;
			}
		}
		
		if(indexOfNewTexture)
		{
			if(addCircleOrSquare == 1 && selectedSquareBody->nameOfTexture != BStoString(theNewTexture))
			{
				glDeleteTextures(1, &selectedSquareBody->texture);
				selectedSquareBody->nameOfTexture = BStoString(theNewTexture);
				gOpenGLTexture->loadATexture(theNewTexture, selectedSquareBody->texture);
			}
			else
				if(addCircleOrSquare == -1 && selectedRoundBody->nameOfTexture != BStoString(theNewTexture))
				{
					glDeleteTextures(1, &selectedRoundBody->texture);
					selectedRoundBody->nameOfTexture = BStoString(theNewTexture);
					gOpenGLTexture->loadATexture(theNewTexture, selectedRoundBody->texture);
				}
			
		}
	}
}

void BSUtilities::consoleDeleteSelectedObstacleTexture()
{
	if(consoleString == "delete selected obstacle texture" && (selectedRoundBody || selectedSquareBody))
	{
		if(selectedRoundBody)
		{
			selectedRoundBody->texture = NULL;
			selectedRoundBody->nameOfTexture = "";
		}
		else
			if(selectedSquareBody)
			{
				selectedSquareBody->texture = NULL;
				selectedSquareBody->nameOfTexture = "";
			}
	}
}

void BSUtilities::consoleDeleteSelectedObstacleColor()
{
	if(consoleString == "delete selected obstacle color" && (selectedRoundBody || selectedSquareBody))
	{
		if(selectedRoundBody)
		{
			selectedRoundBody->color = {1.f, 1.f, 1.f, 1.f};
		}
		else
			if(selectedSquareBody)
			{
				selectedSquareBody->color = {1.f, 1.f, 1.f, 1.f};
			}
	}
}

void BSUtilities::consoleSetSelectedObstacleColor()
{
	if(consoleString.find("set selected obstacle color: ") != std::string::npos &&
	   (consoleString.find("red ") != std::string::npos || consoleString.find("green ") != std::string::npos ||
		consoleString.find("blue ") != std::string::npos || consoleString.find("alpha ") != std::string::npos) &&
	   (selectedRoundBody || selectedSquareBody))
	{
		float theNumber = checkForNumberInString(consoleString);
		int i = 0; //1-red, 2-green, 3-blue, 4-alpha
		BSColorRGBA theColor;
		
		///Get the current color
		if(selectedRoundBody)
		{
			theColor = selectedRoundBody->color;
		}
		else
		{
			theColor = selectedSquareBody->color;
		}
		
		///Get the new color
		if(consoleString.find("red") != std::string::npos)
		{
			std::cout<<"new red color ";
			theColor.r = theNumber;
		}
		else
			if(consoleString.find("green") != std::string::npos)
			{
				std::cout<<"new green color ";
				theColor.g = theNumber;
			}
			else
				if(consoleString.find("blue") != std::string::npos)
				{
					std::cout<<"new blue color ";
					theColor.b = theNumber;
				}
				else
					if(consoleString.find("alpha") != std::string::npos)
					{
						std::cout<<"new alpha color ";
						theColor.a = theNumber;
					}
		
		///Set the new color
		if(selectedRoundBody)
		{
			selectedRoundBody->color = theColor;
			std::cout<<selectedRoundBody->color.r<<" "<<selectedRoundBody->color.g<<" "<<
			selectedRoundBody->color.b<<" "<<selectedRoundBody->color.a<<'\n';
		}
		else
		{
			selectedSquareBody->color = theColor;
			std::cout<<selectedSquareBody->color.r<<" "<<selectedSquareBody->color.g<<" "<<
			selectedSquareBody->color.b<<" "<<selectedSquareBody->color.a<<'\n';
		}
	}
}

void BSUtilities::consoleSetNewTexture()
{
	if(consoleString.find("set new texture: ") != std::string::npos)
	{
		char theNewTexture[100] = "";
		int indexOfNewTexture = 0, nrPauze = 0;
		//std::string nameOfTheNewTexture = "";
		
		///Caut numarul cu care o sa mut obiectul
		for(int i = 0; i < consoleString.size(); i++)
		{
			if(nrPauze >= 3)
			{
				theNewTexture[indexOfNewTexture] = consoleString[i];
				indexOfNewTexture++;
			}
			
			if(consoleString[i] == ' ')
			{
				nrPauze++;
			}
		}
		
		if(indexOfNewTexture)
		{
		}
	}
}

void BSUtilities::consoleSendObstacleToBack()
{
	if(consoleString == "send obstacle to back" && (selectedRoundBody || selectedSquareBody))
	{
		if(selectedSquareBody)
		{
			std::cout<<"sent to back"<<'\n';
			//			BSTheSquareBodies *p = selectedSquareBody;
			//
			//			selectedSquareBody->adresaUrmatoare = NULL;
			//			selectedSquareBody->adresaAnterioara = ultimulSquareStatic->adresaAnterioara;
			//			ultimulSquareStatic->adresaAnterioara->adresaUrmatoare = selectedSquareBody;
			//
			//			ultimulSquareStatic->adresaUrmatoare = p->adresaUrmatoare;
			//			ultimulSquareStatic->adresaAnterioara = p->adresaAnterioara;
			//			p->adresaAnterioara->adresaUrmatoare = ultimulSquareStatic;
			//			p->adresaUrmatoare->adresaAnterioara = ultimulSquareStatic;
			//
			//			selectedSquareBody = ultimulSquareStatic;
			//			ultimulSquareStatic = p;
			//			selectedSquareBody = NULL;
		}
	}
}

void BSUtilities::consoleSendTextureToBack()
{
	
}

void BSUtilities::consoleBringObstacleToFront()
{
	
}

void BSUtilities::consoleBringTextureToFront()
{
	
}

void BSUtilities::consoleSetRoundObstacleRotate()
{
	if(consoleString == "set rotating obstacle true" && selectedRoundBody)
	{
		std::cout<<"se misca"<<'\n';
		selectedRoundBody->isRotating = true;
	}
	else
		if(consoleString == "set rotating obstacle false" && selectedRoundBody)
		{
			std::cout<<"nu se mai misca"<<'\n';
			selectedRoundBody->isRotating = false;
		}
}

void BSUtilities::consoleSaveWorldBoundaries()
{
	if(consoleString == "save world boundaries")
	{
		std::ofstream save("world boundaries.txt");
		save<<WorldBoundaryLeft<<" "<<WorldBoundaryDown<<" "<<WorldBoundaryUp<<" "<<WorldBoundaryRight;
	}
	else
		if(consoleString == "set left boundary")
		{
			canSetBoundaryLeft = true;
			canSetBoundaryRight = false;
			canSetBoundaryDown = false;
			canSetBoundaryUp = false;
		}
		else
			if(consoleString == "set right boundary")
			{
				canSetBoundaryLeft = false;
				canSetBoundaryRight = true;
				canSetBoundaryDown = false;
				canSetBoundaryUp = false;
			}
			else
				if(consoleString == "set up boundary")
				{
					canSetBoundaryLeft = false;
					canSetBoundaryRight = false;
					canSetBoundaryDown = false;
					canSetBoundaryUp = true;
				}
				else
					if(consoleString == "set down boundary")
					{
						canSetBoundaryLeft = false;
						canSetBoundaryRight = false;
						canSetBoundaryDown = true;
						canSetBoundaryUp = false;
					}
					else
						if(consoleString == "set world boundaries")
						{
							std::ifstream setBound("world boundaries.txt");
							float l, r, u, d;
							setBound>>l>>d>>u>>r;
							CameraExtremeDown = d + SCREEN_HEIGHT / 2.f / scaleSize;
							CameraExtremeLeft = l + SCREEN_WIDTH / 2.f / scaleSize;
							CameraExtremeUp = u - SCREEN_HEIGHT / 2.f / scaleSize;
							CameraExtremeRight = r - SCREEN_WIDTH / 2.f / scaleSize;
						}
						else
						{
							canSetBoundaryLeft = false;
							canSetBoundaryRight = false;
							canSetBoundaryDown = false;
							canSetBoundaryUp = false;
						}
}

void BSUtilities::consoleAddCoins()
{
	if(consoleString == "add coins")
	{
		canAddCoins = true;
	}
	else
	{
		canAddCoins = false;
	}
}

void BSUtilities::consoleSaveCoins()
{
	if(consoleString == "save coins")
	{
		std::ofstream fout("coins.txt");
		std::list<BSCoins*>::iterator it;
		for(it = listOfCoins.begin(); it != listOfCoins.end(); it++)
		{
			fout<<(*it)->xCord<<' '<<(*it)->yCord<<'\n';
		}
	}
}




float BSUtilities::checkForNumberInString(std::string theString)
{
	char theNumber[10];
	int indexOfNumber = 0;
	bool areNumar = false;
	
	for(int i = 0; i < theString.size(); i++)
	{
		if(isdigit(theString[i]) == true || (theString[i] == '.' && areNumar == true))
		{
			theNumber[indexOfNumber] = theString[i];
			indexOfNumber++;
			areNumar = true;
		}
		else
		{
			//sa retina decat primul numar
			if(indexOfNumber != 0)
			{
				break;
			}
		}
	}
	
	if(areNumar)
	{
		return atof(theNumber);
	}
	
	return -1;
}




//void BSUtilities::setStringToChar


