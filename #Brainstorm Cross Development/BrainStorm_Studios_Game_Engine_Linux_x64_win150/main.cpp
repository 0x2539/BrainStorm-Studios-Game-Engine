#include "BSValues.h"
#include "BSUtilities.h"
#include <iostream>
#include <string>
#include <Box2D/Box2D.h>
#include <SOIL/SOIL.h>
#include "BSObstacles.h"
#include "BSTexture.h"
#include "BSActionStuff.h"
#include "BSTexturedPolygonProgram2D.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <ctime>
#include "BSActionStuffRound.h"
#include "BSLevelMenu.h"

#include "BSInputClass.h"
//#include <pthread.h>



	// comenteriu hack

GLuint blankTexture, whiteTexture;

BSBody *originalParticle = new BSBody, *originalTransparentMenu = new BSBody, *originalCoin = new BSBody, *originalFan = new BSBody,
		*originalBody = new BSBody, *originalDarkLevel = new BSBody, *originalDarkMenu = new BSBody, *originalRainDrop = new BSBody,
		*originalWormHole = new BSBody, *originalDustBody = new BSBody, *originalFanParticleX = new BSBody, *originalFanParticleY = new BSBody;
BSWormHole *lastWorm = NULL;

std::list<BSSnowFlakes*>listOfRainDrops;
long long timer = 0;

	BSTheSquareBodies *hero = new BSTheSquareBodies,
						*Hero2nd = new BSTheSquareBodies,
						*selectedSquareBody = NULL;
	BSTheRoundBodies *selectedRoundBody = NULL;

	BSLevelMenu *theLevelMenuObject = new BSLevelMenu();
	BSUtilities *objBSUtils = new BSUtilities();
	BSObstacles *objObstacles = new BSObstacles();
	BSActionStuff *action = new BSActionStuff();
	BSActionStuffRound *action2 = new BSActionStuffRound();
	BSTexture* randareMenu = new BSTexture();
	BSInputClass *ibjectInputMain = new BSInputClass();
	BSTheBackgrounds *backgroundSky = new BSTheBackgrounds,
					*backgroundMountain = new BSTheBackgrounds,
					*backgroundBush = new BSTheBackgrounds,
					*backgroundField = new BSTheBackgrounds,
					*backgroundHighField = new BSTheBackgrounds;
	BSAnimation *SoundButtonTexture = new BSAnimation;
	BSTextureSquare *selectedTextureSquare= new BSTextureSquare,
					*mouseTexture = new BSTextureSquare;
	BSTextureRound *selectedTextureRound = new BSTextureRound;
	BSTheSquare *theRenderedObstacleSquare = new BSTheSquare,
				*theRenderedTextureSquare = new BSTheSquare;
	BSTheCircle *theRenderedObstacleCircle = new BSTheCircle,
				*theRenderedTextureCircle = new BSTheCircle;
	BSSceneStructure* deadScene = new BSSceneStructure;
	BSTheFontLetters *letters[256];
	ChapterStructure *chaptere[100];
	b2World* world = new b2World(b2Vec2(0, -40));
	BSTexturedVertex2D mainDarkData[4], darkLevelData[4],
						coinData[4], fnData[4], particleData[4], transparentMenuBlock[4];
	GLuint mainDarkTexture, mainDarkVao, darkLevelTexture, darkLevelVao, vboMainDark, vboDarkLevel, iboMainDark, iboDarkLevel,
			coinTexture, coinVao, coinVbo, coinIbo, fanTexture, fanVao, fanVbo, fanIbo, soundPlayerTexture,// mVBOID = 0, mIBOID = 0,
			particleVaoBuffer, particleVboBuffer, particleIboBuffer,
				whenHitsGroundVaoBuffer, whenHitsGroundVboBuffer, whenHitsGroundIboBuffer,
				transparentMenuBlockVao, transparentMenuBlockVbo, transparentMenuBlockIbo, iData[4], gVertexBuffer = 0, texVertexBuffer = 0,
			texture, textureMill, playerTexture, playerTextureDead, playerTextureRound,
			starsTexture1, starsTexture2, starsTexture3, starsTexture4, backgroundTexture, clouds[6];

	LevelChooserPlayerTexture *levelChoserPlayer = new LevelChooserPlayerTexture;
	BSTexturedPolygonProgram2D* mainTexturedPolygonProgram2D = NULL;
	BSPlayerControls *heroKeyboard = new BSPlayerControls;

