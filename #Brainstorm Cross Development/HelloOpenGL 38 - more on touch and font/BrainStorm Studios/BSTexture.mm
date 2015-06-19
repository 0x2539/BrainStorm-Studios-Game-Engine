#include "BSTexture.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <fstream>
//#include "BSVertexData2D.h"
#include "BSObstacles.h"
#include "BSLevelMenu.h"
#include "BSAnimationClass.h"
//#include "BSInputClass.h"
#include "BSActionStuff.h"


BSActionStuff *actionObj = new BSActionStuff();

float SX = 0, SminiX = 0, SY = 0, SminiY = 0, SvariabilaImpartireX = 0, SvariabilaImpartireY = 0, SpozitiaX = 0, SpozitiaY = 0;
int Sx = 0, Sy = 0;


int nrEnding = 0;

//void freeVBO();

//Texture name
//GLuint mTextureID;

//Current pixels
GLuint* mPixels32;
GLubyte* mPixels8;

//Pixel format
GLuint mPixelFormat;

//Texture dimensions
GLuint mTextureWidth;
GLuint mTextureHeight;

//Unpadded image dimensions
GLuint mImageWidth;
GLuint mImageHeight;


//Initialize class variables
GLenum DEFAULT_TEXTURE_WRAP = GL_REPEAT;
//BSTexturedPolygonProgram2D* BSTexture::bTexturedPolygonProgram2D = NULL;

BSLevelMenu *theLevelMenuPlayer = new BSLevelMenu();
//BSInputClass *theInputForMouse = new BSInputClass();

//set no texture
GLuint theTextureToRender = NULL;
//set the color
BSColorRGBA theColorToRender = { 1.f, 1.f, 1.f, 1.f }; //transparent color

float colorOfDeadScene = 0;
int colorGoesUpOrDown = 0; ///Este -1 pentru cand culoarea de la deadScene a ajuns un negru complet, si 1, cand abia a murit si incepe sa
						   ///innegreasca ecranul

float redSinForCoins = 0;


BSObstacles* addObstacle = new BSObstacles();


double BSTexture::SDL_GetTicks()
{
	return CACurrentMediaTime() * 1000;
}

void BSTexture::loadTheLoadingImage()
{
	theLoadingImage->width = (float) SCREEN_WIDTH / 17.0f;
	theLoadingImage->height = (float) SCREEN_HEIGHT / 17.0f;
	theLoadingImage->depth = 0;
	addObstacle->setTheVaoData(theLoadingImage->vao, theLoadingImage->vbo, theLoadingImage->ibo,
							   theLoadingImage->data, theLoadingImage->width,theLoadingImage->height);
	
	loadATexture("smb loading.png", theLoadingImage->texture);
	theLoadingImage->color.r = 1;
	theLoadingImage->color.g = 1;
	theLoadingImage->color.b = 1;
	theLoadingImage->color.a = 1;
}

void BSTexture::renderTheLoadingImage(float alphaColor)
{
	glUniform1f(ShaderScaleSize, scaleSize);
	glUniform1f(ShaderRotationAngle, 0);
	glUniform1f(ShaderIsCircle, 0);
	glUniform1f(ShaderCircleRadius, 0);
	
	theLoadingImage->color.a = alphaColor;
	//	theLoadingImage->color.r ++;//= alphaColor;
	
    renderAnVboAndVaoObject(SCREEN_WIDTH / 17.0f / 2.0f + CameraPosition->xCord - CameraExtremeLeft,
							SCREEN_HEIGHT / 17.0f / 2.0f + CameraPosition->yCord - CameraExtremeDown,
							scaleSizeInitial, 0, 0 ,0,
							theLoadingImage->texture,
							theLoadingImage->color,
							theLoadingImage->vao, theLoadingImage->width, theLoadingImage->height, theLoadingImage->depth);
}




void BSTexture::initVboAndVao()
{
	loadTheLoadingImage();
	//If texture is loaded and VBO does not already exist
	if( texture != 0)// && mVBOID == 0 )
	{
		///Set the Hero data
        //		setTheVao(hero->vao, hero->dataOfBody, hero->vbo, hero->ibo);
        
		///Set the Hero2nd data
        //		setTheVao(Hero2nd->vao, Hero2nd->dataOfBody, Hero2nd->vbo, Hero2nd->ibo);
        
		///Set the obstacles data
        //		std::list<BSTheSquareBodies*>::iterator iteratorSquareBody;
        //
        //		for(iteratorSquareBody = ListOfSquareBodies.begin(); iteratorSquareBody != ListOfSquareBodies.end(); iteratorSquareBody++)
        //		{
        //			setTheVao((*iteratorSquareBody)->vao, (*iteratorSquareBody)->dataOfBody);
        //		}
        
        
        //		std::list<BSTheRoundBodies*>::iterator iteratorRoundBody;
        //
        //		for(iteratorRoundBody = ListOfRoundBodies.begin(); iteratorRoundBody != ListOfRoundBodies.end(); iteratorRoundBody++)
        //		{
        //			setTheVao((*iteratorRoundBody)->vao, (*iteratorRoundBody)->dataOfBody);
        //		}
        
		///Set the particles data
        //		setTheVao(particleVaoBuffer, particleData, particleVboBuffer, particleIboBuffer);
        
		///Set the deadScene data
        //		setTheVao(deadScene->vaoBufferOfScene, deadScene->DataOfScene, deadScene->vbo, deadScene->ibo);
        
		///Set the sound animation
        //		setTheVao(SoundButtonTexture->vaoBufferOfAnimation, SoundButtonTexture->dataOfAnimation,
        //					SoundButtonTexture->vbo, SoundButtonTexture->ibo);
        
		///Set the Square
        //		setTheVao(theRenderedObstacleSquare->vao, theRenderedObstacleSquare->DataOfSquare,
        //					theRenderedObstacleSquare->vbo, theRenderedObstacleSquare->ibo);
        
		///Set the Circle
        //		setTheVao(theRenderedObstacleCircle->vao, theRenderedObstacleCircle->DataOfCircle,
        //					theRenderedObstacleCircle->vbo, theRenderedObstacleCircle->ibo);
	}
}





void BSTexture::getStringArray(std::string path, std::string cuvs[])
{
	bool isTxt =false, isXML = false;
	if(path[path.size() - 1] == 't')//.txt
	{
		isTxt = true;
	}
	else
		if(path[path.size() - 1] == 'l')//.xml
		{
			isXML = true;
		}
	std::string newPath = "", copyOfPath = path;
	
	for(int i = 0 ; i < path.size() - 4; i++)
	{
		newPath += path[i];
	}
	
	path = newPath;
	//std::cout<<"path: "<<path<<'\n';
	
	NSString *fileName = [NSString stringWithCString:path.c_str()
											encoding:[NSString defaultCStringEncoding]];
	//std::cout<<"pula1"<<'\n';
	NSString *paths;
	if(isTxt)
	{
		paths = [[NSBundle mainBundle] pathForResource:fileName ofType:@"txt"];
	}
	else
		if(isXML)
		{
			paths = [[NSBundle mainBundle] pathForResource:fileName ofType:@"xml"];
		}
	NSString *fileTextt = [NSString stringWithContentsOfFile:paths];
	//std::cout<<"pula2 "<<path<<' '<<isTxt<<' '<<BStoString(fileTextt)<<'\n';
	
	std::string bar([fileTextt cStringUsingEncoding:NSUTF8StringEncoding]);
	//std::cout<<"pula2.5 "<<bar<<'\n';
	
	char theCuv[1000] = "";
	strcpy(theCuv, bar.c_str());//= bar.c_str();
								//std::cout<<"pula3"<<'\n';
	
	const char* cuvinte = strtok(theCuv, " \n");
	
    //std::string *bar = new std::string([fileTextt UTF8String]);
	
	int i = 0;
	while(cuvinte)
	{
		//std::cout<<cuvinte<<'\n';
		cuvs[i] = BStoString(cuvinte);// cuvinte);
		
		cuvinte = strtok(NULL, " \n");
		i++;
	}
	
	//std::cout<<bar<<'\n';
	//NSLog(@"%@",fileTextt);
}



void BSTexture::initMenuButtons()
{
	std::cout<<"Began loading the buttons from the menus..."<<'\n';
	std::cout<<'\n';
	///Adaug butoanele din meniuri
	//std::ifstream citesteMeniurile("Menus/menus details.txt");
	int nrMeniuri, nrButtons;
	std::string namesOfMenus = "";
	
	std::string mens[1000];
	int mensNR = 0;
	
	getStringArray("Menus/menus details.txt", mens);
	//citesteMeniurile>>nrMeniuri;
    nrMeniuri = atof(mens[mensNR].c_str());
	mensNR++;
    
	///Set the Menu Transparent Block
	addObstacle->setTheVaoData(transparentMenuBlockVao, transparentMenuBlockVbo, transparentMenuBlockIbo,
                               transparentMenuBlock, SCREEN_WIDTH / scaleSize, SCREEN_HEIGHT / scaleSize);
	///Set the Trnasparent Block For Menu
    //	setTheVao(transparentMenuBlockVao, transparentMenuBlock, transparentMenuBlockVbo, transparentMenuBlockIbo);
    
    
    
	///Set the mouse texture
	addObstacle->setTheVaoData(mouseTexture->vao, mouseTexture->vbo, mouseTexture->ibo,
                               mouseTexture->data, Hero_size / 4.f, Hero_size / 4.f);
	///Set the mouse texture
    //	setTheVao(mouseTexture->vao, mouseTexture->data, mouseTexture->vbo, mouseTexture->ibo);
    
	//mouseTexture->color = {1.f, 1.f, 1.f, 1.f};
	mouseTexture->color.r = 1;
	mouseTexture->color.g = 1;
	mouseTexture->color.b = 1;
	mouseTexture->color.a = 1;
	mouseTexture->nameOfTexture = "Animations/mouseImage.png";
	loadATexture(mouseTexture->nameOfTexture, mouseTexture->texture);
	mouseTexture->width = Hero_size / 4.f;
	mouseTexture->height = Hero_size / 4.f;
	mouseTexture->xCord = hero->theBody->GetPosition().x;
	mouseTexture->yCord = hero->theBody->GetPosition().y;
    
    
    
	float width, height, xCord, yCord, lastY, lastH;
    
	for(int i = 0 ; i < nrMeniuri ; i++)
	{
		BSMenuStructure *newMenu = new BSMenuStructure;
		//citesteMeniurile>>newMenu->MenuIndex>>namesOfMenus>>nrButtons;
		
		newMenu->MenuIndex = atof(mens[mensNR].c_str());
		mensNR++;
		namesOfMenus = mens[mensNR];
		mensNR++;
		nrButtons = atof(mens[mensNR].c_str());
		mensNR++;
		
		newMenu->numberOfButtons = nrButtons;
		newMenu->indexOfMenu = i;//incep cu jocul
		std::cout<<"The "<<namesOfMenus<<" is loading: index: "<<newMenu->MenuIndex<<"; number of buttons: "<<nrButtons<<'\n';
        
        
		loadATexture("Menus/first.png", newMenu->textureOfMenu);
        
		for(int j = 0 ; j < nrButtons ; j++)
		{
			BSButtonStructure *newButton = new BSButtonStructure;
			//citesteMeniurile>>width>>height>>newButton->NextMenuIndex;
            
			width = atof(mens[mensNR].c_str());
			mensNR++;
			height = atof(mens[mensNR].c_str());
			mensNR++;
			newButton->NextMenuIndex = atof(mens[mensNR].c_str());
			mensNR++;
			
			
			newButton->indexOfButton = j;
			newButton->width = width;
			newButton->height = height;
			width = width / 2;
			height = height / 2;
			//newButton->color = {1.f, 1.f, 1.f, 1.f};
			newButton->color.r = 1;
			newButton->color.g = 1;
			newButton->color.b = 1;
			newButton->color.a = 1;
            
			///Dau coordonatele primului buton
			if(!j)
			{
				xCord = SCREEN_WIDTH / 2 / 16.0f;
				yCord = SCREEN_HEIGHT / 2 / 16.0f;
				lastH = height * 2;
				lastY = yCord;
				//width = width + 0.1;
				//height = height + 0.1;
			}
			else
				///Dau coordonatele urmatoarelor butoane
			{
				///Setez pozitia urmatorului buton, in functie de cel de dinainte
				float theHeight = lastH + 0.3;
				///Daca e al 2lea buton atunci, modific marimea primului, ca sa ii dau o pozitie corecta
				//if(j == 1)
				{
					//theHeight = newMenu->Buttons[j - 1]->height + 0.2;
				}
				yCord -= theHeight;
				lastH = height * 2;
			}
            
			newButton->xCord = xCord;
			newButton->yCord = yCord;
			newButton->zCord = scaleSizeInitial;
            
			///Change the name of texture to char
			//"Button images\New Buttons\FirstMenu\The Unnamed Buttons"
			std::string nameForTexture = "Button images/New Buttons/" + namesOfMenus +
            "/The Unnamed Buttons/picture" + BStoString(j) + ".png";
			const char *nameForTextureChar = nameForTexture.c_str();
            
			loadATexture(nameForTextureChar, newButton->textureOfButtons[0]);
            
            
            
			///Change the name of texture to char
			//"Button images\New Buttons\FirstMenu\The Unnamed Buttons"
			nameForTexture = "Button images/New Buttons/" + namesOfMenus +
            "/The Unnamed Buttons/picture0" + BStoString(j) + ".png";
            
			nameForTextureChar = nameForTexture.c_str();
            
            
			loadATexture(nameForTextureChar, newButton->textureOfButtons[1]);
            
            
            
            
			///Set the data for the menu buttons
			addObstacle->setTheVaoData(newButton->vaoOfButtons[0], newButton->vbo[0], newButton->ibo[0],
                                       newButton->dataOfButtons[0], width * 2.0f, height * 2.0f);
			//addObstacle->setTheMenuButtons(newButton, newButton->dataOfButtons[0],
			//								xCord, yCord, width, height);
			///Set the data for the menu buttons
			addObstacle->setTheVaoData(newButton->vaoOfButtons[1], newButton->vbo[1], newButton->ibo[1],
                                       newButton->dataOfButtons[1], (width + 0.1f) * 2.0f, (height + 0.1f) * 2.0f);
			//addObstacle->setTheMenuButtons(newButton, newButton->dataOfButtons[1],
			//								xCord, yCord, width + 0.1, height + 0.1);
            
			///Set the Vao Buffer
            //			setTheVao(newButton->vaoBufferOfButtons[0], newButton->dataOfButtons[0], newButton->vbo[0], newButton->ibo[0]);
			///Set the Vao Buffer
            //			setTheVao(newButton->vaoBufferOfButtons[1], newButton->dataOfButtons[1], newButton->vbo[1], newButton->ibo[1]);
            
			newMenu->listOfButtons.push_back(newButton);
            
			if(!i && !j)
			{
				currentMenu = newMenu;
				currentButton = newButton;
			}
		}
        
		listOfMenus.push_back(newMenu);
	}
    
	std::cout<<'\n';
	std::cout<<"Finished loading the buttons from the menus!"<<'\n';
}

void BSTexture::initMenuLevels()
{
	for(int i = 0 ; i < nrOfChapters; i++)
	{
		///Set the Menu Chapters
		addObstacle->setTheVaoData(chaptere[i]->vao, chaptere[i]->vbo, chaptere[i]->ibo,
								   chaptere[i]->data, chaptere[i]->width, chaptere[i]->height);
		
		for(int j = 0 ; j < chaptere[i]->nrOfLevels ; j++)
		{
			///Set the Menu Levels
			addObstacle->setTheVaoData(chaptere[i]->levelFromChapter[j]->vaoBufferOfLevel,
									   chaptere[i]->levelFromChapter[j]->vboBufferOfLevel,
									   chaptere[i]->levelFromChapter[j]->iboBufferOfLevel,
									   chaptere[i]->levelFromChapter[j]->dataOfLevel,
									   chaptere[i]->levelFromChapter[j]->width, chaptere[i]->levelFromChapter[j]->height);
		}
		
		///Setez texturile de conexiune dintre nivele
		chaptere[i]->levelFromChapter[0]->widthConnectionLeftRightLevel = (chaptere[i]->levelFromChapter[0]->width / 1.4) * 2.0f;
		chaptere[i]->levelFromChapter[0]->heightConnectionLeftRightLevel = chaptere[i]->levelFromChapter[0]->height / 5;
		
		chaptere[i]->levelFromChapter[0]->widthConnectionUpDownLevel = chaptere[i]->levelFromChapter[0]->width / 5;
		chaptere[i]->levelFromChapter[0]->heightConnectionUpDownLevel = (chaptere[i]->levelFromChapter[0]->height / 1.4) * 2.0f;
		addObstacle->setTheVaoData(chaptere[i]->levelFromChapter[0]->vaoBufferOfConnectionLeftRight,
								   chaptere[i]->levelFromChapter[0]->vboBufferOfConnectionLeftRight,
								   chaptere[i]->levelFromChapter[0]->iboBufferOfConnectionLeftRight,
								   chaptere[i]->levelFromChapter[0]->dataOfConnectionLeftRight,
								   (chaptere[i]->levelFromChapter[0]->width / 1.4) * 2.0f,
								   chaptere[i]->levelFromChapter[0]->height / 5);
		
		addObstacle->setTheVaoData(chaptere[i]->levelFromChapter[0]->vaoBufferOfConnectionUpDown,
								   chaptere[i]->levelFromChapter[0]->vboBufferOfConnectionUpDown,
								   chaptere[i]->levelFromChapter[0]->iboBufferOfConnectionUpDown,
								   chaptere[i]->levelFromChapter[0]->dataOfConnectionUpDown,
								   chaptere[i]->levelFromChapter[0]->width / 5,
								   (chaptere[i]->levelFromChapter[0]->height / 1.4) * 2.0f);
		
		///Setez textura pentru Finished Level
		chaptere[i]->levelFromChapter[0]->widthFinishedLevel = chaptere[i]->levelFromChapter[0]->width;
		chaptere[i]->levelFromChapter[0]->heightFinishedLevel = chaptere[i]->levelFromChapter[0]->height;
		addObstacle->setTheVaoData(chaptere[i]->levelFromChapter[0]->vaoBufferOfFinishedLevel,
								   chaptere[i]->levelFromChapter[0]->vboBufferOfFinishedLevel,
								   chaptere[i]->levelFromChapter[0]->iboBufferOfFinishedLevel,
								   chaptere[i]->levelFromChapter[0]->dataOfFinishedLevel,
								   chaptere[i]->levelFromChapter[0]->width, chaptere[i]->levelFromChapter[0]->height);
		
	}
	
	///Setez data si vao al animatiei cu care ma voi plimba prin nivele ca sa il aleg pe cel care vreau
	addObstacle->setTheVaoData(levelChoserPlayer->vao, levelChoserPlayer->vbo, levelChoserPlayer->ibo,
							   levelChoserPlayer->data, levelChoserPlayer->width, levelChoserPlayer->height);
	
	
	
	
	///Setez texturile de conexiune dintre chaptere
	float sizeOfConnectionStringX = abs(chaptere[0]->xCord - chaptere[1]->xCord) - chaptere[0]->width / 2.0f;
	float sizeOfConnectionStringY = abs(chaptere[0]->yCord - chaptere[4]->yCord) - chaptere[0]->height / 2.0f;
	
	chaptere[0]->levelFromChapter[0]->widthConnectionLeftRightChapter = sizeOfConnectionStringX;
	chaptere[0]->levelFromChapter[0]->heightConnectionLeftRightChapter = chaptere[0]->height / 4.0f;
	
	chaptere[0]->levelFromChapter[0]->widthConnectionUpDownChapter = chaptere[0]->width / 4.0f;
	chaptere[0]->levelFromChapter[0]->heightConnectionUpDownChapter = sizeOfConnectionStringY;
	
	chaptere[0]->levelFromChapter[0]->widthFinishedChapter = chaptere[0]->levelFromChapter[0]->width;
	chaptere[0]->levelFromChapter[0]->heightFinishedChapter = chaptere[0]->levelFromChapter[0]->height;
	
	
	addObstacle->setTheVaoData(chaptere[0]->levelFromChapter[0]->vaoBufferOfConnectionLeftRightChapter,
							   chaptere[0]->levelFromChapter[0]->vboBufferOfConnectionLeftRightChapter,
							   chaptere[0]->levelFromChapter[0]->iboBufferOfConnectionLeftRightChapter,
							   chaptere[0]->levelFromChapter[0]->dataOfConnectionLeftRightChapter,
							   sizeOfConnectionStringX, chaptere[0]->height / 4.0f);
	
	addObstacle->setTheVaoData(chaptere[0]->levelFromChapter[0]->vaoBufferOfConnectionUpDownChapter,
							   chaptere[0]->levelFromChapter[0]->vboBufferOfConnectionUpDownChapter,
							   chaptere[0]->levelFromChapter[0]->iboBufferOfConnectionUpDownChapter,
							   chaptere[0]->levelFromChapter[0]->dataOfConnectionUpDownChapter,
							   chaptere[0]->width / 4.0f, sizeOfConnectionStringY);
	
	///Setez textura pentru Finished Chapter
	addObstacle->setTheVaoData(chaptere[0]->levelFromChapter[0]->vaoBufferOfFinishedLevelChapter,
							   chaptere[0]->levelFromChapter[0]->vboBufferOfFinishedLevelChapter,
							   chaptere[0]->levelFromChapter[0]->iboBufferOfFinishedLevelChapter,
							   chaptere[0]->levelFromChapter[0]->dataOfFinishedLevelChapter,
							   chaptere[0]->width, chaptere[0]->height);
}






