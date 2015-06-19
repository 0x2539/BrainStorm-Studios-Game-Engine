#include "BSValues.h"
#include "BSRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <Box2D/Box2D.h>
#include "BSUtilities.h"
#include "BSObstacles.h"
#include "BSTexture.h"
#include "BSActionStuff.h"
#include "BSTexturedPolygonProgram2D.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "BSLevelMenu.h"
#include "BSInputClass.h"
#include <sstream>


zip *APKArchive;
zip_file* file;
int xTouch = -1, yTouch = -1;
BackButton *backBtn = new BackButton, *btnDarkLevels = new BackButton, *btnTimeControl = new BackButton,
			*btnPowerUp1 = new BackButton, *btnPowerUp2 = new BackButton, *btnPowerUp3 = new BackButton;

int movedX, movedY, tapX, tapY, tapRadius;
double swipeDistance;
bool tapped, moved;
bool jumpPressed;
bool isButtonDown;
int buttonSize;
int quadrantIndex;
BSPoint lastMovementPosition = {-1, -1};
BSPoint startPoint, endPoint;
bool justJumped = false, justJumped2 = false;


GLushort iData[] = { 0, 1, 2, 3 };


int SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;

std::string apkLocation;

GLuint iboBuffer;

float worldAngle = 0;
b2Vec2 worldGravity = b2Vec2(0, -40);
int gravityIsChanging = 0, startAngle = 0;


// comenteriu hack

GLuint blankTexture, whiteTexture;

BSBody *originalParticle = new BSBody, *originalTransparentMenu = new BSBody, *originalCoin = new BSBody, *originalFan = new BSBody,
*originalBody = new BSBody, *originalDarkLevel = new BSBody, *originalDarkMenu = new BSBody, *originalRainDrop = new BSBody,
*originalWormHole = new BSBody, *originalDustBody = new BSBody, *originalFanParticleX = new BSBody, *originalFanParticleY = new BSBody;
BSWormHole *lastWorm = NULL;

std::vector<BSSnowFlakes*>listOfRainDrops;
long long timer = 0;

BSTheSquareBodies *hero = new BSTheSquareBodies,
*Hero2nd = new BSTheSquareBodies;

BSLevelMenu *theLevelMenuObject = new BSLevelMenu();
BSUtilities *objBSUtils = new BSUtilities();
BSObstacles *objObstacles = new BSObstacles();
BSActionStuff *action = new BSActionStuff();
//BSActionStuffRound *action2 = new BSActionStuffRound();
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
transparentMenuBlockVao, transparentMenuBlockVbo, transparentMenuBlockIbo, gVertexBuffer = 0, texVertexBuffer = 0,
        texture, textureMill, playerTexture, playerTextureDead, playerTextureRound,
        starsTexture1, starsTexture2, starsTexture3, starsTexture4, backgroundTexture, clouds[6];

LevelChooserPlayerTexture *levelChoserPlayer = new LevelChooserPlayerTexture;
//BSTexturedPolygonProgram2D* mainTexturedPolygonProgram2D = NULL;
//BSPlayerControls *heroKeyboard = new BSPlayerControls;

BSMenuStructure *currentMenu = new BSMenuStructure;
BSButtonStructure *currentButton = new BSButtonStructure;


//Vertex buffer
GLuint ShaderCameraExtremeLeft, ShaderCameraExtremeRight,
ShaderCameraExtremeUp, ShaderCameraExtremeDown,
ShaderPlayerCoordinatesX, ShaderPlayerCoordinatesY,
ShaderMouseX, ShaderMouseY, ShaderIsTheSquare, ShaderWidthOfSquare, ShaderHeightOfSquare,
ShaderAflaRestulWidthOfSquare, ShaderAflaRestulHeightOfSquare, ShaderScaleSize,
ShaderRotationAngle, ShaderRotated, ShaderIsText, ShaderTextCoord, ShaderTextTex, ShaderIsCircle, ShaderCircleRadius,
ShaderCosRotation, ShaderSinRotation, ShaderScaleOnX, ShaderScaleOnY, ShaderDark, ShaderFlake;
//GLint mVertexPos2DLocation;
//GLint mTexCoordLocation;
GLuint locationBSVertexPosition3D, locationBSTextureCoordinate, locationBSModelViewMatrix, locationBSProjectionMatrix;
GLuint locationBSTextureColor, locationBSTextureUnit;
GLuint BSProgramID;

