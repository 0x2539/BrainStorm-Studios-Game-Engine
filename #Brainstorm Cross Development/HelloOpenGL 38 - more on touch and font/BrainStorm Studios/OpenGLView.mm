

#import "OpenGLView.h"
extern "C"
{
}
#import <QuartzCore/CAAnimation.h>
#import "BSTexture.h"
#import "BSValues.h"
#import "BSUtilities.h"
#import "BSObstacles.h"
#import "BSLevelMenu.h"
#import "BSActionStuff.h"
#import "InputClass.h"

#import "glm/glm.hpp"
#import "glm/gtx/transform.hpp"
#import "glm/gtc/type_ptr.hpp"

//#import
#import <libxml/xmlmemory.h>


@implementation OpenGLView

#define TEX_COORD_MAX   4


GLuint blankTexture, whiteTexture;
int quadrantIndex = 0;

bool isButtonDown = false;
int buttonSize = 35;

BSWormHole *lastWorm = new BSWormHole;

BackButton *backBtn = new BackButton, *btnDarkLevels = new BackButton, *btnTimeControl = new BackButton, *btnPowerUp1 = new BackButton, *btnPowerUp2 = new BackButton, *btnPowerUp3 = new BackButton;

BSBody *originalParticle = new BSBody, *originalTransparentMenu = new BSBody, *originalCoin = new BSBody, *originalFan = new BSBody, *originalBody = new BSBody, *originalDarkLevel = new BSBody, *originalDarkMenu = new BSBody, *originalRainDrop = new BSBody, *originalWormHole = new BSBody, *originalDustBody = new BSBody, *originalFanParticleX = new BSBody, *originalFanParticleY = new BSBody;

int timeWhenTeleported = 0;


BSNewList *listOfAnimations[100];
int nrOfListOfAnimations;
BsActiveAnimations *listOfActiveAnimations[5];

float gameBoundLeft = 0, gameBoundRight = 0, gameBoundDown = 0, gameBoundUp = 0;

float zValue = 4;

long long timer = 0;

BSTheSquareBodies *hero = new BSTheSquareBodies,
*Hero2nd = new BSTheSquareBodies,
*selectedSquareBody = NULL;
BSTheRoundBodies *selectedRoundBody = NULL;

BSLevelMenu *theLevelMenuObject = new BSLevelMenu();
BSUtilities *objBSUtils = new BSUtilities();
//BSSetUpEverything *objSetUps = new BSSetUpEverything();
BSObstacles *objObstacles = new BSObstacles();
//BSVboRendering *objVboRender = new BSVboRendering();
BSActionStuff *action = new BSActionStuff();
//BSActionStuffRound *action2 = new BSActionStuffRound();
BSTexture* randareMenu = new BSTexture();
//BSInputClass *ibjectInputMain = new BSInputClass();
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
BSTheFontLetters *letters[100];
ChapterStructure *chaptere[100];
b2World* world = new b2World(b2Vec2(0, -40));
BSTexturedVertex2D mainDarkData[4], darkLevelData[4],
coinData[4], fanData[4], particleData[4], transparentMenuBlock[4];
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

/*ALuint SourceSoundBeginningGame, SourceSoundJump, SourceSoundDies, SourceSoundMusic, SourceSoundCoin;
 ALuint BufferSoundBeginningGame, BufferSoundJump, BufferSoundDies, BufferSoundMusic, BufferSoundCoin;
 
 ALCdevice *deviceOpenAL;
 ALCcontext *contextOpenAL;*/
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


bool levelHasScript = false;


long long timeSinceMovedMouse = 0, timeSinceMovedLittleCircle = 0;

std::list<BSTheSquareBodies*> ListOfSquareBodies;
std::list<BSWormHole*> listOfWormHoles;
std::list<BSTheSquareBodies*> ListOfSquareDustBodies;
std::list<BSSnowFlakes*> listOfSnowFlakes;
std::list<BSWorldOfGooMouse*> listOfMouseCircles;
std::list<BSCloudyParticles*> listOfCloudyParticles;
std::list<BSTheRoundBodies*> ListOfRoundBodies;
std::list<BSTheParticles*> ListOfParticles;
///std::list<BSNewList*> listOfAnimations;
std::list<BSMenuStructure*> listOfMenus;
std::list<BSTheMessages*>listOfMessages;
std::list<BSFans*> listOfFans;
std::list<BSCoins*> listOfCoins;
std::list<BSTextureSquare*> ListOfSquareTextures;
std::list<BSTextureRound*> ListOfRoundTextures;