ALuint SourceSoundBeginningGame, SourceSoundJump, SourceSoundDies,
    SourceSoundMusic1, SourceSoundMusic2, SourceSoundMusic3, SourceSoundCoin, SourceSoundPowerUp, SourceSoundTeleport;
ALuint BufferSoundBeginningGame, BufferSoundJump, BufferSoundDies,
    BufferSoundMusic1, BufferSoundMusic2, BufferSoundMusic3, BufferSoundCoin, BufferSoundPowerUp, BufferSoundTeleport;

	ALCdevice *deviceOpenAL;
	ALCcontext *contextOpenAL;
	BSMenuStructure *currentMenu = new BSMenuStructure;
	BSButtonStructure *currentButton = new BSButtonStructure;


//Vertex buffer
GLint ShaderCameraExtremeLeft, ShaderCameraExtremeRight,
		ShaderCameraExtremeUp, ShaderCameraExtremeDown,
		ShaderPlayerCoordinatesX, ShaderPlayerCoordinatesY,
		ShaderMouseX, ShaderMouseY, ShaderIsTheSquare, ShaderWidthOfSquare, ShaderHeightOfSquare,
		ShaderAflaRestulWidthOfSquare, ShaderAflaRestulHeightOfSquare, ShaderScaleSize,
		ShaderRotationAngle, ShaderRotated, ShaderIsText, ShaderTextCoord, ShaderTextTex, ShaderIsCircle, ShaderCircleRadius,
		ShaderCosRotation, ShaderSinRotation, ShaderScaleOnX, ShaderScaleOnY, ShaderDark, ShaderFlake;
//GLint mVertexPos2DLocation;
//GLint mTexCoordLocation;
GLint locationBSVertexPosition3D, locationBSTextureCoordinate, locationBSModelViewMatrix, locationBSProjectionMatrix;
GLint locationBSTextureColor, locationBSTextureUnit;
GLuint BSProgramID;

glm::mat4 BSProjectionMatrix;
glm::mat4 BSModelViewMatrix;



	long long timeSinceMovedMouse = 0, timeSinceMovedLittleCircle = 0;

	std::list<BSTheSquareBodies*> ListOfSquareBodies;
    std::list<BSTheSquareBodies*> ListOfSquareDustBodies;
	std::list<BSSnowFlakes*> listOfSnowFlakes;
	std::list<BSWorldOfGooMouse*> listOfMouseCircles;
	std::list<BSCloudyParticles*> listOfCloudyParticles;
	std::list<BSTheRoundBodies*> ListOfRoundBodies;
	std::list<BSTheParticles*> ListOfParticles;
	BSNewList *listOfAnimations[100];
	int nrOfListOfAnimations = 0;
	///std::list<BSNewList*> listOfAnimations;
	std::list<BSMenuStructure*> listOfMenus;
	std::list<BSTheMessages*>listOfMessages;
	std::list<BSFans*> listOfFans;
	std::list<BSCoins*> listOfCoins;
	std::list<BSTextureSquare*> ListOfSquareTextures;
	std::list<BSTextureRound*> ListOfRoundTextures;
    std::list<BSWormHole*> listOfWormHoles;
    BsActiveAnimations *listOfActiveAnimations[5];

    float theCoinX, theCoinY;

