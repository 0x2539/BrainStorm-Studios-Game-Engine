
#include "BSObstacles.h"

//Quad vertices

	BSAnimationClass *animationsObstacleClass = new BSAnimationClass();

	BSTexture *renderObstacleClass = new BSTexture();


b2Body* BSObstacles::createBodies(b2BodyType Type, float LocationX, float LocationY, float Width, float Height,
								  std::string userData, int &NumberOfBodies, int timeUntilIsDistroyed, bool corpDistrus)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = Type;
	USERDATA* userdata = new USERDATA;

	if(NumberOfBodies == 0)
	{
		myBodyDef.bullet = true;
	}

	myBodyDef.position.Set((float) LocationX, (float) LocationY);

	userdata->name = userData;

	if(userData == "particle")
	{
		userdata->timeUntilDestroy = timeUntilIsDistroyed;
		userdata->BumTime = SDL_GetTicks() + timeUntilIsDistroyed;
	}

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox((float) Width / 2, (float) Height / 2);

	b2Body* box = world->CreateBody(&myBodyDef);

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	if(userData == "wall" || userData == "object")
	{
		//myFixtureDef.friction = 200.f;
	}

	box->ResetMassData();
	box->SetFixedRotation(true);


	box->SetUserData(userdata);


	if(userData == "particle")
	{
		box->SetFixedRotation(false);
		myFixtureDef.filter.groupIndex = BinaryParticles;
		//box->GetContactList()->contact->SetEnabled(false);
	}
	else if(userData == "hero")
	{
		myFixtureDef.filter.groupIndex = BinaryPlayer;
	}
	else
	{
		myFixtureDef.filter.groupIndex = BinaryScenery;
	}


	box->CreateFixture(&myFixtureDef);

//	BodySize[NumberOfBodies][0] = (float) Width / 2;// / PixelToMeters;
//	BodySize[NumberOfBodies][1] = (float) Height / 2;// / PixelToMeters;


	if(userData != "particle")
	{
		//setTheVaoData(vData[NumberOfBodies], BodySize[NumberOfBodies][0], BodySize[NumberOfBodies][1]);
	}

	if(corpDistrus == false)
	{
		NumberOfBodies++;
	}

	//free(box);

	//delete userdata;
	//userdata = NULL;

	return box;
}



b2Body* BSObstacles::createCircleBodies(b2BodyType Type, float LocationX, float LocationY, float Radius,
										std::string userData, int &NumberOfBodies, int timeUntilIsDistroyed, bool corpDistrus)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = Type;
	USERDATA* userdata = new USERDATA;

	if(NumberOfBodies == 0)
	{
		myBodyDef.bullet = true;
	}

	myBodyDef.position.Set((float) LocationX, (float) LocationY);

	userdata->name = userData;

	if(userData == "particle")
	{
		userdata->timeUntilDestroy = timeUntilIsDistroyed;
		userdata->BumTime = SDL_GetTicks() + timeUntilIsDistroyed;
	}

	b2CircleShape circleShape;
	circleShape.m_radius = Radius;

	b2Body* box = world->CreateBody(&myBodyDef);

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = 1;

	if(userData == "wall" || userData == "object")
	{
		//myFixtureDef.friction = 200.f;
	}

	box->ResetMassData();
	box->SetFixedRotation(true);


	box->SetUserData(userdata);


	if(userData == "particle")
	{
		box->SetFixedRotation(false);
		myFixtureDef.filter.groupIndex = BinaryParticles;
		//box->GetContactList()->contact->SetEnabled(false);
	}
	else if(userData == "hero")
	{
		myFixtureDef.filter.groupIndex = BinaryPlayer;
	}
	else
	{
		myFixtureDef.filter.groupIndex = BinaryScenery;
	}


	if(userData == "Hero2nd" || userData == "hero")
	{
		box->SetFixedRotation(false);
		myFixtureDef.filter.groupIndex = BinaryPlayer;
	}

	box->CreateFixture(&myFixtureDef);

//	BodySize[NumberOfBodies][0] = (float) Radius / 2;// / PixelToMeters;
//	BodySize[NumberOfBodies][1] = (float) Radius / 2;// / PixelToMeters;


	if(userData != "particle")
	{
		//setTheVaoData(vData[NumberOfBodies], BodySize[NumberOfBodies][0], BodySize[NumberOfBodies][1]);
	}

	if(corpDistrus == false)
	{
		NumberOfBodies++;
	}

	//free(box);

	//delete userdata;
	//userdata = NULL;

	return box;
}



void BSObstacles::setTheVao( GLuint &theVaoBuffer, BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind)
{
//	if(!theVaoBuffer)
	{
		//Generate VAO buffer
		glGenVertexArrays( 1, &theVaoBuffer );

		//Bind vertex array
		glBindVertexArray( theVaoBuffer );

		//bind the VBO
		bindVBO(dataToBind, theVboToBind, theIbotoBind);

		glEnableVertexAttribArray(locationBSVertexPosition3D);
		glVertexAttribPointer( locationBSVertexPosition3D, 3, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, position ) );

		glEnableVertexAttribArray(locationBSTextureCoordinate);
		glVertexAttribPointer( locationBSTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, texCoord ) );

		//Unbind VAO
		glBindVertexArray( NULL );
		glBindBuffer( GL_ARRAY_BUFFER, NULL );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, NULL );
	}
}


void BSObstacles::bindVBO(BSTexturedVertex2D dataToBind[4], GLuint &theVboToBind, GLuint &theIbotoBind)
{
	//Create VBO
	glGenBuffers( 1, &theVboToBind );
	glBindBuffer( GL_ARRAY_BUFFER, theVboToBind );
	glBufferData( GL_ARRAY_BUFFER, 4 * sizeof(BSTexturedVertex2D), dataToBind, GL_DYNAMIC_DRAW );

	//Create IBO
	glGenBuffers( 1, &theIbotoBind );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, theIbotoBind );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), iData, GL_DYNAMIC_DRAW );
}


void BSObstacles::setTheVaoData(GLuint &vaoBuffer, GLuint &vboBuffer, GLuint &iboBuffer,
								BSTexturedVertex2D dataToSet[4], GLfloat widthToSet, GLfloat heightToSet)
{
	widthToSet = 1 / 2.0f;
	heightToSet = 1 / 2.0f;


	GLfloat texTop = 1;//heightToSet * 2;
	GLfloat texBottom = 0;
	GLfloat texLeft = 0;
	GLfloat texRight = 1;//widthToSet * 2;

	//Vertex coordinates
	GLfloat quadWidth = widthToSet;// + hero->theBody->GetAngle();
	GLfloat quadHeight = heightToSet;

	//Texture coordinates
	dataToSet[0].texCoord.s = texLeft;
	dataToSet[0].texCoord.t = texTop;
	dataToSet[1].texCoord.s = texLeft;
	dataToSet[1].texCoord.t = texBottom;
	dataToSet[2].texCoord.s = texRight;
	dataToSet[2].texCoord.t = texBottom;
	dataToSet[3].texCoord.s = texRight;
	dataToSet[3].texCoord.t = texTop;

	//Vertex positions
	dataToSet[0].position.x = -quadWidth;
	dataToSet[0].position.y = -quadHeight;
	dataToSet[0].position.z = scaleSizeInitial;
	dataToSet[1].position.x = -quadWidth;
	dataToSet[1].position.y = quadHeight;
	dataToSet[1].position.z = scaleSizeInitial;
	dataToSet[2].position.x = quadWidth;
	dataToSet[2].position.y = quadHeight;
	dataToSet[2].position.z = scaleSizeInitial;
	dataToSet[3].position.x = quadWidth;
	dataToSet[3].position.y = -quadHeight;
	dataToSet[3].position.z = scaleSizeInitial;

	setTheVao(vaoBuffer, dataToSet, vboBuffer, iboBuffer);
}


void BSObstacles::setVaoForChunckObjects(GLuint &vaoBuffer, GLuint &vboBuffer, GLuint &iboBuffer, BSTexturedVertex2D dataToSet[4], GLfloat widthToSet, GLfloat heightToSet)
{
	GLfloat texTop = 1;//heightToSet * 2;
	GLfloat texBottom = 0;
	GLfloat texLeft = 0;
	GLfloat texRight = 1;//widthToSet * 2;

	//Vertex coordinates
	GLfloat quadWidth = widthToSet / 2.0f;// + hero->theBody->GetAngle();
	GLfloat quadHeight = heightToSet / 2.0f;

	//Texture coordinates
	dataToSet[0].texCoord.s = texLeft;	dataToSet[0].texCoord.t = texTop;
	dataToSet[1].texCoord.s = texLeft;	dataToSet[1].texCoord.t = texBottom;
	dataToSet[2].texCoord.s = texRight;	dataToSet[2].texCoord.t = texBottom;
	dataToSet[3].texCoord.s = texRight;	dataToSet[3].texCoord.t = texTop;

	//Vertex positions
	dataToSet[0].position.x = -quadWidth;	dataToSet[0].position.y = -quadHeight;	dataToSet[0].position.z = scaleSizeInitial;
	dataToSet[1].position.x = -quadWidth;	dataToSet[1].position.y = quadHeight;	dataToSet[1].position.z = scaleSizeInitial;
	dataToSet[2].position.x = quadWidth;	dataToSet[2].position.y = quadHeight;	dataToSet[2].position.z = scaleSizeInitial;
	dataToSet[3].position.x = quadWidth;	dataToSet[3].position.y = -quadHeight;	dataToSet[3].position.z = scaleSizeInitial;

	setTheVao(vaoBuffer, dataToSet, vboBuffer, iboBuffer);
}