/*
 void BSTexture::setTexturedPolygonProgram2D( BSTexturedPolygonProgram2D* program )
 {
 //Set class rendering program
 bTexturedPolygonProgram2D = program;
 }*/


int BSTexture::aflaRestul(float numarul)
{
	if(numarul - floor(numarul) > 1/2.f)
	{
		return floor(numarul) + 1;
	}
    
	return floor(numarul);
}

BSTexture::BSTexture()
{
	//Initialize texture ID and pixels
	texture = 0;
	mPixels32 = NULL;
	mPixels8 = NULL;
	mPixelFormat = NULL;
    
	//Initialize image dimensions
	//5 = 0;
	//5 = 0;
    
	//Initialize texture dimensions
	//1 = 0;
	//1 = 0;
    
	//Initialize VBO
    //	mVBOID = 0;
    //	mIBOID = 0;
}

BSTexture::~BSTexture()
{
	//Free texture data if needed
	//freeTexture();
    
	//Free VBO and IBO if needed
	//freeVBO();
}



/*void BSTexture::ReinitializeResoultion(float newWidth, float newHeight)
 {
 //	glutDestroyWindow(1);
 
 //glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
 //glutInitWindowSize( newWidth, newHeight );
 //glutCreateWindow( SCREEN_TITLE );
 //glutSetWindow(glutGetWindow());
 
 //	glutReshapeWindow(newWidth, newHeight);
 
 //Set the viewport
 glViewport( 0.f, 0.f, newWidth, newHeight );
 
 //Initialize projection
 bTexturedPolygonProgram2D->setProjection( glm::ortho<GLfloat>( 0.0, newWidth, 0.0, newHeight, 1.0, -1.0 ) );
 bTexturedPolygonProgram2D->updateProjection();
 
 //Initialize modelview
 bTexturedPolygonProgram2D->setModelView( glm::mat4() );
 bTexturedPolygonProgram2D->updateModelView(false);
 
 }*/



void BSTexture::setTheVao( GLuint &theVaoBuffer, BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind)
{
	/*
	 //	if(!theVaoBuffer)
	 {
	 //Generate VAO buffer
	 glGenVertexArraysOES( 1, &theVaoBuffer );
	 //Bind vertex array
	 glBindVertexArrayOES( theVaoBuffer );
	 //bind the VBO
	 bindVBO(dataToBind, theVboToBind, theIbotoBind);
	 //std::cout<<theVboToBind<<' '<<theIbotoBind<<' '<<theVaoBuffer<<'\n';
	 
	 
	 glEnableVertexAttribArray(mVertexPos2DLocation);
	 glVertexAttribPointer(mVertexPos2DLocation, 3, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), 0);
	 
	 glEnableVertexAttribArray(mTexCoordLocation);
	 glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*) (sizeof(float) * 3));
	 
	 
	 //Unbind VAO
	 glBindVertexArrayOES( NULL );
	 glBindBuffer( GL_ARRAY_BUFFER, NULL );
	 glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, NULL );
	 }*/
}

GLuint mVBOID = 0;
GLuint mIBOID = 0;



void BSTexture::bindVBO(BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind)
{
    glGenBuffers(1, &theVboToBind);
    glBindBuffer(GL_ARRAY_BUFFER, theVboToBind);
    glBufferData(GL_ARRAY_BUFFER, sizeof(dataToBind), dataToBind, GL_DYNAMIC_DRAW);
    
    glGenBuffers(1, &theIbotoBind);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIbotoBind);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iData), iData, GL_DYNAMIC_DRAW);
    
}

//void BSTexture::freeVBO()
//{
//Free VBO and IBO
//	if( mVBOID != 0 )
//	{
//		glDeleteBuffers( 1, &mVBOID );
//		glDeleteBuffers( 1, &mIBOID );
//	}
//}

void BSTexture::setTheValuesForShaders()
{
    //	std::cout<<CameraExtremeLeft<<" "<<CameraExtremeDown<<" "<<CameraExtremeUp<<" "<<CameraExtremeRight<<'\n';
	glUniform1f(ShaderScaleSize, scaleSize);
	glUniform1f(ShaderRotationAngle, Hero2nd->theBody->GetAngle());
	glUniform1f(ShaderIsCircle, 0);
	glUniform1f(ShaderCircleRadius, Hero2nd->width);
	
	//float angle = hero->theBody->GetAngle();
	/*while (angle <= 0)
     {
     angle += 360;
     }
     while (angle > 360)
     {
     angle -= 360;
     }*/
    
    
	//float inversa =sqrt(vData[0][0].position.x * vData[0][0].position.x +
	//					vData[0][0].position.y * vData[0][0].position.y);
	//glUniform3f(ShaderRotationAngle, vData[0][0].position.x, vData[0][0].position.y, inversa);
    //	std::cout<<angle<<'\n';
    
    
    
    //	bTexturedPolygonProgram2D->mModelViewMatrix = glm::mat4();
    //
    //	bTexturedPolygonProgram2D->mModelViewMatrix = glm::rotate(bTexturedPolygonProgram2D->mModelViewMatrix, angle * 0.1f, glm::vec3(1.0f, 1.0f, 0.0f));
    //
    //	glUniformMatrix4fv(	bTexturedPolygonProgram2D->mModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr( bTexturedPolygonProgram2D->mModelViewMatrix ) );
}










void BSTexture::renderVboAndVao()
{
	setTheValuesForShaders();
	
	//renderBackgroundNo1();
	
	renderTheObstacles();
	renderDustBodies();
	renderCoins();
	renderFans();
	renderWormHoles();
	renderPlayer();
	renderMessages();
	
	
	setCameraPosition();
	
	if(DarkLevels)
	{
		renderDarkLevel();
	}
	
	
	if(useSnow)
	{
		renderSnowFlakes();
	}
	else
		if(useRain)
		{
			renderRainDrops();
		}
		else
			if(useAssassinsCreed)
			{
				///renderAssassinsCreed();
			}
	
	
	renderQuadrants();
	
	if(!DarkLevels)
    {
        BSColorRGBA cul = {0, 0, 0, 1};
        renderMyFont(BStoString(coinsTotalNo + coinsThisLevel), originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 1.5f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, 1.5f, 1.5f, cul);
    }
    else
    {
        BSColorRGBA cul = {1, 1, 1, 1};
        renderMyFont(BStoString(coinsTotalNo + coinsThisLevel), originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 1.5f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, 1.5f, 1.5f, cul);
    }
	renderTheCoin();
}


void BSTexture::buildRainDrops()
{
	originalRainDrop->width = 1;
	originalRainDrop->height = 1;
	originalRainDrop->depth = 0;
	addObstacle->setTheVaoData(originalRainDrop->vao, originalRainDrop->vbo, originalRainDrop->ibo, originalRainDrop->data, 1, 1);
	
	
	float maximX = 50;///gameBoundRight;///SCREEN_WIDTH / 32;
	float minimX = -3.0f;
	
	float maximY = 40;///gameBoundUp + 2;///SCREEN_HEIGHT / 32;
	float minimY = 0.0f;
	
	float maximZ = -scaleSizeInitial + 1;
	float minimZ = 2 * scaleSizeInitial;
	
	float posX, posY, posZ, xSpeedMin, xSpeedMax, ySpeedMin, ySpeedMax, xSpeed, ySpeed;
	int leftOrRight = 0;
	
	for(int i = 0 ; i < 1000; i++)
	{
		posX = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximX - minimX + 1) + minimX;
		posY = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximY - minimY + 1) + minimY;
		posZ = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximZ - minimZ + 1) + minimZ;
		
		xSpeed = 0.07f;//(float) (rand() % 4 + 2) / 1000 * leftOrRight;
		ySpeed = -0.25f;//(float) (rand() % 10 + 2) / 100;
		
		addARainDrop(posX, posY, posZ, xSpeed, ySpeed);
	}
}

void BSTexture::resetRainDrops()
{
	std::list<BSSnowFlakes*>::iterator i;
	for(i = listOfRainDrops.begin(); i!= listOfRainDrops.end(); i++)
	{
		
		float maximX = 50;///gameBoundRight;///SCREEN_WIDTH / 32;
		float minimX = -3.0f;
		
		float maximY = 40;///gameBoundUp + 2;///SCREEN_HEIGHT / 32;
		float minimY = 0.0f;
		
		(*i)->xCord = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximX - minimX + 1) + minimX;
		(*i)->yCord = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximY - minimY + 1) + minimY;
	}
}

void BSTexture::addARainDrop(float x, float y, float z, float xPower, float yPower)
{
	BSSnowFlakes *newDrop = new BSSnowFlakes;
	newDrop->color.r = 0;
	newDrop->color.g = 0;
	newDrop->color.b = 255;
	newDrop->color.a = 0.2f;
	
	if(z > -3)
	{
		newDrop->width = 0.02f;//0.02f;//0.003f
							   //		newDrop->width = 0.001f;//0.02f;//0.003f
	}
	else
	{
		newDrop->width = 0.04f;
		//		newDrop->width = 0.02f;
	}
	newDrop->height = 0.4f;
	newDrop->depth = 0;
	newDrop->xCord = x;
	newDrop->yCord = y;
	newDrop->zCord = z;//scaleSizeInitial;
	newDrop->xPower = xPower;
	newDrop->yPower = yPower;
	newDrop->xInit = x;
	newDrop->yInit = y;
	listOfRainDrops.push_back(newDrop);
}

void BSTexture::renderRainDrops()
{
	setTheValuesForShaders();
	
	
	float maximX = 50;///gameBoundRight;///SCREEN_WIDTH / 32;
	float minimX = -3.0f;
	
	float maximY = 40;///gameBoundUp + 2;///SCREEN_HEIGHT / 32;
	float minimY = 0.0f;
	
	
	float posX, posY, posZ;
	
	
	std::list<BSSnowFlakes*>::iterator i;
	for(i = listOfRainDrops.begin(); i!= listOfRainDrops.end(); i++)
	{
		(*i)->xCord += (*i)->xPower;
		(*i)->yCord += (*i)->yPower;
		renderAnVboAndVaoObject((*i)->xCord, (*i)->yCord, (*i)->zCord, 10, 0, 0, blankTexture,
								(*i)->color, originalRainDrop->vao, (*i)->width, (*i)->height, (*i)->depth);
		if((*i)->yCord < 0)
		{
			posX = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximX - minimX + 1) + minimX;
			//			posZ = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximZ - minimZ + 1) + minimZ;
			(*i)->yCord = maximY;
			(*i)->xCord = (*i)->xInit;
		}
	}
}



void BSTexture::renderCoins()
{
	if(redSinForCoins < 180)
	{
		redSinForCoins += 2.0f;
	}
	else
	{
		redSinForCoins = 0;
	}
	
	std::list<BSCoins*>::iterator it;
	for(it = listOfCoins.begin(); it != listOfCoins.end(); it++)
	{
		if((*it)->available)
		{
			///Daca e in limite
			if(( (hero->theBody->GetPosition().x + hero->width / 2.f >= (*it)->xCord - (*it)->width / 2.f &&
				  hero->theBody->GetPosition().x + hero->width / 2.f <= (*it)->xCord + (*it)->width / 2.f) ||
				(hero->theBody->GetPosition().x - hero->width / 2.f <= (*it)->xCord + (*it)->width / 2.f &&
				 hero->theBody->GetPosition().x - hero->width / 2.f >= (*it)->xCord - (*it)->width / 2.f) )
			   &&
			   ((hero->theBody->GetPosition().y + hero->height / 2.f >= (*it)->yCord - (*it)->height / 2.f &&
				 hero->theBody->GetPosition().y + hero->height / 2.f <= (*it)->yCord + (*it)->height / 2.f) ||
				(hero->theBody->GetPosition().y - hero->height / 2.f <= (*it)->yCord + (*it)->height / 2.f &&
				 hero->theBody->GetPosition().y - hero->height / 2.f >= (*it)->yCord - (*it)->height / 2.f)))
			{
				(*it)->available = false;
				(*it)->sinValue = 90;
				(*it)->sinValue2 = 0;
				coinsThisLevel++;
				//alSourcePlay(SourceSoundCoin);
			}
		}
		else
		{
			///Daca nu e transparent de tot
			if((*it)->sinValue > 0)
			{
				(*it)->sinValue -= 4.5f;
				(*it)->color.a = sin(toRadians((*it)->sinValue));
				(*it)->sinValue2 += 0.5f;
				(*it)->yCord += sin(toRadians((*it)->sinValue2));
				
				///Daca e transparent de tot
				if((*it)->sinValue <= 0)
				{
					(*it)->deleteIt = true;
				}
			}
		}
		///Daca il poate desena
		if(!(*it)->deleteIt)
		{
			(*it)->color.r = 1 + sin(toRadians(redSinForCoins));
			renderAnVboAndVaoObject((*it)->xCord, (*it)->yCord, (*it)->zCord, 0, 0, 0, originalCoin->texture,
									(*it)->color, originalCoin->vao, (*it)->width, (*it)->height, (*it)->depth);
		}
	}
	
}

void BSTexture::renderFans()
{
	std::list<BSFans*>::iterator it;
	for(it = listOfFans.begin(); it != listOfFans.end(); it++)
	{
		if((*it)->powerY)
		{
			///Daca e in limite
			if(( (hero->theBody->GetPosition().x + hero->width / 2.f >= (*it)->xCord - (*it)->width / 2.f &&
				  hero->theBody->GetPosition().x + hero->width / 2.f <= (*it)->xCord + (*it)->width / 2.f) ||
				(hero->theBody->GetPosition().x - hero->width / 2.f <= (*it)->xCord + (*it)->width / 2.f &&
				 hero->theBody->GetPosition().x - hero->width / 2.f >= (*it)->xCord - (*it)->width / 2.f) )
			   &&
			   (hero->theBody->GetPosition().y - hero->height / 2.f <= (*it)->yCord + (*it)->lenthOfPower ) )
			{
				hero->theBody->ApplyForce(b2Vec2((*it)->powerX, (*it)->powerY), hero->theBody->GetWorldCenter());
			}
		}
		///Daca il poate desena
		renderAnVboAndVaoObject((*it)->xCord, (*it)->yCord, (*it)->zCord, 0, 0, 0, originalFan->texture,
								(*it)->color, originalFan->vao, (*it)->width, (*it)->height, (*it)->depth);
		
		
        std::list<BSBody*>::iterator i;
        for(i = (*it)->particles.begin(); i != (*it)->particles.end(); i++)
        {
            (*i)->xCord += (*i)->value1;
            (*i)->yCord += (*i)->value2;
            if((*i)->yCord > (*it)->yMax + 4)
            {
                (*i)->yCord = (*it)->yMin;
            }
            if((*i)->xCord > (*it)->xMax + 4)
            {
                (*i)->xCord = (*it)->xMin;
            }
            renderAnVboAndVaoObject((*i)->xCord, (*i)->yCord, (*i)->zCord, 0, 0, 0, originalFan->texture,
                                    (*i)->color, originalFan->vao, (*i)->width, (*i)->height, (*i)->depth);
        }
	}
	
}


