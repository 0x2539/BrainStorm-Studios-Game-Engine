#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

//#include "BSOpenGL.h"
#include <stdio.h>
#include <string>
//#include "BSRectangle.h"
//#include <SOIL/SOIL.h>
#include "BSValues.h"
//#include "BSTexturedPolygonProgram2D.h"
//#include "BSTexturedVertex2D.h"

#ifdef __OBJC__
//#import "CC3GLMatrix.h"
//#import <QuartzCore/CAAnimation.h>
//#import <UIKit/UIKit.h>
//#include "OpenGLView.h"
#endif


class BSTexture
{
public:
    //static void setTexturedPolygonProgram2D( BSTexturedPolygonProgram2D* program );
    
	double SDL_GetTicks();
	
	void getStringArray(std::string path, std::string cuvs[]);
	
	
    void loadTheLoadingImage();
    void renderTheLoadingImage(float alphaColor);
    
    BSTexture();
    virtual ~BSTexture();
    
    int aflaRestul(float numarul);
    void renderStuff();
	
	void renderThePauseBtn();
    
    void initTexturesID();
    void initMenuButtons();
    void initVboAndVao();
    void initMenuLevels();
    
	void addARainDrop(float x, float y, float z, float xPower, float yPower);
	void resetRainDrops();
	void buildRainDrops();
	void renderRainDrops();


    
    void checkCollisionsWormHoles();
    void renderWormHoles();
	
	
	void renderQuadrants();
	
    
    void renderSomething();
    
    
    void renderAnyButtons(BSMenuStructure *theMenu);
    
    void ReinitializeResoultion(float newWidth, float newHeight);
    
    void renderVboAndVao();
    void setTheVao( GLuint &theVaoBuffer, BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind);
    
    //void setTheVaoOnce(GLuint &theVaoBuffer, BSTexturedVertex2D dataToBind[4]);
    //void bindVBOONCE(BSTexturedVertex2D dataToBind[4]);
    
    void bindVBO(BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind);
    
    void renderAnVboAndVaoObject(float coordX, float coordY, float coordZ,
                                            float angleX, float angleY, float angleZ,
                                            GLuint theTextureIdToRender, BSColorRGBA theColorOfObstacle,
                                            GLuint theVaoBuffer, float ScaleOnX, float ScaleOnY, float ScaleOnZ);
    
    void renderANormalVboAndVaoObject(float coordX, float coorY, GLuint theTextureIdToRender,
                                      BSColorRGBA theColorOfObstacle, GLuint theVaoBuffer, float ScaleOnX, float ScaleOnY);
    
    
    
    
    void renderMenuLevels(int nrOfLevels, ChapterLevelsStructure* theLevelsToRender[]);
    void renderMenuChapters();
    
    void renderMessages();
    void renderCoins();
    void renderFans();
    void renderDarkLevel();
    void ifCollideWithMessage();
    
    
    
    void renderTransparentSquare(BSColorRGBA theColorToRender, float coordinateX, float coordinateY);
    void setTheValuesForShaders();
    
    void renderFirstMenuButtons();
    void renderOptionsMenuButtons();
    void renderSettingsMenuButtons();
    
    void renderSoundAnimation(float yCord, float theVolume);
    
    
    
    
    void setCameraPosition();
    
    void renderTheSquareObstacles();
    void renderTheCircleObstacles();
    
    void renderOnlyTheTextures();
    
    void renderSelectedSquareObstacle();
    void renderSelectedRoundObstacle();
    
    void renderTheObstacles();
    void renderPlayer();
    void renderRoundPlayer();
    void renderBackgroundNo1();
    void renderCamera();
    
    void renderDustBodies();
    void checkBodyScript(BSTheSquareBodies *square, BSTheRoundBodies *round);
    void resetDustBodies();
    
    void renderDeadSceneChange();
    void renderNextLevelSceneChange();
    void renderLevelSceneChangeFromMenuLevels();
    
    
    
    void getTheAnimation(std::list<BSAnimation*> theList, BSNewList* listOfCurrentAnimation);
    void renderNewPlayerAnimation();//(BSAnimation* &currentPlayer);
    void renderPlayerAnimation();
	void getTheNextImageForAnimationInTheCycle(std::list<BSAnimation*> theList,
                                               BSAnimation* &theCurrentImage, int nrOfImgs);
	void getTheNextImageForAnimationNOTInTheCycle(std::list<BSAnimation*> theList1,
                                                  std::list<BSAnimation*> theList2,
                                                  BSAnimation* &theCurrentImage, int nrOfImgs, int i);
    
    
    
    void loadTextures();
    void loadATexture(std::string name, GLuint &theTextureId);
    void getTextureWidthAndHeight(char name[], int &width, int &height);
    
    
    void loadMenuButtonsTexture(int numberOfButtons, std::string pathAndName, GLuint theButtonsTexture[]);
    
    
    float toRadians(float x);
    
    void FreeTypeTextRenderer(const char *text, float x, float y, float sx, float sy);
    
    void renderTheCoin();
    
    void initTheFont();
    void renderMyFont(std::string theStringToRenderString, float xCord, float yCord, float FontSizeX, float FontSizeY,
                      BSColorRGBA color);
    
	bool coinIsInBounds(BSCoins *theCoin);
	void renderSnowFlakes();
	void checkIfSnowFlakesOfBoundary();
    
    
	void createMouseCircles();
	void renderMouseTexture();
    
	void renderTheCloudyParticles();
    
	void consoleSalveazaHarta();
    void salveazaFinishedLevel();
	
	//(GLuint)setupTexture:(std::string)fileNameString;
    
//protected:
    //Rendering program
    //static BSTexturedPolygonProgram2D* bTexturedPolygonProgram2D;
    
    
};


#endif // LTEXTURE_H_INCLUDED