void BSObstacles::setTheVaoDataForFont(BSTexturedVertex2D dataTSet[4], GLfloat widthToSet, GLfloat heightToSet, float xCord, float yCord, GLuint &vaoBuffer, GLuint &vboBuffer, GLuint &iboBuffer)
{
    glGenVertexArrays(1, &vaoBuffer);
    glBindVertexArray(vaoBuffer);

	BSTexturedVertex2D data[4];
	float texBottom = yCord / 1024.f;
	float texTop = (yCord + heightToSet) / 1024.f;//heightToSet * 2;
	float texLeft = xCord / 1024.f;
	float texRight = (xCord + widthToSet) / 1024.f;//widthToSet * 2;

	//Vertex coordinates
	float quadWidth = 1 / 2.f;
	float quadHeight = 1 / 2.f;
	quadWidth = (float) widthToSet / heightToSet / 2.f;


	//Texture coordinates
	data[0].texCoord.s = texLeft;	data[0].texCoord.t = texTop;
	data[1].texCoord.s = texLeft;	data[1].texCoord.t = texBottom;
	data[2].texCoord.s = texRight;	data[2].texCoord.t = texBottom;
	data[3].texCoord.s = texRight;	data[3].texCoord.t = texTop;

	//Vertex positions
	data[0].position.x = -quadWidth;	data[0].position.y = -quadHeight;	data[0].position.z = scaleSizeInitial;
	data[1].position.x = -quadWidth;	data[1].position.y = quadHeight;	data[1].position.z = scaleSizeInitial;
	data[2].position.x = quadWidth;		data[2].position.y = quadHeight;	data[2].position.z = scaleSizeInitial;
	data[3].position.x = quadWidth;		data[3].position.y = -quadHeight;	data[3].position.z = scaleSizeInitial;




    glGenBuffers(1, &vboBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &iboBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iData), iData, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(locationBSVertexPosition3D);
    glVertexAttribPointer(locationBSVertexPosition3D, 3, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), 0);

    glEnableVertexAttribArray(locationBSTextureCoordinate);
    glVertexAttribPointer(locationBSTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*) (sizeof(float) * 3));

    //Unbind VAO
    glBindVertexArray( NULL );
    glBindBuffer( GL_ARRAY_BUFFER, NULL );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, NULL );
}



void BSObstacles::setUpBodies()
{
	setUpOriginals();

	incarcaHarta("Menu Of Levels/Chapter1/The Levels objects/level1.xml");

	renderObstacleClass->initVboAndVao();
}


void BSObstacles::setUpOriginals()
{
    for(int i = 0 ; i < 5; i++)
    {
        listOfActiveAnimations[i] = new BsActiveAnimations;
        listOfActiveAnimations[i]->indexOfAnimation = 0;
        listOfActiveAnimations[i]->isAtStepOfAnimation1 = false;
        listOfActiveAnimations[i]->isAtStepOfAnimation2 = false;
        listOfActiveAnimations[i]->isAtStepOfAnimation3 = false;
        listOfActiveAnimations[i]->canPlayAnimation1 = false;
        listOfActiveAnimations[i]->canPlayAnimation2 = false;
        listOfActiveAnimations[i]->canPlayAnimation3 = false;
        listOfActiveAnimations[i]->canPlayIt = false;
    }//0-hero, 1-berserk, 2-electricity, 3-wormHole, 4-last power up

	///Set the particle data !!!!!!!! Need initialization only once, vaoBuffer too
	originalParticle->width = 1 / 8.f;
	originalParticle->height = 1 / 8.f;
	originalParticle->depth = 0;
	setTheVaoData(originalParticle->vao, originalParticle->vbo, originalParticle->ibo, originalParticle->data, 1  / 16.0f, 1  / 16.0f);

	///Hero2nd
	Hero2nd->theBody = createCircleBodies(b2_dynamicBody, 6, 4, Hero_size, "Hero2nd", nrBodies, 0, false);
	Hero2nd->width = Hero_size + 0.15;
	Hero2nd->height = Hero_size + 0.15;
	Hero2nd->depth = 0;
	Hero2nd->texture = playerTexture;
	Hero2nd->color = { 1.f, 1.f, 1.f, 1.f };
	setTheVaoData(Hero2nd->vao, Hero2nd->vbo, Hero2nd->ibo, Hero2nd->data, Hero2nd->width, Hero2nd->height);


	///SoundButton texture
	SoundButtonTexture->width = Hero_size;
	SoundButtonTexture->height = Hero_size;
	SoundButtonTexture->depth = 0;
	SoundButtonTexture->texture = playerTexture;
	SoundButtonTexture->color = { 1.f, 1.f, 1.f, 1.f };
	SoundButtonTexture->xCord = (float) SCREEN_WIDTH / 32 / 2;
	SoundButtonTexture->yCord = (float) SCREEN_HEIGHT / 32 / 2;
	SoundButtonTexture->zCord = scaleSizeInitial;
	setTheVaoData(SoundButtonTexture->vao, SoundButtonTexture->vbo, SoundButtonTexture->ibo,
				  SoundButtonTexture->data, SoundButtonTexture->width, SoundButtonTexture->height);



	///Set the coin
	renderObstacleClass->loadATexture("Animations/coin.png", originalCoin->texture);
	originalCoin->width = Hero_size;
	originalCoin->height = Hero_size;
	originalCoin->depth = 0;
	originalCoin->xCord = 2;
	originalCoin->yCord = (float) SCREEN_HEIGHT / 32 - 1;
	originalCoin->zCord = scaleSizeInitial;
	setTheVaoData(originalCoin->vao, originalCoin->vbo, originalCoin->ibo, originalCoin->data, 1, 1);


	///Set the dust bodies
	renderObstacleClass->loadATexture("Animations/dust.png", originalDustBody->texture);
	originalDustBody->width = 1;
	originalDustBody->height = 1;
	originalDustBody->depth = 0;
	originalDustBody->xCord = 0;
	originalDustBody->yCord = 0;
	originalDustBody->zCord = scaleSizeInitial;
	setTheVaoData(originalDustBody->vao, originalDustBody->vbo, originalDustBody->ibo, originalDustBody->data, 1, 1);


	///Set the fans
	renderObstacleClass->loadATexture("Animations/fan.png", originalFan->texture);
	originalFan->width = Hero_size * 10;
	originalFan->height = Hero_size;
	originalFan->depth = 0;
	setTheVaoData(originalFan->vao, originalFan->vbo, originalFan->ibo, originalFan->data, 1, 1);
	setVaoForChunckObjects(originalFanParticleX->vao, originalFanParticleX->vbo, originalFanParticleX->ibo, originalFanParticleX->data, 1, 0.05f);
	setVaoForChunckObjects(originalFanParticleY->vao, originalFanParticleY->vbo, originalFanParticleY->ibo, originalFanParticleY->data, 0.05f, 1);


	///Set the dark level light
	renderObstacleClass->loadATexture("Animations/dark.png", mainDarkTexture);
	originalDarkMenu->width = (float) (SCREEN_WIDTH / 32 + 2) * 2;
	originalDarkMenu->height = (float) (SCREEN_HEIGHT / 32 + 2) * 2;
	originalDarkMenu->depth = 0;
	setTheVaoData(originalDarkMenu->vao, originalDarkMenu->vbo, originalDarkMenu->ibo, originalDarkMenu->data, 1, 1);


	originalDarkLevel->width = (float) SCREEN_WIDTH / 32 - Hero_size * 6.f;
	originalDarkLevel->height = (float) SCREEN_HEIGHT / 32 - Hero_size * 6.f;
	originalDarkLevel->depth = 0;
	setTheVaoData(originalDarkLevel->vao, originalDarkLevel->vbo, originalDarkLevel->ibo, originalDarkLevel->data, 1, 1);


	originalWormHole->width = 2;
	originalWormHole->height = 2;
	originalWormHole->depth= 0;
	setTheVaoData(originalWormHole->vao, originalWormHole->vbo, originalWormHole->ibo, originalWormHole->data, 1, 1);
	renderObstacleClass->loadATexture("Animations/wormHole.png", originalWormHole->texture);
	BSColorRGBA color = {1.0f, 1.0f, 1.0f, 1.0f};
	originalWormHole->color = color;

	hero->heroIsBerserk1 = false;
	hero->heroIsBerserk2 = false;
	hero->heroIsBerserk3 = false;
	// hack

	///The rendered Square
	theRenderedObstacleSquare->width = hero->width;
	theRenderedObstacleSquare->height = hero->height;
	theRenderedObstacleSquare->depth = 0;
	theRenderedObstacleSquare->color = { 1.f, 0.8f, 0.f, 0.5f }; //transparent yellowish
	theRenderedObstacleSquare->texture = blankTexture;
	setTheVaoData(theRenderedObstacleSquare->vao, theRenderedObstacleSquare->vbo, theRenderedObstacleSquare->ibo,
				  theRenderedObstacleSquare->data, 1, 1);

	originalTransparentMenu->width = SCREEN_WIDTH / 32.0f;
	originalTransparentMenu->height = SCREEN_HEIGHT / 32.0f;
	originalTransparentMenu->depth = 0.0f;
	originalTransparentMenu->color = { 1.f, 0.8f, 0.f, 0.5f }; //transparent yellowish
	originalTransparentMenu->texture = blankTexture;
	setTheVaoData(originalTransparentMenu->vao, originalTransparentMenu->vbo, originalTransparentMenu->ibo,
				  originalTransparentMenu->data, 1, 1);

	///The rendered Circle
	theRenderedObstacleCircle->radius = hero->width;
	theRenderedObstacleCircle->radius = hero->height;
	theRenderedObstacleCircle->depth = 0;
	theRenderedObstacleCircle->color = { 1.f, 0.8f, 0.f, 0.5f }; //transparent yellowish
	theRenderedObstacleCircle->texture = blankTexture;
	setTheVaoData(theRenderedObstacleCircle->vao, theRenderedObstacleCircle->vbo, theRenderedObstacleCircle->ibo,
				  theRenderedObstacleCircle->data, 1, 1);


	///Set the Dead Scene data
	deadScene->width = SCREEN_WIDTH * 1.5f / 32 * 2;
	deadScene->height = SCREEN_HEIGHT * 1.5f / 32 * 2;
	deadScene->depth = 0;
	deadScene->color = {0.f, 0.f, 0.f, 0.f};
//	deadScene->nextLevelOrSomeLevel = 1;
	deadScene->texture = NULL;
	setTheVaoData(deadScene->vao, deadScene->vbo, deadScene->ibo, deadScene->data, 1, 1);
}