void BSTexture::renderQuadrants()
{
	float var = 17;
	BSColorRGBA darkWhite = { 1, 1, 1, 0.3f };
	BSColorRGBA lightWhite = { 1, 1, 1, 0.2f };
	BSColorRGBA white = { 1, 1, 1, 0.2f };
	GLuint theTexture = whiteTexture;

	//the 2 perpendicular lines
	//horizontal
	renderAnVboAndVaoObject(CameraPosition->xCord - CameraExtremeLeft + SCREEN_WIDTH / var / 2.0f, CameraPosition->yCord - CameraExtremeDown + SCREEN_HEIGHT / var / 2.0f, scaleSizeInitial, 0, 0, 0, theTexture, darkWhite, originalFan->vao, SCREEN_WIDTH / var, 0.2f, 0);
	//vertical
	renderAnVboAndVaoObject(CameraPosition->xCord - CameraExtremeLeft + SCREEN_WIDTH / var / 2.0f, CameraPosition->yCord - CameraExtremeDown + SCREEN_HEIGHT / var / 2.0f, scaleSizeInitial, 0, 0, 0, theTexture, darkWhite, originalFan->vao, 0.2f, SCREEN_HEIGHT / var, 0);
	
	
	//the 4 quadrants
	if(quadrantIndex == 1)
	{
		//bottom left
		renderAnVboAndVaoObject(CameraPosition->xCord - CameraExtremeLeft + SCREEN_WIDTH / var / 4.0f, CameraPosition->yCord - CameraExtremeDown + SCREEN_HEIGHT / var / 4.0f, scaleSizeInitial, 0, 0, 0, theTexture, white, originalFan->vao, SCREEN_WIDTH / var / 2.0f, SCREEN_HEIGHT / var / 2.0f, 0);
	}
	else
		if(quadrantIndex == 2)
		{
			//bottom right
			renderAnVboAndVaoObject(CameraPosition->xCord - CameraExtremeLeft + SCREEN_WIDTH * 3.0f / var / 4.0f, CameraPosition->yCord - CameraExtremeDown + SCREEN_HEIGHT / var / 4.0f, scaleSizeInitial, 0, 0, 0, theTexture, white, originalFan->vao, SCREEN_WIDTH / var / 2.0f, SCREEN_HEIGHT / var / 2.0f, 0);
		}
	else
		if(quadrantIndex == 3)
		{
			//top left
			renderAnVboAndVaoObject(CameraPosition->xCord - CameraExtremeLeft + SCREEN_WIDTH / var / 4.0f, CameraPosition->yCord - CameraExtremeDown + SCREEN_HEIGHT * 3.0f / var / 4.0f, scaleSizeInitial, 0, 0, 0, theTexture, white, originalFan->vao, SCREEN_WIDTH / var / 2.0f, SCREEN_HEIGHT / var / 2.0f, 0);
		}
	else
		if(quadrantIndex == 4)
		{
			//top right
			renderAnVboAndVaoObject(CameraPosition->xCord - CameraExtremeLeft + SCREEN_WIDTH * 3.0f / var / 4.0f, CameraPosition->yCord - CameraExtremeDown + SCREEN_HEIGHT * 3.0f / var / 4.0f, scaleSizeInitial, 0, 0, 0, theTexture, white, originalFan->vao, SCREEN_WIDTH / var / 2.0f, SCREEN_HEIGHT / var / 2.0f, 0);
		}
}

void BSTexture::renderDarkLevel()
{
	glUniform1f(ShaderDark, 1);
	glUniform1f(ShaderIsCircle, 1);
	glUniform1f(ShaderCircleRadius, Hero_size / 3.f);
	
	float xCordL, xCordR, xCordU, xCordD, yCordL, yCordR, yCordU, yCordD;
	
	xCordL = hero->theBody->GetPosition().x - SCREEN_WIDTH / 32.0f + Hero_size * 6.f;
	xCordD = hero->theBody->GetPosition().x;
	xCordU = hero->theBody->GetPosition().x;
	xCordR = hero->theBody->GetPosition().x + SCREEN_WIDTH / 32.0f - Hero_size * 6.f;
	
	yCordL = hero->theBody->GetPosition().y;
	yCordD = hero->theBody->GetPosition().y - SCREEN_HEIGHT / 32.0f + Hero_size * 6.f;
	yCordU = hero->theBody->GetPosition().y + SCREEN_HEIGHT / 32.0f - Hero_size * 6.f;
	yCordR = hero->theBody->GetPosition().y;
	
	BSColorRGBA mainColor = {0.f, 0.f, 0.f, 1.f};
	renderAnVboAndVaoObject(hero->theBody->GetPosition().x, hero->theBody->GetPosition().y, hero->zCord, 0, 0, 0,
							blankTexture, mainColor, originalDarkMenu->vao, originalDarkMenu->width, originalDarkMenu->height, originalDarkMenu->depth);
	renderAnVboAndVaoObject(hero->theBody->GetPosition().x, hero->theBody->GetPosition().y, hero->zCord, 0, 0, 0,
							blankTexture, mainColor, originalDarkMenu->vao, originalDarkMenu->width, originalDarkMenu->height, originalDarkMenu->depth);
	
	glUniform1f(ShaderDark, 0);
	glUniform1f(ShaderIsCircle, 0);
}




void BSTexture::renderPlayer()
{
	//renderPlayerAnimation();
	renderNewPlayerAnimation();//(currentPlayerAnimation);
	glUniform1f(ShaderRotated, 0);
	//set the texture
	theTextureToRender = playerTexture;
	//set the color
	//theColorToRender = { 1.f, 1.f, 1.f, 1.f };
	theColorToRender.r = 1;
	theColorToRender.g = 1;
	theColorToRender.b = 1;
	theColorToRender.a = 1;
    
	//float angle = hero->theBody->GetAngle() * 2;
	//bTexturedPolygonProgram2D->setModelView( glm::mat4() );
	//bTexturedPolygonProgram2D->leftMultModelView( glm::rotate(bTexturedPolygonProgram2D->mModelViewMatrix, angle, glm::vec3(1.0f, 1.0f, 0.0f)));
	//bTexturedPolygonProgram2D->updateModelView(true);
    
    //	//render the player
    //	renderAnVboAndVaoObject(hero->theBody->GetPosition().x, hero->theBody->GetPosition().y,
    //								currentPlayerAnimation->theTexture, currentPlayerAnimation->colorOfAnimation, hero->vao);
}

void BSTexture::renderRoundPlayer()
{
	//glUniform1f(ShaderCircleRadius, theRenderedObstacleCircle->radiusOfCircle);
	glUniform1f(ShaderIsCircle, 1);
	glUniform1f(ShaderRotated, 1);
	glUniform1f(ShaderCosRotation, 0);
    
    
	//set the texture
	theTextureToRender = playerTextureRound;
	//set the color
	//theColorToRender = { 1.f, 1.f, 1.f, 1.f };
	theColorToRender.r = 1;
	theColorToRender.g = 1;
	theColorToRender.b = 1;
	theColorToRender.a = 1;
    
	//float angle = hero->theBody->GetAngle() * 2;
	//bTexturedPolygonProgram2D->setModelView( glm::mat4() );
	//bTexturedPolygonProgram2D->leftMultModelView( glm::rotate(bTexturedPolygonProgram2D->mModelViewMatrix, angle, glm::vec3(1.0f, 1.0f, 0.0f)));
	//bTexturedPolygonProgram2D->updateModelView(true);
    
	//render the player
	renderAnVboAndVaoObject(Hero2nd->theBody->GetPosition().x, Hero2nd->theBody->GetPosition().y, hero->zCord, 0, 0, 0, theTextureToRender, theColorToRender, Hero2nd->vao, Hero2nd->width, Hero2nd->height, Hero2nd->depth);
    
    
    
    
	glUniform1f(ShaderIsCircle, 0);
	glUniform1f(ShaderRotated, 0);
}



void BSTexture::renderTheSquareObstacles()
{
	theTextureToRender = texture;
    
	std::list<BSTheSquareBodies*>::iterator i;
    
	for(i = ListOfSquareBodies.begin(); i != ListOfSquareBodies.end(); i++)
	{
		if((*i)->ObstacleCanKillHero)
		{
			//(*i)->color = { 2.f, 0.3f, 0.f, 1.f };
			(*i)->color.r = 2;
			(*i)->color.g = 0.3f;
			(*i)->color.b = 0;
			(*i)->color.a = 1.f;
		}
		else
			if((*i)->ObstacleFinishesLevel)
			{
				//(*i)->color = { 0.f, 2.f, 0.f, 1.f };
				(*i)->color.r = 0;
				(*i)->color.g = 2;
				(*i)->color.b = 0;
				(*i)->color.a = 1.f;
			}
			else
			{
				//(*i)->color = { 1.f, 1.f, 1.f, 1.f };
				(*i)->color.r = 1;
				(*i)->color.g = 1;
				(*i)->color.b = 1;
				(*i)->color.a = 1;
			}
        
        checkBodyScript((*i), NULL);
		
		///Daca are textura sau culoare, il desenez
		if( ((*i)->color.r != 1.0 || (*i)->color.g != 1.0 || (*i)->color.b != 1.0 || (*i)->color.a != 1.0)
           || (*i)->texture)
		{
			renderAnVboAndVaoObject((*i)->theBody->GetPosition().x, (*i)->theBody->GetPosition().y, (*i)->zCord, 0, 0, 0, (*i)->texture, (*i)->color, (*i)->vao, (*i)->width, (*i)->height, (*i)->depth);
		}
	}
    
}

void BSTexture::checkBodyScript(BSTheSquareBodies *square, BSTheRoundBodies *round)
{
    BSBodyScript *script = NULL;
    float xCord = 0, yCord = 0;
    float xSpeed = 0, ySpeed = 0;
    float slowSpeed = 6;
    
    if(square)
    {
        script = square->script;
        xCord = square->theBody->GetPosition().x;
        yCord = square->theBody->GetPosition().y;
    }
    else
        if(round)
        {
            script = round->script;
            xCord = round->theBody->GetPosition().x;
            yCord = round->theBody->GetPosition().y;
        }
    
    if(script)
    {
        float maxRight = (float) (script->xInitial + (script->xLength / 2));
        float maxLeft = (float) (script->xInitial - (script->xLength / 2));
        float maxUp = (float) (script->yInitial + (script->yLength / 2));
        float maxDown = (float) (script->yInitial - (script->yLength / 2));
        
        if(script->value2 >= 360)
        {
            script->value2 = script->value2 - 360;
        }
        
        if(script->xPower)
        {
            ///if he is moving right and didn't reach the border
            if(xCord < maxRight && script->value1 > 0)
            {
                ///daca mai are putin si ajunge la border, il incetinesc
                if(xCord > maxRight - 1)
                {
                    ///ii las viteza mica (nu il opresc complet)
                    if(script->value2 < 170)
                    {
                        script->value2 += slowSpeed;
                    }
                }
                else
                    ///daca tocmai a cotit la dreapta
                    if(xCord < maxRight - 1)
                    {
                        ///ii las viteza mica (nu il opresc complet)
                        if(script->value2 < 90)
                        {
                            script->value2 += slowSpeed;
                        }
                    }
                ///daca nu trebuie sa incetineasca sau sa accelereze
                    else
                    {
                        if(sin(toRadians(script->value2)) > 0)
                        {
                            script->value2 = 90;
                        }
                        else
                            if(sin(toRadians(script->value2)) < 0)
                            {
                                script->value2 = 270;
                            }
                    }
                //                xSpeed = script->xPower;
            }
            else
                ///if he is moving left and didn't reach the border
                if(xCord > maxLeft && script->value1 < 0)
                {
                    ///daca tocmai a cotit la stanga
                    if(xCord > maxRight - 1)
                    {
                        ///ii las viteza mica (nu il opresc complet)
                        if(script->value2 < 270)
                        {
                            script->value2 += slowSpeed;
                        }
                    }
                    else
                        ///daca mai are putin si ajunge la border, il incetinesc
                        if(xCord < maxLeft + 1)
                        {
                            ///ii las viteza mica (nu il opresc complet)
                            if(script->value2 < 350)
                            {
                                script->value2 += slowSpeed;
                            }
                        }
                    ///daca nu trebuie sa incetineasca sau sa accelereze
                        else
                        {
                            if(sin(toRadians(script->value2)) > 0)
                            {
                                script->value2 = 90;
                            }
                            else
                                if(sin(toRadians(script->value2)) < 0)
                                {
                                    script->value2 = 270;
                                }
                        }
                    //                    xSpeed = -script->xPower;
                }
                else
                    ///if he got out of borders
                    if(xCord >= maxRight)
                    {
                        //                        xSpeed = -script->xPower;
                        script->value1 = -1;
                        script->value2 = 190;
                    }
                    else
                        if(xCord <= maxLeft)
                        {
                            //                            xSpeed = script->xPower;
                            script->value1 = 1;
                            script->value2 = 10;
                        }
            
            xSpeed = script->xPower * sin(toRadians(script->value2));
        }
        else
            if(script->yPower)
            {
                ///if he is moving right and didn't reach the border
                if(yCord < maxUp && script->value1 > 0)
                {
                    ///daca mai are putin si ajunge la border, il incetinesc
                    if(yCord > maxUp - 1)
                    {
                        ///ii las viteza mica (nu il opresc complet)
                        if(script->value2 < 170)
                        {
                            script->value2 += slowSpeed;
                        }
                    }
                    else
                        ///daca tocmai a cotit la dreapta
                        if(yCord < maxUp - 1)
                        {
                            ///ii las viteza mica (nu il opresc complet)
                            if(script->value2 < 90)
                            {
                                script->value2 += slowSpeed;
                            }
                        }
                    ///daca nu trebuie sa incetineasca sau sa accelereze
                        else
                        {
                            if(sin(toRadians(script->value2)) > 0)
                            {
                                script->value2 = 90;
                            }
                            else
                                if(sin(toRadians(script->value2)) < 0)
                                {
                                    script->value2 = 270;
                                }
                        }
                    //                    ySpeed = script->yPower;
                }
                else
                    ///if he is moving left and didn't reach the border
                    if(yCord > maxDown && script->value1 < 0)
                    {
                        ///daca tocmai a cotit la stanga
                        if(yCord > maxUp - 1)
                        {
                            ///ii las viteza mica (nu il opresc complet)
                            if(script->value2 < 270)
                            {
                                script->value2 += slowSpeed;
                            }
                        }
                        else
                            ///daca mai are putin si ajunge la border, il incetinesc
                            if(yCord < maxDown + 1)
                            {
                                ///ii las viteza mica (nu il opresc complet)
                                if(script->value2 < 350)
                                {
                                    script->value2 += slowSpeed;
                                }
                            }
                        ///daca nu trebuie sa incetineasca sau sa accelereze
                            else
                            {
                                if(sin(toRadians(script->value2)) > 0)
                                {
                                    script->value2 = 90;
                                }
                                else
                                    if(sin(toRadians(script->value2)) < 0)
                                    {
                                        script->value2 = 270;
                                    }
                            }
                        //                        ySpeed = -script->yPower;
                    }
                    else
                        ///if he got out of borders
                        if(yCord >= maxUp)
                        {
                            //                            ySpeed = -script->yPower;
                            script->value1 = -1;
                            script->value2 = 190;
                        }
                        else
                            if(yCord <= maxDown)
                            {
                                //                                ySpeed = script->yPower;
                                script->value1 = 1;
                                script->value2 = 10;
                            }
                
                ySpeed = script->yPower * sin(toRadians(script->value2));
            }
    }
    
    
    if(square)
    {
        square->theBody->SetLinearVelocity(b2Vec2(xSpeed, ySpeed));
    }
    else
        if(round)
        {
            round->theBody->SetLinearVelocity(b2Vec2(xSpeed, ySpeed));
        }
}




void BSTexture::renderDustBodies()
{
    for(std::list<BSTheSquareBodies*>::iterator i = ListOfSquareDustBodies.begin(); i != ListOfSquareDustBodies.end(); i++)
    {
        BSColorRGBA color = {1, 1, 1, 0};
        float decal = 0;
        USERDATA *userData = NULL;
        if((*i)->theBody)
        {
            userData = (USERDATA*)(*i)->theBody->GetUserData();
        }
        ///if(userData)
        {
            if(userData && !userData->isDust)
            {
                color.a = 1.f;
            }
            else
            {
                ///if it's not invisible
                if((*i)->value1 < 90)
                {
                    (*i)->value1 += 1.f;
                    
                    ///destroy the body
                    if((*i)->value1 > 30 && (*i)->theBody)
                    {
                        world->DestroyBody((*i)->theBody);
                        (*i)->theBody = NULL;
                    }
                }
                else
                {
                    (*i)->value1 = 90;
                }
                
                if((*i)->value1 > 30)
                {
                    decal = 2 * sin(toRadians((*i)->value1 - 30));
                }
                color.a = cos(toRadians((*i)->value1));
            }
        }
        
        if(color.a > 0)
        {
            renderAnVboAndVaoObject((*i)->xCord, (*i)->yCord - decal, (*i)->zCord, 0, 0, 0, originalDustBody->texture, color, originalDustBody->vao, (*i)->width, (*i)->height, (*i)->depth);
        }
    }
}

void BSTexture::resetDustBodies()
{
    for(std::list<BSTheSquareBodies*>::iterator i = ListOfSquareDustBodies.begin(); i != ListOfSquareDustBodies.end(); i++)
    {
        if((*i)->theBody == NULL)
        {
            (*i)->theBody = addObstacle->createBodies(b2_staticBody, (*i)->xInit, (*i)->yInit, (*i)->width, (*i)->height,
                                                      "object", nrBodies, 0, false);
        }
        
        (*i)->value1 = 0;
        (*i)->value2 = 0;
        
        USERDATA* dataForUser = new USERDATA;
        
        dataForUser->isDustAble = 1;
        dataForUser->isDust = 0;
        
        dataForUser->canKillHero = false;
        dataForUser->isToNextLevel = false;
        
        dataForUser->name = "object";
        (*i)->theBody->SetUserData(dataForUser);
        
    }
}



void BSTexture::renderTheCircleObstacles()
{
	theTextureToRender = texture;
	glUniform1f(ShaderIsCircle, 1);
	///glUniform1f(ShaderRotated, 1);
	
	std::list<BSTheRoundBodies*>::iterator i;
	
	for(i = ListOfRoundBodies.begin(); i != ListOfRoundBodies.end(); i++)
	{
        float theAngle = (*i)->theBody->GetAngle();
		if((*i)->isRotating)
		{
			if(((*i)->theBody->GetAngle() < 0 && (*i)->theBody->GetAngle() <= -2 * 180) ||//3.1415) ||
			   ((*i)->theBody->GetAngle() > 0 && (*i)->theBody->GetAngle() >= 2 * 180))//3.1415))
			{
				theAngle = 0;
				
				//theAngle = abs(p->theBody->GetAngle()) - 3.1415;
				if((*i)->theBody->GetAngle() < 0)
				{
					theAngle *= -1;
				}
			}
			
			theAngle -= 5.1 * (60 / theTimeHowFast);
			(*i)->theBody->SetTransform(b2Vec2((*i)->theBody->GetPosition().x, (*i)->theBody->GetPosition().y), theAngle);
			///glUniform1f(ShaderCosRotation, theAngle);
		}
		
		glUniform1f(ShaderCircleRadius, (*i)->radius);
		
		if((*i)->ObstacleCanKillHero)
		{
			(*i)->color.r = 120;
			(*i)->color.g = 0.3f;
			(*i)->color.b = 0;
			(*i)->color.a = 1;
		}
		else
			if((*i)->ObstacleFinishesLevel)
			{
				(*i)->color.r = 0;
				(*i)->color.g = 20;
				(*i)->color.b = 0;
				(*i)->color.a = 1;
			}
			else
			{
				//p->color = { 1.f, 1.f, 1.f, 1.f };
			}
		
        checkBodyScript(NULL, (*i));
		
		///Daca are textura sau culoare, il desenez
		if( ((*i)->color.r != 1.0 || (*i)->color.g != 1.0 || (*i)->color.b != 1.0 || (*i)->color.a != 1.0)
		   || (*i)->texture)
		{
			renderAnVboAndVaoObject((*i)->theBody->GetPosition().x, (*i)->theBody->GetPosition().y, (*i)->zCord, theAngle, 0, 0,
									(*i)->texture, (*i)->color, (*i)->vao, (*i)->radius, (*i)->radius, (*i)->depth);
		}
	}
	
	
	glUniform1f(ShaderIsCircle, 0);
	///glUniform1f(ShaderRotated, 0);
}





