#include "BSUtilities.h"

bool aIncarcatHarta = false;
BSObstacles *obstacle = new BSObstacles();
BSLevelMenu *theLevels = new BSLevelMenu;

//Textured polygon shader
BSTexturedPolygonProgram2D gTexturedPolygonProgram2D;

//Loaded texture
BSTexture *gOpenGLTexture = new BSTexture;
BSColorRGBA gTextureColor = { 1.f, 1.f, 1.f, 1.f };



int endWithError(std::string msg, int error = 0)
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

	return true;
}
/*
 * openTheWavfile method is taken from the documentation of OpenAL. Any rights are reserved to OpenAL.
 */
bool BSUtilities::openTheWavfile(std::string path, ALuint &sourceOfSound, ALuint &bufferOfSound)
{
	//Loading of the WAVE file
	FILE *fp = NULL;                                                            //Create FILE pointer for the WAVE file
	fp = fopen(path.c_str(), "rb");                                         //Open the WAVE file
	if(!fp) return endWithError("Failed to open file");                         //Could not open file

	//Variables to store info about the WAVE file (all of them is not needed for OpenAL)
	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;

	//Check that the WAVE file is OK
	fread(type, sizeof(char), 4, fp);                                           //Reads the first bytes in the file
	if(type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')    //Should be "RIFF"
		return endWithError("No RIFF");                                             //Not RIFF

	fread(&size, sizeof(DWORD), 1, fp);                                         //Continue to read the file
	fread(type, sizeof(char), 4, fp);                                           //Continue to read the file
	if(type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')    //This part should be "WAVE"
		return endWithError("not WAVE");                                            //Not WAVE

	fread(type, sizeof(char), 4, fp);                                           //Continue to read the file
	if(type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')    //This part should be "fmt "
		return endWithError("not fmt ");                                            //Not fmt

	//Now we know that the file is a acceptable WAVE file
	//Info about the WAVE data is now read and stored
	fread(&chunkSize, sizeof(DWORD), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if(type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')    //This part should be "data"
		return endWithError("Missing DATA");                                        //not data

	fread(&dataSize, sizeof(DWORD), 1, fp);                                     //The size of the sound data is read


	unsigned char* buf = new unsigned char[dataSize];                           //Allocate memory for the sound data
	std::cout << fread(buf, sizeof(BYTE), dataSize, fp) << " bytes loaded\n";        //Read the sound data and display the
	//number of bytes loaded.
	//Should be the same as the Data Size if OK


	///The Sample Rate of the WAVE file
	ALuint frequency = sampleRate;
	///The audio format (bits per sample, number of channels)
	ALenum format = 0;



	///Generate one OpenAL Buffer and link to "buffer"
	alGenBuffers(1, &bufferOfSound);
	///Generate one OpenAL Source and link to "source"
	alGenSources(1, &sourceOfSound);


	if(alGetError() != AL_NO_ERROR)
	{
		std::cout << "error GenSource" << '\n';
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
		std::cout << "Wrong BitPerSample" << '\n';
	}

	///Store the sound data in the OpenAL Buffer
	alBufferData(bufferOfSound, format, buf, dataSize, frequency);

	if(alGetError() != AL_NO_ERROR)
	{
		std::cout << "Error loading ALBuffer" << '\n';
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
	alSourcei(sourceOfSound, AL_BUFFER,   bufferOfSound);
	//Set the pitch of the source
	alSourcef(sourceOfSound, AL_PITCH,    1.0f);
	//Set the gain of the source
	alSourcef(sourceOfSound, AL_GAIN,     1.0f);
	//Set the position of the source
	alSourcefv(sourceOfSound, AL_POSITION, SourcePos);
	//Set the velocity of the source
	alSourcefv(sourceOfSound, AL_VELOCITY, SourceVel);
	//Set if source is looping sound
	alSourcei(sourceOfSound, AL_LOOPING,  AL_FALSE);


	//Play the sound buffer linked to the source
	if(alGetError() != AL_NO_ERROR)
	{
		std::cout << "Error playing sound" << '\n';
	}
	return true;
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

	return true;
}

bool BSUtilities::initGL()
{
	//Initialize GLEW
	GLenum glewError = glewInit();

	if(glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		return false;
	}

	//Make sure OpenGL 2.1 is supported
	if(!GLEW_VERSION_2_1)
	{
		printf("OpenGL 2.1 not supported!\n");
		return false;
	}

	//Initialize clear color
	glClearColor(1.f, 1.f, 1.f, 1.f);

	//Enable texturing
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Check for error
	GLenum error = glGetError();

	if(error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}

	return true;
}

bool BSUtilities::loadGP()
{
	//Load textured shader program
	if(!gTexturedPolygonProgram2D.loadProgram())
	{
		printf("Unable to load textured polygon program!\n");
		return false;
	}

	//Bind textured shader program
	gTexturedPolygonProgram2D.bind();

	//Initialize projection
	BSProjectionMatrix = glm::perspective(45.f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 10000.0f);
	glUniformMatrix4fv(locationBSProjectionMatrix, 1, GL_FALSE, glm::value_ptr(BSProjectionMatrix));

	//Initialize modelview
	BSModelViewMatrix = glm::mat4();
	glUniformMatrix4fv(locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr(BSModelViewMatrix));

	//Set texture unit
	glUniform1i(locationBSTextureUnit, 0);

	return true;
}

bool BSUtilities::loadMedia()
{
	iData[0] = 0;
	iData[1] = 1;
	iData[2] = 2;
	iData[3] = 3;

	SDL_PollEvent(&event);

	obstacle->setTheVaoData(originalBody->vao, originalBody->vbo, originalBody->ibo, originalBody->data, 1.0f, 1.0f);

	gOpenGLTexture->loadTheLoadingImage();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gOpenGLTexture->renderTheLoadingImage(1);
	SDL_GL_SwapBuffers();

	loadATexture("blank.png", blankTexture);


	std::cout << "Began loading some textures..." << '\n' << '\n';
	gOpenGLTexture->loadTextures();
	std::cout << '\n' << "Finished loading the textures!" << '\n' << '\n';

	std::cout << "Began loading backgrounds..." << '\n' << '\n';
	obstacle->addBackgrounds();
	std::cout << '\n' << "Finished loading backgrounds..." << '\n' << '\n';

	std::cout << "Began loading the bodies..." << '\n' << '\n';
	obstacle->setUpBodies();
	std::cout << '\n' << "Finished loading the bodies!" << '\n' << '\n';

	std::cout << "Began loading the snow flakes..." << '\n' << '\n';
	obstacle->addSnowFlakeS();///functia incarcaHarta() trebuie sa fie interogata inainte!!! pentru CameraExtremeLeft,up,right,down
	std::cout << '\n' << "Finished loading the snow flakes!" << '\n' << '\n';

	///std::cout<<"Began loading the mouse circles..."<<'\n'<<'\n';
	///obstacle->createMouseCircles();
	///std::cout<<'\n'<<"Finished loading the mouse circles!"<<'\n'<<'\n';

	std::cout << "Began loading the cloudy particles..." << '\n' << '\n';
	obstacle->addCloudyParticles();
	std::cout << '\n' << "Finished loading cloudy particles!" << '\n' << '\n';

	std::cout << "Began loading the rain drops..." << '\n' << '\n';
	gOpenGLTexture->buildRainDrops();
	std::cout << '\n' << "Finished loading rain drops!" << '\n' << '\n';

	std::cout << "Began loading the stats of coins and deaths..." << '\n' << '\n';
	loadCoinsAndDeaths();
	std::cout << '\n' << "Finished loading the stats of coins and deaths!" << '\n' << '\n';

	///gOpenGLTexture->initVboAndVao();

	std::cout << "Began loading the chapters..." << '\n' << '\n';
	theLevels->loadChapters();
	std::cout << '\n' << "Finished loading the chapters!" << '\n' << '\n';

	std::cout << "Began loading the menu buttons..." << '\n' << '\n';
	gOpenGLTexture->initMenuButtons();
	std::cout << '\n' << "Finished loading the menu buttons!" << '\n' << '\n';

	///theLevels->loadLevels();
	std::cout << "Began loading the menu levels..." << '\n' << '\n';
	gOpenGLTexture->initMenuLevels();
	std::cout << '\n' << "Finished loading the menu levels!" << '\n' << '\n';

	std::cout << "Began loading the font..." << '\n' << '\n';
	gOpenGLTexture->initTheFont();
	std::cout << '\n' << "Finished loading the font!" << '\n' << '\n';

	std::cout << "done utilities" << '\n';
	return true;
}

void BSUtilities::loadCoinsAndDeaths()
{
	std::ifstream coinsAndDeaths("coinsAndDeaths");
	coinsAndDeaths >> coinsTotalNo >> deathsTotalNo;
}

void BSUtilities::update()
{
	if(!isTeleporting && gravityIsChanging == 0)
	{
		world->Step((float) 1 / theTimeHowFast , 8, 3); //1/60, 8, 3
		//world.step(1/30,10,10); //performs a time step in the box2d simulation
		world->ClearForces();
		//world->DrawDebugData();
	}
}

void canPressKeyAgainFunc(unsigned char key)
{
	if(canPressKeyAgain[key] == false)
	{
		canPressKeyAgain[key] = true;
	}
}