void BSObstacles::incarcaHarta(char nume[])
{
	BSXmlFiles *doc = new BSXmlFiles();
	char theNodes[10][100], theAttributes[6][100];
	ListaDeCaractere *levelDetails[1000], *levelDetailsAttributes[1];
	strcpy(theNodes[0], "Body_Type");
	strcpy(theNodes[1], "Texture_path");
	strcpy(theNodes[2], "Kill_or_Next_Level");
	strcpy(theNodes[3], "xCoordinate");
	strcpy(theNodes[4], "yCoordinate");
	strcpy(theNodes[5], "width");
	strcpy(theNodes[6], "height");
	strcpy(theNodes[7], "userName");
	strcpy(theNodes[8], "Animation_name");
	strcpy(theNodes[9], "Index");

	strcpy(theAttributes[0], "name");
	strcpy(theAttributes[1], "boundary_Left");
	strcpy(theAttributes[2], "boundary_Down");
	strcpy(theAttributes[3], "boundary_Up");
	strcpy(theAttributes[4], "boundary_Right");
	strcpy(theAttributes[5], "script");

	doc->readAnyXML(nume, "Level", "obstacle", levelDetails, theNodes, theAttributes, levelDetailsAttributes, 10, 6);


	CameraExtremeLeft = atof(levelDetailsAttributes[0]->theCharArray2DAttributes[1]) + SCREEN_WIDTH / 2.f / 32;
	CameraExtremeDown = atof(levelDetailsAttributes[0]->theCharArray2DAttributes[2]) + SCREEN_HEIGHT / 2.f / 32;
	CameraExtremeUp = atof(levelDetailsAttributes[0]->theCharArray2DAttributes[3]) - SCREEN_HEIGHT / 2.f / 32;
	CameraExtremeRight = atof(levelDetailsAttributes[0]->theCharArray2DAttributes[4]) - SCREEN_WIDTH / 2.f / 32;

	gameBoundLeft = atof(levelDetailsAttributes[0]->theCharArray2DAttributes[1]);
	gameBoundDown = atof(levelDetailsAttributes[0]->theCharArray2DAttributes[2]);
	gameBoundUp = atof(levelDetailsAttributes[0]->theCharArray2DAttributes[3]);
	gameBoundRight = atof(levelDetailsAttributes[0]->theCharArray2DAttributes[4]);

	levelHasScript = atof(levelDetailsAttributes[0]->theCharArray2DAttributes[5]);

	std::cout<<'\n';

	HeroInitialX = atof(levelDetails[0]->theCharArray2D[3]);
	HeroInitialY = atof(levelDetails[0]->theCharArray2D[4]);


	///Hero
	hero->animationIndexPlayerMoveRight = 0;
	hero->animationIndexPlayerMoveLeft = 1;
	hero->animationIndexPlayerMoveUpRight = 2;
	hero->animationIndexPlayerMoveUpLeft = 3;
	hero->animationIndexPlayerMoveDownRight = 4;
	hero->animationIndexPlayerMoveDownLeft = 5;
	hero->animationIndexPlayerStand = 6;
	hero->animationIndexPlayerDieLeft = 7;
	hero->animationIndexPlayerDieRight = 8;
	hero->animationIndexPlayerTeleportedIn = 9;
	hero->animationIndexPlayerTeleportedOut = 10;
	hero->animationIndexPlayerAura1 = 11;
	hero->animationIndexPlayerAura2 = 12;
	hero->animationIndexPlayerAura3 = 13;
	hero->animationIndexPlayerAuraElectricity = 14;
	hero->animationIndexPlayerWormHole = 15;
	hero->animationIndexPlayerWallLeft = 16;
	hero->animationIndexPlayerWallRight = 17;
	hero->animationIndexPlayerStoppedFromMovingRight = 18;
	hero->animationIndexPlayerStoppedFromMovingLeft = 19;

	hero->animationIndexCurrentAnimation = 0;

	hero->heroIsDead = false;

	//if(hero->width != atof(levelDetails[0]->theCharArray2D[5]) ||
	//	hero->height != atof(levelDetails[0]->theCharArray2D[6]))
	std::ifstream playerSize("playerSize.txt");
	float width, height;
	playerSize>>width>>height;

	if(hero->width != Hero_size && hero->height != Hero_size)
	{
		hero->theBody = createBodies(b2_dynamicBody, HeroInitialX, HeroInitialY,
									 Hero_size, Hero_size,
									 levelDetails[0]->theCharArray2D[7], nrBodies, 0, false);

		playerAnimWidth = Hero_size;
		playerAnimHeight = Hero_size;

		setTheVaoData(hero->vao, hero->vbo, hero->ibo, hero->data, playerAnimWidth, playerAnimHeight);

		hero->zCord = scaleSizeInitial;
		hero->width = Hero_size;
		hero->height = Hero_size;
	}

	if(hero->nameOfTexture != levelDetails[0]->theCharArray2D[1])
	{
//		hero->nameOfTexture = levelDetails[0]->theCharArray2D[1];
//		renderObstacleClass->loadATexture(hero->nameOfTexture, hero->texture);
//		hero->color = { 1.f, 1.f, 1.f, 1.f };
	}

	///Delete the Animations
//	destroyAllAnimations();
	///Add the animations
	if(nrOfListOfAnimations == 0)
	{
		addTheAnimationsForMap(levelDetails[0]->theCharArray2D[8]);
	}



	///Sterg mesajele daca exista
	deleteAllMessageTexture();

	//the current obstacle that is added
	int currentInWhile = 1;

	while(levelDetails[currentInWhile])
	{
		///Daca e patrat
		if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 0)
		{
			addDinamicSquare(atof(levelDetails[currentInWhile]->theCharArray2D[3]), atof(levelDetails[currentInWhile]->theCharArray2D[4]),
							 atof(levelDetails[currentInWhile]->theCharArray2D[5]), atof(levelDetails[currentInWhile]->theCharArray2D[6]),
							 levelDetails[currentInWhile]->theCharArray2D[1], NULL, levelDetails[currentInWhile]->theCharArray2D[7],
							 b2_staticBody, atof(levelDetails[currentInWhile]->theCharArray2D[2]), 0);

             ListOfSquareBodies.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
		}
		else
			///Daca e cerc
			if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 1)
			{
				addDinamicRound(atof(levelDetails[currentInWhile]->theCharArray2D[3]), atof(levelDetails[currentInWhile]->theCharArray2D[4]),
								atof(levelDetails[currentInWhile]->theCharArray2D[5]), levelDetails[currentInWhile]->theCharArray2D[1],
								NULL, levelDetails[currentInWhile]->theCharArray2D[7],
								b2_staticBody, atof(levelDetails[currentInWhile]->theCharArray2D[5]));

                ListOfRoundBodies.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
			}
			else
				///Daca e mesaj
				if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 2)
				{
					addMessageTexture(atof(levelDetails[currentInWhile]->theCharArray2D[3]), atof(levelDetails[currentInWhile]->theCharArray2D[4]),
									  atof(levelDetails[currentInWhile]->theCharArray2D[5]), atof(levelDetails[currentInWhile]->theCharArray2D[6]),
									  levelDetails[currentInWhile]->theCharArray2D[1]);

                    listOfMessages.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
				}
				else
					///Daca e texture square
					if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 3)
					{
						addOnlyTexture(1, atof(levelDetails[currentInWhile]->theCharArray2D[3]),
									   atof(levelDetails[currentInWhile]->theCharArray2D[4]),
									   atof(levelDetails[currentInWhile]->theCharArray2D[5]),
									   atof(levelDetails[currentInWhile]->theCharArray2D[6]),
									   levelDetails[currentInWhile]->theCharArray2D[1]);

                        ListOfSquareTextures.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
					}
					else
						///Daca e texture circle
						if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 4)
						{
							addOnlyTexture(-1, atof(levelDetails[currentInWhile]->theCharArray2D[3]),
										   atof(levelDetails[currentInWhile]->theCharArray2D[4]),
										   atof(levelDetails[currentInWhile]->theCharArray2D[5]),
										   atof(levelDetails[currentInWhile]->theCharArray2D[6]),
										   levelDetails[currentInWhile]->theCharArray2D[1]);

                            ListOfRoundTextures.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
						}
						else
							///Daca e coin
							if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 5)
							{
								addCoin(atof(levelDetails[currentInWhile]->theCharArray2D[3]),
										atof(levelDetails[currentInWhile]->theCharArray2D[4]),
										atof(levelDetails[currentInWhile]->theCharArray2D[8]));

                                listOfCoins.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
							}
							else
								///Daca e fan
								if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 6)
								{
									std::string details = levelDetails[currentInWhile]->theCharArray2D[7];
									char length[100] = "", powerX[100] = "", powerY[100] = "";
									int nrPauze = 0, kLength = 0, kPowerX = 0, kPowerY = 0;

									for(int i = 0 ; i < details.size(); i++)
									{
										///Length
										if(!nrPauze)
										{
											length[kLength] = details[i];
											kLength++;
										}
										else

											///PowerX
											if(nrPauze == 1)
											{
												powerX[kPowerX] = details[i];
												kPowerX++;
											}
											else

												///PowerY
												if(nrPauze == 2)
												{
													powerY[kPowerY] = details[i];
													kPowerY++;
												}

										if(details[i] == ' ')
										{
											nrPauze++;
										}
									}

									addFan(atof(levelDetails[currentInWhile]->theCharArray2D[3]),
										   atof(levelDetails[currentInWhile]->theCharArray2D[4]),
										   atof(levelDetails[currentInWhile]->theCharArray2D[5]),
										   atof(levelDetails[currentInWhile]->theCharArray2D[6]),
										   atof(length), atof(powerX), atof(powerY));

                                    listOfFans.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
								}
								else
									///Daca e worm hole
									if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 7)
									{
										addWormHole(atof(levelDetails[currentInWhile]->theCharArray2D[7]),
                                                      atof(levelDetails[currentInWhile]->theCharArray2D[8]),
                                                      atof(levelDetails[currentInWhile]->theCharArray2D[3]),
                                                      atof(levelDetails[currentInWhile]->theCharArray2D[4]));

                                        listOfWormHoles.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
									}
                                    else
                                        ///Daca e kinematic square
                                        if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 8)
                                        {
                                            addDinamicSquare(atof(levelDetails[currentInWhile]->theCharArray2D[3]),
                                                             atof(levelDetails[currentInWhile]->theCharArray2D[4]),
                                                             atof(levelDetails[currentInWhile]->theCharArray2D[5]),
                                                             atof(levelDetails[currentInWhile]->theCharArray2D[6]),
                                                             levelDetails[currentInWhile]->theCharArray2D[1], NULL,
                                                             levelDetails[currentInWhile]->theCharArray2D[7],
                                                             b2_kinematicBody, atof(levelDetails[currentInWhile]->theCharArray2D[2]), 0);

                                             ListOfSquareBodies.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
                                        }
                                        else
                                            ///Daca e kinematic circle
                                            if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 9)
                                            {
                                                addDinamicRound(atof(levelDetails[currentInWhile]->theCharArray2D[3]),
                                                                atof(levelDetails[currentInWhile]->theCharArray2D[4]),
                                                                atof(levelDetails[currentInWhile]->theCharArray2D[5]),
                                                                levelDetails[currentInWhile]->theCharArray2D[1],
                                                                NULL, levelDetails[currentInWhile]->theCharArray2D[7],
                                                                b2_kinematicBody, atof(levelDetails[currentInWhile]->theCharArray2D[2]));

                                                ListOfRoundBodies.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
                                            }
                                            else
                                                ///Daca e dust body
                                                if(atof(levelDetails[currentInWhile]->theCharArray2D[0]) == 10)
                                                {
                                                    addDinamicSquare(atof(levelDetails[currentInWhile]->theCharArray2D[3]),
                                                                     atof(levelDetails[currentInWhile]->theCharArray2D[4]),
                                                                     atof(levelDetails[currentInWhile]->theCharArray2D[5]),
                                                                     atof(levelDetails[currentInWhile]->theCharArray2D[6]),
                                                                     levelDetails[currentInWhile]->theCharArray2D[1], NULL,
                                                                     levelDetails[currentInWhile]->theCharArray2D[7],
                                                                     b2_staticBody, atof(levelDetails[currentInWhile]->theCharArray2D[2]), 1);

                                                     ListOfSquareDustBodies.back()->index = atof(levelDetails[currentInWhile]->theCharArray2D[9]);
                                                }
            delete levelDetails[currentInWhile];
		currentInWhile++;
	}

	hero->theBody->SetTransform(b2Vec2(HeroInitialX, HeroInitialY), hero->theBody->GetAngle());
	hero->theBody->ApplyLinearImpulse(b2Vec2(0.1, 0.1), hero->theBody->GetWorldCenter());

	delete levelDetailsAttributes[0];
	delete doc;

	if(levelHasScript)
    {
        addScript(nume);///change nume- add "-script" in its name!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(do it in the function)
    }

	backgroundSky->xInit = (CameraExtremeRight + CameraExtremeLeft) / 2.0f ;
	backgroundSky->yInit = (CameraExtremeUp + CameraExtremeDown) / 2.0f ;

	backgroundMountain->xInit = (CameraExtremeRight + CameraExtremeLeft) / 2.0f ;
	backgroundMountain->yInit = CameraExtremeDown - SCREEN_HEIGHT / 64 / 2.0f ;

	backgroundBush->xInit = (CameraExtremeLeft - SCREEN_WIDTH / 2.0 / 64) + backgroundBush->width / 2.0f;
	backgroundBush->yInit = CameraExtremeDown - SCREEN_HEIGHT / 64 / 2.0f ;

	backgroundHighField->xInit = (CameraExtremeRight + SCREEN_WIDTH / 2.0 / 64) - backgroundHighField->width / 2.0f;
	backgroundHighField->yInit = CameraExtremeDown - SCREEN_HEIGHT / 64 / 2.0f ;