void BSTexture::renderOnlyTheTextures()
{
	for(std::list<BSTextureSquare*>::iterator i = ListOfSquareTextures.begin(); i != ListOfSquareTextures.end(); i++)
	{
		renderAnVboAndVaoObject((*i)->xCord, (*i)->yCord, (*i)->zCord, 0, 0, 0, (*i)->texture, (*i)->color, (*i)->vao, (*i)->width, (*i)->height, (*i)->depth);
	}
    
    
	glUniform1f(ShaderIsCircle, 1);
	glUniform1f(ShaderRotated, 1);
	
	for(std::list<BSTextureRound*>::iterator i = ListOfRoundTextures.begin(); i != ListOfRoundTextures.end(); i++)
	{
		renderAnVboAndVaoObject((*i)->xCord, (*i)->yCord, (*i)->zCord, 0, 0, 0, (*i)->texture, (*i)->color, (*i)->vao, (*i)->radius, (*i)->radius, 0);
	}
    
	glUniform1f(ShaderIsCircle, 0);
	glUniform1f(ShaderRotated, 0);
}



void BSTexture::renderTheObstacles()
{
	///Render the round bodies
	renderTheCircleObstacles();
	///Render the square bodies
	renderTheSquareObstacles();
	renderOnlyTheTextures();
    
	///Render Particles
	theTextureToRender = NULL;
	//theColorToRender = { 0.f, 0.f, 0.0f, 1.f };
	theColorToRender.r = 0;
	theColorToRender.g = 0;
	theColorToRender.b = 0;
	theColorToRender.a = 1;
    
	for(std::list<BSTheParticles*>::iterator i = ListOfParticles.begin(); i != ListOfParticles.end(); i++)
	{
		if((*i)->isDestroyed == false)
		{
            
			(*i)->theBodyOfParticle->SetTransform(b2Vec2((*i)->theBodyOfParticle->GetPosition().x,
														 (*i)->theBodyOfParticle->GetPosition().y),
												  (*i)->theBodyOfParticle->GetAngle() * 1.2);
            
			if((*i)->BumTime < SDL_GetTicks() + 50)
			{
				//(*i)->ColorOfParticle = { (*i)->ColorOfParticle.r + 0.15f, (*i)->ColorOfParticle.g + 0.15f, 0.f, 1.f};
				(*i)->color.r = (*i)->color.r + 0.15f;
				(*i)->color.g = (*i)->color.g + 0.15f;
				(*i)->color.b = 0;
				(*i)->color.a = 1;
			}
            
			renderAnVboAndVaoObject((*i)->theBodyOfParticle->GetPosition().x, (*i)->theBodyOfParticle->GetPosition().y, (*i)->zCord, 0, 0, 0, NULL, (*i)->color, particleVaoBuffer, (*i)->width, (*i)->height, (*i)->depth);
            
			if((*i)->BumTime <= SDL_GetTicks())
			{
				(*i)->isDestroyed = true;
				(*i)->theBodyOfParticle->SetTransform(b2Vec2((*i)->theBodyOfParticle->GetPosition().x,
															 (*i)->theBodyOfParticle->GetPosition().y),
													  0);
			}
		}
	}
}


void BSTexture::setCameraPosition()
{
	if(hero->theBody->GetPosition().x <= CameraExtremeLeft)
	{
        CameraPosition->xCord = CameraExtremeLeft;
	}
	else
		if(hero->theBody->GetPosition().x > CameraExtremeLeft && hero->theBody->GetPosition().x < CameraExtremeRight)
		{
            CameraPosition->xCord = hero->theBody->GetPosition().x;
		}
		else
			if(hero->theBody->GetPosition().x >= CameraExtremeRight)
			{
                CameraPosition->xCord = CameraExtremeRight;
			}
    
	if(hero->theBody->GetPosition().y <= CameraExtremeDown)
	{
        CameraPosition->yCord = CameraExtremeDown;
	}
	else
		if(hero->theBody->GetPosition().y > CameraExtremeDown && hero->theBody->GetPosition().y < CameraExtremeUp)
		{
            CameraPosition->yCord = hero->theBody->GetPosition().y;
		}
		else
			if(hero->theBody->GetPosition().y >= CameraExtremeUp)
			{
                CameraPosition->yCord = CameraExtremeUp;
			}
}







void BSTexture::renderDeadSceneChange()
{
	if(deadScene->SinValueColorOfTheScene < 90 && deadScene->colorGoesUpOrDown == 1)
	{
		deadScene->SinValueColorOfTheScene += 2.9f;
	}
	else
		if(deadScene->SinValueColorOfTheScene >=90 && deadScene->colorGoesUpOrDown == 1)
		{
			//alSourcePlay(SourceSoundBeginningGame);
            
            std::list<BSCoins*>::iterator it;
            for(it = listOfCoins.begin(); it != listOfCoins.end(); it++)
            {
                if((*it)->alreadyHadIt == false)
                {
                    (*it)->available = true;
                    (*it)->deleteIt = false;
                    coinsThisLevel = 0;
                    (*it)->sinValue = 90;
                    (*it)->sinValue2 = 0;
                    (*it)->color.a = 1.0f;
                    (*it)->xCord = (*it)->xInit;
                    (*it)->yCord = (*it)->yInit;
                }
            }
			deadScene->colorGoesUpOrDown = -1;
			deadScene->SinValueColorOfTheScene -= 1.9f;
			hero->theBody->SetTransform(b2Vec2(HeroInitialX, HeroInitialY), 0);
			hero->heroIsDead = false;
			hero->texture = playerTexture;
			canJumpHorizontally = false;
			canJumpVertically = false;
			isOnGround = false;
			isInAir = true;
			isOnLeftWall = false;
			isOnRightWall = false;
			hero->theBody->SetTransform(b2Vec2(HeroInitialX, HeroInitialY), 0);
            
			std::ofstream coinsAndDeaths("coinsAndDeaths");
			coinsAndDeaths<<coinsTotalNo<<' '<<deathsTotalNo;
		}
		else
			if(deadScene->SinValueColorOfTheScene > 0 && deadScene->colorGoesUpOrDown == -1)
			{
				if(deadScene->SinValueColorOfTheScene < 60 && hero->theBody->GetLinearVelocity().y == 0)
				{
					hero->theBody->SetLinearVelocity(b2Vec2(0, 0.1));
					hero->theBody->ApplyLinearImpulse(b2Vec2(0, 0.1), hero->theBody->GetWorldCenter());
				}
                
				deadScene->SinValueColorOfTheScene -= 2.9f;
			}
			else
			{
				deadScene->SinValueColorOfTheScene = 0.f;
				deadScene->colorGoesUpOrDown = 0;
			}
    
	deadScene->color.a = sin(toRadians(deadScene->SinValueColorOfTheScene));
	deadScene->xCord = CameraPosition->xCord - CameraExtremeLeft;
	deadScene->yCord = CameraPosition->yCord - CameraExtremeDown;
	renderAnVboAndVaoObject(deadScene->xCord, deadScene->yCord, scaleSizeInitial, 0, 0, 0, deadScene->texture, deadScene->color, deadScene->vao, deadScene->width, deadScene->height, 0);
    
}




void BSTexture::renderNextLevelSceneChange()
{
	if(deadScene->CosValueColorOfTheScene < 90 && deadScene->colorGoesUpOrDown == 1)
	{
		deadScene->CosValueColorOfTheScene += 2.9f;
	}
	else
		if(deadScene->CosValueColorOfTheScene >=90 && deadScene->colorGoesUpOrDown == 1)
		{
			consoleSalveazaHarta();
			coinsTotalNo += coinsThisLevel;
			coinsThisLevel = 0;
			std::ofstream fout("coinsAndDeaths");
			fout<<coinsTotalNo<<' '<<1;
            
			//alSourcePlay(SourceSoundBeginningGame);
            
			deadScene->colorGoesUpOrDown = -1;
			deadScene->CosValueColorOfTheScene -= 2.9f;
            
            
			///Vad daca a terminat nivelul
			levelChoserPlayer->justFinished = false;
			levelChoserPlayer->indexOfLevelThatItIsOn++;
            
			///addObstacle->destroyAllBodiesSquare();
			///addObstacle->destroyAllBodiesRound();
            
			std::string nameString = "Menu Of Levels/Chapter" +
            BStoString(levelChoserPlayer->indexOfChapterThatItIsOn + 1) + "/The Levels objects/level" +
            BStoString(levelChoserPlayer->indexOfLevelThatItIsOn + 1) + ".xml";
			char nameChar[100] = "";
			strcpy(nameChar, nameString.c_str());
            
            //			for(int i = 0 ; i < nameString.size() ; i++)
            //			{
            //				nameChar[i] = nameString[i];
            //			}
            
			addObstacle->destroyLevel();
			addObstacle->incarcaHarta(nameChar);
			levelChoserPlayer->xCord =
            chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter[levelChoserPlayer->indexOfLevelThatItIsOn]->xCord;
			///nivele[levelChoserPlayer->indexOfMenuThatItIsOn]->xCord;
			levelChoserPlayer->yCord =
            chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter[levelChoserPlayer->indexOfLevelThatItIsOn]->yCord;
			///nivele[levelChoserPlayer->indexOfMenuThatItIsOn]->yCord;
            
            
			hero->theBody->SetTransform(b2Vec2(HeroInitialX, HeroInitialY), 0);
            
            
            
			/*
             ///Set the extremes of the camera
             std::string nameOfLevel = "Menu Of Levels/Chapter" +
             BStoString(levelChoserPlayer->indexOfChapterThatItIsOn + 1) + "/The Levels details/level" +
             BStoString(levelChoserPlayer->indexOfLevelThatItIsOn + 1) + ".txt";
             char nameOfLevelChar[100] = "";
             strcpy(nameOfLevelChar, nameOfLevel.c_str());
             
             //			for(int j = 0 ; j < nameOfLevel.size(); j++)
             //			{
             //				nameOfLevelChar[j] = nameOfLevel[j];
             //			}
             
             std::ifstream citesteLevelulCurent(nameOfLevelChar);
             float a1, a2, l, d, u, r;
             std::string cacat;
             citesteLevelulCurent>>a1>>a2>>cacat>>l>>d>>u>>r;
             
             CameraExtremeDown = d + SCREEN_HEIGHT / 2.f / scaleSize;
             CameraExtremeLeft = l + SCREEN_WIDTH / 2.f / scaleSize;
             CameraExtremeUp = u - SCREEN_HEIGHT / 2.f / scaleSize;
             CameraExtremeRight = r - SCREEN_WIDTH / 2.f / scaleSize;*/
		}
		else
			if(deadScene->CosValueColorOfTheScene > 0 && deadScene->colorGoesUpOrDown == -1)
			{
				if(deadScene->CosValueColorOfTheScene < 60 && hero->theBody->GetLinearVelocity().y == 0)
				{
					hero->theBody->SetLinearVelocity(b2Vec2(0, 0.1));
					hero->theBody->ApplyLinearImpulse(b2Vec2(0, 0.1), hero->theBody->GetWorldCenter());
				}
                
				deadScene->CosValueColorOfTheScene -= 2.9f;
			}
			else
			{
				deadScene->CosValueColorOfTheScene = 0.f;
				deadScene->colorGoesUpOrDown = 0;
			}
    
	deadScene->color.a = sin(toRadians(deadScene->CosValueColorOfTheScene));
	deadScene->xCord = CameraPosition->xCord - CameraExtremeLeft;
	deadScene->yCord = CameraPosition->yCord - CameraExtremeDown;
	renderAnVboAndVaoObject(deadScene->xCord, deadScene->yCord, scaleSizeInitial, 0, 0, 0, deadScene->texture, deadScene->color, deadScene->vao, deadScene->width, deadScene->height, 0);
    
}



void BSTexture::renderLevelSceneChangeFromMenuLevels()
{
	if(deadScene->CosValueColorOfTheScene < 90 && deadScene->colorGoesUpOrDown == 1)
	{
		deadScene->CosValueColorOfTheScene += 0.9f;
	}
	else
		if(deadScene->CosValueColorOfTheScene >=90 && deadScene->colorGoesUpOrDown == 1)
		{
			//alSourcePlay(SourceSoundBeginningGame);
            
			deadScene->colorGoesUpOrDown = -1;
			deadScene->CosValueColorOfTheScene -= 1.9f;
            
            
			///Vad daca a terminat nivelul
			levelChoserPlayer->justFinished = false;
            
			addObstacle->destroyLevel();
            
			std::string nameString = "Menu Of Levels/Chapter" +
            BStoString(levelChoserPlayer->indexOfChapterThatItIsOn + 1) + "/The Levels objects/level" +
            BStoString(levelChoserPlayer->indexOfLevelThatItIsOn + 1) + ".xml";
			char nameChar[100] = "";
			strcpy(nameChar, nameString.c_str());
            
			addObstacle->incarcaHarta(nameChar);
            
			hero->theBody->SetTransform(b2Vec2(HeroInitialX, HeroInitialY), 0);
            
            
            
			///Set the extremes of the camera
			std::string nameOfLevel = "Menu Of Levels/Chapter" +
            BStoString(levelChoserPlayer->indexOfChapterThatItIsOn + 1) + "/The Levels details/level" +
            BStoString(levelChoserPlayer->indexOfLevelThatItIsOn + 1) + ".txt";
			char nameOfLevelChar[100] = "";
			strcpy(nameOfLevelChar, nameOfLevel.c_str());
            
			std::ifstream citesteLevelulCurent(nameOfLevelChar);
			float a1, a2, l, d, u, r;
			std::string cacat;
			citesteLevelulCurent>>a1>>a2>>cacat>>l>>d>>u>>r;
            
			CameraExtremeDown = d + SCREEN_HEIGHT / 2.f / scaleSize;
			CameraExtremeLeft = l + SCREEN_WIDTH / 2.f / scaleSize;
			CameraExtremeUp = u - SCREEN_HEIGHT / 2.f / scaleSize;
			CameraExtremeRight = r - SCREEN_WIDTH / 2.f / scaleSize;
            
			std::cout<<"extremes: "<<l<<" "<<d<<" "<<u<<" "<<r<<'\n';
		}
		else
			if(deadScene->CosValueColorOfTheScene > 0 && deadScene->colorGoesUpOrDown == -1)
			{
				if(deadScene->CosValueColorOfTheScene < 60 && hero->theBody->GetLinearVelocity().y == 0)
				{
					hero->theBody->SetLinearVelocity(b2Vec2(0, 0.1));
					hero->theBody->ApplyLinearImpulse(b2Vec2(0, 0.1), hero->theBody->GetWorldCenter());
				}
                
				deadScene->CosValueColorOfTheScene -= 0.9f;
			}
			else
			{
				deadScene->CosValueColorOfTheScene = 0.f;
				deadScene->colorGoesUpOrDown = 0;
			}
    
	deadScene->color.a = sin(toRadians(deadScene->CosValueColorOfTheScene));
	deadScene->xCord = CameraPosition->xCord - CameraExtremeLeft;
	deadScene->yCord = CameraPosition->yCord - CameraExtremeDown;
	renderAnVboAndVaoObject(deadScene->xCord, deadScene->yCord, scaleSizeInitial, 0, 0, 0, deadScene->texture, deadScene->color, deadScene->vao, deadScene->width, deadScene->height, 0);
    
}








void BSTexture::getTheAnimation(std::list<BSAnimation*> theList, BSNewList* listOfCurrentAnimation)// BSAnimation* &primul, int numberOfWantedAnimation)
{
	std::list<BSAnimation*>::iterator iteratorAnimations;
    
	for(iteratorAnimations = theList.begin(); iteratorAnimations != theList.end(); iteratorAnimations++)
	{
		///Daca nu a ajuns la sfarsitul listei
		if(listOfCurrentAnimation->theCurrentAnimation->indexOfAnimation + 1 != theList.size())
		{
			if((*iteratorAnimations)->indexOfAnimation == listOfCurrentAnimation->theCurrentAnimation->indexOfAnimation + 1)
			{
				listOfCurrentAnimation->theCurrentAnimation = (*iteratorAnimations);
				break;
			}
		}
		///Daca este ultima animatie din lista, atunci trece din nou la prima animatie
		else
		{
			listOfCurrentAnimation->theCurrentAnimation = theList.front();
			break;
		}
	}
    
	/*
     bool searchedAlready = false;
     BSAnimation *copie = primul;
     while(primul->animationNR != numberOfWantedAnimation)
     {
     if(primul == copie && searchedAlready)
     {
     break;
     }
     primul = primul->adresaUrmatoare;
     searchedAlready = true;
     }*/
}

