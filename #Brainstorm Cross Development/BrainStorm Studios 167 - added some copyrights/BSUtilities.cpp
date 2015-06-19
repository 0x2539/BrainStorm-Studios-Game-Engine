#include "BSUtilities.h"

bool aIncarcatHarta = false;
BSObstacles *obstacle = new BSObstacles();
BSLevelMenu *theLevels = new BSLevelMenu;

//Textured polygon shader
BSTexturedPolygonProgram2D gTexturedPolygonProgram2D;

//Loaded texture
BSTexture *gOpenGLTexture = new BSTexture;
BSColorRGBA gTextureColor = { 1.f, 1.f, 1.f, 1.f };



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

    return true;
}
/*
 * openTheWavfile method is taken from the documentation of OpenAL. Any rights are reserved to OpenAL.
 */
bool BSUtilities::openTheWavfile(std::string path, ALuint &sourceOfSound, ALuint &bufferOfSound)
{
    //Loading of the WAVE file
    FILE *fp = NULL;                                                            //Create FILE pointer for the WAVE file
    fp=fopen(path.c_str(),"rb");                                            //Open the WAVE file
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

	if( glewError != GLEW_OK )
	{
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
		return false;
	}

	//Make sure OpenGL 2.1 is supported
	if( !GLEW_VERSION_2_1 )
	{
		printf( "OpenGL 2.1 not supported!\n" );
		return false;
	}

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
    BSProjectionMatrix = glm::perspective(45.f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 10000.0f);
	glUniformMatrix4fv(	locationBSProjectionMatrix, 1, GL_FALSE, glm::value_ptr( BSProjectionMatrix ) );

	//Initialize modelview
	BSModelViewMatrix = glm::mat4();
	glUniformMatrix4fv(	locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr( BSModelViewMatrix ) );

	//Set texture unit
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


	std::cout<<"Began loading some textures..."<<'\n'<<'\n';
	gOpenGLTexture->loadTextures();
	std::cout<<'\n'<<"Finished loading the textures!"<<'\n'<<'\n';

	std::cout<<"Began loading backgrounds..."<<'\n'<<'\n';
	obstacle->addBackgrounds();
	std::cout<<'\n'<<"Finished loading backgrounds..."<<'\n'<<'\n';

	std::cout<<"Began loading the bodies..."<<'\n'<<'\n';
	obstacle->setUpBodies();
	std::cout<<'\n'<<"Finished loading the bodies!"<<'\n'<<'\n';

	std::cout<<"Began loading the snow flakes..."<<'\n'<<'\n';
	obstacle->addSnowFlakeS();///functia incarcaHarta() trebuie sa fie interogata inainte!!! pentru CameraExtremeLeft,up,right,down
	std::cout<<'\n'<<"Finished loading the snow flakes!"<<'\n'<<'\n';

	///std::cout<<"Began loading the mouse circles..."<<'\n'<<'\n';
	///obstacle->createMouseCircles();
	///std::cout<<'\n'<<"Finished loading the mouse circles!"<<'\n'<<'\n';

    std::cout<<"Began loading the cloudy particles..."<<'\n'<<'\n';
	obstacle->addCloudyParticles();
	std::cout<<'\n'<<"Finished loading cloudy particles!"<<'\n'<<'\n';

    std::cout<<"Began loading the rain drops..."<<'\n'<<'\n';
	gOpenGLTexture->buildRainDrops();
	std::cout<<'\n'<<"Finished loading rain drops!"<<'\n'<<'\n';

    std::cout<<"Began loading the stats of coins and deaths..."<<'\n'<<'\n';
	loadCoinsAndDeaths();
	std::cout<<'\n'<<"Finished loading the stats of coins and deaths!"<<'\n'<<'\n';

    ///gOpenGLTexture->initVboAndVao();

	std::cout<<"Began loading the chapters..."<<'\n'<<'\n';
	theLevels->loadChapters();
	std::cout<<'\n'<<"Finished loading the chapters!"<<'\n'<<'\n';

	std::cout<<"Began loading the menu buttons..."<<'\n'<<'\n';
	gOpenGLTexture->initMenuButtons();
    std::cout<<'\n'<<"Finished loading the menu buttons!"<<'\n'<<'\n';

	///theLevels->loadLevels();
	std::cout<<"Began loading the menu levels..."<<'\n'<<'\n';
	gOpenGLTexture->initMenuLevels();
    std::cout<<'\n'<<"Finished loading the menu levels!"<<'\n'<<'\n';

	std::cout<<"Began loading the font..."<<'\n'<<'\n';
	gOpenGLTexture->initTheFont();
    std::cout<<'\n'<<"Finished loading the font!"<<'\n'<<'\n';

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
	if(!isTeleporting && gravityIsChanging == 0)
	{
		world->Step((float) 1/theTimeHowFast , 8, 3); //1/60, 8, 3
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
	}

	//daca nu scrie in consola, atunci poate folosi una din comenzile
	if(canWriteInConsole == false)
	{
		consoleMoveCamera();

		consoleSalveazaHarta();

		consoleChangeScaleSize();

		consoleTeleportHero();

		consoleIncarcaHarta();

		consoleAddCoins();

		consoleSaveCoins();
	}
	else
	//daca vrea sa scrie in consola, blochez toate comenzile
	{
		canMoveCamera = false;
	}

	lastConsoleString = consoleString;
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

void BSUtilities::consoleChangeScaleSize()
{
	if(consoleString.find("change scale size") != std::string::npos)
	{
		canChangeScaleSize = true;
		char theNewSize[10];
		int indexOfNewSize = 0;
		bool areNumar = false;

		for(unsigned int i = 0; i < consoleString.size(); i++)
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

			for(unsigned int i = 0 ; i < consoleString.size() ; i++)
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

			for(unsigned int i = 0 ; i < theNameOfMap.size() ; i++)
			{
				numeHarta[i] = theNameOfMap[i];
			}

			///Verific daca exista nivelul
			std::ifstream ifFile(numeHarta);

			if(ifFile)
			{
				obstacle->destroyLevel();
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
}

void BSUtilities::consoleSalveazaHarta()
{
//	if(consoleString.find("salveaza harta ") != std::string::npos && aSalvatHarta == false)
//	{
//		int pauze = 0, indexNumeHarta = 0, nrOfLinesSave = 0;
//		char numeHarta[100] = "", nodesName[100][100], attributesName[100][100], attributesValues[100][100];
//		ListaDeCaractere *nodesForXML[1000];
//		std::string theNameOfMap = "Levels/";
//
//		for(unsigned int i = 0 ; i < consoleString.size() ; i++)
//		{
//			if(pauze >= 2)
//			{
//				theNameOfMap += consoleString[i];
//			}
//
//			if(consoleString[i] == ' ')
//			{
//				pauze++;
//			}
//		}
//
//		///Creez fisierul cu nivelul
//		theNameOfMap += ".xml";
//
//		strcpy(numeHarta, theNameOfMap.c_str());
//
//		///Salvez jucatorul
//		nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
//		nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = 0;
//		nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = 0;
//		nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = 0;
//		nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = 0;
//		nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = 0;
//		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "0");
//		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], "playerTexture.png");
//		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
//		std::string theSave = BStoString(HeroInitialX);
//		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
//		theSave = BStoString(HeroInitialY);
//		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
//		theSave = BStoString(Hero_size);
//		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
//		theSave = BStoString(Hero_size);
//		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
//		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], "hero");
//		strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "playerAnimation");
//
//
//
//		nrOfLinesSave++;
//
//
//		std::cout<<'\n'<<"Salveaza harta: "<<numeHarta<<'\n';
//		//Parcurg toate corpurile si le salvez
//
//
//
//		std::list<BSTheRoundBodies*>::iterator iteratorRoundBodies;
//		for(iteratorRoundBodies = ListOfRoundBodies.begin(); iteratorRoundBodies != ListOfRoundBodies.end(); iteratorRoundBodies++)
//		{
//			//extrag userData-ul
//			USERDATA *salveazaUserData = (USERDATA*)(*iteratorRoundBodies)->theBody->GetUserData();
//
//			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = 0;
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "1");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], (*iteratorRoundBodies)->nameOfTexture.c_str());
//
//			theSave = BStoString((*iteratorRoundBodies)->theBody->GetPosition().x);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
//			theSave = BStoString((*iteratorRoundBodies)->theBody->GetPosition().y);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
//			theSave = BStoString((*iteratorRoundBodies)->radius);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
//			theSave = BStoString((*iteratorRoundBodies)->radius);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], salveazaUserData->name.c_str());
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "roundAnimation");
//
//
//			if((*iteratorRoundBodies)->ObstacleFinishesLevel == true)
//			{
//				strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "2");
//			}
//			else
//			{
//				theSave = BStoString((*iteratorRoundBodies)->ObstacleCanKillHero);
//				strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], theSave.c_str());
//			}
//
//			nrOfLinesSave++;
//
//			delete salveazaUserData;
//		}
//
//		std::list<BSTheSquareBodies*>::iterator iteratorSquareBodies;
//		for(iteratorSquareBodies = ListOfSquareBodies.begin(); iteratorSquareBodies != ListOfSquareBodies.end(); iteratorSquareBodies++)
//		{
//			USERDATA *salveazaUserData = (USERDATA*)(*iteratorSquareBodies)->theBody->GetUserData();
//
//			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = 0;
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "0");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], (*iteratorSquareBodies)->nameOfTexture.c_str());
//
//			theSave = BStoString((*iteratorSquareBodies)->theBody->GetPosition().x);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
//			theSave = BStoString((*iteratorSquareBodies)->theBody->GetPosition().y);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
//			theSave = BStoString((*iteratorSquareBodies)->width);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
//			theSave = BStoString((*iteratorSquareBodies)->height);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], salveazaUserData->name.c_str());
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "textureAnimation");
//
//
//			///Vad daca obstacolul va fi cel care il va trece pe jucator la nivelul urmator
//			if((*iteratorSquareBodies)->ObstacleFinishesLevel == true)
//			{
//				strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "2");
//			}
//			else
//			{
//				theSave = BStoString((*iteratorSquareBodies)->ObstacleCanKillHero);
//				strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], theSave.c_str());
//			}
//
//
//
//			nrOfLinesSave++;
//
//		}
//
//		std::list<BSTheMessages*>::iterator i;
//		for(i = listOfMessages.begin(); i != listOfMessages.end(); i++)
//		{
//			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = 0;
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "2");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], (*i)->nameOfTextureMessage.c_str());
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
//			theSave = BStoString((*i)->xCord);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
//			theSave = BStoString((*i)->yCord);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], "0");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], "0");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], "message");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "messageAnimation");
//
//			nrOfLinesSave++;
//		}
//
//		std::list<BSCoins*>::iterator iq;
//		for(iq = listOfCoins.begin(); iq != listOfCoins.end(); iq++)
//		{
//			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = 0;
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "5");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], "Animations/coin.png");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
//			theSave = BStoString((*iq)->xCord);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
//			theSave = BStoString((*iq)->yCord);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], "1");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], "1");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], "coin");
//			theSave = BStoString((*iq)->available);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], theSave.c_str());
//
//			nrOfLinesSave++;
//		}
//
//		std::list<BSFans*>::iterator iqq;
//		for(iqq = listOfFans.begin(); iqq != listOfFans.end(); iqq++)
//		{
//			nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = 0, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = 0;
//			nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = 0;
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "6");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], "Animations/fan.png");
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
//			theSave = BStoString((*iqq)->xCord);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
//			theSave = BStoString((*iqq)->yCord);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
//			theSave = BStoString((*iqq)->width);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
//			theSave = BStoString((*iqq)->height);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
//
//			theSave = BStoString((*iqq)->lenthOfPower) + " " + BStoString((*iqq)->powerX) + " " + BStoString((*iqq)->powerY);
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], theSave.c_str());
//			strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "none");
//
//			nrOfLinesSave++;
//		}
//
//		BSXmlFiles *saveTheMap = new BSXmlFiles();
//		strcpy(nodesName[0], "Body_Type");
//		strcpy(nodesName[1], "Texture_path");
//		strcpy(nodesName[2], "Kill_or_Next_Level");
//		strcpy(nodesName[3], "xCoordinate");
//		strcpy(nodesName[4], "yCoordinate");
//		strcpy(nodesName[5], "width");
//		strcpy(nodesName[6], "height");
//		strcpy(nodesName[7], "userName");
//		strcpy(nodesName[8], "Animation_name");
//		strcpy(nodesName[9], "Index");
//
//		strcpy(attributesName[0], "name");
//		strcpy(attributesName[1], "boundary_Left");
//		strcpy(attributesName[2], "boundary_Down");
//		strcpy(attributesName[3], "boundary_Up");
//		strcpy(attributesName[4], "boundary_Right");
//		strcpy(attributesName[5], "script");
//
//		strcpy(attributesValues[0], numeHarta);
//		strcpy(attributesValues[1], BStoString(CameraExtremeLeft - SCREEN_WIDTH / 2.f / scaleSize).c_str());
//		strcpy(attributesValues[2], BStoString(CameraExtremeDown - SCREEN_HEIGHT / 2.f / scaleSize).c_str());
//		strcpy(attributesValues[3], BStoString(CameraExtremeUp + SCREEN_HEIGHT / 2.f / scaleSize).c_str());
//		strcpy(attributesValues[4], BStoString(CameraExtremeRight + SCREEN_WIDTH / 2.f / scaleSize).c_str());
//		strcpy(attributesValues[5], "0");
//
//
//		saveTheMap->writeAnyXML(numeHarta, "Level", "obstacle",
//								nodesName, nodesForXML,
//								attributesName, attributesValues,
//								10, nrOfLinesSave, 5, 5);
//		delete saveTheMap, nodesForXML;
//
//
//
//		aSalvatHarta = true;
//	}
//	else
//		if(consoleString == "salveaza harta" && aSalvatHarta == true)
//		{
//			aSalvatHarta = false;
//		}
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
		for(int i = 0; i < listOfCoins.size(); i++)
		{
			fout<<listOfCoins[i]->xCord<<' '<<listOfCoins[i]->yCord<<'\n';
		}
	}
}




float BSUtilities::checkForNumberInString(std::string theString)
{
	char theNumber[10];
	int indexOfNumber = 0;
	bool areNumar = false;

	for(unsigned int i = 0; i < theString.size(); i++)
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
