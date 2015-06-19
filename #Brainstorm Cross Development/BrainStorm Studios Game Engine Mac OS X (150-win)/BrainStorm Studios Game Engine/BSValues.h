#ifndef VALUES_H_INCLUDED
#define VALUES_H_INCLUDED

#include "BSOpengl.h"
#include <list>
#include <Box2D/Box2D.h>
#include <sstream>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include "glm/glm.hpp"


#include <SDL/SDL.h>


//Screen Constants
///#define SCREEN_WIDTH 800//sa le schimb si in main
///#define SCREEN_HEIGHT 600
///#define SCREEN_FPS 60
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_FPS;
extern int SCREEN_BPP;
extern float scaleSize;
///#define SCREEN_BPP 32
#define Hero_size 1 //it has to be even, cuz when i render, i do it by /2
					//#define scaleSize 32
#define scaleSizeInitial -11.3
//#define PixelToMeters 20

template <typename Cons>
std::string BStoString(const Cons& t)
{
    std::ostringstream os;
    os<<t;
    std::string s(os.str());
    return s;
}

struct BSTexCoord
{
    GLfloat s;
    GLfloat t;
};

struct BSRectangle
{
    GLfloat x;
    GLfloat y;
    GLfloat w;
    GLfloat h;
};

struct BSColorRGBA
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

struct BSVertexPos2D
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct BSTexturedVertex2D
{
    BSVertexPos2D position;
	BSTexCoord texCoord;
};

struct BSBody
{
	float xCord, yCord, zCord, width, height, depth, radius, value1, value2, xInit, yInit;
	BSColorRGBA color;
	int index;
    BSTexturedVertex2D data[4];
    GLuint texture, vao, vbo, ibo;
};

struct BSVertices3D
{
    float x, y, z;
};

///UserData-ul din obstacole
struct USERDATA
{
    std::string name, width, height;
    int timeUntilDestroy;
    long long BumTime;
    bool canKillHero, isToNextLevel;
    int isDustAble, isDust;
};

///Butoanele
struct BSButtonStructure : BSBody
{
	int indexOfButton;
    float NextMenuIndex;
    BSTexturedVertex2D dataOfButtons[2][4]; //[0]->butonul cand nu este selectat, [1]->butonul este selectat
    GLuint vaoOfButtons[2], vbo[2], ibo[2];
    GLuint textureOfButtons[2];
	
    bool isSelected;
	
    std::string name;
};

struct BSMenuStructure
{
	int indexOfMenu;
    //BSButtonStructure *Buttons[40];
	
    std::list<BSButtonStructure*> listOfButtons;
	
    int MenuIndex, numberOfButtons;
	
    GLuint textureOfMenu;
	
    ///int MenuState, NumberOfButtons;
    ///BSButtonStructure* thebuttons[];
};

///Backgroundurile
struct BSTheBackgrounds : BSBody
{
    float xInit, yInit;
};extern BSTheBackgrounds *backgroundSky, *backgroundMountain, *backgroundBush, *backgroundField, *backgroundHighField;

///Patratul cel mic cu care vad unde pun obiectele
struct BSTheSquare : BSBody
{
};

///Cercul cel mic cu care vad unde pun obiectele
struct BSTheCircle : BSBody
{
};

///Particulele
struct BSTheParticles : BSBody
{
    b2Body *theBodyOfParticle;
    float speedX, speedY, startX, startY;
    long long BumTime;//retine momentul in care e distrusa
    int timeUntilBum;//retine cat de mult sta pana face BUM
    BSColorRGBA initialcolor;
    bool isDestroyed;
};

struct BSBodyScript : BSBody
{
    float xPower, yPower, xLength, yLength, xInitial, yInitial;
};

///Structura pentru obiectele din Box2D
struct BSTheSquareBodies : BSBody
{
    b2Body *theBody;
    std::string nameOfTexture;
    bool heroIsDead, heroWasDead, heroWasToNextLevel, heroIsBerserk1, heroIsBerserk2, heroIsBerserk3,
	ObstacleCanKillHero, ObstacleFinishesLevel, heroStopped, heroBegan, heroIsMoving;
	
    BSBodyScript *script;
	