glm::mat4 BSProjectionMatrix;
glm::mat4 BSModelViewMatrix;
glm::vec3 m_position = glm::vec3(0, 0, 11.34);
glm::vec3 m_direction = glm::vec3(0, 0, -10);
glm::vec3 m_up = glm::vec3(0, 1, 0);



long long timeSinceMovedMouse = 0, timeSinceMovedLittleCircle = 0;

std::vector<BSTheSquareBodies*> ListOfSquareBodies;
std::vector<BSTheSquareBodies*> ListOfSquareDustBodies;
std::vector<BSSnowFlakes*> listOfSnowFlakes;
std::vector<BSWorldOfGooMouse*> listOfMouseCircles;
std::vector<BSCloudyParticles*> listOfCloudyParticles;
std::vector<BSTheRoundBodies*> ListOfRoundBodies;
std::vector<BSTheParticles*> ListOfParticles;
std::vector<BSNewList*>listOfAnimations;
int nrOfListOfAnimations = 0;
///std::vector<BSNewList*> listOfAnimations;
std::vector<BSMenuStructure*> listOfMenus;
std::vector<BSTheMessages*>listOfMessages;
std::vector<BSFans*> listOfFans;
std::vector<BSCoins*> listOfCoins;
std::vector<BSTextureSquare*> ListOfSquareTextures;
std::vector<BSTextureRound*> ListOfRoundTextures;
std::vector<BSWormHole*> listOfWormHoles;
std::vector<BsActiveAnimations*>listOfActiveAnimations;
std::vector<BSAnimList*>listOfLoadedAnimations;

float theCoinX, theCoinY;

int NrOfTotalLetters, nrOfChapters = 0, heroFacesLeftOrRight = 1, nrOfMessageSign = 0,
		coinsTotalNo = 0, coinsThisLevel = 0, deathsTotalNo = 0, deathsThisLevel = 0, variableWall = 0,
		nrBodiesDistroyed = 0, indexOfSelectedBody = 0, nrParticlesDistroyed = 0,
		nrParticles = 0, nrOfWhenItHits = 0, numberOfSquaresForPath = 0, nrBodies = 0;

//int SCREEN_WIDTH = 800;
//int SCREEN_HEIGHT = 600;
int SCREEN_FPS = 60;//usually 60
int SCREEN_BPP = 32, timeWhenTeleported = 0, muscicIndex = 0;


bool DarkLevels = false, canAddCoins = false, canAddFans = false, settingsFromFirstOrGame = false,
	canChangeVolumeMusic = false, canChangeVolumeAudioSfx = false, canChangeResolution = false,
	wasPressed[256], corpulEsteDistrus[1000], itMovedX = false, itMovedY = false, itMovedXLeft = false,
	itMovedXRight = false, itTurnedX = false, canMoveCamera = false, canWriteInConsole = false,
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


glm::mat4 LookAtMatrix;

long long startTime = 0, endTime = 0;

float HeroInitialX = 3, HeroInitialY = 3, newVolumeAudio = 1.f, newVolumeSFX = 1.f, currentVolumeAudio = 1.f, currentVolumeSFX = 1.f, scaleSize = 32, theTimeHowFast = 60,
	   CameraExtremeLeft = SCREEN_WIDTH / 2 / (SCREEN_HEIGHT / 18.f), CameraExtremeRight = SCREEN_WIDTH / 2 / (SCREEN_HEIGHT / 18.f) + 2000 / scaleSize,
	   CameraExtremeUp = SCREEN_HEIGHT / 2 / (SCREEN_HEIGHT / 18.f) + 230 / scaleSize, CameraExtremeDown =  SCREEN_HEIGHT / 2 / (SCREEN_HEIGHT / 18.f),
	   MenuCoordinateX = SCREEN_WIDTH / 2 / scaleSize, MenuCoordinateY = SCREEN_HEIGHT / 2 / scaleSize, WorldBoundaryLeft = 0, WorldBoundaryDown = 0,
	   WorldBoundaryUp = CameraExtremeUp, WorldBoundaryRight = CameraExtremeRight, lastMovedX = 0, changeInPosition = 0, lastPositionOfHeroX = 0, lastPositionOfHeroY = 0,
	   startPositionCameraX = 0, sinX = 0, sinY = 0, iteratieSin = 1.f * 5, widthOfObstacle = Hero_size, heightOfObstacle = Hero_size, createObstacleX = 0, createObstacleY = 0,
	   razaInitialaInner = 40, razaInitialaOuter = 40, MouseX = 0, MouseY = 0, MouseXLast = 0, MouseYLast = 0, SursaDeLuminaX = 0, SursaDeLuminaY = 0, lastTime = 0,
	   speedWalk = 25, speedWalkFast = 50, speedRun = 1.2, speedJumpUp = 17.7f, speedJumpToSide = 17, speedGoDown = -20, speedWalkInAir = 25, speedWalkInAirFast = 50,
	   speedJumpToTheSameSide = 17.1, speedJumpUpOnWall = 21.f, timeToStayInAirWhenJumpsOnTheSameWall = 175, timeToStayOnWall = 250, buttonMenuWidth = 3 / 2.f,
	   buttonMenuHeight = 1 / 2.f, moveStringX = 0, moveStringY = 0;