std::list<BSSnowFlakes*>listOfRainDrops;
bool useSnow = true, useRain = false, useAssassinsCreed = false;


GLuint locationBSVertexPosition3D, locationBSTextureCoordinate, locationBSModelViewMatrix, locationBSProjectionMatrix;
GLuint locationBSTextureColor, locationBSTextureUnit;
GLuint BSProgramID;


float theCoinX, theCoinY;

int NrOfTotalLetters, nrOfChapters = 0, heroFacesLeftOrRight = 1, addCircleOrSquare = 1, nrOfMessageSign = 0,
coinsTotalNo = 0, coinsThisLevel = 0, deathsTotalNo = 0, deathsThisLevel = 0, variableWall = 0,
LittleBigMoveTheObstacle = 0, nrBodiesDistroyed = 0, indexOfSelectedBody = 0, nrParticlesDistroyed = 0,
nrParticles = 0, nrOfWhenItHits = 0, numberOfSquaresForPath = 0, nrBodies = 0;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int SCREEN_FPS = 60;//usually 60
int SCREEN_BPP = 32;



bool DarkLevels = false, canAddCoins = false, canAddFans = false, settingsFromFirstOrGame = false,
canSetBoundaryLeft = false, canSetBoundaryDown = false, canSetBoundaryUp = false, canSetBoundaryRight = false,
canChangeVolumeMusic = false, canChangeVolumeAudioSfx = false, canChangeResolution = false,
wasPressed[256], corpulEsteDistrus[1000], itMovedX = false, itMovedY = false, itMovedXLeft = false,
itMovedXRight = false, itTurnedX = false, canMoveCamera = false, canAddObstacles = false, canWriteInConsole = false,
canClickLeft = true, canClickRight = true, aSalvatHarta = false, canChangeScaleSize = false, canTeleportHero = false,
keyStates[256], canPressKeyAgain[256], existsGamePad = false, useKeyboardOrGamePad = true, theLevelHasFinished = false,
clean = false, isPaused = false, canPressTheKey = true, ButtonUp = false, ButtonDown = false,
ButtonRight = false, ButtonLeft = false, ButtonRun = false, ButtonJump = false,
MouseLeft = false, MouseRight = false, MouseMoved = false,
quit = false, moveLeftGround = false, moveRightGround = false, moveLeftAir = false, moveRightAir = false, isJumping = false,
canJumpVertically = false, canJumpHorizontally = false, isInCorner = false, canClick = false, aDatClick = false,
isOnGround = false, isOnLeftWall = false, isOnRightWall = false, isInAir = false, jumpsUpTheWall = false;

bool pressedJumpSecond = false, jumpSecondSpinned = false, isTeleporting = false;
float jumpSecondSpinAngle = 0;

float HeroInitialX = 3, HeroInitialY = 3, newVolumeAudio = 1.f, newVolumeSFX = 1.f, currentVolumeAudio = 1.f,
currentVolumeSFX = 1.f, scaleSize = 1, theTimeHowFast = 60,
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
speedWalk = 25, speedWalkFast = 50, speedRun = 1.2, speedJumpUp = 17.7f, speedJumpToSide = 17, speedGoDown = -20, originalMoveSpeed = speedWalk,
speedWalkInAir = 25, speedWalkInAirFast = 50, speedJumpToTheSameSide = 17.1, speedJumpUpOnWall = 21.f,
timeToStayInAirWhenJumpsOnTheSameWall = 175, timeToStayOnWall = 250,
buttonMenuWidth = 3 / 2.f, buttonMenuHeight = 1 / 2.f, moveStringX = 0, moveStringY = 0;

bool justJumped = false, justJumped2 = false;