    float animationIndexPlayerStand,
	animationIndexPlayerMoveRight, animationIndexPlayerMoveLeft,
	animationIndexPlayerMoveUpRight, animationIndexPlayerMoveUpLeft,
	animationIndexPlayerMoveDownRight, animationIndexPlayerMoveDownLeft,
	animationIndexPlayerDied, animationIndexPlayerWallLeft, animationIndexPlayerWallRight,
	animationIndexPlayerStoppedFromMovingRight, animationIndexPlayerStoppedFromMovingLeft,
	animationIndexPlayerDieLeft, animationIndexPlayerDieRight,
	animationIndexCurrentAnimation, animationIndexCurrentAnimationBerserk, animationIndexIntermediary,
	animationIndexPlayerTeleportedIn, animationIndexPlayerTeleportedOut,
	animationIndexPlayerAura1, animationIndexPlayerAura2, animationIndexPlayerAura3, animationIndexPlayerAuraElectricity,
	animationIndexPlayerWormHole;
	
    bool IsAtStepOfAnimation1, IsAtStepOfAnimation2, IsAtStepOfAnimation3;
    bool IsAtStepOfAnimation21, IsAtStepOfAnimation22, IsAtStepOfAnimation23;
    bool IsAtStepOfAnimation31, IsAtStepOfAnimation32, IsAtStepOfAnimation33;
    bool IsAtStepOfAnimation41, IsAtStepOfAnimation42, IsAtStepOfAnimation43;
    //bool playedAnimationOnce1, playedAnimationOnce2, playedAnimationOnce3;
}; extern int heroFacesLeftOrRight, timeWhenTeleported;

///Structura pentru obiectele din Box2D
struct BSTheRoundBodies : BSBody
{
    b2Body *theBody;
    BSBodyScript *script;
    std::string nameOfTexture;
    bool heroIsDead, heroWasDead, heroIsBerserk, ObstacleCanKillHero, ObstacleFinishesLevel;
    bool isRotating;
};

///Structura pentru mesajele jucatorului
struct BSTheMessages : BSBody
{
    float widthOfSign, heightOfSign, widthOfMessage, heightOfMessage;
    BSColorRGBA colorOfSign, colorOfMessage;
    GLuint textureOfSign, vaoBufferOfSign, textureOfMessage, vaoBufferOfMessage,
	vboBufferOfSign, vboBufferOfMessage, iboBufferOfSign, iboBufferOfMessage;
    std::string nameOfTextureSign, nameOfTextureMessage;
    BSTexturedVertex2D dataOfSign[4], dataOfMessage[4];
	
    bool isShownTheMessage;
};
extern std::list<BSTheMessages*>listOfMessages; //BSTheMessages *theMessages[100];
extern int nrOfMessageSign;

struct BSCoins : BSBody
{
	float sinValue, sinValue2, xInit, yInit;
	int value;
	bool available, deleteIt, alreadyHadIt;
}; 	extern std::list<BSCoins*> listOfCoins;
extern BSTexturedVertex2D coinData[4];
extern GLuint coinTexture, coinVao, coinVbo, coinIbo;
extern bool canAddCoins;
extern float theCoinX, theCoinY;

struct BSFans : BSBody
{
	float powerX, powerY, lenthOfPower;
	int nrOfParticles;
	float xMax, xMin, yMax, yMin;
	std::list<BSBody*> particles;
}; 	extern std::list<BSFans*> listOfFans;
extern BSTexturedVertex2D fanData[4];
extern GLuint fanTexture, fanVao, fanVbo, fanIbo;
extern bool canAddFans;

struct BSSnowFlakes : BSBody
{
	float xPower, yPower, xInit, yInit, sinValue;
	
};extern std::list<BSSnowFlakes*> listOfSnowFlakes;
extern long long timeSinceMovedMouse, timeSinceMovedLittleCircle;


struct BSCloudyParticles : BSBody
{
	float xPower, yPower, xInit, yInit, sinValue;
};extern std::list<BSCloudyParticles*> listOfCloudyParticles;
extern GLuint clouds[6];


struct BSWormHole : BSBody
{
    int indexOfWorm, connectionIndex;
}; extern std::list<BSWormHole*> listOfWormHoles;
extern BSWormHole *lastWorm;


struct BSWorldOfGooMouse : BSBody
{
};extern std::list<BSWorldOfGooMouse*> listOfMouseCircles;


///Structura pentru o scena, de ex: se innegreste ecranul cand moare
struct BSSceneStructure : BSBody
{
    float SinValueColorOfTheScene, CosValueColorOfTheScene;
    int colorGoesUpOrDown;
};