void BSTexture::renderNewPlayerAnimation()//BSAnimation* &currentPlayer)
{
    ///i will pass this variable in renderAnVboAndVaoObject, if I render the berserk
    float sizeForBerserk = 0;
	
	//std::list<BSNewList*>::iterator itLista;
	float rotationSpeed = 26;
	
    ///daca a apasat a doua oara pe jump si nu s-a invartit o data
	if(pressedJumpSecond && !jumpSecondSpinned)
    {
        ///daca se misca spre dreapta
        if(hero->theBody->GetLinearVelocity().x <= 0)
        {
            ///daca se misca spre dreapta si nu s-a invartit complet
            if(jumpSecondSpinAngle >= 0 && jumpSecondSpinAngle < 360)
            {
                jumpSecondSpinAngle+=rotationSpeed;
            }
            else
                ///daca se misca spre stanga si dupa schimba directia spre dreapta
                if(jumpSecondSpinAngle < 0 && jumpSecondSpinAngle > -360)
                {
                    jumpSecondSpinAngle *= -1;
                    jumpSecondSpinAngle+=rotationSpeed;
                }
                else
					///daca a terminat rotatia
                {
                    jumpSecondSpinAngle = 0;
                    jumpSecondSpinned = true;
                }
        }
        else
            ///daca se misca spre stanga
            if(hero->theBody->GetLinearVelocity().x > 0)
            {
                ///daca se misca spre stanga si nu s-a invartit complet
                if(jumpSecondSpinAngle <= 0 && jumpSecondSpinAngle > -360)
                {
                    jumpSecondSpinAngle-=rotationSpeed;
                }
                else
                    ///daca se misca spre dreapta si dupa schimba directia spre stanga
                    if(jumpSecondSpinAngle > 0 && jumpSecondSpinAngle < 360)
                    {
                        jumpSecondSpinAngle *= -1;
                        jumpSecondSpinAngle-=rotationSpeed;
                    }
                    else
						///daca a terminat rotatia
                    {
                        jumpSecondSpinAngle = 0;
                        jumpSecondSpinned = true;
                    }
            }
    }
    else
    {
        jumpSecondSpinAngle = 0;
    }
	
	///Strabate toate listele cu animatii
    for(int i = 0 ; i < 5; i++)
    {
    	int ind = listOfActiveAnimations[i]->indexOfAnimation;
        if(listOfActiveAnimations[i]->canPlayIt)
        {
            ///for(itLista = listOfAnimations.begin(); itLista != listOfAnimations.end(); itLista++)
            {
                sizeForBerserk = 0;
                ///daca e animatie de miscare sau de berserk
                ///if((*itLista)->animationIndex == listOfActiveAnimations[i]->indexOfAnimation)
                {
                    if(i == 1 || i == 2 || i == 4)
                    {
                        sizeForBerserk = 1;
                    }
					
					
					//                    (*itLista)->playThisAnimation = true;
                    ///Daca acum incepe animatia
                    if(listOfActiveAnimations[i]->isAtStepOfAnimation1 && listOfAnimations[ind]->listForAnimations1.size())
                    {
                        nrEnding = 0;
                        listOfActiveAnimations[i]->isAtStepOfAnimation1 = false;
                        ///poate anima
                        listOfActiveAnimations[i]->canPlayAnimation1 = true;
                        ///setez inceputul animatiei (prima imagine)
                        listOfActiveAnimations[i]->theCurrentAnimation = listOfAnimations[ind]->listForAnimations1.front();
                        ///setez cat timp dureaza
                        listOfActiveAnimations[i]->theCurrentAnimation->timeToShow = (theTimeHowFast / 60) *
						listOfActiveAnimations[i]->theCurrentAnimation->timeUntilNext + SDL_GetTicks();
                    }
					
                    ///daca este la sfarsitul animatiei
                    if(listOfActiveAnimations[i]->isAtStepOfAnimation3 && listOfAnimations[ind]->listForAnimations3.size())
                    {
                        nrEnding = 0;
                        listOfActiveAnimations[i]->isAtStepOfAnimation3 = false;
                        listOfActiveAnimations[i]->canPlayAnimation3 = true;
                        ///setez inceputul sfarsitului animatiei (prima imagine din sfarsit)
                        listOfActiveAnimations[i]->theCurrentAnimation = listOfAnimations[ind]->listForAnimations3.front();
                        ///setez cat timp dureaza
                        listOfActiveAnimations[i]->theCurrentAnimation->timeToShow = (theTimeHowFast / 60) *
						listOfActiveAnimations[i]->theCurrentAnimation->timeUntilNext + SDL_GetTicks();
                    }
					
                    ///termin animatia daca jucatorul s-a oprit
                    if(hero->heroStopped && listOfActiveAnimations[i]->canPlayAnimation3 && i == 0 &&
					   listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation + 1 ==
					   listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR + listOfAnimations[ind]->thirdNR )
                    {
                        if(!nrEnding)
                        {
                            listOfActiveAnimations[i]->theCurrentAnimation = listOfAnimations[ind]->listForAnimations3.back();
                            listOfActiveAnimations[i]->theCurrentAnimation->timeToShow = (theTimeHowFast / 60) *
							listOfActiveAnimations[i]->theCurrentAnimation->timeUntilNext + SDL_GetTicks();
							
                            nrEnding++;
                        }
                        renderAnVboAndVaoObject(listOfActiveAnimations[i]->theCurrentAnimation->theSquareBodyBinded->theBody->GetPosition().x,
												listOfActiveAnimations[i]->theCurrentAnimation->theSquareBodyBinded->theBody->GetPosition().y,
												hero->zCord, jumpSecondSpinAngle, 0, 0,
												listOfActiveAnimations[i]->theCurrentAnimation->texture,
												listOfActiveAnimations[i]->theCurrentAnimation->color,
												listOfActiveAnimations[i]->theCurrentAnimation->theSquareBodyBinded->vao,
												Hero_size, Hero_size, 0);
						
                        if(nrEnding == 1 && listOfActiveAnimations[i]->theCurrentAnimation->timeToShow <= SDL_GetTicks())
                        {
							///std::cout<<nrEnding<<'\n';
                            hero->heroStopped = false;
							//                            (*itLista)->playThisAnimation = false;
                            listOfActiveAnimations[i]->canPlayAnimation3 = false;
                        }
                    }
					
                    ///Daca gaseste in lista curenta o animatie de randat
                    if(listOfActiveAnimations[i]->theCurrentAnimation->timeToShow <= SDL_GetTicks())
                    {
                        ///Daca poate desena prima animatie, si nu a ajuns la sfarsitul animatiei
                        if(listOfActiveAnimations[i]->canPlayAnimation1 && listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation < listOfAnimations[ind]->firstNR)
                        {
                            ///Daca animatia este ciclica pe prima parte
                            if(listOfAnimations[ind]->isOnLoopAnimation1)
                            {
                                getTheNextImageForAnimationInTheCycle(listOfAnimations[ind]->listForAnimations1, listOfActiveAnimations[i]->theCurrentAnimation, listOfAnimations[ind]->firstNR);
                            }
                            else
								///Daca animatia nu e ciclica pe prima parte
                            {
                                ///Daca nu a ajuns la a 2a parte a animatiei
                                if(listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation < listOfAnimations[ind]->firstNR)
                                {
                                    getTheNextImageForAnimationNOTInTheCycle(listOfAnimations[ind]->listForAnimations1, listOfAnimations[ind]->listForAnimations2,
																			 listOfActiveAnimations[i]->theCurrentAnimation, listOfAnimations[ind]->firstNR, i);
                                }
								
                                ///Daca a terminat animatia de inceput, pun animatiile urmatoare
                                if(listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation >= listOfAnimations[ind]->firstNR && listOfAnimations[ind]->secondNR)
                                {
									//                                    (*itLista)->doneAnimation1 = true;
                                    listOfActiveAnimations[i]->canPlayAnimation1 = false;
                                    ///Daca exista animatii in continuare
                                    if(listOfAnimations[ind]->secondNR > 0)
                                    {
                                        listOfActiveAnimations[i]->canPlayAnimation2 = true;
                                    }
                                    else
                                        if(listOfAnimations[ind]->thirdNR > 0)
                                        {
                                            listOfActiveAnimations[i]->canPlayAnimation3 = true;
                                        }
                                }
                                else
                                    if(listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation >= listOfAnimations[ind]->firstNR - 1 && listOfAnimations[ind]->secondNR == 0)
                                    {
										//                                        (*itLista)->doneAnimation1 = true;
                                        listOfActiveAnimations[i]->canPlayAnimation1 = false;
                                        ///Daca exista animatii in continuare
                                        if(listOfAnimations[ind]->secondNR > 0)
                                        {
                                            listOfActiveAnimations[i]->canPlayAnimation2 = true;
                                        }
                                        else
                                            if(listOfAnimations[ind]->thirdNR > 0)
                                            {
                                                listOfActiveAnimations[i]->canPlayAnimation3 = true;
                                            }
                                    }
                            }
                        }
                        else
							///Daca poate desena a 2a animatie, a terminat prima animatie si nu a ajuns la sfarsitul animatiei
							if(listOfActiveAnimations[i]->canPlayAnimation2 && listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation >= listOfAnimations[ind]->firstNR &&
							   listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation < listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR)
							{
								///Daca a ajuns in a 2a parte a animatiei
								//if(listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation >= listOfAnimations[ind]->firstNR)
								{
									///Daca a 2a parte a animatiei este ciclica
									if(listOfAnimations[ind]->isOnLoopAnimation2)
									{
										getTheNextImageForAnimationInTheCycle(listOfAnimations[ind]->listForAnimations2,
																			  listOfActiveAnimations[i]->theCurrentAnimation, listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR);
									}
									///Daca a 2a parte a animatiei NU este ciclica
									else
									{
										///Daca nu a ajuns la a 3a parte a animatiei
										if(listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation < listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR)
										{
											getTheNextImageForAnimationNOTInTheCycle(listOfAnimations[ind]->listForAnimations2,
																					 listOfAnimations[ind]->listForAnimations3,
																					 listOfActiveAnimations[i]->theCurrentAnimation,
																					 listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR, i);
										}
										///Daca a terminat a 2a animatie, pun animatiile urmatoare
										if(listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation >= listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR)
										{
											//                                        (*itLista)->doneAnimation2 = true;
											listOfActiveAnimations[i]->canPlayAnimation2 = false;
											///Daca exista animatii in continuare
											if(listOfAnimations[ind]->thirdNR)
											{
												listOfActiveAnimations[i]->canPlayAnimation3 = true;
											}
										}
									}
								}
							}
							else
								///Daca poate desena a 3a animatie, a terminat a 2a animatie si nu a ajuns la sfarsitul animatiei
								if(listOfActiveAnimations[i]->canPlayAnimation3 &&
								   listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation >= listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR &&
								   listOfActiveAnimations[i]->theCurrentAnimation->indexOfAnimation < listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR + listOfAnimations[ind]->thirdNR)
								{
									///Daca a 3a parte a animatiei este ciclica
									if(listOfAnimations[ind]->isOnLoopAnimation3)
									{
										getTheNextImageForAnimationInTheCycle(listOfAnimations[ind]->listForAnimations3,
																			  listOfActiveAnimations[i]->theCurrentAnimation,
																			  listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR + listOfAnimations[ind]->thirdNR);
									}
									///Daca a 3a parte a animatiei NU este ciclica
									else
									{
										getTheNextImageForAnimationNOTInTheCycle(listOfAnimations[ind]->listForAnimations3,
																				 listOfAnimations[ind]->listForAnimations3,
																				 listOfActiveAnimations[i]->theCurrentAnimation,
																				 listOfAnimations[ind]->firstNR + listOfAnimations[ind]->secondNR + listOfAnimations[ind]->thirdNR, i);
									}
								}
						
                        listOfActiveAnimations[i]->theCurrentAnimation->timeToShow = (theTimeHowFast / 60) *
						listOfActiveAnimations[i]->theCurrentAnimation->timeUntilNext + SDL_GetTicks();
                    }
					
					
					if(i != 3)
					{
						renderAnVboAndVaoObject(listOfActiveAnimations[i]->xCord,
												listOfActiveAnimations[i]->yCord + (sizeForBerserk / 2.0f),
												listOfActiveAnimations[i]->zCord, jumpSecondSpinAngle, 0, 0,
												listOfActiveAnimations[i]->theCurrentAnimation->texture,
												listOfActiveAnimations[i]->theCurrentAnimation->color,
												listOfActiveAnimations[i]->theCurrentAnimation->theSquareBodyBinded->vao,
												Hero_size + sizeForBerserk, Hero_size + sizeForBerserk, 0);
					}
                }
            }
        }
	}
	
	
	
}



void BSTexture::getTheNextImageForAnimationInTheCycle(std::list<BSAnimation*> theList, BSAnimation* &theCurrentImage, int nrOfImgs)
{
    if(!isPaused)
	{
	    ///==true, daca a gasit urmatoarea animatie
        bool foundTheAnimation = false;
        
        ///Daca nu a ajuns la sfarsitul listei de animatii
        if(theCurrentImage->indexOfAnimation + 1 < nrOfImgs)
        {
            ///Afisez urmatoarea animatie
            std::list<BSAnimation*>::iterator itAnim;
            
            for(itAnim = theList.begin(); itAnim != theList.end(); itAnim++)
            {
                if((*itAnim)->indexOfAnimation == theCurrentImage->indexOfAnimation + 1)
                {
                    theCurrentImage = (*itAnim);
                    foundTheAnimation = true;
                    break;
                }
            }
        }
        ///Daca a ajuns la sfarsitul animatiei, o ia de la inceput
        else
        {
            theCurrentImage = theList.front();
            foundTheAnimation = true;
        }
        
        if(!foundTheAnimation)
        {
            theCurrentImage = theList.front();
        }
	}
}


void BSTexture::getTheNextImageForAnimationNOTInTheCycle(std::list<BSAnimation*> theList1, std::list<BSAnimation*> theList2,
                                                         BSAnimation* &theCurrentImage, int nrOfImgs, int i)
{
    if(!isPaused)
	{
	    ///==true, daca a gasit urmatoarea animatie
        bool foundTheAnimation = false;
        ///Daca nu a ajuns la sfarsitul listei de animatii
        if(theCurrentImage->indexOfAnimation + 1 < nrOfImgs)
        {
            ///Afisez urmatoarea animatie
            std::list<BSAnimation*>::iterator itAnim;
            
            for(itAnim = theList1.begin(); itAnim != theList1.end(); itAnim++)
            {
                if((*itAnim)->indexOfAnimation == theCurrentImage->indexOfAnimation + 1)
                {
                    theCurrentImage = (*itAnim);
                    foundTheAnimation = true;
                    break;
                }
            }
        }
        ///Daca a ajuns la sfarsitul animatiei, o ia de la inceputul celeilalte liste
        else
        {
            if(theList1 != theList2)
            {
                theCurrentImage = theList2.front();
            }
            else
            {
                //                theListWithAnimations->doneAnimation3 = true;
                listOfActiveAnimations[i]->canPlayAnimation3 = false;
            }
            foundTheAnimation = true;
        }
        
        if(!foundTheAnimation)
        {
            theCurrentImage = theList2.front();
        }
	}
}




void BSTexture::renderWormHoles()
{
    BSColorRGBA color = {1, 1, 1, 1};
	checkCollisionsWormHoles();
	
    std::list<BSWormHole*>::iterator i;
	
    if(!listOfWormHoles.empty())
    {
		//        if(!listOfActiveAnimations[3]->canPlayIt)
		//        {
		//            listOfActiveAnimations[3]->isAtStepOfAnimation1 = true;
		//            listOfActiveAnimations[3]->isAtStepOfAnimation2 = false;
		//            listOfActiveAnimations[3]->isAtStepOfAnimation3 = false;
		//        }
		//        listOfActiveAnimations[3]->canPlayIt = true;
        for(i = listOfWormHoles.begin(); i != listOfWormHoles.end(); i++)
        {
            (*i)->value1-=4;
            if((*i)->value1 < -360)
            {
                (*i)->value1 = (*i)->value1 + 360;
            }
			//        std::cout<<(*i)->xCord<<' '<<(*i)->yCord<<"; "<<hero->theBody->GetPosition().x<<' '<<hero->theBody->GetPosition().y<<'\n';
            renderAnVboAndVaoObject((*i)->xCord, (*i)->yCord, (*i)->zCord, (*i)->value1, 0, 0,
                                    originalWormHole->texture, color, originalWormHole->vao,
                                    originalWormHole->width, originalWormHole->height, originalWormHole->depth);
        }
    }
    else
    {
        listOfActiveAnimations[3]->isAtStepOfAnimation1 = false;
        listOfActiveAnimations[3]->isAtStepOfAnimation2 = false;
        listOfActiveAnimations[3]->isAtStepOfAnimation3 = false;
        listOfActiveAnimations[3]->canPlayIt = false;
    }
}

void BSTexture::checkCollisionsWormHoles()
{
    ///daca nu se teleporteaza, si nici nu a terminat de rematerializat la destinatie
    if(!isTeleporting && lastWorm == NULL)
    {
        std::list<BSWormHole*>::iterator i;
		
        for(i = listOfWormHoles.begin(); i != listOfWormHoles.end(); i++)
        {
            ///daca a intra intr-o gaura neagra, ii caut destinatia
            if( hero->theBody->GetPosition().x - (hero->width / 8.0f) > (*i)->xCord - (originalWormHole->width / 2.0f) && ///collision body left - worm left
			   hero->theBody->GetPosition().x + (hero->width / 8.0f) < (*i)->xCord + (originalWormHole->width / 2.0f) && ///collision body right - worm right
			   hero->theBody->GetPosition().y - (hero->height / 8.0f) > (*i)->yCord - (originalWormHole->height / 2.0f) && ///collision body down - worm down
			   hero->theBody->GetPosition().y + (hero->height / 8.0f) < (*i)->yCord + (originalWormHole->height / 2.0f)) ///collision body up - worm up
            {
                std::list<BSWormHole*>::iterator j;
				
                ///look for destination
                for(j = listOfWormHoles.begin(); j != listOfWormHoles.end(); j++)
                {
                    if((*j)->indexOfWorm == (*i)->connectionIndex)
                    {
						//alSourcePlay(SourceSoundTeleport);
                        actionObj->ActionFuncTeleportHero((*j)->xCord, (*j)->yCord);
                        lastWorm = (*j);
                    }
                }
            }
        }
    }
    else
        ///daca a inceput rematerializarea, verifica daca a iesit din worm hole pentru a nu se teleporta la nesfarsit intre cele 2
        if(lastWorm != NULL && hero->animationIndexCurrentAnimation != hero->animationIndexPlayerTeleportedIn)
        {
            if( hero->theBody->GetPosition().x - (hero->width / 8.0f) > lastWorm->xCord - (originalWormHole->width / 2.0f) && ///collision body left - worm left
			   hero->theBody->GetPosition().x + (hero->width / 8.0f) < lastWorm->xCord + (originalWormHole->width / 2.0f) && ///collision body right - worm right
			   hero->theBody->GetPosition().y - (hero->height / 8.0f) > lastWorm->yCord - (originalWormHole->height / 2.0f) && ///collision body down - worm down
			   hero->theBody->GetPosition().y + (hero->height / 8.0f) < lastWorm->yCord + (originalWormHole->height / 2.0f)) ///collision body up - worm up
            {
            }
            else
            {
                lastWorm = NULL;
            }
        }
}






void BSTexture::renderTheCoin()
{
    BSColorRGBA color = {1, 1, 1, 1};
	renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft,
                            originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown,
                            originalCoin->zCord, 0, 0, 0,
							originalCoin->texture, color, originalCoin->vao, originalCoin->width, originalCoin->height, originalCoin->depth);
}