int NrOfTotalLetters, nrOfChapters = 0, heroFacesLeftOrRight = 1, addCircleOrSquare = 1, nrOfMessageSign = 0,
		coinsTotalNo = 0, coinsThisLevel = 0, deathsTotalNo = 0, deathsThisLevel = 0, variableWall = 0,
		LittleBigMoveTheObstacle = 0, nrBodiesDistroyed = 0, indexOfSelectedBody = 0, nrParticlesDistroyed = 0,
		nrParticles = 0, nrOfWhenItHits = 0, numberOfSquaresForPath = 0, nrBodies = 0;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int SCREEN_FPS = 60;//usually 60
int SCREEN_BPP = 32, timeWhenTeleported = 0, muscicIndex = 0;



bool DarkLevels = false, canAddCoins = false, canAddFans = false, settingsFromFirstOrGame = false,
	canSetBoundaryLeft = false, canSetBoundaryDown = false, canSetBoundaryUp = false, canSetBoundaryRight = false,
	canChangeVolumeMusic = false, canChangeVolumeAudioSfx = false, canChangeResolution = false,
	wasPressed[256], corpulEsteDistrus[1000], itMovedX = false, itMovedY = false, itMovedXLeft = false,
	itMovedXRight = false, itTurnedX = false, canMoveCamera = false, canAddObstacles = false, canWriteInConsole = false,
	canClickLeft = true, canClickRight = true, aSalvatHarta = false, canChangeScaleSize = false, canTeleportHero = false,
	keyStates[256], canPressKeyAgain[256], existsGamePad = false, useKeyboardOrGamePad = true, theLevelHasFinished = false,
	clean = false, isPaused = true, canPressTheKey = true, ButtonUp = false, ButtonDown = false,
	ButtonRight = false, ButtonLeft = false, ButtonRun = false, ButtonJump = false,
	MouseLeft = false, MouseRight = false, MouseMoved = false,
	quit = false, moveLeftGround = false, moveRightGround = false, moveLeftAir = false, moveRightAir = false, isJumping = false,
	canJumpVertically = false, canJumpHorizontally = false, isInCorner = false, canClick = false, aDatClick = false,
	isOnGround = false, isOnLeftWall = false, isOnRightWall = false, isInAir = false, jumpsUpTheWall = false,
	pressedJumpSecond = false, canJumpSecond = true, jumpSecondSpinned = false, isTeleporting = false, isSpaceDown = false;
   float jumpSecondSpinAngle = 0;
bool useSnow = true, useRain = false, useAssassinsCreed = false;
int levelHasScript = 0;


float HeroInitialX = 3, HeroInitialY = 3, newVolumeAudio = 1.f, newVolumeSFX = 1.f, currentVolumeAudio = 1.f,
	currentVolumeSFX = 1.f, scaleSize = 32, theTimeHowFast = 60,
	CameraExtremeLeft = SCREEN_WIDTH / 2 / scaleSize,
	CameraExtremeRight = SCREEN_WIDTH / 2 / scaleSize + 2000 / scaleSize,
	CameraExtremeUp = SCREEN_HEIGHT / 2 / scaleSize + 230 / scaleSize,
	CameraExtremeDown =  SCREEN_HEIGHT / 2 / scaleSize,
	MenuCoordinateX = SCREEN_WIDTH / 2 / scaleSize,
	MenuCoordinateY = SCREEN_HEIGHT / 2 / scaleSize,
	WorldBoundaryLeft = 0, WorldBoundaryDown = 0, WorldBoundaryUp = CameraExtremeUp, WorldBoundaryRight = CameraExtremeRight,
	lastMovedX = 0, changeInPosition = 0, lastPositionOfHeroX = 0, lastPositionOfHeroY = 0,
	startPositionCameraX = 0, sinX = 0, sinY = 0, iteratieSin = 1.f * 5,
	widthOfObstacle = Hero_size, heightOfObstacle = Hero_size, createObstacleX = 0, createObstacleY = 0,
	razaInitialaInner = 40, razaInitialaOuter = 40, MouseX = 0, MouseY = 0, MouseXLast = 0, MouseYLast = 0,
	SursaDeLuminaX = 0, SursaDeLuminaY = 0, lastTime = 0,
	speedWalk = 25, speedWalkFast = 50, speedRun = 1.2, speedJumpUp = 17.7f, speedJumpToSide = 17, speedGoDown = -20,
	speedWalkInAir = 25, speedWalkInAirFast = 50, speedJumpToTheSameSide = 17.1, speedJumpUpOnWall = 21.f,
	timeToStayInAirWhenJumpsOnTheSameWall = 175, timeToStayOnWall = 250,
	buttonMenuWidth = 3 / 2.f, buttonMenuHeight = 1 / 2.f, moveStringX = 0, moveStringY = 0;



	BSTextureSquare *theLoadingImage = new BSTextureSquare;
	SDL_Event event;
	bool doneLoadingTheGame = false, canRenderGameNow = false;