//	backgroundField->xInit = (CameraExtremeRight + CameraExtremeLeft) / 2.0f ;
//	backgroundField->yInit = (CameraExtremeUp + CameraExtremeDown) / 2.0f ;

	std::cout<<'\n'<<"added objects"<<'\n';
}


void BSObstacles::addScript(std::string Path)
{
    ///set the actual path of the script.
    ///if the path of the level is: Level/level1.xml then the path of the script is: Level/level1-script.xml
    std::string newPath = "";
    for(int i = 0; i < Path.size() - 4; i++)
    {
        newPath += Path[i];
    }
    Path = newPath + "-script.xml";

	BSXmlFiles *doc = new BSXmlFiles();
	char theNodes[7][100];
	ListaDeCaractere *levelDetails[1000];
	strcpy(theNodes[0], "Index");
	strcpy(theNodes[1], "xPower");
	strcpy(theNodes[2], "yPower");
	strcpy(theNodes[3], "xLength");
	strcpy(theNodes[4], "yLength");
	strcpy(theNodes[5], "xCoordinate");
	strcpy(theNodes[6], "yCoordinate");

	doc->readAnyXML(Path.c_str(), "Level", "obstacle", levelDetails, theNodes, NULL, NULL, 7, 0);

	int i = 0;

	while(levelDetails[i])
    {
        int index = atof(levelDetails[i]->theCharArray2D[0]);
        bool founded = false;
        ///search the scripted body in the squareBody list
        for(std::list<BSTheSquareBodies*>::iterator j = ListOfSquareBodies.begin(); j != ListOfSquareBodies.end(); j++)
        {
            if((*j)->index == index)
            {
                founded = true;

                BSBodyScript *newScript = new BSBodyScript;
                newScript->xCord = atof(levelDetails[i]->theCharArray2D[5]);
                newScript->xInitial = newScript->xCord;
                newScript->yCord = atof(levelDetails[i]->theCharArray2D[6]);
                newScript->yInitial = newScript->yCord;
                newScript->xPower = atof(levelDetails[i]->theCharArray2D[1]);
                newScript->yPower = atof(levelDetails[i]->theCharArray2D[2]);
                newScript->xLength = atof(levelDetails[i]->theCharArray2D[3]);
                newScript->yLength = atof(levelDetails[i]->theCharArray2D[4]);
                newScript->value1 = 1;
                newScript->value2 = 90;

                (*j)->script = newScript;

                break;
            }
        }
        ///daca nu l-a gasit in lista de squareBody atunci e in cea de roundBodies
        if(!founded)
        {
            for(std::list<BSTheRoundBodies*>::iterator j = ListOfRoundBodies.begin(); j != ListOfRoundBodies.end(); j++)
            {
                if((*j)->index == index)
                {
                    founded = true;

                    BSBodyScript *newScript = new BSBodyScript;
                    newScript->xCord = atof(levelDetails[i]->theCharArray2D[5]);
                    newScript->xInitial = newScript->xCord;
                    newScript->yCord = atof(levelDetails[i]->theCharArray2D[6]);
                    newScript->yInitial = newScript->yCord;
                    newScript->xPower = atof(levelDetails[i]->theCharArray2D[1]);
                    newScript->yPower = atof(levelDetails[i]->theCharArray2D[2]);
                    newScript->xLength = atof(levelDetails[i]->theCharArray2D[3]);
                    newScript->yLength = atof(levelDetails[i]->theCharArray2D[4]);
                    newScript->value1 = 1;
                    newScript->value2 = 90;

                    (*j)->script = newScript;

                    break;
                }
            }
        }

        std::cout<<"new script: "<<index<<' '<<levelDetails[i]->theCharArray2D[5]<<' '<<
                                                    levelDetails[i]->theCharArray2D[6]<<'\n';

		delete levelDetails[i];

        i++;
        ///citesteLevelulCurent.close();
    }

    delete doc;
}