void BSTexture::renderThePauseBtn()
{
	BSColorRGBA color = {1, 1, 1, 1};
	if(backBtn->isDown == false)
	{
		renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 4 + backBtn->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, backBtn->textureUp, color, backBtn->vao, backBtn->w, backBtn->h, 0);
	}
	else
	{
		renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 4 + backBtn->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, backBtn->textureDown, color, backBtn->vao, backBtn->w, backBtn->h, 0);
	}
	
	if(btnDarkLevels->isDown == false)
	{
		if(DarkLevels)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 8 + btnDarkLevels->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnDarkLevels->textureDown, color, btnDarkLevels->vao, btnDarkLevels->w, btnDarkLevels->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 8 + btnDarkLevels->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnDarkLevels->textureUp, color, btnDarkLevels->vao, btnDarkLevels->w, btnDarkLevels->h, 0);
		}
	}
	else
	{
		if(DarkLevels)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 8 + btnDarkLevels->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnDarkLevels->textureUp, color, btnDarkLevels->vao, btnDarkLevels->w, btnDarkLevels->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 8 + btnDarkLevels->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnDarkLevels->textureDown, color, btnDarkLevels->vao, btnDarkLevels->w, btnDarkLevels->h, 0);
		}
	}
	
	if(btnTimeControl->isDown == false)
	{
		if(theTimeHowFast == 120)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 12 + btnTimeControl->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnTimeControl->textureUp, color, btnTimeControl->vao, btnTimeControl->w, btnTimeControl->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 12 + btnTimeControl->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnTimeControl->textureDown, color, btnTimeControl->vao, btnTimeControl->w, btnTimeControl->h, 0);
		}
	}
	else
	{
		if(theTimeHowFast == 120)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 12 + btnTimeControl->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnTimeControl->textureDown, color, btnTimeControl->vao, btnTimeControl->w, btnTimeControl->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 12 + btnTimeControl->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnTimeControl->textureUp, color, btnTimeControl->vao, btnTimeControl->w, btnTimeControl->h, 0);
		}
	}
    
    if(btnPowerUp1->isDown == false)
    {
		if(hero->heroIsBerserk1)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 16 + btnPowerUp1->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp1->textureUp, color, btnPowerUp1->vao, btnPowerUp1->w, btnPowerUp1->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 16 + btnPowerUp1->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp1->textureDown, color, btnPowerUp1->vao, btnPowerUp1->w, btnPowerUp1->h, 0);
		}
    }
    else
    {
		if(!hero->heroIsBerserk1)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 16 + btnPowerUp1->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp1->textureUp, color, btnPowerUp1->vao, btnPowerUp1->w, btnPowerUp1->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 16 + btnPowerUp1->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp1->textureDown, color, btnPowerUp1->vao, btnPowerUp1->w, btnPowerUp1->h, 0);
		}
    }
    
    if(btnPowerUp2->isDown == false)
    {
		if(hero->heroIsBerserk2)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 20 + btnPowerUp2->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp2->textureUp, color, btnPowerUp2->vao, btnPowerUp2->w, btnPowerUp2->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 20 + btnPowerUp2->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp2->textureDown, color, btnPowerUp2->vao, btnPowerUp2->w, btnPowerUp2->h, 0);
		}
    }
    else
    {
		if(!hero->heroIsBerserk2)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 20 + btnPowerUp2->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp2->textureUp, color, btnPowerUp2->vao, btnPowerUp2->w, btnPowerUp2->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 20 + btnPowerUp2->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp2->textureDown, color, btnPowerUp2->vao, btnPowerUp2->w, btnPowerUp2->h, 0);
		}
    }
    
    if(btnPowerUp3->isDown == false)
    {
		if(hero->heroIsBerserk3)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 24 + btnPowerUp3->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp3->textureUp, color, btnPowerUp3->vao, btnPowerUp3->w, btnPowerUp3->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 24 + btnPowerUp3->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp3->textureDown, color, btnPowerUp3->vao, btnPowerUp3->w, btnPowerUp3->h, 0);
		}
    }
    else
    {
		if(!hero->heroIsBerserk3)
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 24 + btnPowerUp3->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp3->textureUp, color, btnPowerUp3->vao, btnPowerUp3->w, btnPowerUp3->h, 0);
		}
		else
		{
			renderAnVboAndVaoObject(originalCoin->xCord + CameraPosition->xCord - CameraExtremeLeft + 24 + btnPowerUp3->w / 2.0f, originalCoin->yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, btnPowerUp3->textureDown, color, btnPowerUp3->vao, btnPowerUp3->w, btnPowerUp3->h, 0);
		}
    }
}


void BSTexture::renderMenuLevels(int nrOfLevels, ChapterLevelsStructure* theLevelsToRender[])
{
	BSColorRGBA theColorToRender;
	if(DarkLevels)
	{
		theColorToRender.r = 2;
		theColorToRender.g = 1;
		theColorToRender.b = 1;
		theColorToRender.a = 0.9f;
		//theColorToRender = theColorToRenderssss;
	}
	else
	{
		theColorToRender.r = 1;
		theColorToRender.g = 1;
		theColorToRender.b = 1;
		theColorToRender.a = 0.9f;
	}
	renderTransparentSquare(theColorToRender, SCREEN_WIDTH / 17.0f / 2.0f + CameraPosition->xCord - CameraExtremeLeft,
							SCREEN_HEIGHT / 17.0f / 2.0f + CameraPosition->yCord - CameraExtremeDown);
	
	for(int i = 0 ; i < nrOfLevels ; i++)
	{
		///First, render the connection strings
		///Daca poate pune la stanga, atunci pune
		if( (i + 1) % 5 != 0)
		{
			if(DarkLevels)
			{
				theLevelsToRender[i + 1]->color.r = 2.f;
			}
			else
			{
				theLevelsToRender[i + 1]->color.r = 1.f;
			}
			renderAnVboAndVaoObject(theLevelsToRender[i]->xCord + CameraPosition->xCord - CameraExtremeLeft +
									theLevelsToRender[i]->width / 2.f + theLevelsToRender[i]->width / 2.f,
									theLevelsToRender[i]->yCord + CameraPosition->yCord - CameraExtremeDown,
									scaleSizeInitial, 0, 0, 0,
									theLevelsToRender[0]->textureOfConnectionLeftRight,
									theLevelsToRender[i + 1]->color, theLevelsToRender[0]->vaoBufferOfConnectionLeftRight,
									theLevelsToRender[0]->widthConnectionLeftRightLevel, theLevelsToRender[0]->heightConnectionLeftRightLevel, theLevelsToRender[0]->depth);
		}
		
		if(i < 20)
		{
			if(DarkLevels)
			{
				theLevelsToRender[i + 5]->color.r = 2.f;
			}
			else
			{
				theLevelsToRender[i + 5]->color.r = 1.f;
			}
			renderAnVboAndVaoObject(theLevelsToRender[i]->xCord + CameraPosition->xCord - CameraExtremeLeft,
									theLevelsToRender[i]->yCord - theLevelsToRender[i]->height / 2.f -
									theLevelsToRender[i]->height / 2.f + CameraPosition->yCord - CameraExtremeDown,
									scaleSizeInitial, 0, 0, 0,
									theLevelsToRender[0]->textureOfConnectionUpDown,
									theLevelsToRender[i + 5]->color, theLevelsToRender[0]->vaoBufferOfConnectionUpDown,
									theLevelsToRender[0]->widthConnectionUpDownLevel,
									theLevelsToRender[0]->heightConnectionUpDownLevel, theLevelsToRender[0]->depth);
		}
	}
	
	///Randez nivelele
	for(int i = 0 ; i < nrOfLevels ; i++)
	{
		///Second, render the level images
		if(DarkLevels)
		{
			theLevelsToRender[i]->color.r = 2.f;
		}
		else
		{
			theLevelsToRender[i]->color.r = 1.f;
		}
		renderAnVboAndVaoObject(theLevelsToRender[i]->xCord + CameraPosition->xCord - CameraExtremeLeft,
                                theLevelsToRender[i]->yCord + CameraPosition->yCord - CameraExtremeDown,
                                scaleSizeInitial, 0, 0, 0,
								theLevelsToRender[0]->textureOfLevel,
								theLevelsToRender[i]->color, theLevelsToRender[i]->vaoBufferOfLevel,
								theLevelsToRender[0]->width, theLevelsToRender[0]->height, theLevelsToRender[0]->depth);
		
		if(i < 9)
		{
			renderMyFont(theLevelsToRender[i]->textOnLevel, theLevelsToRender[i]->xCord + CameraPosition->xCord - CameraExtremeLeft,
						 theLevelsToRender[i]->yCord + CameraPosition->yCord - CameraExtremeDown, 1.2f, 1.25f, theLevelsToRender[i]->color);
		}
		else
		{
			renderMyFont(theLevelsToRender[i]->textOnLevel, theLevelsToRender[i]->xCord + CameraPosition->xCord - CameraExtremeLeft - 0.4f,
						 theLevelsToRender[i]->yCord + CameraPosition->yCord - CameraExtremeDown, 1.2f, 1.25f, theLevelsToRender[i]->color);
			//theLevelsToRender[i]->xCord + CameraPosition->xCord - CameraExtremeLeft - letters[char((i + 1) / 10 % 10)]->widthOfLetterOnScreen / 2 * 1.2f,
		}
		
		if(theLevelsToRender[i]->isFinished)
		{
			if(DarkLevels)
			{
				theLevelsToRender[0]->color.r = 2.f;
			}
			else
			{
				theLevelsToRender[0]->color.r = 1.f;
			}
			renderAnVboAndVaoObject(theLevelsToRender[i]->xCord+ CameraPosition->xCord - CameraExtremeLeft,
                                    theLevelsToRender[i]->yCord + CameraPosition->yCord - CameraExtremeDown,
                                    scaleSizeInitial, 0, 0, 0,
									theLevelsToRender[0]->textureOfFinishedLevel,
									theLevelsToRender[0]->color, theLevelsToRender[0]->vaoBufferOfFinishedLevel,
									theLevelsToRender[0]->width, theLevelsToRender[0]->height, theLevelsToRender[0]->depth);
		}
	}
	
	
	///Randez animatia cu care ma voi misca prin nivele
	renderAnVboAndVaoObject(levelChoserPlayer->xCord+ CameraPosition->xCord - CameraExtremeLeft,
							levelChoserPlayer->yCord + CameraPosition->yCord - CameraExtremeDown,
							scaleSizeInitial, 0, 0, 0, levelChoserPlayer->texture, levelChoserPlayer->color,
							levelChoserPlayer->vao, levelChoserPlayer->width, levelChoserPlayer->height,
							levelChoserPlayer->depth);
	
	theLevelMenuPlayer->walkThroughLevels(0, 0, theLevelsToRender);
}


void BSTexture::renderMenuChapters()
{
	BSColorRGBA theColorToRender = { 1.f, 1.f, 1.f, 0.9f };
	renderTransparentSquare(theColorToRender, SCREEN_WIDTH / 17.0f / 2.0f + CameraPosition->xCord - CameraExtremeLeft,
							SCREEN_HEIGHT / 17.0f / 2.0f + CameraPosition->yCord - CameraExtremeDown);
	
	
	for(int i = 0 ; i < nrOfChapters - 1 ; i++)
	{
		int indexulUrmatoruluiNivel = 0;
		///First, render the connection strings
		///Daca poate pune la stanga, atunci pune
		float sizeOfConnectionStringX = 0, sizeOfConnectionStringY = 0;
		
		if(i + 1 < nrOfChapters)//( (i + 1) % 5 != 0)
		{
			indexulUrmatoruluiNivel = i + 1;
			sizeOfConnectionStringX = abs(chaptere[i]->xCord - chaptere[i+1]->xCord) - chaptere[i]->width;
			sizeOfConnectionStringY = abs(chaptere[i]->yCord - chaptere[i+1]->yCord) - chaptere[i]->height;
		}
		else
		{
			indexulUrmatoruluiNivel = 0;
			sizeOfConnectionStringX = abs(chaptere[i]->xCord - chaptere[0]->xCord) - chaptere[i]->width;
			sizeOfConnectionStringY = abs(chaptere[i]->yCord - chaptere[0]->yCord) - chaptere[i]->height;
		}
		
		///Daca este mai la dreapta
		if(chaptere[indexulUrmatoruluiNivel]->xCord > chaptere[i]->xCord)
		{
			renderAnVboAndVaoObject(chaptere[i]->xCord + CameraPosition->xCord - CameraExtremeLeft + chaptere[i]->width / 2.f + sizeOfConnectionStringX / 2.f + 0.1,
									chaptere[i]->yCord + CameraPosition->yCord - CameraExtremeDown,
									scaleSizeInitial, 0, 0, 0,
									chaptere[0]->levelFromChapter[0]->textureOfConnectionLeftRightChapter,
									chaptere[indexulUrmatoruluiNivel]->color,
									chaptere[0]->levelFromChapter[0]->vaoBufferOfConnectionLeftRightChapter,
									chaptere[0]->levelFromChapter[0]->widthConnectionLeftRightChapter,
									chaptere[0]->levelFromChapter[0]->heightConnectionLeftRightChapter, 0);
		}
		else
			
			///Daca este mai la stanga
			if(chaptere[indexulUrmatoruluiNivel]->xCord < chaptere[i]->xCord)
			{
				renderAnVboAndVaoObject(chaptere[i]->xCord + CameraPosition->xCord - CameraExtremeLeft - chaptere[i]->width / 2.f - sizeOfConnectionStringX / 2.f - 0.12,
										chaptere[i]->yCord + CameraPosition->yCord - CameraExtremeDown,
										scaleSizeInitial, 0, 0, 0,
										chaptere[0]->levelFromChapter[0]->textureOfConnectionLeftRightChapter,
										chaptere[indexulUrmatoruluiNivel]->color,
										chaptere[0]->levelFromChapter[0]->vaoBufferOfConnectionLeftRightChapter,
										chaptere[0]->levelFromChapter[0]->widthConnectionLeftRightChapter,
										chaptere[0]->levelFromChapter[0]->heightConnectionLeftRightChapter, 0);
			}
			else
				
				///Daca este mai jos
				if(chaptere[indexulUrmatoruluiNivel]->yCord < chaptere[i]->yCord)
				{
					renderAnVboAndVaoObject(chaptere[i]->xCord + CameraPosition->xCord - CameraExtremeLeft,
											chaptere[i]->yCord + chaptere[i]->height / 2.f - sizeOfConnectionStringY / 2.f + 0.2 + CameraPosition->yCord - CameraExtremeDown,
											scaleSizeInitial, 0, 0, 0,
											chaptere[0]->levelFromChapter[0]->textureOfConnectionUpDownChapter,
											chaptere[indexulUrmatoruluiNivel]->color,
											chaptere[0]->levelFromChapter[0]->vaoBufferOfConnectionUpDownChapter,
											chaptere[0]->levelFromChapter[0]->widthConnectionUpDownChapter,
											chaptere[0]->levelFromChapter[0]->heightConnectionUpDownChapter, 0);
				}
				else
					
					///Daca este mai sus
					if(chaptere[indexulUrmatoruluiNivel]->yCord > chaptere[i]->yCord)
					{
						renderAnVboAndVaoObject(chaptere[i]->xCord + CameraPosition->xCord - CameraExtremeLeft,
												chaptere[i]->yCord + chaptere[i]->height / 2.f + sizeOfConnectionStringY / 2.f + CameraPosition->yCord - CameraExtremeDown,
												scaleSizeInitial, 0, 0, 0,
												chaptere[0]->levelFromChapter[0]->textureOfConnectionUpDownChapter,
												chaptere[indexulUrmatoruluiNivel]->color,
												chaptere[0]->levelFromChapter[0]->vaoBufferOfConnectionUpDownChapter,
												chaptere[0]->levelFromChapter[0]->widthConnectionUpDownChapter,
												chaptere[0]->levelFromChapter[0]->heightConnectionUpDownChapter, 0);
					}
		
	}
	
	///Randez chapterele
	for(int i = 0 ; i < nrOfChapters ; i++)
	{
		///Second, render the level images
		renderAnVboAndVaoObject(chaptere[i]->xCord + CameraPosition->xCord - CameraExtremeLeft,
								chaptere[i]->yCord + CameraPosition->yCord - CameraExtremeDown,
								scaleSizeInitial, 0, 0, 0,
								chaptere[i]->texture,
								chaptere[i]->color,
								chaptere[i]->vao,
								chaptere[i]->width, chaptere[i]->height, chaptere[i]->depth);
		
		if(chaptere[i]->isFinishedChapter)
		{
			renderAnVboAndVaoObject(chaptere[i]->xCord+ CameraPosition->xCord - CameraExtremeLeft,
									chaptere[i]->yCord + CameraPosition->yCord - CameraExtremeDown,
									scaleSizeInitial, 0, 0, 0,
									chaptere[0]->levelFromChapter[0]->textureOfFinishedLevel,
									chaptere[0]->levelFromChapter[0]->color,
									chaptere[0]->levelFromChapter[0]->vaoBufferOfFinishedLevel, 0, 0, 0);
		}
	}
	
	///Randez animatia cu care ma voi misca prin nivele
	renderAnVboAndVaoObject(levelChoserPlayer->xCord + CameraPosition->xCord - CameraExtremeLeft,
							levelChoserPlayer->yCord + CameraPosition->yCord - CameraExtremeDown,
							scaleSizeInitial, 0, 0, 0,
							levelChoserPlayer->texture, levelChoserPlayer->color, levelChoserPlayer->vao,
							levelChoserPlayer->width, levelChoserPlayer->height, levelChoserPlayer->depth);
	
	theLevelMenuPlayer->walkThroughChapters(0, 0);
}




float mesF = 0;

void BSTexture::renderMessages()
{
	ifCollideWithMessage();
    
	if(nrOfMessageSign)
	{
		for(std::list<BSTheMessages*>::iterator i = listOfMessages.begin(); i != listOfMessages.end(); i++)
		{
			///Randez semnul
			renderAnVboAndVaoObject((*i)->xCord, (*i)->yCord, (*i)->zCord, 0, 0, 0, (*i)->textureOfSign, (*i)->colorOfSign, (*i)->vaoBufferOfSign, (*i)->widthOfSign, (*i)->heightOfSign, 0);
            
			///Randez mesajul daca este afisat
			if((*i)->isShownTheMessage)
			{
				///Il fac opac
				if((*i)->colorOfMessage.a < 0.9f)
				{
					//mesF++;
					(*i)->colorOfMessage.a += 0.04f;
				}
				else
				{
					(*i)->colorOfMessage.a = 0.9f;
				}
				//(*i)->colorOfMessage.a = sin(toRadians(mesF));
				//std::cout<<(*i)->colorOfMessage.a<<'\n';
				renderAnVboAndVaoObject((*i)->xCord + (*i)->widthOfMessage / 2.f, (*i)->yCord + (*i)->heightOfMessage / 2.f + (*i)->heightOfSign / 2.f + 0.2f, (*i)->zCord, 0, 0, 0, (*i)->textureOfMessage, (*i)->colorOfMessage, (*i)->vaoBufferOfMessage, (*i)->widthOfMessage, (*i)->heightOfMessage, 0);
			}
			else
			{
				///Il fac transparent
				if((*i)->colorOfMessage.a > 0.f)
				{
					(*i)->colorOfMessage.a -= 0.04;
                    
					renderAnVboAndVaoObject((*i)->xCord + (*i)->widthOfMessage / 2.f, (*i)->yCord + (*i)->heightOfMessage / 2.f + (*i)->heightOfSign / 2.f + 0.2f, (*i)->zCord, 0, 0, 0, (*i)->textureOfMessage, (*i)->colorOfMessage, (*i)->vaoBufferOfMessage, (*i)->widthOfMessage, (*i)->heightOfMessage, 0);
				}
				else
				{
					(*i)->colorOfMessage.a = 0.f;
				}
			}
		}
	}
}