BSTextureSquare *theLoadingImage = new BSTextureSquare;
bool doneLoadingTheGame = false, canRenderGameNow = false;

short BinaryPlayer = -1;//0x0001;  // 0000000000000001 in binary
short BinaryMonster = -2;//0x0002; // 0000000000000010 in binary
short BinaryScenery = 1;//0x0004; // 0000000000000100 in binary
short BinaryParticles = -1;//0x0008; // 0000000000000100 in binary


float gameBoundLeft, gameBoundRight, gameBoundDown, gameBoundUp;

BSBody *CameraPosition = new BSBody;

float playerAnimWidth, playerAnimHeight;


char initialSquareTexturePath[100], initialRoundTexturePath[100];
float cross_platform_scale = 0;

const char* SCREEN_TITLE = "BrainStorm Studios";
std::string consoleString = "";
std::string anotherString = "false";
std::string theString;

void runMainLoop();
void renderTheMenusAndGame();
void renderTheLoadingState();
void renderTheMenuBeforeItBecomesFullyVisible();




GLuint textureID, vaoBuffer, vboBuffer;
BSTexturedVertex2D data[4];



double getDistance(int x1, int y1, int x2, int y2)
{
    return sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
}

static bool isTouchInButtonRange(BackButton *btn, BSPoint point)
{
	if(point.x < btn->x * cross_platform_scale)// - (btn->w * cross_platform_scale) / 2)
	{
		return false;
	}
	if(point.x > btn->x * cross_platform_scale + (btn->w * cross_platform_scale))// / 2)
	{
		return false;
	}
	if(SCREEN_HEIGHT - point.y < btn->y * cross_platform_scale - (btn->h * cross_platform_scale) / 2)
	{
		return false;
	}
	if(SCREEN_HEIGHT - point.y > btn->y * cross_platform_scale + (btn->h * cross_platform_scale) / 2)
	{
		return false;
	}
	return true;
}