///Structura pentru animatie
struct BSAnimation : BSBody
{
    std::string nameOfTheAnimation;
	
	
    BSTheSquareBodies *theSquareBodyBinded;
    BSTheRoundBodies *theRoundBodyBinded;
	
    bool canAnimate;
    ///Vad care instanta o randez //de ex, pot avea 2 animatii pentru acelasi corp, animatie cand merge la dreapta sau la stanga
    int animationIndex, animationNR;//animationNR - nr animatiei
    int indexOfAnimation;
	
    float timeUntilNext;//timpul cat dureaza animatia
    float timeToShow;//timpul in care trece la urmatoarea
    int nrOfAnimations;
	
	//int theCurrentIndexOfAnimation;
	
    bool itPlayedThisAnimation;
};

struct BSNewList
{
	int firstNR, secondNR, thirdNR;
	std::list<BSAnimation*> listForAnimations1, listForAnimations2, listForAnimations3;
	
    int animationIndex;
    bool isContinuing, isOnLoopAnimation1, isOnLoopAnimation2, isOnLoopAnimation3;
	
    BSAnimation* theCurrentAnimation;
};
extern BSNewList *listOfAnimations[100];
extern int nrOfListOfAnimations;

struct BsActiveAnimations : BSBody
{
    int indexOfAnimation;
	
    bool isAtStepOfAnimation1, isAtStepOfAnimation2, isAtStepOfAnimation3,
	canPlayAnimation1, canPlayAnimation2, canPlayAnimation3,
	canPlayIt;
	
	BSAnimation *theCurrentAnimation;
};
extern BsActiveAnimations *listOfActiveAnimations[5];


///Structura doar pentru texturi patrate
struct BSTextureSquare : BSBody
{
    std::string nameOfTexture;
}; extern BSTextureSquare *mouseTexture;

///Structura doar pentru texturi rotunde
struct BSTextureRound : BSBody
{
    std::string nameOfTexture;
};


///Structura Level Choose-rului
struct ChapterLevelsStructure : BSBody
{
    bool isFinished, isCurrent, indexOfLevel, canPlayIt;
	
    GLuint textureOfLevel, textureOfConnectionLeftRight, textureOfConnectionUpDown, textureOfFinishedLevel,
	vaoBufferOfLevel, vaoBufferOfConnectionLeftRight, vaoBufferOfConnectionUpDown, vaoBufferOfFinishedLevel,
	vboBufferOfLevel, vboBufferOfConnectionLeftRight, vboBufferOfConnectionUpDown, vboBufferOfFinishedLevel,
	iboBufferOfLevel, iboBufferOfConnectionLeftRight, iboBufferOfConnectionUpDown, iboBufferOfFinishedLevel;
	
    GLuint textureOfConnectionLeftRightChapter, textureOfConnectionUpDownChapter, textureOfFinishedLevelChapter,
	vaoBufferOfConnectionLeftRightChapter, vaoBufferOfConnectionUpDownChapter, vaoBufferOfFinishedLevelChapter,
	vboBufferOfConnectionLeftRightChapter, vboBufferOfConnectionUpDownChapter, vboBufferOfFinishedLevelChapter,
	iboBufferOfConnectionLeftRightChapter, iboBufferOfConnectionUpDownChapter, iboBufferOfFinishedLevelChapter;
	
    BSTexturedVertex2D dataOfLevel[4], dataOfConnectionLeftRight[4], dataOfConnectionUpDown[4], dataOfFinishedLevel[4];
    BSTexturedVertex2D dataOfConnectionLeftRightChapter[4], dataOfConnectionUpDownChapter[4], dataOfFinishedLevelChapter[4];
	
	float widthConnectionLeftRightLevel, widthConnectionUpDownLevel, widthConnectionLeftRightChapter, widthConnectionUpDownChapter,
	heightConnectionLeftRightLevel, heightConnectionUpDownLevel, heightConnectionLeftRightChapter, heightConnectionUpDownChapter,
	widthFinishedLevel, heightFinishedLevel, widthFinishedChapter, heightFinishedChapter;
	std::string textOnLevel;
};
///Structura Chapterelor
struct ChapterStructure : BSBody
{
	ChapterLevelsStructure *levelFromChapter[100];
	bool isFinishedChapter, isAvailableChapter;
	int nrOfLevels;
	std::string nameOfTheChapter;
	