void BSObstacles::addCoin(float x, float y, int taken)
{
//	if(taken == 0)
	{
		BSCoins *newCoin = new BSCoins;
		newCoin->color = {1.f, 1.f, 1.f, 1.f};
		newCoin->width = Hero_size;// / 2.f;
		newCoin->height = Hero_size;// / 2.f;
		newCoin->depth = 0;
		newCoin->sinValue = 90;
		newCoin->deleteIt = false;
		newCoin->xCord = x;
		newCoin->yCord = y;
		newCoin->zCord = scaleSizeInitial;
		newCoin->xInit = x;
		newCoin->yInit = y;

		newCoin->available = taken;

		///daca a fost taken (not available) inseamna ca deja o are
		if(taken == false)
		{
			newCoin->alreadyHadIt = true;
			newCoin->sinValue = 0;
			newCoin->deleteIt = true;
			newCoin->color = {1.f, 1.f, 1.f, 0.f};
		}
		else
		{
			newCoin->alreadyHadIt = false;
		}

		listOfCoins.push_back(newCoin);
	}
}

void BSObstacles::addFan(float x, float y, float width, float height, float length, float powerX, float powerY)
{
	BSFans *newFan = new BSFans;
	newFan->color = {1.f, 1.f, 1.f, 1.f};
	newFan->width = width;
	newFan->height = height;
	newFan->xCord = x;
	newFan->yCord = y;
	newFan->zCord = scaleSizeInitial;
	newFan->powerX = powerX;
	newFan->powerY = powerY;
	newFan->lenthOfPower = length;
	newFan->nrOfParticles = 100;
	listOfFans.push_back(newFan);


	for(int i = 0; i < newFan->nrOfParticles; i++)
    {
        BSBody *newPart = new BSBody;
        BSColorRGBA black = {0, 0, 0, 1};
        newPart->color = black;
        newPart->zCord = scaleSizeInitial;
        float maximX, minimX, maximY, minimY;

        ///daca e pe orizontala
        if(powerX)
        {
            newPart->width = 1;
            newPart->height = 0.05f;
            ///daca bate vantul spre dreapta
            if(powerX > 0)
            {
                maximX = x + length;
                minimX = x;
                ///salvez viteza particulelor pozitiva pe orizontala
                newPart->value1 = (rand()%3 + 1 ) / 10.0f;
            }
            else
            {
                maximX = x;
                minimX = x - length;
                ///salvez viteza particulelor negativa pe orizontala
                newPart->value1 = (rand()%3 + 1) * (-1) / 10.0f;
            }

            maximY = y + (height / 2.0f);
            minimY = y - (height / 2.0f);
            ///viteza pe verticala este 0
            newPart->value2 = 0;
        }
        else
        {
            newPart->width = 0.1f;
            newPart->height = 1;
            maximX = x + (width / 2.0f);
            minimX = x - (width / 2.0f);

            if(powerY > 0)
            {
                maximY = y + length;
                minimY = y;
                newPart->value2 = (rand()%3 + 1 ) / 10.0f;
            }
            else
            {
                maximY = y;
                minimY = y - length;
                newPart->value2 = (rand()%3 + 1) * (-1) / 10.0f;
            }
            newPart->value1 = 0;
        }

        float posX = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximX - minimX + 1) + minimX;
        float posY = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximY - minimY + 1) + minimY;

        newFan->xMax = maximX;
        newFan->yMax = maximY;
        newFan->xMin = minimX;
        newFan->yMin = minimY;

        newPart->xCord = posX;
        newPart->yCord = posY;
        newFan->particles.push_back(newPart);
    }
}






void BSObstacles::setTheMenuButtons(BSButtonStructure* theButtonToSet, BSTexturedVertex2D dataToSet[4],
									float coordinateX, float coordinateY, float ToWidth, float ToHeight,
									GLuint vaoData, GLuint vboData, GLuint iboData)
{
	setTheVaoData(vaoData, vboData, iboData, dataToSet, ToWidth, ToHeight);
}





void BSObstacles::addTheAnimationsForMap(char theLocationOfAnimation[])
{
	std::string newAnimationDetailPath = "Animations/" + BStoString(theLocationOfAnimation) + "/animations.txt";// + "/playerTexture";
	std::string detailName = "";
	char newAnimationDetailPathChar[300] = "";

	for(int  i = 0 ; i < newAnimationDetailPath.size(); i++)
	{
		newAnimationDetailPathChar[i] = newAnimationDetailPath[i];
	}

	std::ifstream animationsDetails(newAnimationDetailPathChar);
	int totalNrAnimations, total1, total2, total3, totalTime1, totalTime2, totalTime3, totalLoop1, totalLoop2, totalLoop3;

	animationsDetails>>totalNrAnimations;

	for(int i = 0 ; i < totalNrAnimations ; i++)
		//while(animationsDetails>>total1>>total2>>total3>>totalTime1>>totalTime2>>totalTime3>>totalLoop1>>totalLoop2>>totalLoop3>>detailName)
	{
		animationsDetails>>total1>>total2>>total3>>totalTime1>>totalTime2>>totalTime3>>totalLoop1>>totalLoop2>>totalLoop3>>detailName;

		std::string newAnimationCale = "Animations/" + BStoString(theLocationOfAnimation) + "/" + detailName + "/playerTexture";// + "/playerTexture";

		//std::cout<<total1<<" "<<total2<<" "<<total3<<" "<<totalTime1<<" "<<totalTime2<<" "<<totalTime3<<" "<<
		//totalLoop1<<" "<<totalLoop2<<" "<<totalLoop3<<" "<<detailName<<'\n';

		int animationIndex = 0;

//	hero->animationIndexPlayerMoveRight = 0;
//	hero->animationIndexPlayerMoveLeft = 1;
//	hero->animationIndexPlayerMoveUpRight = 2;
//	hero->animationIndexPlayerMoveUpLeft = 3;
//	hero->animationIndexPlayerMoveDownRight = 4;
//	hero->animationIndexPlayerMoveDownLeft = 5;
//	hero->animationIndexPlayerStand = 6;
//	hero->animationIndexPlayerDieLeft = 7;
//	hero->animationIndexPlayerDieRight = 8;
//	hero->animationIndexPlayerTeleportedIn = 9;
//	hero->animationIndexPlayerTeleportedOut = 10;
//	hero->animationIndexPlayerAura1 = 11;
//	hero->animationIndexPlayerAura2 = 12;
//	hero->animationIndexPlayerAura3 = 13;
//	hero->animationIndexPlayerAuraElectricity = 14;
//	hero->animationIndexPlayerWormHole = 15;
//	hero->animationIndexPlayerStoppedFromMovingRight = 16;
//	hero->animationIndexPlayerStoppedFromMovingLeft = 17;
//	hero->animationIndexPlayerWallLeft = 18;
//	hero->animationIndexPlayerWallRight = 19;


		if(detailName == "right")
		{
			animationIndex = hero->animationIndexPlayerMoveRight;
		}
		else if(detailName == "left")
		{
			animationIndex = hero->animationIndexPlayerMoveLeft;
		}
		else if(detailName == "up-right")
		{
			animationIndex = hero->animationIndexPlayerMoveUpRight;
		}
		else if(detailName == "up-left")
		{
			animationIndex = hero->animationIndexPlayerMoveUpLeft;
		}
		else if(detailName == "down-right")
		{
			animationIndex = hero->animationIndexPlayerMoveDownRight;
		}
		else if(detailName == "down-left")
		{
			animationIndex = hero->animationIndexPlayerMoveDownLeft;
		}
		else if(detailName == "stand")
		{
			animationIndex = hero->animationIndexPlayerStand;
		}
		else if(detailName == "death-left")
		{
			animationIndex = hero->animationIndexPlayerDieLeft;
		}
		else if(detailName == "death-right")
		{
			animationIndex = hero->animationIndexPlayerDieRight;
		}
		else if(detailName == "teleport-in")
		{
			animationIndex = hero->animationIndexPlayerTeleportedIn;
		}
		else if(detailName == "teleport-out")
		{
			animationIndex = hero->animationIndexPlayerTeleportedOut;
		}
		else if(detailName =="aura1")
        {
            animationIndex = hero->animationIndexPlayerAura1;
        }
		else if(detailName =="aura2")
        {
            animationIndex = hero->animationIndexPlayerAura2;
        }
		else if(detailName =="aura3")
        {
            animationIndex = hero->animationIndexPlayerAura3;
        }
		else if(detailName =="aura-electricity")
        {
            animationIndex = hero->animationIndexPlayerAuraElectricity;
        }
		else if(detailName =="wormHole")
        {
            animationIndex = hero->animationIndexPlayerWormHole;
        }



		animationsObstacleClass->AddObjectInAnimationList(hero, NULL, total1, total2, total3,
				totalTime1, totalTime2, totalTime3,
				newAnimationCale, totalLoop1, totalLoop2, totalLoop3,
				animationIndex);
	}

	std::string newAnimationCale = "Animations/" + BStoString(theLocationOfAnimation) + "/leftWall";// + "/playerTexture";

	///Animation Left Wall
	animationsObstacleClass->AddObjectInAnimationList(hero, NULL, 1, 0, 0,
			10000, 0, 0,
			newAnimationCale, 1, 0, 0,
			hero->animationIndexPlayerWallLeft);

	newAnimationCale = "Animations/" + BStoString(theLocationOfAnimation) + "/rightWall";
	///Animation Right Wall
	animationsObstacleClass->AddObjectInAnimationList(hero, NULL, 1, 0, 0,
			10000, 0, 0,
			newAnimationCale, 1, 0, 0,
			hero->animationIndexPlayerWallRight);

	hero->IsAtStepOfAnimation1 = false;
	hero->IsAtStepOfAnimation2 = false;
	hero->IsAtStepOfAnimation3 = false;

	for(int i = 0 ; i < 5; i++)
	{
		listOfActiveAnimations[i]->indexOfAnimation = i;
	}
}