static void onTouchBegin()
{
//	//LOGI("%d %d; %f %f - %f %f", lastMovementPosition.x, lastMovementPosition.y,
//				backBtn->x * cross_platform_scale - backBtn->w * cross_platform_scale / 2,
//				backBtn->x * cross_platform_scale + backBtn->w * cross_platform_scale / 2,
//				backBtn->y * cross_platform_scale - backBtn->h * cross_platform_scale / 2,
//				backBtn->y * cross_platform_scale + backBtn->h * cross_platform_scale / 2);
	if(isTouchInButtonRange(backBtn, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
	           hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
	{
		//LOGI("%s", "began on back");
		//std::cout<<"hold back"<<'\n';
		isButtonDown = true;
		backBtn->isDown = true;
		startPoint.x = 0;
		startPoint.y = 0;
	}
	else
		if(isTouchInButtonRange(btnDarkLevels, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
		   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
		{
			//LOGI("%s", "began on dark");
			//std::cout<<"hold dark"<<'\n';
			isButtonDown = true;
			btnDarkLevels->isDown = true;
			startPoint.x = 0;
			startPoint.y = 0;
		}
		else
			if(isTouchInButtonRange(btnTimeControl, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
			   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
			{
				//LOGI("%s", "began on time");
				//std::cout<<"hold time"<<'\n';
				isButtonDown = true;
				btnTimeControl->isDown = true;
				startPoint.x = 0;
				startPoint.y = 0;
			}
			else
				if(isTouchInButtonRange(btnPowerUp1, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
				   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
				{
					//LOGI("%s", "began on power1");
					//std::cout<<"hold power 1"<<'\n';
					isButtonDown = true;
					btnPowerUp1->isDown = true;
					startPoint.x = 0;
					startPoint.y = 0;
				}
				else
					if(isTouchInButtonRange(btnPowerUp2, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
					   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
					{
						//LOGI("%s", "began on power2");
						//std::cout<<"hold power 2"<<'\n';
						isButtonDown = true;
						btnPowerUp2->isDown = true;
						startPoint.x = 0;
						startPoint.y = 0;
					}
					else
						if(isTouchInButtonRange(btnPowerUp3, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
						   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
						{
							//LOGI("%s", "began on power3");
							//std::cout<<"hold power 3"<<'\n';
							isButtonDown = true;
							btnPowerUp3->isDown = true;
							startPoint.x = 0;
							startPoint.y = 0;
						}
						else
						{
							isButtonDown = false;
							startPoint = lastMovementPosition;
						}
}

static void onTouchEnd()
{
	if(isTouchInButtonRange(backBtn, lastMovementPosition) && backBtn->isDown == true)
	{
		//LOGI("%s", "end on back");
		//std::cout<<"clicked back"<<'\n';
		backBtn->isDown = false;
		backBtn->canClick = true;
		endPoint.x = 0;
		endPoint.y = 0;
		moved = false;
		tapped = false;
	}
	else
		if(isTouchInButtonRange(btnDarkLevels, lastMovementPosition) && btnDarkLevels->isDown == true)
		{
			//LOGI("%s", "end on dark");
			//std::cout<<"clicked dark"<<'\n';
			btnDarkLevels->isDown = false;
			btnDarkLevels->canClick = true;
			endPoint.x = 0;
			endPoint.y = 0;
			moved = false;
			tapped = false;
		}
		else
			if(isTouchInButtonRange(btnTimeControl, lastMovementPosition) && btnTimeControl->isDown == true)
			{
				//LOGI("%s", "end on time");
				//std::cout<<"clicked time"<<'\n';
				btnTimeControl->isDown = false;
				btnTimeControl->canClick = true;
				endPoint.x = 0;
				endPoint.y = 0;
				moved = false;
				tapped = false;
			}
			else
				if(isTouchInButtonRange(btnPowerUp1, lastMovementPosition) && btnPowerUp1->isDown)
				{
					//LOGI("%s", "end on power1");
					//std::cout<<"clicked power 1"<<'\n';
					btnPowerUp1->isDown = false;
					btnPowerUp1->canClick = true;
					endPoint.x = 0;
					endPoint.y = 0;
					moved = false;
					tapped = false;
				}
				else
					if(isTouchInButtonRange(btnPowerUp2, lastMovementPosition) && btnPowerUp2->isDown)
					{
						//LOGI("%s", "end on power2");
						//std::cout<<"clicked power 2"<<'\n';
						btnPowerUp2->isDown = false;
						btnPowerUp2->canClick = true;
						endPoint.x = 0;
						endPoint.y = 0;
						moved = false;
						tapped = false;
					}
					else
						if(isTouchInButtonRange(btnPowerUp3, lastMovementPosition) && btnPowerUp3->isDown)
						{
							//LOGI("%s", "end on power3");
							//std::cout<<"clicked power 3"<<'\n';
							btnPowerUp3->isDown = false;
							btnPowerUp3->canClick = true;
							endPoint.x = 0;
							endPoint.y = 0;
							moved = false;
							tapped = false;
						}
						else
						{
							isButtonDown = false;
							backBtn->isDown = false;
							backBtn->canClick = false;
							btnTimeControl->isDown = false;
							btnTimeControl->canClick = false;
							btnDarkLevels->isDown = false;
							btnDarkLevels->canClick = false;

							btnPowerUp1->isDown = false;
							btnPowerUp1->canClick = false;
							btnPowerUp2->isDown = false;
							btnPowerUp2->canClick = false;
							btnPowerUp3->isDown = false;
							btnPowerUp3->canClick = false;

							endPoint = lastMovementPosition;
							lastMovementPosition.x = 0;
							lastMovementPosition.y = 0;

							movedX = endPoint.x - startPoint.x;
							movedY = -endPoint.y + startPoint.y;
							swipeDistance = getDistance(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

							if(movedX == 0)
							{
								movedX++;
							}
							if(movedY == 0)
							{
								movedY++;
							}

							//when tap the screen
							if(abs(movedX) < 10 && abs(movedY) < 10)
							{
								tapX = (startPoint.x + endPoint.x ) / 2;
								tapY = (startPoint.y + endPoint.y ) / 2;
								tapped = true;
								moved = false;
								//std::cout<<"tapped"<<'\n';
							}
							else
							{
								moved = true;
								tapped = false;
							}

							////LOGI("%i %i : %i %i", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
						}
}


std::string aplicationPath = "";


bool setupGraphics(int w, int h)
{
	startTime = now_ms();
    objBSUtils->loadGP(w, h);

    glGenBuffers(1, &iboBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLushort), iData, GL_DYNAMIC_DRAW);

    int width, height;
    loadTexture("playerTexture.png", textureID);

    objObstacles->setTheVaoData(vaoBuffer, vboBuffer, iboBuffer, data, 1, 1);

    glViewport(0, 0, w, h);
    cross_platform_scale = (float)h / 19;


    //std::string someFile = getFile("file.txt");
    //std::stringstream streamer;
    //streamer << someFile;
    //std::string cit;
    //streamer>>cit;
    ////LOGI("%s", cit.c_str());

    glUniform1f(ShaderIsCircle, 0.0f);
    glUniform1i(locationBSTextureUnit, 0 );

    //BSProjectionMatrix = glm::perspective(45.f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 10000.0f);
    BSProjectionMatrix = glm::ortho( 0.0f, (float) SCREEN_WIDTH, 0.0f, (float) SCREEN_HEIGHT, 0.1f, 10000.0f);
    //glm::mat4 Projection = glm::ortho( 0.0f, 800.0f, 600.0f, 0.0f,-5.0f, 5.0f);

    glUniformMatrix4fv(	locationBSProjectionMatrix, 1, GL_FALSE, glm::value_ptr( BSProjectionMatrix ) );

    scaleSize = 11.34;
	CameraPosition->xCord = 0;
	CameraPosition->yCord = 0;
	CameraPosition->zCord = -scaleSize;

	//int wid, hei;
	//loadTextureFromPNG("texture.png", texture);
/*
	std::string path = aplicationPath + "here.txt";
	//LOGI("%s %s", "before write:", path.c_str());
	std::string input = "shap shap";
	const char *in = "shap shap";//input.c_str();
	char in2[] = "shap shap";
	FILE *f = fopen(path.c_str(), "a+"); \
	  fprintf(f, "%s", input.c_str());//, __VA_ARGS__);
	  fflush(f);
	  fclose(f);
		//LOGI("%s", "after write");
	  std::string out = getFile("here.txt");
	  //LOGI("%s", out.c_str());*/

	LOGE("color types: %i %i", GL_RGB, GL_RGBA);

    ////LOGI("%s", "began loading the media content");
    objBSUtils->loadMedia();
    ////LOGI("%s", "loaded the media content");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);



    return true;
}

void renderFrame()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    {
        runMainLoop();
		randareMenu->renderThePauseBtn();
    }
    //BSColorRGBA theColorOfObstacle = {1.0f, 1.0f, 1.0f, 1.0f};
    //renderBody(0, 0, scaleSizeInitial, 0, 0, 0, textureID, theColorOfObstacle, vboBuffer, 2, 4, 0);

    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    //randareMenu->renderVboAndVao();
}




BSPoint lastLastPos = {-1, -1};


int lastFPS = 0, showFPS = 0, FPS = 0;
BSColorRGBA black = {0.f, 0.f, 0.f, 1};
//val este pentru a da un delay la timer, gen daca este 10, sa astepte 10 ms
void runMainLoop()
{
//    uint32 curFPS = SDL_GetTicks() - lastFPS;
    /*long curFPS = SDL_GetTicks();
    if(curFPS % 1000 < 100 && lastFPS % 1000 > 100)
    {
        showFPS = FPS;
    	//LOGI("%i", showFPS);
        FPS = 1;
        lastFPS = curFPS;
    }
    else
    {
        FPS++;
        lastFPS = curFPS;
    }*/
//    lastFPS = SDL_GetTicks();
//
//    if(curFPS)
//    {
//        showFPS = (float)1000/curFPS;
//    }

	///Check if the music is still playing (you got 3 melodies that play through out the game, and you want to play it one after another)
	/*if(muscicIndex == 1 && !objBSUtils->isPlaying(SourceSoundMusic1))
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
    if((!hero->heroIsBerserk1 && !hero->heroIsBerserk2 && !hero->heroIsBerserk3) || isPaused)
    {
        alSourceStop(SourceSoundPowerUp);
    }
	*/

    ///the rendering function
	renderTheMenusAndGame();

//        randareMenu->renderMyFont("FPS " + BStoString(showFPS), originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft,
//                        originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown - 1.2f, 1, 1, black);

    ///Get the keyboard or gamepad input
	///ibjectInputMain->handleInput();

	if((lastLastPos.x != -1 && lastMovementPosition.x == -1) || (lastLastPos.y != -1 && lastMovementPosition.y == -1))
	{
		lastMovementPosition = lastLastPos;
		onTouchEnd();
		lastMovementPosition.x = -1;
		lastMovementPosition.y = -1;
		////LOGI("%s", "touches ended");
		///touches ended;
	}
	else
		if((lastLastPos.x == -1 && lastMovementPosition.x != -1) || (lastLastPos.y == -1 && lastMovementPosition.y != -1))
		{
			onTouchBegin();
			////LOGI("%s", "touches began");
			///touches began;
		}
	////LOGI("%i %i", lastMovementPosition.x, lastMovementPosition.y);
	//LOGI("%s", "before touchscreen");
	ibjectInputMain->getTouch();
	//LOGI("%s", "after touchscreen");
	//LOGI("%s", "before touch");
	action->heroTouchesObjects();
	//LOGI("%s", "after touch");
	//LOGI("%s", "before move");
    action->moveThePlayer();
	//LOGI("%s", "after move");
}

float toRadians(float x)
{
	float pi = 3.1415;
	return (float) (pi/2 * x)/90;
}

int sign(float nr)
{
    if(nr > 0)
    {
        return 1;
    }
    else
        if(nr < 0)
        {
            return -1;
        }
        else
        {
            return 0;
        }
}
float modul(float nr)
{
    if(nr > 0)
    {
        return nr;
    }
    else
        return -nr;
}

void renderTheMenusAndGame()
{
	if(gravityIsChanging == 1)
    {
    	////LOGI("%s", "game2");
        if(worldAngle < startAngle + 90)
        {
        	////LOGI("%s", "game3");
            worldAngle += 2.2f;
        }
        else
        {
        	////LOGI("%s", "game4");
            worldAngle = startAngle + 90;
            gravityIsChanging = 0;
            worldGravity = b2Vec2((int)(-sin(toRadians(worldAngle))* 40), (int)(cos(toRadians(worldAngle))* -40));

            if(worldGravity.x != 0)
            {
                speedWalk = modul(speedWalk) * sign(worldGravity.x);
                speedWalkInAir = modul(speedWalkInAir) * sign(worldGravity.x);
                speedJumpToSide = modul(speedJumpToSide) * sign(worldGravity.x);
                speedJumpToTheSameSide = modul(speedJumpToTheSameSide) * sign(worldGravity.x);
            }
            else
            {
                speedWalk = modul(speedWalk) * -sign(worldGravity.y);
                speedWalkInAir = modul(speedWalkInAir) * -sign(worldGravity.y);
                speedJumpToSide = modul(speedJumpToSide) * -sign(worldGravity.y);
                speedJumpToTheSameSide = modul(speedJumpToTheSameSide) * -sign(worldGravity.y);
            }
            world->SetGravity(worldGravity);

            hero->theBody->SetLinearVelocity(b2Vec2(0, 0));
            world->Step((float) 1/theTimeHowFast , 8, 3); //1/60, 8, 3
            world->ClearForces();
        }
//        hero->theBody->SetTransform(hero->theBody->GetPosition(), toRadians(-worldAngle));
        hero->xAngle = -worldAngle;
    }
    else
        if(gravityIsChanging == -1)
        {
        	////LOGI("%s", "game5");
            if(worldAngle > startAngle - 90)
            {
                worldAngle -= 2.2f;
            }
            else
            {
                worldAngle = startAngle - 90;
                gravityIsChanging = 0;
                worldGravity = b2Vec2((int)(-sin(toRadians(worldAngle)) * 40), (int)(cos(toRadians(worldAngle)) * -40));

                if(worldGravity.x != 0)
                {
                    speedWalk = modul(speedWalk) * sign(worldGravity.x);
                    speedWalkInAir = modul(speedWalkInAir) * sign(worldGravity.x);
                    speedJumpToSide = modul(speedJumpToSide) * sign(worldGravity.x);
                    speedJumpToTheSameSide = modul(speedJumpToTheSameSide) * sign(worldGravity.x);
                }
                else
                {
                    speedWalk = modul(speedWalk) * -sign(worldGravity.y);
                    speedWalkInAir = modul(speedWalkInAir) * -sign(worldGravity.y);
                    speedJumpToSide = modul(speedJumpToSide) * -sign(worldGravity.y);
                    speedJumpToTheSameSide = modul(speedJumpToTheSameSide) * -sign(worldGravity.y);
                }
                world->SetGravity(worldGravity);

                hero->theBody->SetLinearVelocity(b2Vec2(0, 0));
                world->Step((float) 1/theTimeHowFast , 8, 3); //1/60, 8, 3
                world->ClearForces();
            }
//            hero->theBody->SetTransform(hero->theBody->GetPosition(), toRadians(-worldAngle));
            hero->xAngle = -worldAngle;
        }
//        std::cout<<worldGravity.x<<' '<<worldGravity.y<<'\n';

	///render the game if it's not in any other menu
	if(currentMenu->indexOfMenu == 3)
	{
		////LOGI("%s", "game6");
	    isPaused = false;
		randareMenu->renderVboAndVao();
		bool doesItNeedsUpdateNext = false, doesItNeedsUpdateDead = false;

		///Set the Next Level Scene
		if(levelChoserPlayer->justFinished || deadScene->CosValueColorOfTheScene)
		{
			////LOGI("%s", "game7");
			randareMenu->renderNextLevelSceneChange();
			if(deadScene->CosValueColorOfTheScene == 0)
			{
				deadScene->colorGoesUpOrDown = 1;
			}
		}
		else
		{
			////LOGI("%s", "game8");
			doesItNeedsUpdateNext = true;
			hero->heroWasToNextLevel = false;
		}

		///Set the deadScene
		if(hero->heroIsDead || deadScene->SinValueColorOfTheScene)
		{
			////LOGI("%s", "game9");
			randareMenu->renderDeadSceneChange();
			if(deadScene->SinValueColorOfTheScene == 0)
			{
				deadScene->colorGoesUpOrDown = 1;
			}
		}
		else
			///if he isn't dead
			{
			////LOGI("%s", "game10");
				hero->heroWasDead = false;
				doesItNeedsUpdateDead = true;
			}
		if(doesItNeedsUpdateDead && doesItNeedsUpdateNext)
		{
			////LOGI("%s", "game11");
			objBSUtils->update();

			action->generateWhenHitsGroundParticles();
		}
		////LOGI("%s", "game12");
	}
	else
		///Restul meniurilor
		{
		////LOGI("%s", "game13");
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
	canRenderGameNow = true;
}

void renderTheMenuBeforeItBecomesFullyVisible()
{
	/*
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
*/
									glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(currentMenu->indexOfMenu == 3)
		{
			//LOGI("%s", "menu1");
			randareMenu->renderVboAndVao();
//			bool doesItNeedsUpdateNext = false, doesItNeedsUpdateDead = false;
		}
		else
			///Restul meniurilor
			{
				//LOGI("%s", "menu2");
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
						//SDL_GL_SwapBuffers();
}









extern "C"
{
    JNIEXPORT void JNICALL Java_com_BrainStormStudios_BSMainLib_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring apkPath);
    JNIEXPORT void JNICALL Java_com_BrainStormStudios_BSMainLib_step(JNIEnv * env, jobject obj, jint xTouch, jint yTouch);
};

JNIEXPORT void JNICALL Java_com_BrainStormStudios_BSMainLib_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring apkPath)
{
    const char* str;
    jboolean isCopy;
    str = env->GetStringUTFChars(apkPath, &isCopy);
    apkLocation = BStoString(str);
    aplicationPath = apkLocation;
    loadAPK(str);

    setupGraphics(width, height);

}

JNIEXPORT void JNICALL Java_com_BrainStormStudios_BSMainLib_step(JNIEnv * env, jobject obj, jint xTouch, jint yTouch)
{
	////LOGI("%i %i", lastMovementPosition.x, lastMovementPosition.y);
	lastLastPos = lastMovementPosition;
	lastMovementPosition.x = xTouch;
	lastMovementPosition.y = yTouch;
	////LOGI("%i %i", xTouch, yTouch);
    renderFrame();
}