	std::string textOnChapter;
	
};


struct ListaDeCaractere
{
	char theCharArray1D[1000], theCharArray2D[100][100], theCharArray2DAttributes[100][100];
};



struct LevelChooserPlayerTexture : BSBody
{
    int indexOfLevelThatItIsOn, indexOfChapterThatItIsOn;
    int isMovingLeftRight, isMovingUpDown;
    bool canMove, justFinished;
};



struct BSAnimationOfObject : BSBody
{
    std::string nameOfTheTexture;
    float timeUntilNext;//timpul cat dureaza animatia
    float timeToShow;//timpul in care trece la urmatoarea
    int nrOfAnimations;
};

struct BSAnimatedObject : BSBody
{
    std::string nameOfTexture;
    bool isSquare;
};


struct BSGamePadStructure
{
	bool buttonIsPressed[50];
	
	SDL_Joystick *joystick;
	
	float leftAxisDown, leftAxisLeft, leftAxisRight, leftAxisUp,
	rightAxisDown, rightAxisLeft, rightAxisRight, rightAxisUp;
	
	bool leftHat, rightHat, downHat, upHat,
	leftUpHat, rightUpHat, leftDownHat, rightDownHat, centeredHat;
	
	int nrButtons, indexOfGamepad;
}; extern BSGamePadStructure *theGamepads[10];
extern int nrOfGamepads;

struct BSPlayerControls
{
	SDLKey Up, Down, Left, Right, Jump, Run, Escape,
	Enter, MouseUp, MouseDown, MouseLeft, MouseRight, Teleport;
}; extern BSPlayerControls *heroKeyboard;



///Structura pentru obiectele din Box2D
struct BSTheFontLetters : BSBody
{
    float xCordInImage, yCordInImage, xCordOnScreen, yCordOnScreen,
	widthOfLetterInImage, heightOfLetterInImage, widthOfLetterOnScreen, heightOfLetterOnScreen;
	
	double xRatio, yRatio;
	
    char nameOfLetterCapsLockOff, nameOfLetterCapsLockOn;
};
extern BSTheFontLetters *letters[256];
extern int NrOfTotalLetters;

extern std::list<BSSnowFlakes*>listOfRainDrops;
extern bool useSnow, useRain, useAssassinsCreed;

extern bool existsGamePad, useKeyboardOrGamePad;

extern char initialSquareTexturePath[100], initialRoundTexturePath[100];

extern float playerAnimWidth, playerAnimHeight;

extern BSTextureSquare *theLoadingImage;
extern SDL_Event event;
extern bool doneLoadingTheGame, canRenderGameNow;

extern ALCdevice *deviceOpenAL; //Create an OpenAL Device
extern ALCcontext *contextOpenAL; //And an OpenAL Context

extern float gameBoundLeft, gameBoundRight, gameBoundDown, gameBoundUp;

extern GLuint blankTexture, whiteTexture;


extern long long timer;

extern float newVolumeAudio, newVolumeSFX, currentVolumeAudio, currentVolumeSFX;
extern float theTimeHowFast;//FPS in update, the bigger it is, the slower it moves; the smaller it is, the faster it moves
extern float WorldBoundaryLeft, WorldBoundaryDown, WorldBoundaryUp, WorldBoundaryRight;
extern bool canSetBoundaryLeft, canSetBoundaryDown, canSetBoundaryUp, canSetBoundaryRight;

///extern ChapterLevelsStructure *nivele[301];
extern ChapterStructure *chaptere[100];
extern int nrOfChapters;
extern LevelChooserPlayerTexture *levelChoserPlayer;

extern BSBody *CameraPosition;

extern std::list<BSTheSquareBodies*> ListOfSquareBodies;
extern std::list<BSTheSquareBodies*> ListOfSquareDustBodies;
extern BSTheSquareBodies *hero, *Hero2nd;
extern std::list<BSTheRoundBodies*> ListOfRoundBodies;
extern std::list<BSTheParticles*> ListOfParticles;
//extern std::list<BSAnimation*> ListOfAnimations;
///extern BSAnimation *playerAnimation, *currentPlayerAnimation,
extern BSAnimation *SoundButtonTexture;//, *primulPlayer, *ultimulPlayer
extern std::list<BSTextureSquare*> ListOfSquareTextures;
extern BSTextureSquare *selectedTextureSquare;//*primaTexturaSquare, *ultimaTexturaSquare,
extern std::list<BSTextureRound*> ListOfRoundTextures;
extern BSTextureRound *selectedTextureRound;//*primaTexturaRound, *ultimaTexturaRound,