short BinaryPlayer = -1;//0x0001;  // 0000000000000001 in binary
short BinaryMonster = -2;//0x0002; // 0000000000000010 in binary
short BinaryScenery = 1;//0x0004; // 0000000000000100 in binary
short BinaryParticles = -1;//0x0008; // 0000000000000100 in binary


float gameBoundLeft, gameBoundRight, gameBoundDown, gameBoundUp;

BSBody *CameraPosition = new BSBody;

float playerAnimWidth, playerAnimHeight;


char initialSquareTexturePath[100], initialRoundTexturePath[100];


	const char* SCREEN_TITLE = "BrainStorm Studios";
	std::string consoleString = "";
	std::string anotherString = "false";
	std::string theString;

void runMainLoop();
void renderTheMenusAndGame();
void renderTheLoadingState();
void renderTheMenuBeforeItBecomesFullyVisible();


long FPS = 0, lastFPS = 0, showFPS = 0;

int main( int argc, char* args[] )
{
	iData[0] = 0;
	iData[1] = 1;
	iData[2] = 2;
	iData[3] = 3;

    scaleSize = 11.34;
    CameraPosition->xCord = 0;
    CameraPosition->yCord = 0;
    CameraPosition->zCord = -scaleSize;
	ibjectInputMain->setTheVideoDisplayAndWindow();
	ibjectInputMain->initGamePad();


	initialSquareTexturePath[0] = NULL, initialRoundTexturePath[0] = NULL;
	strcpy(initialSquareTexturePath, "Animations/textureAnimation/texture.png");
	strcpy(initialRoundTexturePath, "Animations/roundAnimation/windmillPropeller.png");





	if( !objBSUtils->initAL())
	{
		printf( "Unable to initialize audio library!\n" );
		//return 1;
	}

//	pthread_t threadInput;
//	pthread_create(&threadInput, NULL, &VideoAndInput, &objBSUtils);
//	pthread_exit(NULL);

	if( !objBSUtils->initGL())
	{
		printf( "Unable to initialize graphics library!\n" );
		//return 1;
	}
    //Load graphics programs
    if( !objBSUtils->loadGP() )
    {
        printf( "Unable to load shader programs!\n" );
        //return 1;
    }
	//objObstacles->setUpBodies();
	if( !objBSUtils->loadMedia() )
	{
		printf( "Unable to load media!\n" );
		//return 2;
	}




	for(int i = 0; i <= 255 ;i++)
	{
		canPressKeyAgain[i] = true;
		wasPressed[i] = false;
	}

	lastTime = SDL_GetTicks();


	lastMovedX = hero->theBody->GetPosition().x;


	srand(time(0));

	///objObstacles->setTheVaoData(originalBody->vao, originalBody->vbo, originalBody->ibo, originalBody->data, 1.0f, 1.0f);
//randareMenu->loadTheLoadingImage();
//	randareMenu->buildRainDrops();
	quit = false;
	lastFPS = SDL_GetTicks();
	while(!canRenderGameNow)
    {
        renderTheMenuBeforeItBecomesFullyVisible();
    }
    long long currentTime = 0, previousTime = 0, maxFPS = 60;
	while(!quit)
	{
//		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        SDL_PollEvent( &event );
//
//        if(event.type == SDL_QUIT)
//        {
//            quit = true;
//        }
//
//		///randareMenu->renderTheLoadingImage(1);
//		randareMenu->renderRainDrops();
//		SDL_GL_SwapBuffers();

        runMainLoop();
        currentTime = SDL_GetTicks();

        if (currentTime - previousTime < 1000 / maxFPS)
		{
			SDL_Delay(1000 / maxFPS - currentTime + previousTime);
		}
		previousTime = currentTime;
        //SDL_Delay(13);
	}


		SDL_Quit();
		exit(0);


	return 0;
}


