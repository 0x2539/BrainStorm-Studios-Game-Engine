#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED

#include <Box2D/Box2D.h>
#include <iostream>
//#include "BSTexturedVertex2D.h"
#include "BSValues.h"
#include "BSTexture.h"
#include "BSAnimationClass.h"
#include "BSXmlFiles.h"
#include <fstream>

class BSObstacles
{
public:
    
	
	double SDL_GetTicks();
	
	void getStringArray(std::string path, std::string cuvs[]);
	
    b2Body* createBodies(b2BodyType, float, float, float, float, std::string, int &NumberOfBodies
                         , int timeUntilIsDestroyed, bool corpDistrus);
    
    
	b2Body* createCircleBodies(b2BodyType Type, float LocationX, float LocationY, float Radius,
                               std::string userData, int &NumberOfBodies, int timeUntilIsDistroyed, bool corpDistrus);
    
    void setUpBodies();
    void setUpOriginals();
    
    void incarcaHarta(char nume[]);
    void destroyLevel();
    
    
    
    void addWormHole(int index, int connectionIndex, float x, float y);
    void addScript(std::string Path);
    void deleteAllWormHoles();
    
    
	void addCoin(float x, float y, int taken);
	void addFan(float x, float y, float width, float height, float length, float powerX, float powerY);
	void loadFans(std::string nameOfFile);
	void destroyAllCoins();
	void destroyAllFans();
    
    
    //	void setTheVaoData(BSTexturedVertex2D dataToSet[4], GLfloat widthToSet, GLfloat heightToSet);
	void setTheVaoData(GLuint &vaoBuffer, GLuint &vboBuffer, GLuint &iboBuffer,
                       BSTexturedVertex2D dataToSet[4], GLfloat widthToSet, GLfloat heightToSet);
    
	void setTheVao( GLuint &theVaoBuffer, BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind);
	void bindVBO(BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind);
    
    
	void setTheVaoDataForFont(BSTexturedVertex2D dataToSet[4], GLfloat widthToSet, GLfloat heightToSet, float xCord, float yCord, GLuint &vaoBuffer, GLuint &vboBuffer, GLuint &iboBuffer);
    
	void setTheMenuButtons(BSButtonStructure* theButtonToSet, BSTexturedVertex2D dataToSet[4],
                           float coordinateX, float coordinateY,
                           float ToWidth, float ToHeight,
                           GLuint vaoData, GLuint vboData, GLuint iboData);
    
    
	void addTheAnimationsForMap(char theLocationOfAnimation[]);
    
	void destroyAllAnimations();
	void destroyAllBodiesSquare();
	void destroyAllBodiesRound();
    void destroyAllBodiesDustSquare();
    
	void loadAnimationList(std::string path, int firstPart, int secondPart, int thirdPart);
    
    
    
	void addDinamicSquare(float BodyX, float BodyY, float BodyW, float BodyH,
                          char textureName[], GLuint BodyVaoBuffer,
                          std::string userData, b2BodyType tipulCorpului, int canKillHero, int isDust);
    
	void addDinamicRound(float BodyX, float BodyY, float BodyR,
                         char textureName[], GLuint BodyVaoBuffer,
                         std::string userData, b2BodyType tipulCorpului, int canKillHero);
    
    
    
	void deleteBodySquare(BSTheSquareBodies* &corpulCareVreauSters);
    
    
	void deleteBodyRound(BSTheRoundBodies* &corpulCareVreauSters);
    
	void addAnimation(std::string name, int nrOfAnimations);
    
	void addOnlyTexture(int squareOrCirlce, float xCoord, float yCoord, float widthOfTexture, float heightOfTexture, std::string texturePath);
	void deleteOnlyTexture(float xCoord, float yCoord, float widthOfTexture, float heightOfTexture);
    
    
    
    
    void addMessageTexture(float xCoord, float yCoord, float width, float height, char textureName[]);
    void deleteAllMessageTexture();
    
	void addSnowFlakeS();
	void createMouseCircles();
	void addBackgrounds();
    
    
	void addCloudyParticles();
	void addTheTexturesOfCloudyParticles();
    
	void loadTheLoadingImage();
    
//protected:
    
};
#endif // OBSTACLES_H_INCLUDED