void BSTexture::ifCollideWithMessage()
{
	if(nrOfMessageSign)
	{
		std::list<BSTheMessages*>::iterator i;
        
		for(i = listOfMessages.begin(); i != listOfMessages.end(); i++)
		{
			///if is colliding
			//primele 2 linii - coliziune la stanga
			//urmatoarele 2 linii - coliziune la dreapta
			//urmatoarele 2 linii - coliziune sus/jos
			//urmatoarele 2 linii - coliziune sus/jos
			if(( (hero->theBody->GetPosition().x + hero->width / 2.f >= (*i)->xCord - (*i)->widthOfSign / 2.f &&
                  hero->theBody->GetPosition().x + hero->width / 2.f <= (*i)->xCord + (*i)->widthOfSign / 2.f) ||
                (hero->theBody->GetPosition().x - hero->width / 2.f <= (*i)->xCord + (*i)->widthOfSign / 2.f &&
                 hero->theBody->GetPosition().x - hero->width / 2.f >= (*i)->xCord - (*i)->widthOfSign / 2.f) )
               &&
               ((hero->theBody->GetPosition().y + hero->height / 2.f >= (*i)->yCord - (*i)->heightOfSign / 2.f &&
                 hero->theBody->GetPosition().y + hero->height / 2.f <= (*i)->yCord + (*i)->heightOfSign / 2.f) ||
                (hero->theBody->GetPosition().y - hero->height / 2.f <= (*i)->yCord + (*i)->heightOfSign / 2.f &&
                 hero->theBody->GetPosition().y - hero->height / 2.f >= (*i)->yCord - (*i)->heightOfSign / 2.f)))
			{
				(*i)->isShownTheMessage = true;
			}
			else
			{
				(*i)->isShownTheMessage = false;
			}
		}
	}
}









void BSTexture::renderTransparentSquare(BSColorRGBA theColorToRenders, float coordinateX, float coordinateY)
{
	//    std::cout<<coordinateX<<' '<<coordinateY<<'\n';
	renderAnVboAndVaoObject(coordinateX, coordinateY, scaleSizeInitial, 0, 0, 0, NULL,
							theColorToRenders, originalTransparentMenu->vao,
							originalTransparentMenu->width, originalTransparentMenu->height, originalTransparentMenu->depth);
}

void BSTexture::renderAnyButtons(BSMenuStructure *theMenu)
{
	setTheValuesForShaders();
	
	//Rnder The Background with an alpha black
	theColorToRender.r = 1;
	theColorToRender.g = 1;
	theColorToRender.b = 1;
	theColorToRender.a = 0.9f;
	
	renderTransparentSquare(theColorToRender, SCREEN_WIDTH / 17.0f / 2.0f + CameraPosition->xCord - CameraExtremeLeft,
							SCREEN_HEIGHT / 17.0f / 2.0f + CameraPosition->yCord - CameraExtremeDown);
	
	theTextureToRender = NULL;
	theColorToRender.r = 1;
	theColorToRender.g = 1;
	theColorToRender.b = 1;
	theColorToRender.a = 1;
	
	std::list<BSButtonStructure*>::iterator iteratorButoane;
	
	for(iteratorButoane = theMenu->listOfButtons.begin();
		iteratorButoane != theMenu->listOfButtons.end(); iteratorButoane++)
	{
		float whRatio = (float)(currentButton->height / currentButton->width);
		float newW = (float) currentButton->width + 1 + sin(toRadians(currentButton->value1));
		float newH = (float) currentButton->height + (1 + sin(toRadians(currentButton->value2))) * whRatio;
        if((*iteratorButoane) == currentButton && (currentMenu->indexOfMenu != 2 || (currentMenu->indexOfMenu == 2 && currentButton->indexOfButton != 0 && currentButton->indexOfButton != 1)))
        {
            currentButton->value1 += 5;
		    currentButton->value2 += 5;
			
		    if(currentButton->value1 > 360 && currentButton->value2 > 360)
            {
                currentButton->value1 = currentButton->value1 - 360;
                currentButton->value2 = currentButton->value2 - 360;
            }
        }
		
		if((*iteratorButoane) == currentButton)
		{
			renderAnVboAndVaoObject(currentButton->xCord + CameraPosition->xCord - CameraExtremeLeft,//CameraPosition->xCord - CameraExtremeLeft,
                                    currentButton->yCord + CameraPosition->yCord - CameraExtremeDown,//CameraPosition->yCord - CameraExtremeDown,
                                    scaleSizeInitial, 0, 0, 0,
									currentButton->textureOfButtons[1], currentButton->color, currentButton->vaoOfButtons[1],
									newW, newH, currentButton->depth);
		}
		else
		{
			renderAnVboAndVaoObject((*iteratorButoane)->xCord + CameraPosition->xCord - CameraExtremeLeft,//CameraPosition->xCord - CameraExtremeLeft,
									(*iteratorButoane)->yCord + CameraPosition->yCord - CameraExtremeDown,//CameraPosition->yCord - CameraExtremeDown,
                                    scaleSizeInitial, 0, 0, 0,
									(*iteratorButoane)->textureOfButtons[0],
									(*iteratorButoane)->color,
									(*iteratorButoane)->vaoOfButtons[0],
									(*iteratorButoane)->width, (*iteratorButoane)->height, (*iteratorButoane)->depth);
		}
		
		if(currentMenu->indexOfMenu == 2)
		{
			std::list<BSButtonStructure*>::iterator i;
			
			for(i = theMenu->listOfButtons.begin(); i != theMenu->listOfButtons.end(); i++)
			{
				if((*i)->indexOfButton == 0)
				{
					renderSoundAnimation((*i)->yCord, newVolumeAudio);
				}
				else
					if((*i)->indexOfButton == 1)
					{
						renderSoundAnimation((*i)->yCord, newVolumeSFX);
					}
					else
					{
						break;
					}
			}
		}
	}
	
}





void BSTexture::renderSoundAnimation(float yCord, float theVolume)
{
	setTheValuesForShaders();
    
	for(int i = 0 ; i < theVolume * 10 ; i++)
	{
		renderAnVboAndVaoObject(SoundButtonTexture->xCord + CameraPosition->xCord - CameraExtremeLeft + Hero_size * i + 1 + 0.25 * i - 4, yCord + CameraPosition->yCord - CameraExtremeDown, scaleSizeInitial, 0, 0, 0, SoundButtonTexture->texture, SoundButtonTexture->color,SoundButtonTexture->vao, 1, 1, 0);
	}
}






void BSTexture::renderBackgroundNo1()
{
	//    float val1 = (float) (gameBoundLeft + gameBoundRight) / 2,
	//            val2 = (float) (gameBoundLeft + gameBoundRight) / 2,
	//            val3 = (float) gameBoundLeft + 3,
	//            val4 = (float) gameBoundRight - 3;
	
    float val1 = 25,
	val2 = 25,
	val3 = 3,
	val4 = 47;
    backgroundSky->xCord = val1;
    backgroundMountain->xCord = val2;
    backgroundBush->xCord = val3;
    backgroundHighField->xCord = val4;
	
	
	//    float val11 = (float) (gameBoundDown + gameBoundUp) / 2,
	//            val21 = (float) gameBoundDown + 18,
	//            val31 = (float) gameBoundDown + 17,
	//            val41 = (float) gameBoundDown + 18;
	
    float val11 = 20,
	val21 = 18,
	val31 = 17,
	val41 = 18;
	
    backgroundSky->yCord = val11;
    backgroundMountain->yCord = val21;
    backgroundBush->yCord = val31;
    backgroundHighField->yCord = val41;
	
	
	renderAnVboAndVaoObject(backgroundSky->xCord, backgroundSky->yCord, -100, 0, 0, 0,
							backgroundSky->texture, backgroundSky->color,
							backgroundSky->vao,
							4.4f * backgroundSky->width,
							6 * backgroundSky->height, 0);
	
	renderAnVboAndVaoObject(backgroundMountain->xCord, backgroundMountain->yCord, -80, 0, 0, 0,
							backgroundMountain->texture, backgroundMountain->color,
							backgroundMountain->vao,
							4 * backgroundMountain->width,
							5 * backgroundMountain->height, 0);
	
	renderAnVboAndVaoObject(backgroundBush->xCord, backgroundBush->yCord, -60, 0, 0, 0,
							backgroundBush->texture, backgroundBush->color,
							backgroundBush->vao,
							4 * backgroundBush->width,
							4 * backgroundBush->height, 0);
	
	renderAnVboAndVaoObject(backgroundHighField->xCord, backgroundHighField->yCord, -40, 0, 0, 0,
							backgroundHighField->texture, backgroundHighField->color,
							backgroundHighField->vao,
							3 * backgroundHighField->width,
							3 * backgroundHighField->height, 0);
	
	
}





void BSTexture::renderAnVboAndVaoObject(float coordX, float coordY, float coordZ,
                                        float angleX, float angleY, float angleZ,
                                        GLuint theTextureIdToRender, BSColorRGBA theColorOfObstacle,
                                        GLuint theVaoBuffer, float ScaleOnX, float ScaleOnY, float ScaleOnZ)
{
    glm::vec3 m_position = glm::vec3(CameraPosition->xCord, CameraPosition->yCord, -CameraPosition->zCord);
    glm::vec3 m_direction = glm::vec3(0, 0, -10);
    glm::vec3 m_up = glm::vec3(0, 1, 0);
    
    BSModelViewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
    
	BSModelViewMatrix = glm::translate( coordX, coordY, coordZ ) * BSModelViewMatrix;
	
	BSModelViewMatrix = BSModelViewMatrix * glm::rotate( angleX, 0.0f, 0.0f, 1.0f );
	BSModelViewMatrix = BSModelViewMatrix * glm::rotate( angleY, 0.0f, 1.0f, 0.0f );
	BSModelViewMatrix = BSModelViewMatrix * glm::rotate( angleZ, 1.0f, 0.0f, 0.0f );
	
	if(ScaleOnX == 0)
	{
		ScaleOnX = 1;
	}
	if(ScaleOnY == 0)
	{
		ScaleOnY = 1;
	}
	BSModelViewMatrix = BSModelViewMatrix * glm::scale( ScaleOnX, ScaleOnY, 0.0f );
    
	glUniformMatrix4fv(locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr( BSModelViewMatrix ) );
	glUniform4f(locationBSTextureColor, theColorOfObstacle.r, theColorOfObstacle.g, theColorOfObstacle.b, theColorOfObstacle.a);
	
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, theTextureIdToRender);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	
    
	glBindVertexArrayOES(theVaoBuffer);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, 0);
	glBindVertexArrayOES(NULL);
}