void BSObstacles::loadAnimationList(std::string path, int firstPart, int secondPart, int thirdPart)
{
	for(int i = 0 ; i < firstPart ; i++)
	{

	}
}



void BSObstacles::addDinamicSquare(float BodyX, float BodyY, float BodyW, float BodyH,
								   char textureName[], GLuint vao, std::string userData,
								   b2BodyType tipulCorpului, int canKillHero, int isDust)
{
	std::cout<<"new square Body: "<<canKillHero<<" "<<BodyX<<" "<<BodyY<<" "<<BodyW<<" "<<BodyH<<" "<<userData<<'\n';
	BSTheSquareBodies *p = new BSTheSquareBodies;

	p->theBody = createBodies(tipulCorpului, BodyX, BodyY, BodyW, BodyH, userData, nrBodies, 0, false);
	setTheVaoData(p->vao, p->vbo, p->ibo, p->data, BodyW, BodyH);

	p->xCord = BodyX;
	p->xInit = BodyX;
	p->yCord = BodyY;
	p->yInit = BodyY;
	p->zCord = scaleSizeInitial;

	p->width = BodyW;
	p->height = BodyH;
	p->script = NULL;
	p->nameOfTexture = textureName;
	renderObstacleClass->loadATexture(textureName, p->texture);
	///p->texture = BodyTex;
//	p->vao = vao;
	p->color = { 1.f, 1.f, 1.f, 1.f };

    p->value1 = 0;
    p->value2 = 0;




	USERDATA* dataForUser = new USERDATA;


    dataForUser->isDustAble = isDust;
    dataForUser->isDust = 0;

	if(canKillHero == 2)
	{
		dataForUser->canKillHero = false;
		dataForUser->isToNextLevel = true;
		p->ObstacleCanKillHero = false;
		p->ObstacleFinishesLevel = true;
	}
	else
	{
		dataForUser->canKillHero = canKillHero;
		dataForUser->isToNextLevel = false;
		p->ObstacleCanKillHero = canKillHero;
		p->ObstacleFinishesLevel = false;
	}

	dataForUser->name = userData;
	p->theBody->SetUserData(dataForUser);

//	setTheVao(p->vao, p->data, p->vbo, p->ibo);

    if(!isDust)
	{
	    ListOfSquareBodies.push_back(p);
	}
	else
    {
	    ListOfSquareDustBodies.push_back(p);
    }
}

void BSObstacles::addDinamicRound(float BodyX, float BodyY, float BodyR,
								  char textureName[], GLuint vao, std::string userData,
								  b2BodyType tipulCorpului, int canKillHero)
{
	std::cout<<"new round Body: "<<canKillHero<<" "<<BodyX<<" "<<BodyY<<" "<<BodyR<<" "<<userData<<'\n';
	BSTheRoundBodies *p = new BSTheRoundBodies;

	p->theBody = createCircleBodies(tipulCorpului, BodyX, BodyY, BodyR / 2, userData, nrBodies, 0, false);
	setTheVaoData(p->vao, p->vbo, p->ibo, p->data, BodyR, BodyR);
	p->radius = BodyR;
	p->nameOfTexture = textureName;
	p->script = NULL;
	renderObstacleClass->loadATexture(textureName, p->texture);
//	p->vao = vao;
	p->color = { 1.f, 1.f, 1.f, 1.f };
	p->isRotating = true;
	p->zCord = scaleSizeInitial;




	USERDATA* dataForUser = new USERDATA;


	if(canKillHero == 2)
	{
		dataForUser->canKillHero = false;
		dataForUser->isToNextLevel = true;
		p->ObstacleCanKillHero = false;
		p->ObstacleFinishesLevel = true;
	}
	else
	{
		dataForUser->canKillHero = canKillHero;
		dataForUser->isToNextLevel = false;
		p->ObstacleCanKillHero = canKillHero;
		p->ObstacleFinishesLevel = false;
	}

	dataForUser->name = userData;
	p->theBody->SetUserData(dataForUser);

//	setTheVao(p->vao, p->data, p->vbo, p->ibo);



	ListOfRoundBodies.push_back(p);
}






void BSObstacles::addOnlyTexture(int squareOrCirlce, float xCoord, float yCoord,
								 float width, float height, std::string texturePath)
{
	if(squareOrCirlce == 1)
	{
		BSTextureSquare *p = new BSTextureSquare;
		setTheVaoData(p->vao, p->vbo, p->ibo, p->data, width, height);
		p->width = width;
		p->height = height;
		p->xCord = xCoord;
		p->yCord = yCoord;
		p->zCord = scaleSizeInitial;
		p->nameOfTexture = texturePath;
		p->color = { 1.f, 1.f, 1.f, 1.f };

//		setTheVao(p->vao, p->data, p->vbo, p->ibo);
		char textureCharPath[100] = "";
		strcpy(textureCharPath, texturePath.c_str());
		renderObstacleClass->loadATexture(textureCharPath, p->texture);

		///Salvez primul corp din lista inlantuita
		ListOfSquareTextures.push_back(p);
	}
	else if(squareOrCirlce == -1)
	{
		std::cout<<"from obstacles: added a round"<<'\n';
		BSTextureRound *p = new BSTextureRound;
		setTheVaoData(p->vao, p->vbo, p->ibo, p->data, width, width);
		p->radius = width;
		p->xCord = xCoord;
		p->yCord = yCoord;
		p->zCord = scaleSizeInitial;
		p->nameOfTexture = texturePath;
		p->color = { 1.f, 1.f, 1.f, 1.f };

//			setTheVao(p->vao, p->data, p->vbo, p->ibo);
		char textureCharPath[100] = "";
		strcpy(textureCharPath, texturePath.c_str());
		renderObstacleClass->loadATexture(textureCharPath, p->texture);

		///Salvez primul corp din lista inlantuita
		ListOfRoundTextures.push_back(p);
	}
}