extern int coinsTotalNo, coinsThisLevel, deathsTotalNo, deathsThisLevel;

//extern BSTheRoundBodies *primulRoundStatic, *ultimulRoundStatic;
extern BSTheBackgrounds *theRenderedBackgrounds;
extern BSTheSquare *theRenderedObstacleSquare, *theRenderedTextureSquare;
extern BSTheCircle *theRenderedObstacleCircle, *theRenderedTextureCircle;
//extern BSTheParticles *theRenderedParticles[500], *whenHitsGroundParticles[500];
extern BSSceneStructure *deadScene;

extern bool DarkLevels;
extern BSTexturedVertex2D mainDarkData[4], darkLevelData[4];
extern GLuint mainDarkTexture, mainDarkVao, darkLevelTexture, darkLevelVao,
vboMainDark, vboDarkLevel, iboMainDark, iboDarkLevel;

extern bool settingsFromFirstOrGame, isSpaceDown;

extern float HeroInitialX, HeroInitialY;


///The sound buffers
extern ALuint SourceSoundBeginningGame, SourceSoundJump, SourceSoundDies,
SourceSoundMusic1, SourceSoundMusic2, SourceSoundMusic3, SourceSoundCoin,
SourceSoundPowerUp, SourceSoundTeleport;
extern ALuint BufferSoundBeginningGame, BufferSoundJump, BufferSoundDies,
BufferSoundMusic1, BufferSoundMusic2, BufferSoundMusic3, BufferSoundCoin,
BufferSoundPowerUp, BufferSoundTeleport;


extern int addCircleOrSquare, muscicIndex;///1 = square, -1 = circle, 2 = square texture, -2 = round texture



extern GLuint soundPlayerTexture;
extern std::list<BSMenuStructure*> listOfMenus;
extern BSMenuStructure *currentMenu;
extern BSButtonStructure *currentButton;
//extern BSMenuStructure *TheMenus[10];

extern bool canChangeVolumeMusic, canChangeVolumeAudioSfx, canChangeResolution;

///extern int currentMenuIndex, currentButtonIndex;	//menuState[0]->First menu, [1]->SelectLevel, [2]->TheGame,
//[3]->PauseMenu, [4]->OptionsMenu, [5]->SettingsMenu

extern short BinaryPlayer;  // 0000000000000001 in binary
extern short BinaryMonster; // 0000000000000010 in binary
extern short BinaryScenery; // 0000000000000100 in binary
extern short BinaryParticles; // 0000000000000100 in binary


///extern BSTexturedVertex2D particleData[4], transparentMenuBlock[4];

extern GLuint iData[4];
extern unsigned char* images[1000]; //for textures


extern float CameraExtremeLeft, CameraExtremeRight, CameraExtremeUp, CameraExtremeDown, MenuCoordinateX, MenuCoordinateY;
extern GLint ShaderCameraExtremeLeft, ShaderCameraExtremeRight,
ShaderCameraExtremeUp, ShaderCameraExtremeDown,
ShaderPlayerCoordinatesX, ShaderPlayerCoordinatesY,
ShaderMouseX, ShaderMouseY, ShaderIsTheSquare, ShaderWidthOfSquare, ShaderHeightOfSquare,
ShaderAflaRestulWidthOfSquare, ShaderAflaRestulHeightOfSquare, ShaderScaleSize,
ShaderRotationAngle, ShaderRotated, ShaderIsText, ShaderTextCoord, ShaderTextTex, ShaderIsCircle, ShaderCircleRadius,
ShaderCosRotation, ShaderSinRotation, ShaderScaleOnX, ShaderScaleOnY, ShaderDark, ShaderFlake;
///extern GLint mVertexPos2DLocation;
///extern GLint mTexCoordLocation;

extern GLint locationBSVertexPosition3D, locationBSTextureCoordinate, locationBSModelViewMatrix, locationBSProjectionMatrix;
extern GLint locationBSTextureColor, locationBSTextureUnit;
extern GLuint BSProgramID;

extern glm::mat4 BSProjectionMatrix;
extern glm::mat4 BSModelViewMatrix;