BSTextureSquare *theLoadingImage = new BSTextureSquare;
bool doneLoadingTheGame = false, canRenderGameNow = false, isSpaceDown = false;

short BinaryPlayer = -1;//0x0001;  // 0000000000000001 in binary
short BinaryMonster = -2;//0x0002; // 0000000000000010 in binary
short BinaryScenery = 1;//0x0004; // 0000000000000100 in binary
short BinaryParticles = -1;//0x0008; // 0000000000000100 in binary


float playerAnimWidth, playerAnimHeight;


char initialSquareTexturePath[100], initialRoundTexturePath[100];

glm::mat4 BSModelViewMatrix, BSProjectionMatrix;

const char* SCREEN_TITLE = "BrainStorm Studios";
std::string consoleString = "";
std::string anotherString = "false";
std::string theString;


BSTexture *renderClass = new BSTexture();


GLubyte iData[4];

void *obj;

BSBody *CameraPosition = new BSBody;

//movedX-negativ se misca la stanga
//movedX-pozitiv se misca la dreapta
//movedY-negativ se misca in hos
//movedY-pozitiv se misca in sus
int movedX = 1, movedY = 1, tapX = 0, tapY = 0, tapRadius = 0;
double swipeDistance = 0;
bool tapped = false, moved = false;
bool jumpPressed = false;


BSTexturedVertex2D data1[4];

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (void)setupLayer {
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
}

- (void)setupContext {
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
    obj = self;
    iData[0] = 0;
    iData[1] = 1;
    iData[2] = 2;
    iData[3] = 3;
    
}

- (void)setupRenderBuffer {
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}

- (void)setupDepthBuffer {
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
}

- (void)setupFrameBuffer {
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
}

- (GLuint)compileShader:(NSString*)shaderName withType:(GLenum)shaderType {
    
    // 1
    NSString* shaderPath = [[NSBundle mainBundle] pathForResource:shaderName ofType:@"glsl"];
    NSError* error;
    NSString* shaderString = [NSString stringWithContentsOfFile:shaderPath encoding:NSUTF8StringEncoding error:&error];
    if (!shaderString) {
        NSLog(@"Error loading shader: %@", error.localizedDescription);
        exit(1);
    }
    
    // 2
    GLuint shaderHandle = glCreateShader(shaderType);
    
    // 3
    const char * shaderStringUTF8 = [shaderString UTF8String];
    int shaderStringLength = [shaderString length];
    glShaderSource(shaderHandle, 1, &shaderStringUTF8, &shaderStringLength);
    
    // 4
    glCompileShader(shaderHandle);
    
    // 5
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        NSString *messageString = [NSString stringWithUTF8String:messages];
        NSLog(@"%@", messageString);
        exit(1);
    }
    
    return shaderHandle;
    
}

- (void)compileShaders
{
	GLuint vertexShader = [self compileShader:@"SimpleVertex" withType:GL_VERTEX_SHADER];
    GLuint fragmentShader = [self compileShader:@"SimpleFragment" withType:GL_FRAGMENT_SHADER];
    
    BSProgramID = glCreateProgram();
    glAttachShader(BSProgramID, vertexShader);
    glAttachShader(BSProgramID, fragmentShader);
    glLinkProgram(BSProgramID);
    
    GLint linkSuccess;
    glGetProgramiv(BSProgramID, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(BSProgramID, sizeof(messages), 0, &messages[0]);
        NSString *messageString = [NSString stringWithUTF8String:messages];
        NSLog(@"%@", messageString);
        exit(1);
    }
    
    glUseProgram(BSProgramID);
    
    locationBSVertexPosition3D = glGetAttribLocation(BSProgramID, "BSVertexPosition2D");
    locationBSTextureCoordinate = glGetAttribLocation(BSProgramID, "BSTextureCoordinates");
    
	
    locationBSProjectionMatrix = glGetUniformLocation(BSProgramID, "BSProjectionMatrix");
    locationBSModelViewMatrix = glGetUniformLocation(BSProgramID, "BSModelViewMatrix");
    
    locationBSTextureColor = glGetUniformLocation(BSProgramID, "BSTextureColor");
    locationBSTextureUnit = glGetUniformLocation(BSProgramID, "BSTextureUnit");
    
    
    ShaderScaleSize = glGetUniformLocation(BSProgramID, "ScaleSize");
    ShaderRotationAngle = glGetUniformLocation(BSProgramID, "RotationAngle");
    ShaderCircleRadius = glGetUniformLocation(BSProgramID, "CircleRadius");
	
    ShaderFlake = glGetUniformLocation(BSProgramID, "isFlake");
    ShaderIsCircle = glGetUniformLocation(BSProgramID, "isCircle");
    ShaderDark = glGetUniformLocation(BSProgramID, "isDark");

	std::cout<<"shaders: "<<locationBSVertexPosition3D<<' '<<locationBSTextureCoordinate<<' '<<locationBSProjectionMatrix<<' '<<locationBSModelViewMatrix<<' '<<locationBSTextureColor<<' '<<locationBSTextureUnit;
}

