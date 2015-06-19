#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include "BSOpenGL.h"
#include <stdio.h>
#include <string>
#include <SOIL/SOIL.h>
#include "BSValues.h"
#include "BSTexturedPolygonProgram2D.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <fstream>
#include "BSObstacles.h"
#include "BSLevelMenu.h"
#include "BSInputClass.h"
//#include <SDL/SDL_image.h>


class BSTexture
{
public:

	void loadTheLoadingImage();
	void renderTheLoadingImage(float alphaColor);

	BSTexture();

	int aflaRestul(float numarul);
	void renderStuff();

	void initTexturesID();
	void initMenuButtons();
	void initMenuLevels();

	void buildRainDrops();
	void addARainDrop(float x, float y, float z, float xPower, float yPower);
	void renderRainDrops();
	void resetRainDrops();
    void renderWormHoles();
    void checkCollisionsWormHoles();

	void renderSomething();


	void renderAnyButtons(BSMenuStructure *theMenu);

	void ReinitializeResoultion(float newWidth, float newHeight);

	void renderVboAndVao();
	void setTheVao( GLuint &theVaoBuffer, BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind);

	void bindVBO(BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind);

	void renderSomeBody(float coordX, float coordY, float coordZ,
									float angleX, float angleY, float angleZ,
									GLuint theTextureIdToRender, BSColorRGBA theColorOfObstacle,
									GLuint theVaoBuffer, float ScaleOnX, float ScaleOnY, float ScaleOnZ, bool canRotate);

	void renderChuncksOfObjects(float coordX, float coordY, float coordZ, float ScaleOnX, float ScaleOnY);

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
    void checkBodyScript(BSTheSquareBodies *square, BSTheRoundBodies *round);

	void renderOnlyTheTextures();

    void renderDustBodies();
    void resetDustBodies();

	void renderSelectedSquareObstacle();
	void renderSelectedRoundObstacle();

	void renderTheObstacles();
	void renderRoundPlayer();
	void renderBackgroundNo1();
	void renderCamera();

	void renderDeadSceneChange();
	void renderNextLevelSceneChange();
	void renderLevelSceneChangeFromMenuLevels();



	void getTheAnimation(std::vector<BSAnimation*> theList, BSNewList* listOfCurrentAnimation);
	void renderAllAnimations();//(BSAnimation* &currentPlayer);
    void renderBerserk();
	void renderPlayerAnimation();
	void getTheNextImageForAnimationInTheCycle(std::vector<BSAnimation*> theList,
												BSAnimation* &theCurrentImage, int nrOfImgs);
	void getTheNextImageForAnimationNOTInTheCycle(std::vector<BSAnimation*> theList1,
													std::vector<BSAnimation*> theList2,
													BSAnimation* &theCurrentImage, int nrOfImgs, int i);



	void loadTextures();
	void loadATexture(std::string name, GLuint &theTextureId);

    SDL_Surface* load_image( std::string filename );
    void Load1Texture(SDL_Surface *surface, GLuint &texture);

	void getTextureWidthAndHeight(std::string name, int &width, int &height);


	void loadMenuButtonsTexture(int numberOfButtons, std::string pathAndName, GLuint theButtonsTexture[]);


	float toRadians(float x);

	void FreeTypeTextRenderer(const char *text, float x, float y, float sx, float sy);

	void renderTheCoin();

	void initTheFont();
	void renderMyFont(std::string theStringToRenderString, float xCord, float yCord, float FontSizeX, float FontSizeY,
						BSColorRGBA color, bool can);

	bool coinIsInBounds(BSCoins *theCoin);
	void renderSnowFlakes();
	void checkIfSnowFlakesOfBoundary();


	void createMouseCircles();
	void renderMouseTexture();

	void renderTheCloudyParticles();

	void consoleSalveazaHarta();
    void salveazaFinishedLevel();


};


#endif // LTEXTURE_H_INCLUDED