//extern GLuint vbo, ibo;
//VBO IDs
//extern GLuint mVBOID;
//extern GLuint mIBOID;
//VAO Names

extern BSBody *originalParticle, *originalTransparentMenu, *originalCoin, *originalFan, *originalFanParticleX, *originalFanParticleY, *originalBody, *originalDarkLevel, *originalDarkMenu,
*originalRainDrop, *originalWormHole, *originalDustBody;

//extern GLuint particleVaoBuffer, particleVboBuffer, particleIboBuffer,
//				whenHitsGroundVaoBuffer, whenHitsGroundVboBuffer, whenHitsGroundIboBuffer,
//				transparentMenuBlockVao, transparentMenuBlockVbo, transparentMenuBlockIbo;// = NULL;


extern BSTheSquareBodies *selectedSquareBody;
extern BSTheRoundBodies *selectedRoundBody;
//nrX si nrPass sunt folosite in functia de timer
extern float razaInitialaInner, razaInitialaOuter, changeInPosition, lastPositionOfHeroX, lastPositionOfHeroY,
startPositionCameraX, sinX, sinY, iteratieSin, widthOfObstacle, heightOfObstacle, createObstacleX, createObstacleY;
extern int nrBodies, nrParticles, nrBodiesDistroyed, nrParticlesDistroyed,
nrX, LittleBigMoveTheObstacle, indexOfSelectedBody, nrOfWhenItHits;
extern float MouseX, MouseY, MouseXLast, MouseYLast;
extern bool theLevelHasFinished, quit, clean, isPaused, canPressTheKey, canMoveCamera, canAddObstacles, canWriteInConsole,
canClickLeft, canClickRight, aSalvatHarta, corpulEsteDistrus[1000],//, particleIsDistroyed[1000],
canChangeScaleSize, canTeleportHero, pressedJumpSecond, jumpSecondSpinned, isTeleporting;
extern float jumpSecondSpinAngle;
//LittleBigMoveTheObstacle va retine true daca mut obiectul doar cat este jucatorul,
//si false daca mut jucatorul cat width si height of the box
extern std::string consoleString;

extern float buttonMenuWidth, buttonMenuHeight;

extern bool moveLeftGround, moveRightGround, moveLeftAir, moveRightAir, isJumping, ButtonUp, ButtonDown,
ButtonRight, ButtonLeft, ButtonRun, ButtonJump, MouseLeft, MouseRight, MouseMoved;

extern bool canClick, aDatClick;

extern float speedWalk, speedWalkFast, speedRun, speedJumpUp, speedJumpToSide, speedGoDown, speedJumpUpOnWall,
speedWalkInAir, speedWalkInAirFast, speedJumpToTheSameSide, timeToStayInAirWhenJumpsOnTheSameWall, timeToStayOnWall;

//extern b2Body* bodies[1000];
//extern b2Body* particles[1000];
extern b2World* world;

extern float BodySize[1000][2];

extern const char* SCREEN_TITLE;
extern GLuint texture, textureMill, playerTexture, playerTextureDead, playerTextureRound,
starsTexture1, starsTexture2, starsTexture3, starsTexture4, backgroundTexture;

extern bool canPressKeyAgain[256];
extern std::string theString;
extern float SursaDeLuminaX, SursaDeLuminaY;

extern float ColoredPath[1000][2];
//1000-numarul de patrate pe care merge, [2]-X,Y, [2]-horizontal(up and down), Vertical(left and right)
extern int numberOfSquaresForPath, levelHasScript;
extern float lastTime, lastMovedX;
extern bool itMovedX, itMovedY, itMovedXLeft, itMovedXRight, itTurnedX;


extern bool canJumpVertically, canJumpHorizontally, isOnGround, isOnLeftWall, isOnRightWall, isInAir, jumpsUpTheWall,
isInCorner;
extern std::string anotherString;

extern float moveStringX, moveStringY;

extern int variableWall;

//Texture dimensions
//extern GLuint mTextureWidth;
//extern GLuint mTextureHeight;

extern BSVertexPos2D gQuadVertices[1000][4], menuButtons[1000][4], texQuadVertices[1000][4];
//Vertex buffer
extern GLuint gVertexBuffer, texVertexBuffer;
extern float panta, termenLiber;

extern bool wasPressed[256];



//extern SDL_Event event;


#endif
