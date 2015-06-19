#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include <stdio.h>
#include <string>
#include "BSTexturedPolygonProgram2D.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "BSObstacles.h"
#include "BSLevelMenu.h"
#include "BSInputClass.h"
#include "BSActionStuff.h"
#include "BSRenderer.h"
//#include <SDL/SDL_image.h>


class BSTexture
{
public:
/*
	long long SDL_GetTicks()
	{
		return endTime - startTime;
	};
*/
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

	void renderQuadrants();

	void renderAnyButtons(BSMenuStructure *theMenu);

	void ReinitializeResoultion(float newWidth, float newHeight);

	void renderVboAndVao();
	void setTheVao( GLuint &theVaoBuffer, BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind);

	void bindVBO(BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind);

	//void renderSomeBody(float coordX, float coordY, float coordZ,
	//								float angleX, float angleY, float angleZ,
	//								GLuint theTextureIdToRender, BSColorRGBA theColorOfObstacle,
	//								GLuint theVaoBuffer, float ScaleOnX, float ScaleOnY, float ScaleOnZ);

	void renderChuncksOfObjects(float coordX, float coordY, float coordZ, float ScaleOnX, float ScaleOnY);

	void renderANormalVboAndVaoObject(float coordX, float coorY, GLuint theTextureIdToRender,
									BSColorRGBA theColorOfObstacle, GLuint theVaoBuffer, float ScaleOnX, float ScaleOnY);




	void renderThePauseBtn();
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



	void renderAllAnimations();//(BSAnimation* &currentPlayer);
    void renderBerserk();
	void renderPlayerAnimation();



	void loadTextures();
	///void loadATexture(std::string name, GLuint &theTextureId);


	void getTextureWidthAndHeight(std::string name, int &width, int &height);


	void loadMenuButtonsTexture(int numberOfButtons, std::string pathAndName, GLuint theButtonsTexture[]);


	float toRadians(float x);

	void renderTheCoin();

	void initTheFont();
	void renderMyFont(std::string theStringToRenderString, float xCord, float yCord, float FontSizeX, float FontSizeY,
						BSColorRGBA color);

	bool coinIsInBounds(BSCoins *theCoin);
	void renderSnowFlakes();
	void checkIfSnowFlakesOfBoundary();


	void consoleSalveazaHarta();
    void salveazaFinishedLevel();


};


#endif // LTEXTURE_H_INCLUDED