- (void) setupMatrices
{
    glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
    
    glEnable( GL_BLEND );
    glEnable( GL_DEPTH_TEST );
    
    glDepthFunc(GL_LEQUAL);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
    BSProjectionMatrix = glm::perspective(45.0f, (float) self.frame.size.width / self.frame.size.height, 0.1f, 10000.0f);
    glUniformMatrix4fv(locationBSProjectionMatrix, 1, GL_FALSE, glm::value_ptr( BSProjectionMatrix ) );
    
    SCREEN_WIDTH = self.frame.size.width;
    SCREEN_HEIGHT = self.frame.size.height;
    
    //[modelView populateFromTranslation:CC3VectorMake(0, 0, 11.34)];
    BSModelViewMatrix = glm::mat4();
    glUniformMatrix4fv(locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr( BSModelViewMatrix ) );
    
    // 1
    glViewport(0, 0, self.frame.size.width, self.frame.size.height);
    
    
    
    glUniform1i(locationBSTextureUnit, 0);
}

- (void)Func:(int) a
{
}

void cFunc(int parameter)
{
    [(id) obj Func:parameter];
}

/*
 double SDL_GetTicks()
 {
 return CACurrentMediaTime();
 }*/

void setValueForShaders()
{
    glUniform1f(ShaderScaleSize, 1);
    glUniform1f(ShaderRotationAngle, 0);
    glUniform1f(ShaderIsCircle, 0);
    glUniform1f(ShaderCircleRadius, 0);
}

- (void) renderObst
{
    setValueForShaders();
}

void update()
{
    if(!isTeleporting)
    {
        world->Step((float) 1/theTimeHowFast , 8, 3);
        world->ClearForces();
    }
}

InputClass *in = new InputClass();
bool finishedToLoadGame = false;

void loadMedia()
{
	BSObstacles *obstacle = new BSObstacles();
	BSLevelMenu *theLevels = new BSLevelMenu();
	BSTexture *gOpenGLTexture = new BSTexture();
	
	gOpenGLTexture->loadTextures();
	
	
	obstacle->addBackgrounds();
	obstacle->setUpBodies();
	obstacle->addSnowFlakeS();///functia incarcaHarta() trebuie sa fie interogata inainte!!! pentru CameraExtremeLeft,up,right,down
	gOpenGLTexture->buildRainDrops();
	theLevels->loadChapters();
	gOpenGLTexture->initMenuButtons();
	gOpenGLTexture->initMenuLevels();
	gOpenGLTexture->initTheFont();
	
	finishedToLoadGame = true;
}

void renderTheMenusAndGame()
{
    ///render the game if it's not in any other menu
    if(currentMenu->indexOfMenu == 3)
    {
        randareMenu->renderVboAndVao();
        randareMenu->renderThePauseBtn();
        
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
            update();
            
            action->ClickOnBlock();
            action->generateWhenHitsGroundParticles();
        }
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
        randareMenu->renderThePauseBtn();
    }
}


void runMainLoop()
{
    renderTheMenusAndGame();
    
    in->getTouch();
    
    action->heroTouchesObjects();
    action->moveThePlayer();
}