BSColorRGBA black = {0.f, 0.f, 0.f, 1};
//val este pentru a da un delay la timer, gen daca este 10, sa astepte 10 ms
void runMainLoop()
{
//    uint32 curFPS = SDL_GetTicks() - lastFPS;
    long curFPS = SDL_GetTicks();
    if(curFPS % 1000 < 100 && lastFPS % 1000 > 100)
    {
        showFPS = FPS;
        FPS = 1;
        lastFPS = curFPS;
    }
    else
    {
        FPS++;
        lastFPS = curFPS;
    }
//    lastFPS = SDL_GetTicks();
//
//    if(curFPS)
//    {
//        showFPS = (float)1000/curFPS;
//    }

	///Check if the music is still playing
	if(muscicIndex == 1 && !objBSUtils->isPlaying(SourceSoundMusic1))
	{
		alSourcePlay(SourceSoundMusic2);
		muscicIndex = 2;
	}
	else
        if(muscicIndex == 2 && !objBSUtils->isPlaying(SourceSoundMusic2))
        {
            alSourcePlay(SourceSoundMusic3);
            muscicIndex = 3;
        }
        else
            if(muscicIndex == 3 && !objBSUtils->isPlaying(SourceSoundMusic3))
            {
                alSourcePlay(SourceSoundMusic1);
                muscicIndex = 1;
            }

    ///ii dau sunet in caz ca e in power up
    if(!isPaused)
    {
        if(hero->heroIsBerserk1 || hero->heroIsBerserk2 || hero->heroIsBerserk3)
        {
            if(!objBSUtils->isPlaying(SourceSoundPowerUp))
            {
                alSourcePlay(SourceSoundPowerUp);
            }
        }
    }
    ///scot sunetul daca nu e in power up
    if(!hero->heroIsBerserk1 && !hero->heroIsBerserk2 && !hero->heroIsBerserk3 || isPaused)
    {
        alSourceStop(SourceSoundPowerUp);
    }

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderTheMenusAndGame();

        //randareMenu->renderMyFont("FPS " + BStoString(showFPS), originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft,
          //              originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown - 1.2f, 1, 1, black);

		SDL_GL_SwapBuffers();


	ibjectInputMain->handleInput();
	//objBSUtils->controlConsoleString();


	///For the round player
	//if(addCircleOrSquare == -1)
	{
		//action2->heroTouchesObjects();
		//action2->moveThePlayer();
		//randareMenu->renderRoundPlayer();
	}
	//else
	{
		action->heroTouchesObjects();
		action->moveThePlayer();
	}

}