void BSObstacles::addMessageTexture(float xCoord, float yCoord, float width, float height, char textureName[])
{
	BSTheMessages* newMessage = new BSTheMessages;
	//theMessages[nrOfMessageSign] = new BSTheMessages;
	std::cout<<"animation added: "<<textureName<<'\n';
	///Load the message texture
//    std::string fullTextureName = "Animations/messageAnimation/" + textureName;
//    char nameChar[1000] = "";
//    for(int i = 0 ; i < fullTextureName.size(); i++)
//    {
//        nameChar[i] = fullTextureName[i];
//    }
//std::cout<<"message name: "<<fullTextureName<<'\n';
	renderObstacleClass->loadATexture(textureName, newMessage->textureOfMessage);
	int newWidth, newHeight;
	renderObstacleClass->getTextureWidthAndHeight(textureName, newWidth, newHeight);
	newMessage->widthOfMessage = newWidth / 32;
	newMessage->heightOfMessage = newHeight / 32;

	setTheVaoData(newMessage->vaoBufferOfMessage, newMessage->vboBufferOfMessage, newMessage->iboBufferOfMessage,
				  newMessage->dataOfMessage, newMessage->widthOfMessage, newMessage->heightOfMessage);
//	setTheVao(newMessage->vaoOfMessage, newMessage->dataOfMessage,
//							newMessage->vboBufferOfMessage, newMessage->iboBufferOfMessage);
	newMessage->colorOfMessage = {1.f, 1.f, 1.f, 0.0f};
	newMessage->isShownTheMessage = false;

//    int i = strlen(textureName) - 1;
//    char newNameOfTexture[100] = "";
//    while(textureName[i] != '/')
//	{
//		i--;
//	}
//	for(int j = i + 1 ; j < strlen(textureName); j++)
//	{
//		newNameOfTexture[j - i - 1] = textureName[j];
//	}

	newMessage->nameOfTextureMessage = textureName;

	newMessage->xCord = xCoord;
	newMessage->yCord = yCoord;




	///Load the message sign texture
	//if(!nrOfMessageSign)
	{
		std::string fullTextureName = "Animations/messageAnimation/theMessageSign.png";
		const char *signChar = fullTextureName.c_str();

		renderObstacleClass->loadATexture(signChar, newMessage->textureOfSign);
		setTheVaoData(newMessage->vaoBufferOfSign, newMessage->vboBufferOfSign, newMessage->iboBufferOfSign,
					  newMessage->dataOfSign, Hero_size, Hero_size * 2.0f);
//		setTheVao(newMessage->vaoOfSign, newMessage->dataOfSign,
//								newMessage->vboBufferOfSign, newMessage->iboBufferOfSign);
		newMessage->widthOfSign = Hero_size;
		newMessage->heightOfSign = Hero_size * 1.5f;
		newMessage->colorOfSign = {1.f, 1.f, 1.f, 1.f};
	}
	listOfMessages.push_back(newMessage);
	nrOfMessageSign++;
}



void BSObstacles::addSnowFlakeS()
{
	float maximX = CameraExtremeRight + (SCREEN_WIDTH / 32 / 2.0f);
	float minimX = CameraExtremeLeft - (SCREEN_WIDTH / 32 / 2.0f);

	float maximY = CameraExtremeUp + (SCREEN_HEIGHT / 32 / 2.0f);
	float minimY = CameraExtremeDown - (SCREEN_HEIGHT / 32 / 4.0f);

	float posX, posY, xSpeedMin, xSpeedMax, ySpeedMin, ySpeedMax, xSpeed, ySpeed;
	int leftOrRight;


	for(int i = 0 ; i < 150; i++)
	{
		BSSnowFlakes *newFlake = new BSSnowFlakes;

		posX = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximX - minimX + 1) + minimX;
		posY = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maximY - minimY + 1) + minimY;

		newFlake->xCord = posX;
		newFlake->yCord = posY;
		newFlake->zCord = scaleSizeInitial;

		newFlake->sinValue = 90;
		newFlake->color = {0, 0, 0, 1};

		if(rand() % 2)
		{
			leftOrRight = 1;
		}
		else
		{
			leftOrRight = -1;
		}

		newFlake->radius = float ((rand() % 4 ) / 10.0f);
		newFlake->xPower = float (rand() % 4 + 2) / 1000 * leftOrRight;
		newFlake->yPower = float (rand() % 10 + 2) / 1000;

		setVaoForChunckObjects(newFlake->vao, newFlake->vbo, newFlake->ibo, newFlake->data, newFlake->radius, newFlake->radius);
//		setTheVaoData(newFlake->vao, newFlake->vbo, newFlake->ibo,
//					  newFlake->data, newFlake->radius, newFlake->radius);
//		setTheVao(newFlake->vaoOfFlake, newFlake->dataOfFlake, newFlake->vbo, newFlake->ibo);

		listOfSnowFlakes.push_back(newFlake);
		newFlake = NULL;
		delete newFlake;
	}
}


void BSObstacles::createMouseCircles()
{
	float lastR = 0.2;
	for(int i = 1 ; i < 15 ; i++)
	{
		BSWorldOfGooMouse *circ = new BSWorldOfGooMouse;

		circ->radius = lastR;
		circ->xCord = 0;
		circ->yCord = 0;
		circ->zCord = scaleSizeInitial;
		setTheVaoData(circ->vao, circ->vbo, circ->ibo, circ->data, circ->radius, circ->radius);
//		setTheVao(circ->vaoOfMouse, circ->dataOfMouse, circ->vbo, circ->ibo);
		listOfMouseCircles.push_back(circ);

		lastR += 0.03f;
	}
}

void BSObstacles::addBackgrounds()
{

	float ratioImage = 1.77f;


	BSColorRGBA color = {1, 1, 1, 1};



	backgroundSky->height = (float) SCREEN_HEIGHT / 32;
	backgroundSky->width = (float) backgroundSky->height * ratioImage;
	backgroundSky->color = color;
	renderObstacleClass->loadATexture("Background images/sky.png", backgroundSky->texture);
	setTheVaoData(backgroundSky->vao, backgroundSky->vbo, backgroundSky->ibo,
				  backgroundSky->data, backgroundSky->width, backgroundSky->height);
//	setTheVao(backgroundSky->vao, backgroundSky->data,
//					backgroundSky->vbo, backgroundSky->ibo);

	backgroundMountain->height = (float) SCREEN_HEIGHT / 32;
	backgroundMountain->width = (float) backgroundMountain->height * ratioImage;
	backgroundMountain->color = color;
	renderObstacleClass->loadATexture("Background images/mountains.png", backgroundMountain->texture);
	setTheVaoData(backgroundMountain->vao, backgroundMountain->vbo, backgroundMountain->ibo,
				  backgroundMountain->data, backgroundMountain->width, backgroundMountain->height);
//	setTheVao(backgroundMountain->vao, backgroundMountain->data,
//					backgroundMountain->vbo, backgroundMountain->ibo);

	backgroundBush->height = (float) SCREEN_HEIGHT / 32;
	backgroundBush->width = (float) backgroundBush->height * ratioImage;
	backgroundBush->color = color;
	renderObstacleClass->loadATexture("Background images/bush.png", backgroundBush->texture);
	setTheVaoData(backgroundBush->vao, backgroundBush->vbo, backgroundBush->ibo,
				  backgroundBush->data, backgroundBush->width, backgroundBush->height);
//	setTheVao(backgroundBush->vao, backgroundBush->data,
//					backgroundBush->vbo, backgroundBush->ibo);

	backgroundField->height = (float) SCREEN_HEIGHT / 32;
	backgroundField->width = (float) backgroundField->height * ratioImage;
	backgroundField->color = color;
	renderObstacleClass->loadATexture("Background images/field.png", backgroundField->texture);
	setTheVaoData(backgroundField->vao, backgroundField->vbo, backgroundField->ibo,
				  backgroundField->data, backgroundField->width, backgroundField->height);
//	setTheVao(backgroundField->vao, backgroundField->data,
//					backgroundField->vbo, backgroundField->ibo);

	backgroundHighField->height = (float) SCREEN_HEIGHT / 32;
	backgroundHighField->width = (float) backgroundHighField->height * ratioImage;
	backgroundHighField->color = color;
	renderObstacleClass->loadATexture("Background images/high field.png", backgroundHighField->texture);
	setTheVaoData(backgroundHighField->vao, backgroundHighField->vbo, backgroundHighField->ibo,
				  backgroundHighField->data, backgroundHighField->width, backgroundHighField->height);
//	setTheVao(backgroundHighField->vao, backgroundHighField->data,
//					backgroundHighField->vbo, backgroundHighField->ibo);
}


void BSObstacles::addCloudyParticles()
{
	float minimSize = 3;
	float maximSize = 4;



	int leftOrRight = 0;
	for(int i = 0; i < 10; i++)
	{
		BSCloudyParticles *part = new BSCloudyParticles;
		part->color = {1, 1, 1, 1};
		int randomul = rand() % 5 + 1;

		if(randomul % 2)
		{
			leftOrRight = 1;
		}
		else
		{
			leftOrRight = -1;
		}

		part->texture = clouds[randomul];


		part->width = (float) ((rand() / ((float)RAND_MAX + 1.0)) * (maximSize - minimSize + 1) + minimSize) / 10.0f;///float ((rand() % 10 ) / 10.0f);
		part->height = part->width;///float ((rand() % 10 ) / 10.0f);///((float)rand() / ((float)RAND_MAX + 1.0)) * (maximSize - minimSize + 1) + minimSize;
		part->xPower = float (rand() % 4 + 2) / 1000 * leftOrRight;
		part->yPower = float (rand() % 10 + 2) / 1000 * (-1);

		setTheVaoData(part->vao, part->vbo, part->ibo, part->data, part->width, part->height);
//		setTheVao(part->vaoOfParticle, part->dataOfParticle, part->vbo, part->ibo);

		listOfCloudyParticles.push_back(part);
	}
}