- (void)render:(CADisplayLink*)displayLink
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	if(finishedToLoadGame)
	{
		runMainLoop();
	}
	else
		if(!finishedToLoadGame)
		{
			CameraPosition->xCord = 0;
			CameraPosition->yCord = 0;
			CameraPosition->zCord = -11.34;
			
			BSTexture *gOpenGLTexture = new BSTexture();
			
			gOpenGLTexture->loadTextures();
			
			gOpenGLTexture->loadTheLoadingImage();
			
			gOpenGLTexture->renderTheLoadingImage(1);
			
			loadMedia();
		}
	
    glFlush();
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupDisplayLink
{
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}




- (id)initWithFrame:(CGRect)frame
{
    iData[0] = 0;
    iData[1] = 1;
    iData[2] = 2;
    iData[3] = 3;
	
    self = [super initWithFrame:frame];
    if (self)
    {
        [self setupLayer];
        [self setupContext];
        [self setupDepthBuffer];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
        [self compileShaders];
        [self setupMatrices];
        [self setupDisplayLink];
    }
    return self;
}


- (void)dealloc
{
    [_context release];
    _context = nil;
    [super dealloc];
}


double getDistance(int x1, int y1, int x2, int y2)
{
    return sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
}

CGPoint lastMovementPosition;
CGPoint startPoint, endPoint;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if ([[event touchesForView:self.viewForBaselineLayout] count] == 1)
    {
        CGPoint currentMovementPosition = [[touches anyObject] locationInView:self.viewForBaselineLayout];
        //std::cout<<"Began "<<currentMovementPosition.x<<' '<<currentMovementPosition.y<<'\n';
        
        if(currentMovementPosition.x >= 85 &&
           currentMovementPosition.x <= 85 + buttonSize &&
           currentMovementPosition.y >= 26 &&
           currentMovementPosition.y <= 26 + buttonSize &&
           levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
           hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
        {
			std::cout<<"hold back"<<'\n';
			isButtonDown = true;
            backBtn->isDown = true;
            startPoint = CGPointZero;
        }
        else
            if(currentMovementPosition.x >= 85 + buttonSize * 2 &&
               currentMovementPosition.x <= 85 + buttonSize * 3 &&
               currentMovementPosition.y >= 26 &&
               currentMovementPosition.y <= 26 + buttonSize &&
               levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
               hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
            {
				std::cout<<"hold dark"<<'\n';
				isButtonDown = true;
                btnDarkLevels->isDown = true;
                startPoint = CGPointZero;
            }
            else
                if(currentMovementPosition.x >= 85 + buttonSize * 4 &&
                   currentMovementPosition.x <= 85 + buttonSize * 5 &&
                   currentMovementPosition.y >= 26 &&
                   currentMovementPosition.y <= 26 + buttonSize &&
                   levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
                   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
                {
					std::cout<<"hold time"<<'\n';
					isButtonDown = true;
                    btnTimeControl->isDown = true;
                    startPoint = CGPointZero;
                }
                else
                    if(currentMovementPosition.x >= 85 + buttonSize * 6 &&
                       currentMovementPosition.x <= 85 + buttonSize * 7 &&
                       currentMovementPosition.y >= 26 &&
                       currentMovementPosition.y <= 26 + buttonSize &&
                       levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 && hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
                    {
						std::cout<<"hold power 1"<<'\n';
						isButtonDown = true;
                        btnPowerUp1->isDown = true;
                        startPoint = CGPointZero;
                    }
                    else
                        if(currentMovementPosition.x >= 85 + buttonSize * 8 &&
                           currentMovementPosition.x <= 85 + buttonSize * 9 &&
                           currentMovementPosition.y >= 26 &&
                           currentMovementPosition.y <= 26 + buttonSize &&
                           levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 && hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
                        {
							std::cout<<"hold power 2"<<'\n';
							isButtonDown = true;
                            btnPowerUp2->isDown = true;
                            startPoint = CGPointZero;
                        }
                        else
                            if(currentMovementPosition.x >= 85 + buttonSize * 10 &&
                               currentMovementPosition.x <= 85 + buttonSize * 11 &&
                               currentMovementPosition.y >= 26 &&
                               currentMovementPosition.y <= 26 + buttonSize &&
                               levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 && hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
                            {
								std::cout<<"hold power 3"<<'\n';
								isButtonDown = true;
                                btnPowerUp3->isDown = true;
                                startPoint = CGPointZero;
                            }
							else
							{
								isButtonDown = false;
								startPoint = currentMovementPosition;
								
								//if (isAutorotating)
								//[self startOrStopAutorotation:nil];
								
								NSMutableSet *currentTouches = [[[event touchesForView:self.viewForBaselineLayout] mutableCopy] autorelease];
								[currentTouches minusSet:touches];
								
								// New touches are not yet included in the current touches for the view
								NSSet *totalTouches = [touches setByAddingObjectsFromSet:[event touchesForView:self.viewForBaselineLayout]];
								//if ([totalTouches count] == 1)
								{
									lastMovementPosition = currentMovementPosition;//[[touches anyObject] locationInView:self.viewForBaselineLayout];
								}
							}
    }
    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
{
    //single finger swipe
    if ([[event touchesForView:self.viewForBaselineLayout] count] == 1)
    {
        CGPoint currentMovementPosition = [[touches anyObject] locationInView:self.viewForBaselineLayout];
        
        std::cout<<currentMovementPosition.x<<' '<<currentMovementPosition.y<<'\n';
        
        //lastMovementPosition = currentMovementPosition;
        
        //goes up
        if(lastMovementPosition.y > currentMovementPosition.y)
        {
            //std::cout<<"goes up"<<'\n';
        }
        else
            if(lastMovementPosition.y < currentMovementPosition.y)
            {
                //std::cout<<"goes down"<<'\n';
            }
        //std::cout<<currentMovementPosition.x<<' '<<currentMovementPosition.y<<'\n';
        lastMovementPosition = currentMovementPosition;
    }
    
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    if ([[event touchesForView:self.viewForBaselineLayout] count] == 1)
    {
        CGPoint currentMovementPosition = [[touches anyObject] locationInView:self.viewForBaselineLayout];
        //std::cout<<"Done "<<currentMovementPosition.x<<' '<<currentMovementPosition.y<<'\n';
        
        if(currentMovementPosition.x >= 85 &&
           currentMovementPosition.x <= 85 + buttonSize &&
           currentMovementPosition.y >= 26 &&
           currentMovementPosition.y <= 26 + buttonSize && backBtn->isDown == true)
        {
			std::cout<<"clicked back"<<'\n';
            backBtn->isDown = false;
            backBtn->canClick = true;
            endPoint = CGPointZero;
            moved = false;
            tapped = false;
        }
        else
			if(currentMovementPosition.x >= 85 + buttonSize * 2 &&
			   currentMovementPosition.x <= 85 + buttonSize * 3 &&
			   currentMovementPosition.y >= 26 &&
			   currentMovementPosition.y <= 26 + buttonSize && btnDarkLevels->isDown == true)
			{
				std::cout<<"clicked dark"<<'\n';
				btnDarkLevels->isDown = false;
				btnDarkLevels->canClick = true;
				endPoint = CGPointZero;
				moved = false;
				tapped = false;
			}
			else
				if(currentMovementPosition.x >= 85 + buttonSize * 4 &&
				   currentMovementPosition.x <= 85 + buttonSize * 5 &&
				   currentMovementPosition.y >= 26 &&
				   currentMovementPosition.y <= 26 + buttonSize && btnTimeControl->isDown == true)
				{
					std::cout<<"clicked time"<<'\n';
					btnTimeControl->isDown = false;
					btnTimeControl->canClick = true;
					endPoint = CGPointZero;
					moved = false;
					tapped = false;
				}
				else
					
					if(currentMovementPosition.x >= 85 + buttonSize * 6 &&
					   currentMovementPosition.x <= 85 + buttonSize * 7 &&
					   currentMovementPosition.y >= 26 &&
					   currentMovementPosition.y <= 26 + buttonSize &&
					   btnPowerUp1->isDown)
					{
						std::cout<<"clicked power 1"<<'\n';
						btnPowerUp1->isDown = false;
						btnPowerUp1->canClick = true;
						endPoint = CGPointZero;
						moved = false;
						tapped = false;
					}
					else
						if(currentMovementPosition.x >= 85 + buttonSize * 8 &&
						   currentMovementPosition.x <= 85 + buttonSize * 9 &&
						   currentMovementPosition.y >= 26 &&
						   currentMovementPosition.y <= 26 + buttonSize &&
						   btnPowerUp2->isDown)
						{
							std::cout<<"clicked power 2"<<'\n';
							btnPowerUp2->isDown = false;
							btnPowerUp2->canClick = true;
							endPoint = CGPointZero;
							moved = false;
							tapped = false;
						}
						else
							if(currentMovementPosition.x >= 85 + buttonSize * 10 &&
							   currentMovementPosition.x <= 85 + buttonSize * 11 &&
							   currentMovementPosition.y >= 26 &&
							   currentMovementPosition.y <= 26 + buttonSize &&
							   btnPowerUp3->isDown)
							{
								std::cout<<"clicked power 3"<<'\n';
								btnPowerUp3->isDown = false;
								btnPowerUp3->canClick = true;
								endPoint = CGPointZero;
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
								
								endPoint = currentMovementPosition;
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
								
							}
    }
	
	
	
	
    [self handleTouchesEnding:touches withEvent:event];
    
    // This is placed here to avoid an infinite spawning of alerts under iPhone OS 4.0
    /*if (([[touches anyObject] tapCount] >= 2) && (![SLSMoleculeAppDelegate isRunningOniPad]))
	 {
	 if (moleculeToDisplay.isDoneRendering == YES)
	 {
	 UIActionSheet *actionSheet = [self actionSheetForVisualizationState];
	 [actionSheet showInView:self.viewForBaselineLayout];
	 }
	 }*/
}

- (void)handleTouchesEnding:(NSSet *)touches withEvent:(UIEvent *)event
{
}

-(void) viewDidLoad {
    // Request to turn on accelerometer and begin receiving accelerometer events
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(orientationChanged:) name:UIDeviceOrientationDidChangeNotification object:nil];
}

- (void)orientationChanged:(NSNotification *)notification {
    // Respond to changes in device orientation
}

-(void) viewDidDisappear {
    // Request to stop receiving accelerometer events and turn off accelerometer
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];
}
static const NSTimeInterval accelerometerMin = 0.01;

- (void)startUpdatesWithSliderValue:(int)sliderValue {
    
    // Determine the update interval
    NSTimeInterval delta = 0.005;
    NSTimeInterval updateInterval = accelerometerMin + delta * sliderValue;
    
    // Create a CMMotionManager
    /*CMMotionManager *mManager = [(APLAppDelegate *)[[UIApplication sharedApplication] delegate] sharedManager];
	 APLAccelerometerGraphViewController * __weak weakSelf = self;
	 
	 // Check whether the accelerometer is available
	 if ([mManager isAccelerometerAvailable] == YES) {
	 // Assign the update interval to the motion manager
	 [mManager setAccelerometerUpdateInterval:updateInterval];
	 [mManager startAccelerometerUpdatesToQueue:[NSOperationQueue mainQueue] withHandler:^(CMAccelerometerData *accelerometerData, NSError *error) {
	 [weakSelf.graphView addX:accelerometerData.acceleration.x y:accelerometerData.acceleration.y z:accelerometerData.acceleration.z];
	 [weakSelf setLabelValueX:accelerometerData.acceleration.x y:accelerometerData.acceleration.y z:accelerometerData.acceleration.z];
	 }];
	 }*/
    
    //self.updateIntervalLabel.text = [NSString stringWithFormat:@"%f", updateInterval];
}

/*
 - (void)stopUpdates {
 CMMotionManager *mManager = [(APLAppDelegate *)[[UIApplication sharedApplication] delegate] sharedManager];
 if ([mManager isAccelerometerActive] == YES) {
 [mManager stopAccelerometerUpdates];
 }
 }*/


@end
