#ifndef BSUTILITIES_H
#define BSUTILITIES_H

#include "BSOpenGL.h"
#include <stdio.h>
#include <iostream>
#include "BSValues.h"
#include <fstream>
#include "BSObstacles.h"
#include "BSTexturedPolygonProgram2D.h"
#include "BSTexture.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "BSLevelMenu.h"
#include "BSXmlFiles.h"
#include <AL/al.h>
#include <AL/alc.h>


class BSUtilities
{
    public:


	bool loadTheWavFile(char path[], FILE* &fp);

	bool createOpenAlContext();

	bool isPlaying(ALuint theSource);

	bool openTheWavfile(std::string path, ALuint &sourceOfSound, ALuint &bufferOfSound);



	bool initAL();

    bool initGL();

	bool loadGP();

    bool loadMedia();
	void loadCoinsAndDeaths();

    void update();

    void render();

    void keyboardHandling();

    void controlConsoleString();



    void consoleAddObstacles();
    void consoleMoveCamera();
    void consoleMoveSelectedObstacle();
    void consoleChangeWidthHeight();
    void consoleSalveazaHarta();
    void consoleMoveLittleBig();
    void consoleChangeScaleSize();
    void consoleSetUserData();
    void consoleTeleportHero();
    void consoleIncarcaHarta();
	void consoleSetSelectedObstacleTexture();
	void consoleAddSquareOrRound();
	void consoleSetKillHeroOrNextLevel();
	void consoleDeleteSelectedObstacleTexture();
	void consoleDeleteSelectedObstacleColor();
	void consoleSetSelectedObstacleColor();
	void consoleSetNewTexture();

	void consoleSendObstacleToBack();//make the selected obstacle or texture the first or the last termen of the dynamic allocators
	void consoleBringObstacleToFront();
	void consoleSendTextureToBack();
	void consoleBringTextureToFront();

	void consoleSetRoundObstacleRotate();

    void consoleSaveWorldBoundaries();

    void consoleAddCoins();
	void consoleSaveCoins();






	float checkForNumberInString(std::string theString);
};

#endif