void BSObstacles::addWormHole(int index, int connectionIndex, float x, float y)
{
	std::cout<<"new worm hole: "<<x<<" "<<y<<" "<<index<<" "<<connectionIndex<<'\n';
	BSWormHole *newWorm = new BSWormHole;
	newWorm->value1 = 0;
	newWorm->xCord = x;
	newWorm->yCord = y;
	newWorm->zCord = scaleSizeInitial;
	newWorm->indexOfWorm = index;
	newWorm->connectionIndex = connectionIndex;

	listOfWormHoles.push_back(newWorm);
}

void BSObstacles::deleteAllWormHoles()
{
	while(!listOfWormHoles.empty())
	{
		delete listOfWormHoles.front();
		listOfWormHoles.pop_front();
	}
}





void BSObstacles::addTheTexturesOfCloudyParticles()
{
	for(int i = 1; i <= 5; i++)
	{
		renderObstacleClass->loadATexture("Background images/cloud" + BStoString(i) + ".png", clouds[i]);
	}
}







void BSObstacles::destroyLevel()
{
	destroyAllBodiesSquare();
	destroyAllBodiesRound();
	destroyAllBodiesDustSquare();
	destroyAllCoins();
	destroyAllFans();
	deleteAllWormHoles();
}

void BSObstacles::destroyAllBodiesDustSquare()
{
	//system("PAUSE");
	while(!ListOfSquareDustBodies.empty())
	{
		BSTheSquareBodies *deletedBody = (BSTheSquareBodies*)ListOfSquareDustBodies.front();

		glDeleteBuffers( 1, &deletedBody->vbo);
		glDeleteBuffers( 1, &deletedBody->ibo);
		glDeleteTextures(1, &deletedBody->texture);
		glDeleteVertexArrays(1, &deletedBody->vao);

        if(deletedBody->theBody)
		{
		    world->DestroyBody(deletedBody->theBody);
		}

		delete ListOfSquareDustBodies.front();
		ListOfSquareDustBodies.pop_front();
//		delete deletedBody;
	}

	selectedSquareBody = NULL;
}

void BSObstacles::destroyAllBodiesSquare()
{
	//system("PAUSE");
	while(!ListOfSquareBodies.empty())
	{
		BSTheSquareBodies *deletedBody = (BSTheSquareBodies*)ListOfSquareBodies.front();

		glDeleteBuffers( 1, &deletedBody->vbo);
		glDeleteBuffers( 1, &deletedBody->ibo);
		glDeleteTextures(1, &deletedBody->texture);
		glDeleteVertexArrays(1, &deletedBody->vao);

		world->DestroyBody(deletedBody->theBody);

        if(deletedBody->script)
		{
		    delete deletedBody->script;
		}

		delete deletedBody;
		ListOfSquareBodies.pop_front();
//		delete deletedBody;
	}

	selectedSquareBody = NULL;
}

void BSObstacles::destroyAllBodiesRound()
{
	while(!ListOfRoundBodies.empty())
	{
		BSTheRoundBodies *deletedBody = (BSTheRoundBodies*)ListOfRoundBodies.front();

		glDeleteBuffers( 1, &deletedBody->vbo);
		glDeleteBuffers( 1, &deletedBody->ibo);
		glDeleteTextures(1, &deletedBody->texture);
		glDeleteVertexArrays(1, &deletedBody->vao);

		world->DestroyBody(deletedBody->theBody);

        if(deletedBody->script)
		{
		    delete deletedBody->script;
		}

		delete ListOfRoundBodies.front();
		ListOfRoundBodies.pop_front();
//		delete deletedBody;
	}

	selectedRoundBody = NULL;
}

void BSObstacles::deleteAllMessageTexture()
{
	while(!listOfMessages.empty())
	{
		BSTheMessages *deletedBody = (BSTheMessages*)listOfMessages.front();

		glDeleteBuffers( 1, &deletedBody->vboBufferOfSign);
		glDeleteBuffers( 1, &deletedBody->vboBufferOfMessage);
		glDeleteBuffers( 1, &deletedBody->iboBufferOfMessage);
		glDeleteBuffers( 1, &deletedBody->iboBufferOfSign);
		glDeleteTextures(1, &deletedBody->textureOfMessage);
		glDeleteVertexArrays(1, &deletedBody->vaoBufferOfMessage);
		glDeleteTextures(1, &deletedBody->textureOfSign);
		glDeleteVertexArrays(1, &deletedBody->vaoBufferOfSign);

		//world->DestroyBody(deletedBody->theBody);

		delete listOfMessages.front();
		listOfMessages.pop_front();
//		delete deletedBody;
	}

	nrOfMessageSign = 0;
}

void BSObstacles::deleteBodySquare(BSTheSquareBodies* &corpulCareVreauSters)
{
	world->DestroyBody(corpulCareVreauSters->theBody);

	ListOfSquareBodies.remove(corpulCareVreauSters);
	delete corpulCareVreauSters;
}

void BSObstacles::deleteBodyRound(BSTheRoundBodies* &corpulCareVreauSters)
{
	world->DestroyBody(corpulCareVreauSters->theBody);

	ListOfRoundBodies.remove(corpulCareVreauSters);
	delete corpulCareVreauSters;
}

void BSObstacles::destroyAllCoins()
{
	while(!listOfCoins.empty())
	{
		delete listOfCoins.back();
		listOfCoins.pop_back();
	}
}

void BSObstacles::destroyAllFans()
{
	while(!listOfFans.empty())
	{
	    std::list<BSBody*> theList = ((BSFans*)(listOfFans.back()))->particles;
        while(!theList.empty())
        {
            delete theList.back();
            theList.pop_back();
        }
		delete listOfFans.back();
		listOfFans.pop_back();
	}
}

void BSObstacles::destroyAllAnimations()
{
	///std::list<BSNewList*>::iterator iteratorLista;

	///First, go through every list and delete the animations
	for(int i = 0; i < nrOfListOfAnimations; i++)
	{
		///Deleting the textures and VAOs of every animations
		std::list<BSAnimation*>::iterator j;

		///First list of animations
		for(j = listOfAnimations[i]->listForAnimations1.begin();// ListOfAnimations.begin();
				j != listOfAnimations[i]->listForAnimations1.end();//ListOfAnimations.end();
				j++)
		{
			glDeleteBuffers(1, &(*j)->vbo);
			glDeleteBuffers(1, &(*j)->ibo);
			glDeleteTextures(1, &(*j)->texture);
			glDeleteVertexArrays(1, &(*j)->vao);
		}

		///Emptying the list of animations for each animation List
		while(!listOfAnimations[i]->listForAnimations1.empty())
		{
			delete listOfAnimations[i]->listForAnimations1.front();
			listOfAnimations[i]->listForAnimations1.pop_front();
		}

		///Second list of animations
		for(j = listOfAnimations[i]->listForAnimations2.begin();// ListOfAnimations.begin();
				j != listOfAnimations[i]->listForAnimations2.end();//ListOfAnimations.end();
				j++)
		{
			glDeleteBuffers(1, &(*j)->vbo);
			glDeleteBuffers(1, &(*j)->ibo);
			glDeleteTextures(1, &(*j)->texture);
			glDeleteVertexArrays(1, &(*j)->vao);
		}

		///Emptying the list of animations for each animation List
		while(!listOfAnimations[i]->listForAnimations2.empty())
		{
			delete listOfAnimations[i]->listForAnimations2.front();
			listOfAnimations[i]->listForAnimations2.pop_front();
		}

		///Third list of animations
		for(j = listOfAnimations[i]->listForAnimations3.begin();// ListOfAnimations.begin();
				j != listOfAnimations[i]->listForAnimations3.end();//ListOfAnimations.end();
				j++)
		{
			glDeleteBuffers(1, &(*j)->vbo);
			glDeleteBuffers(1, &(*j)->ibo);
			glDeleteTextures(1, &(*j)->texture);
			glDeleteVertexArrays(1, &(*j)->vao);
		}

		///Emptying the list of animations for each animation List
		while(!listOfAnimations[i]->listForAnimations3.empty())
		{
			delete listOfAnimations[i]->listForAnimations3.front();
			listOfAnimations[i]->listForAnimations3.pop_front();
		}
	}

	///Emptying the list of animations
	while(nrOfListOfAnimations > 0)
	{
		delete listOfAnimations[nrOfListOfAnimations - 1];
		nrOfListOfAnimations--;
	}
}




