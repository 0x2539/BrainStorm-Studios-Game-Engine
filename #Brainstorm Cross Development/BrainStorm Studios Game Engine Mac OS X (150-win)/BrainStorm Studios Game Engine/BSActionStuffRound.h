#ifndef ActionStuffRound_H_INCLUDED
#define ActionStuffRound_H_INCLUDED

#include <iostream>
#include "BSValues.h"
#include "BSObstacles.h"
#include "BSTexture.h""
#include <Box2D/Box2D.h>

class BSActionStuffRound
{
	public:
	//circle that closes on the player when he finishes the level
	void levelFinished();
	void moveThePlayer();

	void moveRightOnGround(b2Body *body);
	void moveLeftOnGround();

	void moveRightInAir();

	void controlAir(float T);
	void controlWall(b2Body *body);
	void controlCorner(b2Body *body);
	inline bool itWalks(b2Body *body, float T);
	bool itWalksInAir(b2Body *body, float T);
	void controlGround(b2Body *body, float T);


	void generateTheParticles();
	void destroyTheParticles();
	void generateWhenHitsGroundParticles();


	void ClickOnBlock();

	void TeleportHero(float coordX, float coordY);
	void ActionFuncTeleportHero();

	void PathColoring(int LeftOrRight);

	void heroTouchesObjects();
	bool CanGoAwayFromWall(float timeToMatch);


	static float easeIn(float t,float b , float c, float d);
	static float easeOut(float t,float b , float c, float d);
	static float easeInOut(float t,float b , float c, float d);

	float radical(float x);



	protected:

//BSVboRendering *timp = new BSVboRendering();
BSObstacles *objectObstacles = new BSObstacles();
BSTexture *objLTexture2 =  new BSTexture();

int timpulCareTrece = 0, timpulCareAtrecut = 0, jumpedFromLeftOrRight = 0;
long long OriginalTimeOnWall = 0, currentTime = 0, timeToStayOnWall = 250, OriginalTimeToJumpUpTheWall = 0, timeToCreateParticles = 0;
bool imprimeForceOnWall = false, heroCanTeleportAgain = true, justHitTheGround = false;

//BSVboRendering *randare = new BSVboRendering();

	b2Vec2 vel, velocity;
    float desiredVelX = 0, desiredVelY = 0;
    float velChangeX, velChangeY;
    float impulseX, impulseY, turnMultiplier = 1.f, turnMultiplierInAir = 3.5f, timeE = 0;

int nnrr = 0;
GLuint textureStarred[10];
float starsPositions[10][10]; //x, y
int currentTexture = 0;

				bool aCreat = false;
				int indexCurent = 0;
				int currentParticleNr = 0;
				int pozitivSauNegativ = 0;
};
#endif // ActionStuffRound_H_INCLUDED