void BSTexture::renderANormalVboAndVaoObject(float coordX, float coorY, GLuint theTextureIdToRender,
                                             BSColorRGBA theColorOfObstacle, GLuint theVaoBuffer, float ScaleOnX, float ScaleOnY)
{
	glUniform1f(ShaderScaleOnX, ScaleOnX);
	glUniform1f(ShaderScaleOnY, ScaleOnY);
    
	if(theTextureIdToRender == NULL)
	{
		theTextureIdToRender = blankTexture;
	}
    
	glBindTexture(GL_TEXTURE_2D, theTextureIdToRender);
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
	//daca este patratul randat la coordonatele mouseului
    
	glUniform1f(ShaderIsTheSquare, 0);
    
    
	//Reset transformations
	//bTexturedPolygonProgram2D->setModelView( glm::mat4() );
	//bTexturedPolygonProgram2D->leftMultModelView( glm::translate( coordX * scaleSize, coorY * scaleSize, 0.f ) );
    
    //bTexturedPolygonProgram2D->updateModelView(false);
    
    
    
	//render a color or a texture
	//bTexturedPolygonProgram2D->setTextureColor( theColorOfObstacle );
    
	//bind the VAO buffer, and draw the objects
	glBindVertexArrayOES( theVaoBuffer );
	glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
	glBindVertexArrayOES(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}





void BSTexture::loadTextures()
{
	/*	int channels = 0, width, height;
	 unsigned char* image = SOIL_load_image
	 (
     "texture.png",
     &width, &height, &channels,
     SOIL_LOAD_AUTO
     );
	 
	 texture = SOIL_create_OGL_texture
	 (
     image,
     width, height, channels,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
	 
	 glBindTexture(GL_TEXTURE_2D, texture);
	 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR );
	 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR );
	 */
	loadATexture("whiteImage.png", whiteTexture);
	
	loadATexture("blank.png", blankTexture);
	
	loadATexture("texture.png", texture);
	
	loadATexture("Animations/roundAnimation/windmillPropeller.png", textureMill);
	
	loadATexture("playerTexture.png", playerTexture);
	
	loadATexture("playerTexture round.png", playerTextureRound);
	
	loadATexture("playerTexture Dead.png", playerTextureDead);
	
	loadATexture("background.png", backgroundTexture);
	
}


//void BSTexture::loadATexture(std::string name, GLuint &theTextureId)
//{
//OpenGLView *v;// = new OpenGLView();
//theTextureId = [(id) obj
//v.loadATexture(name, theTextureId);// getTexture:name];
/*const char *nameChar = name.c_str();
 
 theTextureId = SOIL_load_OGL_texture
 (
 nameChar,
 SOIL_LOAD_AUTO,
 SOIL_CREATE_NEW_ID,
 SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
 );
 
 glBindTexture(GL_TEXTURE_2D, theTextureId);
 
 //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
 
 if(!theTextureId)
 {
 std::cout<<"texture NOT loaded successfully: "<<name<<'\n';
 }
 */
//}

UIImage* loadNewTexture(NSString *path, NSString *name)
{
	return [[UIImage alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:name ofType:@"png" inDirectory:path]];
}



void BSTexture::getTextureWidthAndHeight(char names[], int &width, int &height)
{
	std::string name = BStoString(names);
	int i = name.size() - 1;
	while(i >= 0 && name[i] != '/')
	{
		i--;
	}
	
	UIImage *img;
	std::string newP = "", newN = "";
	if(i == -1)
	{
		for(int j = 0 ; j < name.size() - 4; j++)
		{
			newN += name[j];
		}
		NSString *fileName = [NSString stringWithCString:newN.c_str()
												encoding:[NSString defaultCStringEncoding]];
		img = loadNewTexture(@"", fileName);
	}
	else
	{
		for(int j = 0 ; j < i; j++)
		{
			newP += name[j];
		}
		if(newP.find("\n") != std::string::npos)
		{
			std::cout<<"da"<<'\n';
		}
		for(int j = i + 1 ; j < name.size() - 4; j++)
		{
			newN += name[j];
		}
		NSString *fileName = [NSString stringWithCString:newN.c_str()
												encoding:[NSString defaultCStringEncoding]];
		NSString *filePath = [NSString stringWithCString:newP.c_str()
												encoding:[NSString defaultCStringEncoding]];
		
		img = loadNewTexture(filePath, fileName);
	}
	
    CGImageRef spriteImage = img.CGImage;
    if (!spriteImage) {
		std::cout<<"Failed to load image:"<<newP<<"; "<<newN<<'\n';
        //exit(1);
		return;
    }
    
    width = CGImageGetWidth(spriteImage);
    height = CGImageGetHeight(spriteImage);
	
	
	/*
	 int channels = 0;
	 unsigned char* image = SOIL_load_image
	 (
     name,
     &width, &height, &channels,
     SOIL_LOAD_AUTO
     );
	 */
}




void BSTexture::loadMenuButtonsTexture(int numberOfButtons, std::string pathAndName, GLuint theButtonsTexture[])
{
	/*
	 for(int  i = 0 ; i < numberOfButtons ; i ++)
	 {
	 std::string TextureName = pathAndName + BStoString(i+1) +".png";
	 
	 char TextureName2[100];
	 
	 for(int j = 0; j <=TextureName.size(); j++)
	 {
	 TextureName2[j] = TextureName[j];
	 }
	 
	 theButtonsTexture[i] = SOIL_load_OGL_texture
	 (
	 TextureName2,
	 SOIL_LOAD_RGBA,
	 SOIL_CREATE_NEW_ID,
	 SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	 );
	 }*/
}



float BSTexture::toRadians(float x)
{
	float pi = 3.1415;
	return (float) (pi/2 * x)/90;
}


void writeToFile()
{
	char *saves = "abcd";
	NSData *data = [[NSData alloc] initWithBytes:saves length:4];
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSString *appFile = [documentsDirectory stringByAppendingPathComponent:@"Animations/text.txt"];
	[data writeToFile:appFile atomically:YES];
}


void BSTexture::initTheFont()
{
	//	std::ifstream date("Animations/Font/detaliiFont.txt");
	
	BSXmlFiles *doc = new BSXmlFiles();
	char theNodesNew[6][100];
	ListaDeCaractere *levelDetailsNew[1000];
	
	strcpy(theNodesNew[0], "imagePath");
	strcpy(theNodesNew[1], "n");
	strcpy(theNodesNew[2], "x");
	strcpy(theNodesNew[3], "y");
	strcpy(theNodesNew[4], "w");
	strcpy(theNodesNew[5], "h");
	
	doc->readAnyXML("Animations/Font/dataOfFont.xml", "TextureAtlas", "sprite", levelDetailsNew, NULL, theNodesNew, NULL, 0, 6);
	
	
	int i = 0;
	
	letters[0] = new BSTheFontLetters;
	
	while(levelDetailsNew[i])
	{
		char let = levelDetailsNew[i]->theCharArray2DAttributes[1][0];
		
		letters[let] = new BSTheFontLetters;
		
		letters[let]->nameOfLetterCapsLockOn = levelDetailsNew[i]->theCharArray2DAttributes[1][0];
		letters[let]->xCordInImage = atof(levelDetailsNew[i]->theCharArray2DAttributes[2]);
		letters[let]->yCordInImage = atof(levelDetailsNew[i]->theCharArray2DAttributes[3]);
		letters[let]->widthOfLetterInImage = atof(levelDetailsNew[i]->theCharArray2DAttributes[4]);
		letters[let]->heightOfLetterInImage = atof(levelDetailsNew[i]->theCharArray2DAttributes[5]);
		
		//		letters[let]->widthOfLetterOnScreen = (float) letters[let]->widthOfLetterInImage / letters[let]->heightOfLetterInImage;
		//		letters[let]->heightOfLetterOnScreen = 1;//letters[let]->widthOfLetterInImage / letters[let]->heightOfLetterInImage;
		
		letters[let]->widthOfLetterOnScreen = (float) letters[let]->widthOfLetterInImage / letters[let]->heightOfLetterInImage;
		letters[let]->heightOfLetterOnScreen = 1;
		
		letters[let]->xRatio = (double) letters[let]->widthOfLetterInImage / 1000;
		letters[let]->yRatio = (double) letters[let]->heightOfLetterInImage / 1000;
		
		if(!i)
		{
			loadATexture("Animations/Font/dataOfFont.png", letters[0]->texture);
		}
		
		letters[let]->color.r = 0;
		letters[let]->color.g = 0;
		letters[let]->color.b = 0;
		letters[let]->color.a = 1;
		
		addObstacle->setTheVaoDataForFont(letters[let]->data, letters[let]->widthOfLetterInImage, letters[let]->heightOfLetterInImage, letters[let]->xCordInImage, letters[let]->yCordInImage, letters[let]->vao, letters[let]->vbo, letters[let]->ibo);
		
		//setTheVao(letters[let]->vao, letters[let]->data, letters[let]->vbo, letters[let]->ibo);
		
		i++;
	}
	
	NrOfTotalLetters = i;
	std::cout<<"initialized font"<<'\n';
}

void BSTexture::renderMyFont(std::string theStringToRenderString, float xCord, float yCord, float FontSizeX, float FontSizeY,
							 BSColorRGBA color)
{
	float lastWidth = 0, lastX = 0;
	BSColorRGBA newColor = color;
	
	///Parcurg toate literele sirului randat
	for(int i = 0 ; i < theStringToRenderString.size() ; i++)
	{
		if(letters[theStringToRenderString[i]] || theStringToRenderString[i] == ' ')
		{
			float xSize = FontSizeX, ySize = FontSizeY, newWidth = 1, newY = yCord, pozNou = 0;
			char let = theStringToRenderString[i];
			newColor = color;
			
			//if it is a letter or a number
			if( (theStringToRenderString[i] >= 'a' && theStringToRenderString[i] <= 'z') || (theStringToRenderString[i] >= 'A' && theStringToRenderString[i] <= 'Z') || (theStringToRenderString[i] >= '0' && theStringToRenderString[i] <= '9'))
			{
				newColor = color;
				newWidth = letters[theStringToRenderString[i]]->widthOfLetterOnScreen;
			}
			else
				if(theStringToRenderString[i] == ' ')
				{
					let = 'a';
					newWidth = letters['a']->widthOfLetterOnScreen;
					newColor.r = 1;
					newColor.g = 1;
					newColor.b = 1;
					newColor.a = 0;
				}
				else
					if(theStringToRenderString[i] == '.')
					{
						xSize = FontSizeX / 5.0f;
						ySize = FontSizeY / 5.0f;
						newWidth = letters[theStringToRenderString[i]]->widthOfLetterOnScreen / 5.0f;
						newY = yCord - FontSizeY / 2.0f + 0.1f;
					}
					else
						if(theStringToRenderString[i] == ',')
						{
							xSize = FontSizeX / 3.0f;
							ySize = FontSizeY / 5.0f;
							newWidth = letters[theStringToRenderString[i]]->widthOfLetterOnScreen / 5.0f;
							newY = yCord - FontSizeY / 2.0f + 0.1f;
						}
						else
							if(theStringToRenderString[i] == ';' || theStringToRenderString[i] == ':')
							{
								xSize = FontSizeX / 2.0f;
								ySize = FontSizeY / 1.4f;
								newWidth = letters[theStringToRenderString[i]]->widthOfLetterOnScreen / 2.0f;
								newY = yCord - FontSizeY / 2.0f + 0.1f;
							}
			if(!i)
			{
				pozNou = xCord;
			}
			else
			{
				pozNou = (float) lastX + (newWidth + lastWidth ) * FontSizeX / 2.f + 0.1f;
			}
			lastX = pozNou;
			lastWidth = newWidth;
			
			renderAnVboAndVaoObject(pozNou, newY, scaleSizeInitial, 0, 0, 0, letters[0]->texture, newColor, letters[let]->vao, xSize, ySize, 0);
		}
	}
}



bool BSTexture::coinIsInBounds(BSCoins *theCoin)
{
	if(( (hero->theBody->GetPosition().x + hero->width / 2.f >= theCoin->xCord - theCoin->width / 2.f &&
          hero->theBody->GetPosition().x + hero->width / 2.f <= theCoin->xCord + theCoin->width / 2.f) ||
        (hero->theBody->GetPosition().x - hero->width / 2.f <= theCoin->xCord + theCoin->width / 2.f &&
         hero->theBody->GetPosition().x - hero->width / 2.f >= theCoin->xCord - theCoin->width / 2.f) )
       &&
       ((hero->theBody->GetPosition().y + hero->height / 2.f >= theCoin->yCord - theCoin->height / 2.f &&
         hero->theBody->GetPosition().y + hero->height / 2.f <= theCoin->yCord + theCoin->height / 2.f) ||
        (hero->theBody->GetPosition().y - hero->height / 2.f <= theCoin->yCord + theCoin->height / 2.f &&
         hero->theBody->GetPosition().y - hero->height / 2.f >= theCoin->yCord - theCoin->height / 2.f)))
    {
		return true;
    }
    
    return false;
}



void BSTexture::renderSnowFlakes()
{
	float maximX = gameBoundRight;//CameraExtremeRight + (SCREEN_WIDTH / scaleSize / 2.0f);
	float minimX = gameBoundLeft;//CameraExtremeLeft - (SCREEN_WIDTH / scaleSize / 2.0f);
	
	float maximY = gameBoundUp;//CameraExtremeUp + (SCREEN_HEIGHT / scaleSize / 2.0f);
	float minimY = gameBoundDown;//CameraExtremeDown - (SCREEN_HEIGHT / scaleSize / 4.0f);
	
	glUniform1f(ShaderFlake, 1);
	glUniform1f(ShaderIsCircle, 1);
	BSColorRGBA color = {0, 0, 0, 1};
	
	glUniform1f(ShaderCircleRadius, 0.4f);
	
	std::list<BSSnowFlakes*>::iterator it;
	for(it = listOfSnowFlakes.begin(); it != listOfSnowFlakes.end(); it++)
	{
		//		if((*it)->sinValue < 90)
		//		{
		//			(*it)->sinValue += 0.1f;
		//			(*it)->color.a = sin(toRadians((*it)->sinValue));
		//		}
		//		else
		//		{
		//			(*it)->sinValue = 90;
		//			(*it)->color.a = 1.0f;
		//		}
		(*it)->xCord += (*it)->xPower;
		(*it)->yCord -= (*it)->yPower;
		
		renderAnVboAndVaoObject((*it)->xCord, (*it)->yCord, scaleSizeInitial, 0, 0, 0, blankTexture,
								color, (*it)->vao, 1, 1, (*it)->depth);
		
		
		///check if snow flake got out of boundary
		if((*it)->xCord > maximX || (*it)->xCord < minimX || (*it)->yCord < minimY || (*it)->yCord > maximY)
		{
			(*it)->sinValue = 0;
			(*it)->xCord = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximX - minimX + 1) + minimX;
			(*it)->yCord = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximY - minimY + 1) + minimY;
		}
	}
	glUniform1f(ShaderFlake, 0);
	glUniform1f(ShaderIsCircle, 0);
	
}




void BSTexture::renderMouseTexture()
{
}




void BSTexture::renderTheCloudyParticles()
{
}



void BSTexture::consoleSalveazaHarta()
{
    salveazaFinishedLevel();
    
    int pauze = 0, indexNumeHarta = 0, nrOfLinesSave = 0;
    char numeHarta[100] = "", nodesName[100][100], attributesName[100][100], attributesValues[100][100];
    ListaDeCaractere *nodesForXML[1000];
    std::string theNameOfMap = "Menu Of Levels/Chapter" + BStoString(levelChoserPlayer->indexOfChapterThatItIsOn + 1)
    + "/The Levels objects/level" + BStoString(levelChoserPlayer->indexOfLevelThatItIsOn + 1)
    + ".xml";
    
    
    strcpy(numeHarta, theNameOfMap.c_str());
    
    ///Salvez jucatorul
    nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
    nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
    nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
    nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
    nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
    nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
    strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "0");
    strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], "playerTexture.png");
    strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
    std::string theSave = BStoString(HeroInitialX);
    strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
    theSave = BStoString(HeroInitialY);
    strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
    theSave = BStoString(Hero_size);
    strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
    theSave = BStoString(Hero_size);
    strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
    strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], "hero");
    strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "playerAnimation");
    
    
    
    nrOfLinesSave++;
    
    
    std::cout<<'\n'<<"Salveaza harta: "<<numeHarta<<'\n';
    //Parcurg toate corpurile si le salvez
    
    
    
    std::list<BSTheRoundBodies*>::iterator iteratorRoundBodies;
    for(iteratorRoundBodies = ListOfRoundBodies.begin(); iteratorRoundBodies != ListOfRoundBodies.end(); iteratorRoundBodies++)
    {
        //extrag userData-ul
        USERDATA *salveazaUserData = (USERDATA*)(*iteratorRoundBodies)->theBody->GetUserData();
        
        nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
        nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "1");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], (*iteratorRoundBodies)->nameOfTexture.c_str());
        
        theSave = BStoString((*iteratorRoundBodies)->theBody->GetPosition().x);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
        theSave = BStoString((*iteratorRoundBodies)->theBody->GetPosition().y);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
        theSave = BStoString((*iteratorRoundBodies)->radius);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
        theSave = BStoString((*iteratorRoundBodies)->radius);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], salveazaUserData->name.c_str());
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "roundAnimation");
        
        
        if((*iteratorRoundBodies)->ObstacleFinishesLevel == true)
        {
            strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "2");
        }
        else
        {
            theSave = BStoString((*iteratorRoundBodies)->ObstacleCanKillHero);
            strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], theSave.c_str());
        }
        
        nrOfLinesSave++;
        
        delete salveazaUserData;
    }
    
    std::list<BSTheSquareBodies*>::iterator iteratorSquareBodies;
    for(iteratorSquareBodies = ListOfSquareBodies.begin(); iteratorSquareBodies != ListOfSquareBodies.end(); iteratorSquareBodies++)
    {
        USERDATA *salveazaUserData = (USERDATA*)(*iteratorSquareBodies)->theBody->GetUserData();
        
        nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
        nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "0");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], (*iteratorSquareBodies)->nameOfTexture.c_str());
        
        theSave = BStoString((*iteratorSquareBodies)->theBody->GetPosition().x);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
        theSave = BStoString((*iteratorSquareBodies)->theBody->GetPosition().y);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
        theSave = BStoString((*iteratorSquareBodies)->width);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
        theSave = BStoString((*iteratorSquareBodies)->height);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], salveazaUserData->name.c_str());
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "textureAnimation");
        
        
        ///Vad daca obstacolul va fi cel care il va trece pe jucator la nivelul urmator
        if((*iteratorSquareBodies)->ObstacleFinishesLevel == true)
        {
            strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "2");
        }
        else
        {
            theSave = BStoString((*iteratorSquareBodies)->ObstacleCanKillHero);
            strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], theSave.c_str());
        }
        
        
        
        nrOfLinesSave++;
        
    }
    
    std::list<BSTheMessages*>::iterator i;
    for(i = listOfMessages.begin(); i != listOfMessages.end(); i++)
    {
        nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
        nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "2");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], (*i)->nameOfTextureMessage.c_str());
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
        theSave = BStoString((*i)->xCord);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
        theSave = BStoString((*i)->yCord);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], "0");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], "0");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], "message");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "messageAnimation");
        
        nrOfLinesSave++;
    }
    
    std::list<BSCoins*>::iterator iq;
    for(iq = listOfCoins.begin(); iq != listOfCoins.end(); iq++)
    {
        nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
        nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "5");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], "Animations/coin.png");
        
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
        theSave = BStoString((*iq)->xInit);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
        theSave = BStoString((*iq)->yInit);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], "1");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], "1");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], "coin");
        theSave = BStoString((*iq)->available);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], theSave.c_str());
        
        nrOfLinesSave++;
    }
    
    std::list<BSFans*>::iterator iqq;
    for(iqq = listOfFans.begin(); iqq != listOfFans.end(); iqq++)
    {
        nodesForXML[nrOfLinesSave] = new ListaDeCaractere;
        nodesForXML[nrOfLinesSave]->theCharArray2D[0][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[1][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[2][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[3][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[4][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[5][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[6][0] = NULL, nodesForXML[nrOfLinesSave]->theCharArray2D[7][0] = NULL;
        nodesForXML[nrOfLinesSave]->theCharArray2D[8][0] = NULL;
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[0], "6");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[1], "Animations/fan.png");
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[2], "0");
        theSave = BStoString((*iqq)->xCord);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[3], theSave.c_str());
        theSave = BStoString((*iqq)->yCord);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[4], theSave.c_str());
        theSave = BStoString((*iqq)->width);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[5], theSave.c_str());
        theSave = BStoString((*iqq)->height);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[6], theSave.c_str());
        
        theSave = BStoString((*iqq)->lenthOfPower) + " " + BStoString((*iqq)->powerX) + " " + BStoString((*iqq)->powerY);
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[7], theSave.c_str());
        strcpy(nodesForXML[nrOfLinesSave]->theCharArray2D[8], "none");
        
        nrOfLinesSave++;
    }
    
    BSXmlFiles *saveTheMap = new BSXmlFiles();
    strcpy(nodesName[0], "Square_or_Circle_or_Message"), strcpy(nodesName[1], "Texture_path");
    strcpy(nodesName[2], "Kill_or_Next_Level"), strcpy(nodesName[3], "xCoordinate");
    strcpy(nodesName[4], "yCoordinate"), strcpy(nodesName[5], "width");
    strcpy(nodesName[6], "height"), strcpy(nodesName[7], "userName"), strcpy(nodesName[8], "Animation_name");
    
    strcpy(attributesName[0], "name"), strcpy(attributesName[1], "boundary_Left");
    strcpy(attributesName[2], "boundary_Down"), strcpy(attributesName[3], "boundary_Up");
    strcpy(attributesName[4], "boundary_Right");
    
    strcpy(attributesValues[0], numeHarta);
    strcpy(attributesValues[1], BStoString(CameraExtremeLeft - SCREEN_WIDTH / 2.f / scaleSize).c_str());
    strcpy(attributesValues[2], BStoString(CameraExtremeDown - SCREEN_HEIGHT / 2.f / scaleSize).c_str());
    strcpy(attributesValues[3], BStoString(CameraExtremeUp + SCREEN_HEIGHT / 2.f / scaleSize).c_str());
    strcpy(attributesValues[4], BStoString(CameraExtremeRight + SCREEN_WIDTH / 2.f / scaleSize).c_str());
    
    
    saveTheMap->writeAnyXML(numeHarta, "Level", "obstacle",
                            nodesName, nodesForXML,
                            attributesName, attributesValues,
                            9, nrOfLinesSave, 5, 5);
    delete saveTheMap, nodesForXML;
    
    
    
    aSalvatHarta = true;
}


void BSTexture::salveazaFinishedLevel()
{
    std::string file = "Saves/playerData" + BStoString(levelChoserPlayer->indexOfChapterThatItIsOn + 1) + ".txt";
    std::ifstream fin(file.c_str());
    
    int chpNr, lvlNr, cuv[25][3];
    fin>>chpNr>>lvlNr;
    
    int sw = 0;
    for(int i = 0 ; i < levelChoserPlayer->indexOfLevelThatItIsOn; i++)
    {
        fin>>cuv[i][0]>>cuv[i][1]>>cuv[i][2];
        sw++;
    }
    fin>>cuv[sw][0]>>cuv[sw][1]>>cuv[sw][2];
    cuv[sw][1] = 1;
    
    for(int i = levelChoserPlayer->indexOfChapterThatItIsOn + 1; i < 25; i++)
    {
        fin>>cuv[i][0]>>cuv[i][1]>>cuv[i][2];
    }
    
    std::ofstream fout(file.c_str());
    fout<<chpNr<<' '<<lvlNr<<'\n';
    for(int i = 0 ; i < 25; i ++)
    {
        fout<<cuv[i][0]<<' '<<cuv[i][1]<<' '<<cuv[i][2]<<'\n';
    }
}

void BSTexture::loadATexture(std::string name, GLuint &theTextureId)
{
	int i = name.size() - 1;
	while(i >= 0 && name[i] != '/')
	{
		i--;
	}
	
	UIImage *img;
	std::string newP = "", newN = "";
	if(i == -1)
	{
		for(int j = 0 ; j < name.size() - 4; j++)
		{
			newN += name[j];
		}
		NSString *fileName = [NSString stringWithCString:newN.c_str()
												encoding:[NSString defaultCStringEncoding]];
		img = loadNewTexture(@"", fileName);
	}
	else
	{
		for(int j = 0 ; j < i; j++)
		{
			newP += name[j];
		}
		if(newP.find("\n") != std::string::npos)
		{
			std::cout<<"da"<<'\n';
		}
		for(int j = i + 1 ; j < name.size() - 4; j++)
		{
			newN += name[j];
		}
		NSString *fileName = [NSString stringWithCString:newN.c_str()
												encoding:[NSString defaultCStringEncoding]];
		NSString *filePath = [NSString stringWithCString:newP.c_str()
												encoding:[NSString defaultCStringEncoding]];
		
		img = loadNewTexture(filePath, fileName);
	}
	
    CGImageRef spriteImage = img.CGImage;
    if (!spriteImage) {
		std::cout<<"Failed to load image:"<<newP<<"; "<<newN<<'\n';
        //exit(1);
		return;
    }
    
    size_t width = CGImageGetWidth(spriteImage);
    size_t height = CGImageGetHeight(spriteImage);
	
    GLubyte * spriteData = (GLubyte *) calloc(width*height*4, sizeof(GLubyte));
    
    CGContextRef spriteContext = CGBitmapContextCreate(spriteData, width, height, 8, width*4, CGImageGetColorSpace(spriteImage), kCGImageAlphaPremultipliedLast);
    
    CGContextDrawImage(spriteContext, CGRectMake(0, 0, width, height), spriteImage);
    
    CGContextRelease(spriteContext);
    
    glGenTextures(1, &theTextureId);
    glBindTexture(GL_TEXTURE_2D, theTextureId);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteData);
    
    free(spriteData);
	GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        NSLog(@"Error uploading texture. glError at the end of loadATexture", err);
	//return texName;
    //theTextureId = texName;
}