void renderTheMenusAndGame()
{
	///render the game if it's not in any other menu
	if(currentMenu->indexOfMenu == 3)
	{
	    isPaused = false;
		randareMenu->renderVboAndVao();
		bool doesItNeedsUpdateNext = false, doesItNeedsUpdateDead = false;

		///Set the Next Level Scene
		if(levelChoserPlayer->justFinished || deadScene->CosValueColorOfTheScene)
		{
			randareMenu->renderNextLevelSceneChange();
			if(deadScene->CosValueColorOfTheScene == 0)
			{
				deadScene->colorGoesUpOrDown = 1;
			}
		}
		else
		{
			doesItNeedsUpdateNext = true;
			hero->heroWasToNextLevel = false;
		}

		///Set the deadScene
		if(hero->heroIsDead || deadScene->SinValueColorOfTheScene)
		{
			randareMenu->renderDeadSceneChange();
			if(deadScene->SinValueColorOfTheScene == 0)
			{
				deadScene->colorGoesUpOrDown = 1;
			}
		}
		else
			///if he isn't dead
			{
				hero->heroWasDead = false;
				doesItNeedsUpdateDead = true;
			}
		if(doesItNeedsUpdateDead && doesItNeedsUpdateNext)
		{
			objBSUtils->update();

			action->ClickOnBlock();
			action->generateWhenHitsGroundParticles();
		}
	}
	else
		///Restul meniurilor
		{
            isPaused = true;
			///Daca se afla in meniul de levele, randeaza levelele
			if(currentMenu->indexOfMenu == 4)
			{
				randareMenu->renderVboAndVao();
				randareMenu->renderMenuLevels(chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->nrOfLevels,
												chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter);
			}
			else
				if(currentMenu->indexOfMenu == 5)
				{
					randareMenu->renderVboAndVao();
					randareMenu->renderMenuChapters();
				}
				else
				{
					randareMenu->renderVboAndVao();
					randareMenu->renderAnyButtons(currentMenu);
				}
		}
}






float alphaColorSin = 90;
void renderTheLoadingState()
{
	if(alphaColorSin > 0)
	{
		alphaColorSin -= 1.0f;
		randareMenu->renderTheLoadingImage(sin(randareMenu->toRadians(alphaColorSin)));

        SDL_PollEvent( &event );

        if(event.type == SDL_QUIT)
        {
            quit = true;
        }
	}
	else
	{
		canRenderGameNow = true;
	}
}

void renderTheMenuBeforeItBecomesFullyVisible()
{
	if(muscicIndex == 1 && !objBSUtils->isPlaying(SourceSoundMusic1))
	{
		alSourcePlay(SourceSoundMusic2);
		muscicIndex = 2;
	}
	else
        if(muscicIndex == 2 && !objBSUtils->isPlaying(SourceSoundMusic2))
        {
            alSourcePlay(SourceSoundMusic3);
            muscicIndex = 3;
        }
        else
            if(muscicIndex == 3 && !objBSUtils->isPlaying(SourceSoundMusic3))
            {
                alSourcePlay(SourceSoundMusic1);
                muscicIndex = 1;
            }

									glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(currentMenu->indexOfMenu == 3)
		{
			randareMenu->renderVboAndVao();
			bool doesItNeedsUpdateNext = false, doesItNeedsUpdateDead = false;
		}
		else
			///Restul meniurilor
			{
				///Daca se afla in meniul de levele, randeaza levelele
				if(currentMenu->indexOfMenu == 4)
				{
					randareMenu->renderVboAndVao();
					randareMenu->renderMenuLevels(chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->nrOfLevels,
													chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter);

				}
				else
					if(currentMenu->indexOfMenu == 5)
					{
						randareMenu->renderVboAndVao();
						randareMenu->renderMenuChapters();
					}
					else
					{
						randareMenu->renderVboAndVao();
						randareMenu->renderAnyButtons(currentMenu);
					}
			}


		if(!canRenderGameNow)
		{
			renderTheLoadingState();

                world->Step((float) 1/theTimeHowFast , 8, 3);
                world->ClearForces();
                action->heroTouchesObjects();

                    hero->animationIndexCurrentAnimation = hero->animationIndexPlayerStand;
                    hero->IsAtStepOfAnimation1 = true;
                    hero->IsAtStepOfAnimation2 = false;
                    hero->IsAtStepOfAnimation3 = false;
		}
						SDL_GL_SwapBuffers();
}
