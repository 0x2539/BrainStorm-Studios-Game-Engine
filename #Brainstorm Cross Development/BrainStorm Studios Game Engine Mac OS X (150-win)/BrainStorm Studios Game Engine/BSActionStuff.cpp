
#include "BSActionStuff.h"
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

float TeleportX = 0, TeleportY = 0;

BSObstacles *obstaclesActionClass = new BSObstacles();
BSTexture *renderActionClass =  new BSTexture();


int timpulCareTrece = 0, timpulCareAtrecut = 0, jumpedFromLeftOrRight = 0;
long long OriginalTimeOnWall = 0, currentTime = 0, OriginalTimeToJumpUpTheWall = 0, timeToCreateParticles = 0;
bool imprimeForceOnWall = false, heroCanTeleportAgain = true, justHitTheGround = false;

b2Vec2 vel, velocity;
bool heroJustStopped = false;
float desiredVelX = 0, desiredVelY = 0;
float velChangeX, velChangeY;
float impulseX, impulseY, turnMultiplier = 1.f, turnMultiplierInAir = 5.5f, timeE = 0;

int nnrr = 0;


int currentTexture = 0;


bool aCreat = false;
int indexCurent = 0;
int currentParticleNr = 0;
int pozitivSauNegativ = 0;






void BSActionStuff::levelFinished()
{
	//iau timpul curent
	timpulCareTrece = SDL_GetTicks();
	
	//daca este diferit de -1 inseamna ca a trecut un anumit interval de timp
	if(timpulCareTrece != -1)
	{
		//il fac sa se micsoreze atata timp cat cercul cel mic are o anumita raza
		if(razaInitialaInner > 3)
		{
			razaInitialaInner --;
		}
		else
		{
			//aici numarul timpul in care cercul nu se micsoreaza
			if(timpulCareAtrecut != 30)
			{
				timpulCareAtrecut++;
			}
		}
		
		//daca dupa un anumit timp in care cercul nu s-a micsorat, incep sa il micsorez din nou
		//iar raza trebuie sa fie > 0 pentru ca altfel o sa se albeasca cercul
		//daca se albeste imaginea dupa ce se termina cercul, inseamna ca raza inner, este mai mare decat raza
		//outer, asa ca sa schimb valoarea pe care o scad la razaInitialaInner
		if(timpulCareAtrecut == 30 && razaInitialaInner > 0.1f)
		{
			razaInitialaInner -=0.1f;
			
			if(razaInitialaInner == 0)
			{
				timpulCareAtrecut = 0;
			}
		}
		else
			
			//resetez timpul in care a stat oprit
			if(razaInitialaInner == 0)
			{
				timpulCareAtrecut = 0;
			}
	}
	
}


void BSActionStuff::controlAir(float T, b2Body *body)
{
	if (ButtonJump && pressedJumpSecond)
	{
		alSourcePlay(SourceSoundJump);
		
		canJumpVertically = false;
		velocity.y = speedJumpUp;
		ButtonJump = false;
		body->SetLinearVelocity(velocity);
		return;
	}
	
	// Abort jump if user lets go of button
	if (velocity.y > 0 && !ButtonJump)
	{
		velocity.y = 0;
	}
	
    if (isSpaceDown && hero->heroIsBerserk3 && isInAir && body->GetLinearVelocity().y <= 0)
    {
        body->ApplyForce(b2Vec2(0, 33), body->GetWorldCenter());
		//            std::cout<<"hjere"<<'\n';
		//            velocity.y = 40;
    }
	
	
	if(!itWalksInAir(body, T * 0.2f))
	{
	}
}

void BSActionStuff::controlWall(b2Body *body)
{
	//std::cout<<"touches the wall  "<<SDL_GetTicks()<<" "<<OriginalTimeOnWall<<'\n';
	if(nnrr <= 2)
	{
		nnrr++;
	}
	
	if(nnrr == 3)
	{
		nnrr = 0;
		imprimeForceOnWall = false;
		jumpedFromLeftOrRight = 0;
	}
	
	//ii dau valoarea 0 pe orizontala cand se afla pe perete
	//body->ApplyLinearImpulse( b2Vec2(0,0), body->GetWorldCenter() );
	//velocity.x = 0;
	
	//verifica daca vrea sa  sara de pe perete pe alt perete
	if(canJumpHorizontally && ((ButtonRight && isOnLeftWall) || (ButtonLeft && isOnRightWall)) && ButtonJump)
	{
		alSourcePlay(SourceSoundJump);
		//*-1 pentru ca atunci cand e pe peretele din stanga (de exemplu) va trebui sa ii imprim
		//o forta pozitiva, dar variableWall are val -1 pe peretele din stanga
		velocity.x = speedJumpToSide * variableWall * (-1);
		float velChangeX = velocity.x - hero->theBody->GetLinearVelocity().x;
		float impulseX = body->GetMass() * velChangeX;
		
		
		velocity.y = speedJumpUp * 1.2f;// * variableWall * (-1);
		float velChangeY = velocity.y - hero->theBody->GetLinearVelocity().y;
		float impulseY = body->GetMass() * velChangeY;
		
		
		ButtonJump = false;
		//body->SetLinearVelocity(velocity);
		body->ApplyLinearImpulse( b2Vec2(impulseX,impulseY), body->GetWorldCenter() );
	}
	else
		
		//verific daca vrea sa sara pe acelasi perete in sus
		if(canJumpHorizontally && ((ButtonLeft && isOnLeftWall) || (ButtonRight && isOnRightWall)) && ButtonJump)
		{
			alSourcePlay(SourceSoundJump);
			velocity.x = speedJumpToTheSameSide * variableWall * (-1);
			float velChangeX = velocity.x - hero->theBody->GetLinearVelocity().x;
			float impulseX = body->GetMass() * velChangeX;
			
			
			velocity.y = speedJumpUpOnWall;// * variableWall * (-1);
			float velChangeY = velocity.y - hero->theBody->GetLinearVelocity().y;
			float impulseY = body->GetMass() * velChangeY;
			
			
			//body->SetLinearVelocity(velocity);
			body->ApplyLinearImpulse( b2Vec2(impulseX,impulseY), body->GetWorldCenter() );
			imprimeForceOnWall = true;
			//std::cout<<"jumped"<<'\n';
			nnrr = 1;
			
			OriginalTimeToJumpUpTheWall = SDL_GetTicks();
			
			//salvez de pe care perete a sarit
			if(isOnLeftWall)
			{
				jumpedFromLeftOrRight = -1;
			}
			else
			{
				jumpedFromLeftOrRight = 1;
			}
            ButtonJump = false;
		}
		else
			
			//verific daca vrea sa sara de pe perete
			if(canJumpHorizontally && ButtonJump)
			{
				alSourcePlay(SourceSoundJump);
				velocity.x = (speedJumpToSide / 2.f) * variableWall * (-1);
				float velChangeX = velocity.x - hero->theBody->GetLinearVelocity().x;
				float impulseX = body->GetMass() * velChangeX;
				
				
				velocity.y = speedJumpUp;// * variableWall * (-1);
				float velChangeY = velocity.y - hero->theBody->GetLinearVelocity().y;
				float impulseY = body->GetMass() * velChangeY;
				
				
				//body->SetLinearVelocity(velocity);
				body->ApplyLinearImpulse( b2Vec2(impulseX,impulseY), body->GetWorldCenter() );
                ButtonJump = false;
			}
	
	//CanGoAwayFromWall(12);
	
	//verifica daca vrea sa se indeparteze de perete fara sa sara
	if(((ButtonRight && isOnLeftWall) || (ButtonLeft && isOnRightWall)) && OriginalTimeOnWall == 0)
	{
		//float verifyTime = timp->getTime();
		//if(verifyTime != -1)
		{
			OriginalTimeOnWall = SDL_GetTicks();
		}
	}
	else
		
		//verifica timpul scurs pe perete cand apasa sa sara de pe el
		if(((ButtonRight && isOnLeftWall) || (ButtonLeft && isOnRightWall)) && CanGoAwayFromWall(OriginalTimeOnWall))
		{
			std::cout<<"goes off\n";
			itWalksInAir(body, 1.1f);
			OriginalTimeOnWall = 0;
		}
		else
			
			//in cazul in care renunta sa sara, va reseta timpul in care sa sara
			if(	((ButtonRight == false && isOnLeftWall) || (ButtonLeft == false && isOnRightWall))
               && OriginalTimeOnWall != 0)
			{
				OriginalTimeOnWall = 0;
			}
	
	//std::cout<<"        is on wall\n";
}

void BSActionStuff::controlGround(b2Body *body, float T)
{
	imprimeForceOnWall = false;
	
	//if(body->GetLinearVelocity().x || body->GetLinearVelocity().y)
	//std::cout<<body->GetLinearVelocity().x<<" "<<body->GetLinearVelocity().y<<'\n';
	if (ButtonJump && canJumpVertically)
	{
		alSourcePlay(SourceSoundJump);
		
		canJumpVertically = false;
		velocity.y = speedJumpUp;
		ButtonJump = false;
		body->SetLinearVelocity(velocity);
		return;
	}
	
	// Run on ground
	if (!itWalks(body, T))
	{
		velocity.x = 0;
		body->SetLinearVelocity(velocity);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
     //		//std::cout<<jumpsUpTheWall<<" " << ButtonLeft << " " << ButtonRight << " " << ButtonJump<<'\n';
     b2Vec2 velc;// = new b2Vec2();
     if (ButtonJump == true && canJumpVertically == true)
     {
     //timeStart = getTime();
     canJumpVertically = false;
     //timeStop = 0;
     velc.y = speedJumpUp;
     hero->theBody->SetLinearVelocity(velc);
     return;
     }
     else
     if(ButtonJump == false && canJumpVertically == true)
     {
     velc.y = 0;
     hero->theBody->SetLinearVelocity(velc);
     }
	 
	 
     float sign = 0;
     if (ButtonRight == true && ButtonLeft == false)
     {
     sign = 1;
     }
     else
     if (ButtonRight == false && ButtonLeft == true)
     {
     sign = -1;
     }
	 
     //std::cout<<velc.x<<" " << velc.y << " " << sign << '\n';
	 
     if(sign != 0)
     {
     ////std::cout<<velc.x<<'\n';
     float currSign = 0;
     if(hero->theBody->GetLinearVelocity().x > 0)
     {
     currSign = 1;
     }
     else
     if(hero->theBody->GetLinearVelocity().x < 0)
     {
     currSign = -1;
     }
	 
     //this is to check if AccelerationButton is pressed
     //float v = walkAccel();
     float v = speedWalk;
     float turnMul = 1;
     float T = 0.1f;
	 
     if ((currSign != 0) && (currSign != sign))
     {
     v *= turnMul;
     }
     velc.x += v * sign * T;
     hero->theBody->SetLinearVelocity(velc);
     }
     else
     {
     velc.x = 0;
     hero->theBody->SetLinearVelocity(velc);
     }*/
}

void BSActionStuff::controlCorner(b2Body *body)
{
	//std::cout<<"corner\n";
	
	//pun vel.x =0, pentru ca altfel ar sari la inceput putin, dupa care sare mult
	velocity.x = 0;
	body->SetLinearVelocity(velocity);
	
	velocity.y = 0;
	
	if (ButtonJump && canJumpVertically)
	{
		alSourcePlay(SourceSoundJump);
		canJumpVertically = false;
		velocity.y = speedJumpUpOnWall;
		body->SetLinearVelocity(velocity);
		return;
	}
	
	itWalks(hero->theBody, 0.1f);
}

inline bool BSActionStuff::itWalks(b2Body *body, float T)
{
	float sign = 0;
	
	if (ButtonRight && ButtonLeft == false)
	{
		sign = 1;
	}
	else
		if (ButtonRight == false && ButtonLeft)
		{
			sign = -1;
		}
		else
			return false;
	
	float currentSign = 0;
	
	if(body->GetLinearVelocity().x < 0)
	{
		currentSign = -1;
	}
	else
		if(body->GetLinearVelocity().x > 0)
		{
			currentSign = 1;
		}
	
	float v = speedWalk;
	
	if (currentSign != 0 && currentSign != sign)
	{
		//iau pozitia ca sa stiu cum misc camera
		startPositionCameraX = hero->theBody->GetPosition().x;
		
		v *= turnMultiplier;
		//body->SetLinearVelocity(b2Vec2(0, 0));
		//std::cout<<v<<'\n';
	}
	
	//verific daca viteza curenta este mai mica decat viteza maxima, altfel nu mai maresc viteza
	if(sign < 0)
	{
		if(velocity.x > 0)
		{
			velocity *= -1 * T;
		}
		
		if(velocity.x > -speedWalk)
		{
			velocity.x += v * sign * T;
		}
		else
		{
			velocity.x = -speedWalk;
		}
	}
	else
		if(sign > 0)
		{
			if(velocity.x < 0)
			{
				velocity *= -1 * 0.1f;
			}
			
			if(velocity.x < speedWalk)
			{
				velocity.x += v * sign * T;
			}
			else
			{
				velocity.x = speedWalk;
			}
		}
	
	float velChangeX = velocity.x - hero->theBody->GetLinearVelocity().x;
	float impulseX = body->GetMass() * velChangeX;
	//body->SetLinearVelocity(velocity);
	body->ApplyLinearImpulse( b2Vec2(impulseX,0), body->GetWorldCenter() );
	
	//std::cout<<" "<<hero->theBody->GetLinearVelocity().x<<'\n';
	
	return true;
}

bool BSActionStuff::itWalksInAir(b2Body *body, float T)
{
	if(imprimeForceOnWall == false)
	{
		float sign = 0;
		
		if (ButtonRight && ButtonLeft == false)
		{
			sign = 1;
		}
		else
			if (ButtonRight == false && ButtonLeft)
			{
				sign = -1;
			}
			else
				return false;
		
		float currentSign = 0;
		
		if(body->GetLinearVelocity().x < 0)
		{
			currentSign = -1;
		}
		else
			if(body->GetLinearVelocity().x > 0)
			{
				currentSign = 1;
			}
		
		float v = speedWalkInAir;
		
		if (currentSign != 0 && currentSign != sign)
		{
			//iau pozitia ca sa stiu cum misc camera
			startPositionCameraX = hero->theBody->GetPosition().x;
			v *= turnMultiplierInAir;
		}
		
		//verific daca viteza curenta este mai mica decat viteza maxima, altfel nu mai maresc viteza
		if(sign < 0)
		{
			if(velocity.x > -speedWalkInAir)
			{
				velocity.x += v * sign * T;
			}
			else
			{
				velocity.x = -speedWalkInAir;
			}
		}
		else
		{
			if(velocity.x < speedWalkInAir)
			{
				velocity.x += v * sign * T;
			}
			else
			{
				velocity.x = speedWalkInAir;
			}
		}
		
		float velChangeX = velocity.x - hero->theBody->GetLinearVelocity().x;
		float impulseX = body->GetMass() * velChangeX;
		//body->SetLinearVelocity(velocity);
		body->ApplyLinearImpulse( b2Vec2(impulseX,0), body->GetWorldCenter() );
		
		//std::cout<<hero->theBody->GetLinearVelocity().x<<"     "<<hero->theBody->GetLinearVelocity().y<<"   "<<sign<<'\n';
		
		return true;
	}
	else
	{
		if( (jumpedFromLeftOrRight < 0 && ButtonRight) || (jumpedFromLeftOrRight > 0 && ButtonLeft))
		{
			imprimeForceOnWall = false;
			std::cout<<"a apasat\n";
		}
		
		//std::cout<<"jumps us"<<'\n';
		//if(body->GetLinearVelocity().x > 0)
		
		if(SDL_GetTicks() - OriginalTimeToJumpUpTheWall > timeToStayInAirWhenJumpsOnTheSameWall * (theTimeHowFast / 60))
		{
			if(jumpedFromLeftOrRight < 0)
			{
				velocity.x = -speedJumpToTheSameSide;
			}
			else
			{
				velocity.x = speedJumpToTheSameSide;
				//body->ApplyForce(b2Vec2(100 , 0), body->GetWorldCenter());
			}
			
			float velChangeX = velocity.x - hero->theBody->GetLinearVelocity().x;
			float impulseX = body->GetMass() * velChangeX * 0.07 * 1.2f;
			//body->SetLinearVelocity(velocity);
			
			
			body->ApplyLinearImpulse( b2Vec2(impulseX,0), body->GetWorldCenter() );
			//body->ApplyForce(b2Vec2(-500 , 0), body->GetWorldCenter());
		}
		else
		{
			if(jumpedFromLeftOrRight < 0)
			{
				velocity.x = -speedJumpToTheSameSide;
			}
			else
			{
				velocity.x = speedJumpToTheSameSide;
				//body->ApplyForce(b2Vec2(100 , 0), body->GetWorldCenter());
			}
			
			float velChangeX = velocity.x - hero->theBody->GetLinearVelocity().x;
			float impulseX = body->GetMass() * velChangeX * 0.07 * 0.7f;
			//body->SetLinearVelocity(velocity);
			
			
			body->ApplyLinearImpulse( b2Vec2(impulseX,0), body->GetWorldCenter() );
			//body->ApplyForce(b2Vec2(-500 , 0), body->GetWorldCenter());
		}
	}
}





void BSActionStuff::moveThePlayer()
{
	///Kill the hero if goes over the boundaries
	if(hero->theBody->GetPosition().x < gameBoundLeft - 1 ||
       hero->theBody->GetPosition().x > gameBoundRight + 1 ||
       hero->theBody->GetPosition().y < gameBoundDown - 1 ||
       hero->theBody->GetPosition().y > gameBoundUp + 1)
	{
		alSourcePlay(SourceSoundDies);
		
        hero->heroIsBerserk1 = false;
        hero->heroIsBerserk2 = false;
        hero->heroIsBerserk3 = false;
		
		hero->heroIsDead = true;
		std::cout<<"dead out of boundary"<<'\n';
		hero->texture = playerTextureDead;
		hero->heroWasDead = true;
	}
	
	///ActionFuncTeleportHero();
	//std::cout<<easeOut(1, 1, 1, 2)<<'\n';
	//float timpul = timp->getTime();
	//if(timpul != -1)
	{
		//std::cout<<SDL_GetTicks()<<'\n';
	}
	//vel = hero->theBody->GetLinearVelocity();
	desiredVelX = 0;
	
	///Also Set the animation index for when it stops
	if(hero->theBody->GetPosition().x != lastPositionOfHeroX)
	{
		hero->heroStopped = false;
		heroJustStopped = false;
		itMovedX = true;
		
		///See which direction is the hero facing
		if(hero->theBody->GetLinearVelocity().x > 0)
		{
			heroFacesLeftOrRight = 1;
		}
		else
			if(hero->theBody->GetLinearVelocity().x < 0)
			{
				heroFacesLeftOrRight = -1;
			}
	}
	else
	{
		if(itMovedX)
		{
			hero->heroStopped = true;
			heroJustStopped = true;
			timer = SDL_GetTicks();
		}
		
		itMovedX = false;
	}
	
	if(hero->theBody->GetLinearVelocity().y != 0)
	{
		hero->heroStopped = false;
		heroJustStopped = false;
		itMovedY = true;
	}
	else
	{
		if(itMovedY)
		{
			hero->heroStopped = true;
			heroJustStopped = true;
			timer = SDL_GetTicks();
		}
		
		itMovedY = false;
	}
	
	
	///Set the animation index
	if(!hero->heroIsDead && !isTeleporting)
	{
        if(itMovedX && !itMovedY)
        {
            if(hero->theBody->GetLinearVelocity().x > 0)
            {
                ///Verific daca e mai mic sau mai mare decat animatia, pentru ca daca ar fi mai mare decat animatia de miscare la dreapta
                ///dar mai mica decat miscarea de animatie la dreapta + 1, inseamna ca face ceva intermediar, cum ar fi: incepe
                ///miscare, este in miscare continua, sau termina miscarea
				
                if(hero->animationIndexCurrentAnimation != hero->animationIndexPlayerMoveRight)
                {
                    ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexPlayerMoveRight;
                    listOfActiveAnimations[0]->canPlayIt = true;
                    listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                    listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                    listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
					
                    hero->animationIndexCurrentAnimation = hero->animationIndexPlayerMoveRight;
                    //                    hero->IsAtStepOfAnimation1 = true;
                    //                    hero->IsAtStepOfAnimation2 = false;
                    //                    hero->IsAtStepOfAnimation3 = false;
                }
				
                //			if(!hero->IsAtStepOfAnimation1 && !hero->IsAtStepOfAnimation2 && !hero->IsAtStepOfAnimation3)
                //			{
                //				hero->IsAtStepOfAnimation1 = true;
                //				hero->IsAtStepOfAnimation2 = false;
                //				hero->IsAtStepOfAnimation3 = false;
                //			}
				
                if(itMovedXLeft)
                {
                    itTurnedX = true;
                }
				
                itMovedXRight = true;
                itMovedXLeft = false;
            }
            else
            {
                if(hero->animationIndexCurrentAnimation != hero->animationIndexPlayerMoveLeft)
                {
                    ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexPlayerMoveLeft;
                    listOfActiveAnimations[0]->canPlayIt = true;
                    listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                    listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                    listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
					
                    hero->animationIndexCurrentAnimation = hero->animationIndexPlayerMoveLeft;
                    //                    hero->IsAtStepOfAnimation1 = true;
                    //                    hero->IsAtStepOfAnimation2 = false;
                    //                    hero->IsAtStepOfAnimation3 = false;
                }
				
                //			if(!hero->IsAtStepOfAnimation1 && !hero->IsAtStepOfAnimation2 && !hero->IsAtStepOfAnimation3)
                //			{
                //				hero->IsAtStepOfAnimation1 = true;
                //				hero->IsAtStepOfAnimation2 = false;
                //				hero->IsAtStepOfAnimation3 = false;
                //			}
				
                if(itMovedXRight)
                {
                    itTurnedX = true;
                }
				
                itMovedXRight = false;
                itMovedXLeft = true;
            }
        }
		
        if(itMovedY && isInAir)
        {
            if(hero->theBody->GetLinearVelocity().y > 0)
            {
                ///Daca se misca spre dreapta
                if(heroFacesLeftOrRight == 1)
                {
                    if(hero->animationIndexCurrentAnimation != hero->animationIndexPlayerMoveUpRight)
                    {
                        ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexPlayerMoveUpRight;
                        listOfActiveAnimations[0]->canPlayIt = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                        listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
						
                        hero->animationIndexCurrentAnimation = hero->animationIndexPlayerMoveUpRight;
                        //                        hero->IsAtStepOfAnimation1 = true;
                        //                        hero->IsAtStepOfAnimation2 = false;
                        //                        hero->IsAtStepOfAnimation3 = false;
                    }
                }
                else
                    ///Daca se misca spre stanga
                    //if(heroFacesLeftOrRight == -1)
                {
                    if(hero->animationIndexCurrentAnimation != hero->animationIndexPlayerMoveUpLeft)
                    {
                        ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexPlayerMoveUpLeft;
                        listOfActiveAnimations[0]->canPlayIt = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                        listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
						
                        hero->animationIndexCurrentAnimation = hero->animationIndexPlayerMoveUpLeft;
                        //                            hero->IsAtStepOfAnimation1 = true;
                        //                            hero->IsAtStepOfAnimation2 = false;
                        //                            hero->IsAtStepOfAnimation3 = false;
                    }
                }
            }
            else
            {
                ///Daca se misca spre dreapta
                if(heroFacesLeftOrRight == 1)
                {
                    if(hero->animationIndexCurrentAnimation != hero->animationIndexPlayerMoveDownRight)
                    {
                        ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexPlayerMoveDownRight;
                        listOfActiveAnimations[0]->canPlayIt = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                        listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
						
                        hero->animationIndexCurrentAnimation = hero->animationIndexPlayerMoveDownRight;
                        //                        hero->IsAtStepOfAnimation1 = true;
                        //                        hero->IsAtStepOfAnimation2 = false;
                        //                        hero->IsAtStepOfAnimation3 = false;
                    }
                }
                else
                    ///Daca se misca spre stanga
                    //if(heroFacesLeftOrRight == -1)
                {
                    if(hero->animationIndexCurrentAnimation != hero->animationIndexPlayerMoveDownLeft)
                    {
                        ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexPlayerMoveDownLeft;
                        listOfActiveAnimations[0]->canPlayIt = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                        listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
						
                        hero->animationIndexCurrentAnimation = hero->animationIndexPlayerMoveDownLeft;
                        //                            hero->IsAtStepOfAnimation1 = true;
                        //                            hero->IsAtStepOfAnimation2 = false;
                        //                            hero->IsAtStepOfAnimation3 = false;
                    }
                }
            }
        }
		
        if(!itMovedX && !itMovedY)
        {
            itMovedXRight = false;
            itMovedXLeft = false;
            //hero->heroStopped = true;
            if(hero->heroStopped && heroJustStopped)
            {
                //                hero->IsAtStepOfAnimation3 = true;
                listOfActiveAnimations[0]->isAtStepOfAnimation3 = true;
                heroJustStopped = false;
            }
			
            if(hero->animationIndexCurrentAnimation != hero->animationIndexPlayerStand && !hero->heroStopped)
            {
                ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexPlayerStand;
                listOfActiveAnimations[0]->canPlayIt = true;
                listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
				
                hero->animationIndexCurrentAnimation = hero->animationIndexPlayerStand;
                //                hero->IsAtStepOfAnimation1 = true;
                //                hero->IsAtStepOfAnimation2 = false;
                //                hero->IsAtStepOfAnimation3 = false;
            }
        }
	}
	else
        if(hero->heroIsDead && !isTeleporting &&
           hero->animationIndexCurrentAnimation != hero->animationIndexPlayerDieRight &&
           hero->animationIndexCurrentAnimation != hero->animationIndexPlayerDieLeft)
        {
            if(lastPositionOfHeroX < hero->theBody->GetPosition().x)
			{
			    hero->animationIndexCurrentAnimation = hero->animationIndexPlayerDieRight;
			}
			else
            {
			    hero->animationIndexCurrentAnimation = hero->animationIndexPlayerDieLeft;
            }
            ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexCurrentAnimation;
            listOfActiveAnimations[0]->canPlayIt = true;
            listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
            listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
            listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
			
            //			hero->IsAtStepOfAnimation1 = true;
            //			hero->IsAtStepOfAnimation2 = false;
            //			hero->IsAtStepOfAnimation3 = false;
        }
        else
            ///daca se teleporteaza
            if(isTeleporting)
            {
                ///daca a iesit din worm hole
                if(SDL_GetTicks() - timeWhenTeleported >  12 * 20 && SDL_GetTicks() - timeWhenTeleported <  24 * 20)
                {
                    if(hero->animationIndexCurrentAnimation != hero->animationIndexPlayerTeleportedOut)
                    {
                        ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexPlayerTeleportedOut;
                        listOfActiveAnimations[0]->canPlayIt = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                        listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                        listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
						
                        hero->animationIndexCurrentAnimation = hero->animationIndexPlayerTeleportedOut;
                        //                        hero->IsAtStepOfAnimation1 = true;
                        //                        hero->IsAtStepOfAnimation2 = false;
                        //                        hero->IsAtStepOfAnimation3 = false;
						
                        TeleportHero(TeleportX, TeleportY);
                        //                        objUtil->update();
                        ///mouseTexture->xCord + CameraPosition->xCord - CameraExtremeLeft,
                        ///mouseTexture->yCord + CameraPosition->yCord - CameraExtremeDown);
                    }
                }
                else
                    ///daca a intrat in worm hole
                    if(SDL_GetTicks() - timeWhenTeleported <=  12 * 20)
                    {
                        if(hero->animationIndexCurrentAnimation != hero->animationIndexPlayerTeleportedIn)
                        {
                            ///listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexPlayerTeleportedIn;
                            listOfActiveAnimations[0]->canPlayIt = true;
                            listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                            listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                            listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
							
                            hero->animationIndexCurrentAnimation = hero->animationIndexPlayerTeleportedIn;
                            //                            hero->IsAtStepOfAnimation1 = true;
                            //                            hero->IsAtStepOfAnimation2 = false;
                            //                            hero->IsAtStepOfAnimation3 = false;
                        }
                    }
                    else
                        ///daca a iesit cu totul din worm hole
                        if(SDL_GetTicks() - timeWhenTeleported >= 24 * 20)
                        {
                            isTeleporting = false;
                        }
            }
	
	/*		std::cout<<"misca "<<startPositionCameraX<<" "<<hero->theBody->GetPosition().x<<
     abs(startPositionCameraX - hero->theBody->GetPosition().x)<<"\n";
     */
	if(abs(startPositionCameraX - hero->theBody->GetPosition().x) > 2)
	{
		//std::cout<<"misca "<<startPositionCameraX<<" "<<hero->theBody->GetPosition().x<<
		//abs(startPositionCameraX - hero->theBody->GetPosition().x)<<"\n";
		startPositionCameraX = hero->theBody->GetPosition().x - 2;
		changeInPosition = 2;
	}
	
	
	lastPositionOfHeroX = hero->theBody->GetPosition().x;
	lastPositionOfHeroY = hero->theBody->GetPosition().y;
	
	
	
	
    listOfActiveAnimations[0]->indexOfAnimation = hero->animationIndexCurrentAnimation;
    listOfActiveAnimations[3]->indexOfAnimation = hero->animationIndexPlayerWormHole;
	
    listOfActiveAnimations[0]->xCord = hero->theBody->GetPosition().x;
    listOfActiveAnimations[0]->yCord = hero->theBody->GetPosition().y;
    listOfActiveAnimations[0]->zCord = hero->zCord;
	
    listOfActiveAnimations[1]->xCord = hero->theBody->GetPosition().x;
    listOfActiveAnimations[1]->yCord = hero->theBody->GetPosition().y;
    listOfActiveAnimations[1]->zCord = hero->zCord;
	
    listOfActiveAnimations[2]->xCord = hero->theBody->GetPosition().x;
    listOfActiveAnimations[2]->yCord = hero->theBody->GetPosition().y;
    listOfActiveAnimations[2]->zCord = hero->zCord;
	
    listOfActiveAnimations[4]->xCord = hero->theBody->GetPosition().x;
    listOfActiveAnimations[4]->yCord = hero->theBody->GetPosition().y;
    listOfActiveAnimations[4]->zCord = hero->zCord;
	
	
	if(isInAir)
	{
		controlAir(0.1f, hero->theBody);
	}
	else
		if(isInCorner)
		{
			controlCorner(hero->theBody);
		}
		else
			if(isOnGround)
			{
				controlGround(hero->theBody, 0.05f);
			}
			else
				if((isOnLeftWall || isOnRightWall) && !hero->heroIsDead)
				{
					controlWall(hero->theBody);
					if(isOnLeftWall)
					{
					    hero->animationIndexCurrentAnimation = hero->animationIndexPlayerWallLeft;
					}
					else
                        if(isOnRightWall)
                        {
                            hero->animationIndexCurrentAnimation = hero->animationIndexPlayerWallRight;
                        }
                    listOfActiveAnimations[0]->canPlayIt = true;
                    listOfActiveAnimations[0]->isAtStepOfAnimation1 = true;
                    listOfActiveAnimations[0]->isAtStepOfAnimation2 = false;
                    listOfActiveAnimations[0]->isAtStepOfAnimation3 = false;
					
                    //                    hero->IsAtStepOfAnimation1 = true;
                    //                    hero->IsAtStepOfAnimation2 = false;
                    //                    hero->IsAtStepOfAnimation3 = false;
				}
}




void BSActionStuff::moveRightOnGround(b2Body *body)
{
	//hero->theBody->SetLinearVelocity(b2Vec2(20 * 30, 0));
	
	vel = body->GetLinearVelocity();
	desiredVelX = 0;
	
	if(ButtonRight == true && ButtonLeft == false)
	{
		desiredVelX = b2Min( vel.x + 0.1f,  5.0f );
	}
	else
		if(ButtonLeft == true && ButtonRight == false)
		{
			desiredVelX = b2Max( vel.x - 0.1f, -5.0f );
		}
		else
		{
			desiredVelX = vel.x * 4.0f;
		}
	
	/*
     switch ( //moveState )
     {
     case MS_LEFT:  desiredVel = b2Max( vel.x - 0.1f, -5.0f ); break;
     case MS_STOP:  desiredVel = vel.x * 4.0f; break;
     case MS_RIGHT: desiredVel = b2Min( vel.x + 0.1f,  5.0f ); break;
     }*/
	velChangeX = desiredVelX - vel.x;
	impulseX = body->GetMass() * velChangeX; //disregard time factor
	body->ApplyLinearImpulse( b2Vec2(impulseX,0), body->GetWorldCenter() );
}



void BSActionStuff::destroyTheParticles()
{
	
}

void BSActionStuff::generateTheParticles()
{
	for(int i = 0 ; i < 10; i++)
	{
        //		BSCloudyParticles *part = new BSCloudyParticles;
        //		part->xCord = hero->theBody->GetPosition().x - i / 10.0f;
        //		part->yCord = hero->theBody->GetPosition().y - 1 / 2.0f;
        //		part->radius = 0.4f;
        //		part->colorOfParticle = {1, 1, 1, 1};
        //		part->sinValue = 0;
        //		part->yPower = 1;
        //		part->xPower = 1;
	}
}

void BSActionStuff::generateWhenHitsGroundParticles()
{
	///Add particles
	//daca este pe pamant sau pe perete si se misca
	/*if(justHitTheGround)
	 {
	 currentParticleNr = nrOfWhenItHits;
	 {
	 for(int i = currentParticleNr ; i < currentParticleNr + 50; i++)
	 {
	 aCreat = false;
	 //indexCurent = i;
	 
	 
	 ///Verific daca gaseste particule distruse, ca sa construiesc in locul lor
	 std::list<BSTheParticles*>::iterator iteratorParticule;
	 for(iteratorParticule = ListOfParticles.begin(); iteratorParticule != ListOfParticles.end(); iteratorParticule++)
	 {
	 //verific daca a gasit o particula distrusa pentru a nu mai crea inca una
	 if((*iteratorParticule)->isDestroyed == true) //whenHitsGroundParticles[j]->isDestroyed == true)
	 {
	 //indexCurent = j;
	 int maxim = 5 / scaleSize, minim = 1 / scaleSize / 2.f, negativSauPozitiv = 0, leftOrRight = 0;
	 float timpRandom = rand()%3;
	 float cordX = 0, cordY = 0, speedX = 0, speedY = 0;
	 
	 //reasez particula
	 if(isOnGround)
	 {
	 if(i%2 == 0)
	 {
	 cordX = hero->theBody->GetPosition().x - hero->width / 2 + 0.2 - timpRandom * 0.1;
	 cordY = hero->theBody->GetPosition().y + 1 / 5.f * (rand()%3);
	 negativSauPozitiv = -1;
	 }
	 else
	 {
	 cordX = hero->theBody->GetPosition().x + hero->width / 2 - 0.2 + timpRandom * 0.1;
	 cordY = hero->theBody->GetPosition().y + 1 / 5.f * (rand()%3);
	 negativSauPozitiv = 1;
	 }
	 }
	 
	 
	 (*iteratorParticule)->theBodyOfParticle->SetTransform(b2Vec2(cordX, cordY),
	 (*iteratorParticule)->theBodyOfParticle->GetAngle() * 1.2);
	 //resetez timpul
	 maxim = 500, minim = 400;
	 timpRandom = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maxim - minim + 1) + minim;
	 (*iteratorParticule)->timeUntilBum = timpRandom;
	 (*iteratorParticule)->BumTime = timpRandom + SDL_GetTicks();
	 //resetez culoarea
	 //(*iteratorParticule)->ColorOfParticle = { (6 + rand() % 4) * 0.1f, (2 + rand() % 4) * 0.1f, 0.f, 1.f};
	 (*iteratorParticule)->ColorOfParticle.r = (6 + rand() % 4) * 0.1f;
	 (*iteratorParticule)->ColorOfParticle.g = (2 + rand() % 4) * 0.1f;
	 (*iteratorParticule)->ColorOfParticle.b = 0;
	 (*iteratorParticule)->ColorOfParticle.a = 1;
	 
	 
	 //resetez viteza
	 maxim = 10, minim = 5;
	 timpRandom = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maxim - minim + 1) + minim;
	 
	 if(leftOrRight)
	 {
	 float speed = 1;
	 
	 if(i%2 == 0)
	 {
	 speed = 1.5f;
	 }
	 
	 
	 (*iteratorParticule)->theBodyOfParticle->SetLinearVelocity(b2Vec2(3.5f * leftOrRight, timpRandom * speed));
	 }
	 else
	 {
	 (*iteratorParticule)->theBodyOfParticle->SetLinearVelocity(b2Vec2(3.5f * negativSauPozitiv, timpRandom));
	 }
	 
	 (*iteratorParticule)->isDestroyed = false;
	 
	 aCreat = true;
	 break;
	 }
	 }
	 
	 ///Daca nu a gasit particule distruse, construieste una noua
	 if(aCreat == false)
	 {
	 ///Adaug 2 seturi de particule, unul pentru partea stanga sau dedesubt si unul pentru partea dreapta sau superioara
	 for(int i = 0 ; i < 2 ; i++)
	 {
	 int maxim = 1 / scaleSize, minim = 1 / scaleSize / 2.f;
	 float timpRandom = rand()%5;
	 //std::cout<<"create "<<SDL_GetTicks()<<'\n';
	 BSTheParticles *newParticle = new BSTheParticles;
	 
	 newParticle->theBodyOfParticle = obstaclesActionClass->createBodies(b2_dynamicBody,
	 hero->theBody->GetPosition().x + timpRandom * pozitivSauNegativ * 0.1,
	 hero->theBody->GetPosition().y + (rand()%3),
	 1/10.f, 1/10.f, "particle", nrOfWhenItHits, 300, false);
	 
	 //newParticle->ColorOfParticle = { (6 + rand() % 4) * 0.1f, (2 + rand() % 4) * 0.1f, 0.f, 1.f};
	 (*iteratorParticule)->ColorOfParticle.r = (6 + rand() % 4) * 0.1f;
	 (*iteratorParticule)->ColorOfParticle.g = (2 + rand() % 4) * 0.1f;
	 (*iteratorParticule)->ColorOfParticle.b = 0;
	 (*iteratorParticule)->ColorOfParticle.a = 1;
	 
	 maxim = 200, minim = 20;
	 timpRandom = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maxim - minim + 1) + minim;
	 
	 newParticle->timeUntilBum = timpRandom;
	 newParticle->BumTime = timpRandom + SDL_GetTicks();
	 
	 
	 maxim = 15, minim = 5;
	 timpRandom = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maxim - minim + 1) + minim;
	 float cordX = 0, cordY = 0;
	 //resetez viteza
	 //cordX = hero->theBody->GetPosition().x +
	 //timpRandom * pozitivSauNegativ * 0.1;
	 //cordY = hero->theBody->GetPosition().y + 1/10/2.f;
	 
	 maxim = 15, minim = 5;
	 timpRandom = ((float)rand() / ((float)RAND_MAX + 1.0)) * (maxim - minim + 1) + minim;
	 
	 if(i == 0)
	 {
	 newParticle->theBodyOfParticle->SetLinearVelocity(b2Vec2(3.1f,
	 timpRandom));
	 }
	 else
	 {
	 newParticle->theBodyOfParticle->SetLinearVelocity(b2Vec2(-3.1f,
	 timpRandom));
	 }
	 
	 ListOfParticles.push_back(newParticle);
	 }
	 
	 }
	 }
	 
	 if(timeToCreateParticles == 0)
	 {
	 //timeToCreateParticles = 0 + SDL_GetTicks();
	 }
	 
	 ///Creeaza particulele pentru 100 ms
	 //if(timeToCreateParticles < 0 + SDL_GetTicks())
	 {
	 justHitTheGround = false;
	 timeToCreateParticles = 0;
	 }
	 }
	 
	 }*/
}





void BSActionStuff::ClickOnBlock()
{
	if(MouseLeft && canClickLeft)
	{
		///If can add coins
		if(canAddCoins)
		{
			BSCoins *newCoin = new BSCoins;
			//newCoin->color = {1.f, 1.f, 1.f, 1.f};
			newCoin->color.r = 1;
			newCoin->color.g = 1;
			newCoin->color.b = 1;
			newCoin->color.a = 1;
			newCoin->width = Hero_size;// / 2.f;
			newCoin->height = Hero_size;// / 2.f;
			newCoin->sinValue = 90;
			newCoin->deleteIt = false;
			newCoin->xCord = createObstacleX;
			newCoin->yCord = createObstacleY;
			newCoin->xInit = createObstacleX;
			newCoin->yInit = createObstacleY;
			newCoin->available = true;
			listOfCoins.push_back(newCoin);
		}
		
		
		
		selectedSquareBody = NULL;
		selectedRoundBody = NULL;
		
		///Vad daca pot seta world boundaries
		if(canSetBoundaryDown)
		{
			WorldBoundaryDown = createObstacleY;
		}
		else
			if(canSetBoundaryLeft)
			{
				WorldBoundaryLeft = createObstacleX;
			}
			else
				if(canSetBoundaryRight)
				{
					WorldBoundaryRight = createObstacleX + 1;
				}
				else
					if(canSetBoundaryUp)
					{
						WorldBoundaryUp = createObstacleY + 1;
					}
		
		///Vad daca pot adauga obstacole
		if(canAddObstacles)
		{
			float variabilaAdunareX = 0, variabilaAdunareY = 0;
			
			if(LittleBigMoveTheObstacle == 0)
			{
				variabilaAdunareX = Hero_size / 2.f;
				variabilaAdunareY = Hero_size / 2.f;
			}
			else
				if(LittleBigMoveTheObstacle == 1)
				{
					variabilaAdunareX = widthOfObstacle / 2.f;
					variabilaAdunareY = heightOfObstacle / 2.f;
				}
				else
					if(LittleBigMoveTheObstacle == -1)
					{
						variabilaAdunareX = Hero_size / 4.f;
						variabilaAdunareY = Hero_size / 4.f;
					}
			
			bool dejaExistaSquare = false, dejaExistaRound = false;
			bool dejaExistaSquareTexture = false, dejaExistaRoundTexture = false;
			int indexOfBody = 0;
			b2Body *existingBody = NULL;
			
			///Verific daca se mai afla vreun obiect sau textura in locul asta
			if(addCircleOrSquare == 1)
			{
				std::list<BSTheSquareBodies*>::iterator i;
				for(i = ListOfSquareBodies.begin(); i != ListOfSquareBodies.end(); i++)
				{
					if((*i)->theBody->GetPosition().x == createObstacleX && (*i)->theBody->GetPosition().y == createObstacleY
                       && (*i)->width == widthOfObstacle && (*i)->height == heightOfObstacle)
					{
						dejaExistaSquare = true;
						selectedSquareBody = (*i);
						selectedRoundBody = NULL;
						break;
					}
				}
				
				if(dejaExistaSquare == false)
				{
					std::cout<<"added square body"<<'\n';
					obstaclesActionClass->addDinamicSquare(createObstacleX, createObstacleY, widthOfObstacle, heightOfObstacle,
														   initialSquareTexturePath, NULL, "object", b2_staticBody, false, 0);
                    //					BSTheSquareBodies *theAddedBody = (BSTheSquareBodies*)ListOfSquareBodies.back();
                    //
                    //					objLTexture2->setTheVao(theAddedBody->vaoBufferOfBody, theAddedBody->dataOfBody);
                    //
                    //					theAddedBody = NULL;
                    //					delete theAddedBody;
					
					selectedSquareBody = NULL;
				}
			}
			else
				if(addCircleOrSquare == -1)
				{
					std::list<BSTheRoundBodies*>::iterator i;
					for(i = ListOfRoundBodies.begin(); i != ListOfRoundBodies.end(); i++)
					{
						if((*i)->theBody->GetPosition().x == createObstacleX &&
                           (*i)->theBody->GetPosition().y == createObstacleY
                           && (*i)->radius == theRenderedObstacleCircle->radius)
						{
							dejaExistaRound = true;
							selectedRoundBody = (*i);
							selectedSquareBody = NULL;
							break;
						}
					}
					
					if(dejaExistaRound == false)
					{
						std::cout<<"added round body"<<'\n';
						obstaclesActionClass->addDinamicRound(createObstacleX, createObstacleY, theRenderedObstacleCircle->radius,
															  initialRoundTexturePath, NULL, "object", b2_staticBody, false);
						
                        //						BSTheRoundBodies *theAddedBody = (BSTheRoundBodies*)ListOfRoundBodies.back();
                        //
                        //						objLTexture2->setTheVao(theAddedBody->vaoBufferOfBody, theAddedBody->dataOfBody);
                        //
                        //						theAddedBody = NULL;
                        //						delete theAddedBody;
						
						selectedRoundBody = NULL;
					}
				}
				else
					if(addCircleOrSquare == 2)
					{
						std::list<BSTextureSquare*>::iterator i;
						for(i = ListOfSquareTextures.begin(); i != ListOfSquareTextures.end(); i++)
						{
							if((*i)->xCord == createObstacleX && (*i)->yCord == createObstacleY
                               && (*i)->width == widthOfObstacle && (*i)->height == heightOfObstacle)
							{
								dejaExistaSquareTexture = true;
								break;
							}
						}
						
						if(dejaExistaSquareTexture == false)
						{
							std::cout<<"added square texture"<<'\n';
							obstaclesActionClass->addOnlyTexture(1, createObstacleX, createObstacleY, widthOfObstacle, heightOfObstacle, "texture.png");
							
                            //							BSTextureSquare *newTexture = (BSTextureSquare*)ListOfSquareTextures.back();
                            //
                            //							objLTexture2->setTheVao(newTexture->vaoBufferOfTexture, newTexture->dataOfTexture);
                            //							objLTexture2->loadATexture("texture.png", newTexture->texture);
							
                            //							newTexture = NULL;
                            //							delete newTexture;
						}
					}
					else
						if(addCircleOrSquare == -2)
						{
							std::list<BSTextureRound*>::iterator i;
							for(i = ListOfRoundTextures.begin(); i != ListOfRoundTextures.end(); i++)
							{
								if((*i)->xCord == createObstacleX && (*i)->yCord == createObstacleY
                                   && (*i)->radius == theRenderedObstacleCircle->radius)
								{
									std::cout<<"a gasit un round texture"<<'\n';
									dejaExistaRoundTexture = true;
									break;
								}
							}
							
							if(dejaExistaRoundTexture == false)
							{
								std::cout<<"a adaugat round texture"<<'\n';
								obstaclesActionClass->addOnlyTexture(-1, createObstacleX, createObstacleY, widthOfObstacle, widthOfObstacle, "texture.png");
								
                                //								BSTextureRound *newTexture = (BSTextureRound*)ListOfSquareTextures.back();
                                //
                                //								objLTexture2->setTheVao(newTexture->vaoBufferOfTexture, newTexture->dataOfTexture);
                                //								objLTexture2->loadATexture("texture.png", newTexture->texture);
							}
						}
        }
		
        canClickLeft = false;
    }
	
	
	if(MouseRight && canClickRight)
	{
		selectedSquareBody = NULL;
		selectedRoundBody = NULL;
		
		if(canAddObstacles)
		{
			float variabilaAdunareX = 0, variabilaAdunareY = 0;
			
			if(LittleBigMoveTheObstacle == 0)
			{
				variabilaAdunareX = Hero_size / 2.f;
				variabilaAdunareY = Hero_size / 2.f;
			}
			else
				if(LittleBigMoveTheObstacle == 1)
				{
					variabilaAdunareX = widthOfObstacle / 2.f;
					variabilaAdunareY = heightOfObstacle / 2.f;
				}
				else
					if(LittleBigMoveTheObstacle == -1)
					{
						//variabilaAdunareX = Hero_size / 4.f;
						//variabilaAdunareY = Hero_size / 4.f;
					}
			
			bool dejaExistaSquare = false, dejaExistaRound = false;
			int indexSters = 0;
			
            if(addCircleOrSquare == 1)
            {
                BSTheSquareBodies *CorpulCareVreauSaStergSquare = new BSTheSquareBodies;
				
                std::list<BSTheSquareBodies*>::iterator i;
                for(i = ListOfSquareBodies.begin(); i != ListOfSquareBodies.end(); i++)
                {
                    if((*i)->theBody->GetPosition().x == createObstacleX && (*i)->theBody->GetPosition().y == createObstacleY
                       && (*i)->width == widthOfObstacle && (*i)->height == heightOfObstacle)
                    {
                        CorpulCareVreauSaStergSquare = (*i);
                        dejaExistaSquare = true;
                        break;
                    }
                }
				
                if(dejaExistaSquare)
                {
                    obstaclesActionClass->deleteBodySquare(CorpulCareVreauSaStergSquare);
					
                    std::cout<<"sters square"<<'\n';
                }
            }
            else
                if(addCircleOrSquare == -1)
                {
                    BSTheRoundBodies *CorpulCareVreauSaStergRound = new BSTheRoundBodies;
					
                    std::list<BSTheRoundBodies*>::iterator i;
                    for(i = ListOfRoundBodies.begin(); i != ListOfRoundBodies.end(); i++)
                    {
                        if((*i)->theBody->GetPosition().x == createObstacleX && (*i)->theBody->GetPosition().y == createObstacleY)
                        {
                            CorpulCareVreauSaStergRound = (*i);
                            dejaExistaRound = true;
                            break;
                        }
                    }
					
                    if(dejaExistaRound)
                    {
                        obstaclesActionClass->deleteBodyRound(CorpulCareVreauSaStergRound);
						
                        std::cout<<"sters round"<<'\n';
                    }
                }
			
			
			canClickRight = false;
		}
	}
	
	
	/*
     //if(MouseMoved)
     {
     //pozitia butonului din pauza
     //300,300 - pozitia butonului
     //100 width of the button
     //480 este height of the window
     //if(MouseX > 300 - 100/2 && MouseX < 300 + 100/2 &&
     //MouseY > 480 - 300 - 30/2 && MouseY < 480 - 300 + 30/2)
     if(MouseX / scaleSize > (float) SCREEN_WIDTH / 2.f / scaleSize - 2 - buttonMenuWidth &&// -1 pentru ca
     //sa zicem ca butonul e format din 4 patrate, iar coordonatele butonului este dat in al 3lea patrat
     //butonul: [][]|aici se afla coordonatele lui, care defapt sunt ale urmatorului patrat|[][],
     //si anume patratul 3. Asadar atunci cand verific la stanga daca mouseul se afla in buton mai scad
     //inca un patrat
     MouseX / scaleSize < (float) SCREEN_WIDTH / 2.f / scaleSize - 2 + buttonMenuWidth &&
     MouseY / scaleSize > (float) SCREEN_HEIGHT / scaleSize - SCREEN_HEIGHT / 2 / scaleSize + 2 - buttonMenuHeight &&
     MouseY / scaleSize < (float) SCREEN_HEIGHT / scaleSize - SCREEN_HEIGHT / 2 / scaleSize + 2 + buttonMenuHeight)
	 
     {
     canClick = true;
     theString = "este pe buton";
     //std::cout<<"este pe buton " << MouseX / scaleSize<< "  "  << MouseY / scaleSize<<'\n';
     }
     else
     {
     theString = "nu este pe buton " + toString(SCREEN_WIDTH / 2 / scaleSize - 10) + " " +
     toString(SCREEN_HEIGHT / 2 / scaleSize - 10);
     //std::cout<<"   "<< MouseX / scaleSize<< "  "  << MouseY / scaleSize<<'\n';
     }
     }
	 
     if(MouseLeft == true && canClick == true && aDatClick == false)
     {
     //std::cout<<"CLICK!!!"<<'\n';
     aDatClick = true;
     }*/
}



void BSActionStuff::ActionFuncTeleportHero(float xCord, float yCord)
{
	/*
	 TeleportX = 0, TeleportY = 0;
	 
	 if(hero->theBody->GetPosition().x <= CameraExtremeLeft)
	 {
	 TeleportX = MouseX / scaleSize;
	 }
	 else
	 if(hero->theBody->GetPosition().x > CameraExtremeLeft && hero->theBody->GetPosition().x < CameraExtremeRight)
	 {
	 TeleportX = MouseX / scaleSize + hero->theBody->GetPosition().x - CameraExtremeLeft;
	 }
	 else
	 if(hero->theBody->GetPosition().x > CameraExtremeRight)
	 {
	 TeleportX = MouseX / scaleSize + CameraExtremeRight - CameraExtremeLeft;
	 }
	 
	 if(hero->theBody->GetPosition().y <= CameraExtremeDown)
	 {
	 TeleportY = (float)(SCREEN_HEIGHT - MouseY) / scaleSize;
	 }
	 else
	 if(hero->theBody->GetPosition().y > CameraExtremeDown && hero->theBody->GetPosition().y < CameraExtremeUp)
	 {
	 TeleportY = (float)hero->theBody->GetPosition().y + (SCREEN_HEIGHT - MouseY) / scaleSize - CameraExtremeDown;
	 }
	 else
	 if(hero->theBody->GetPosition().y > CameraExtremeUp)
	 {
	 TeleportY = (SCREEN_HEIGHT - MouseY) / scaleSize + CameraExtremeUp - CameraExtremeDown;
	 }*/
    TeleportX = xCord;
    TeleportY = yCord;
    isTeleporting = true;
    timeWhenTeleported = SDL_GetTicks();
}

void BSActionStuff::TeleportHero(float coordX, float coordY)
{
	std::cout<<"teleported"<<'\n';
	hero->theBody->SetTransform(b2Vec2(coordX, coordY), hero->theBody->GetAngle());
	heroCanTeleportAgain = false;
	hero->theBody->ApplyLinearImpulse(b2Vec2(0, 0.1f), hero->theBody->GetWorldCenter());
}

//deseneaza stelute in spatele lui
void BSActionStuff::PathColoring( int LeftOrRight)
{
	
}

void BSActionStuff::heroTouchesObjects()
{
	b2ContactEdge *edge = hero->theBody->GetContactList(); //get all the objects the hero is contacting with
	
	
	///retin daca se afla in aer ca sa stiu daca creez particule pentru cand atinge pamantul
	bool wasInAir = isInAir;
	
	canJumpVertically = false;
	canJumpHorizontally = false;
	isOnGround = false;
	isInAir = true;
	isInCorner = false;
	isOnLeftWall = false;
	isOnRightWall = false;
	jumpsUpTheWall = false;
	variableWall = 0;
	
	//		hero->heroIsDead = false;
	//		hero->BodyTexture = playerTexture;
	//		std::cout<<"here1 "<<hero->heroIsDead<<'\n';
	
	while (edge != NULL)
	{
		b2WorldManifold *a = new b2WorldManifold();
		edge->contact->GetWorldManifold(a);
		b2Vec2 normal1 = a->normal;
		
		//vad cu care obiecte intra in contact
		if (edge->contact->IsTouching())
		{
		    ///Shallow copy
			//            USERDATA *us = (USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData();
			
			///Deep copy
			//            USERDATA *us = new USERDATA;
			//			us->BumTime = ((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->BumTime;
			//			us->canKillHero = ((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->canKillHero;
			//			us->height = ((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->height;
			//			us->isDust = ((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->isDust;
			//			us->isDustAble = ((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->isDustAble;
			//			us->isToNextLevel = ((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->isToNextLevel;
			//			us->name = ((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->name;
			//			us->timeUntilDestroy = ((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->timeUntilDestroy;
			//			us->width = ((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->width;
			
			///Iau userdataul din corpul pe care il atinge jucatorul, ca sa vad daca il poate omori pe jucator
			//			USERDATA *us2 = (USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData();
			//            USERDATA *us2 = new USERDATA;
			//			us2->BumTime = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->BumTime;
			//			us2->canKillHero = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->canKillHero;
			//			us2->height = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->height;
			//			us2->isDust = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->isDust;
			//			us2->isDustAble = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->isDustAble;
			//			us2->isToNextLevel = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->isToNextLevel;
			//			us2->name = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->name;
			//			us2->timeUntilDestroy = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->timeUntilDestroy;
			//			us2->width = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->width;
			
			if(((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->isDustAble)
			{
                ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->isDust = 1;
			}
			
			///Daca este 1, inseamna ca a atins un obiect care il omoara, asa ca este mort, altfel nu este mort
			if(((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->canKillHero && !hero->heroWasDead)
			{
				//				alSourcePlay(SourceSoundDies);
				
                if(hero->heroIsBerserk1 || hero->heroIsBerserk2 || hero->heroIsBerserk3)
				{
				    listOfActiveAnimations[1]->indexOfAnimation = hero->animationIndexCurrentAnimationBerserk;
                    listOfActiveAnimations[1]->canPlayIt = true;
                    listOfActiveAnimations[1]->isAtStepOfAnimation1 = false;
                    listOfActiveAnimations[1]->isAtStepOfAnimation2 = false;
                    listOfActiveAnimations[1]->isAtStepOfAnimation3 = true;
				}
				
				if(hero->heroIsBerserk2)
				{
				    listOfActiveAnimations[2]->indexOfAnimation = hero->animationIndexPlayerAuraElectricity;
                    listOfActiveAnimations[2]->canPlayIt = false;
                    listOfActiveAnimations[2]->isAtStepOfAnimation1 = false;
                    listOfActiveAnimations[2]->isAtStepOfAnimation2 = false;
                    listOfActiveAnimations[2]->isAtStepOfAnimation3 = false;
				}
				hero->heroIsBerserk1 = false;
				hero->heroIsBerserk2 = false;
				hero->heroIsBerserk3 = false;
				//				hero->IsAtStepOfAnimation23 = true;
				//				hero->IsAtStepOfAnimation21 = false;
				//				hero->IsAtStepOfAnimation22 = false;
				
				hero->heroIsDead = ((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->canKillHero;
				hero->texture = playerTextureDead;
				hero->heroWasDead = true;
				std::cout<<"dead killed by object"<<'\n';
				
				deathsThisLevel++;
				deathsTotalNo++;
				
				world->Step((float) 1/theTimeHowFast , 8, 3);
				world->ClearForces();
			}
			else
				if(((USERDATA*)edge->contact->GetFixtureB()->GetBody()->GetUserData())->isToNextLevel && !hero->heroWasToNextLevel &&
				   levelChoserPlayer->indexOfLevelThatItIsOn + 1 < chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->nrOfLevels &&
				   chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter[levelChoserPlayer->indexOfLevelThatItIsOn + 1]->canPlayIt)
				{
					levelChoserPlayer->justFinished = true;
					//					deadScene->nextLevelOrSomeLevel = 1;
					hero->heroWasToNextLevel = true;
					chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter[levelChoserPlayer->indexOfLevelThatItIsOn]->isFinished = true;
					///nivele[levelChoserPlayer->indexOfLevelThatItIsOn]->isFinished = true;
					
					///Save level as complete
					//					std::string nameOfLevel = "Menu Of Levels/Chapter" +
					//											  BStoString(levelChoserPlayer->indexOfChapterThatItIsOn + 1) + "/The Levels details/level" +
					//											  BStoString(levelChoserPlayer->indexOfLevelThatItIsOn + 1) + ".txt";
					//					const char *nameOfLevelChar = nameOfLevel.c_str();
					
					//					std::ifstream citesteTerminat(nameOfLevelChar);
					//					int term, available;
					//					std::string name;
					//					citesteTerminat>>term>>available>>name;
					//					citesteTerminat.close();
					std::cout<<"atinge"<<'\n';
					
					//					std::ofstream salveazaTerminat(nameOfLevelChar);
					//					salveazaTerminat<<1<<" "<<available<<" "<<name<<" "<<
					//									(CameraExtremeLeft - SCREEN_WIDTH / 2.f / scaleSize)<<" "<<
					//									(CameraExtremeDown - SCREEN_HEIGHT / 2.f / scaleSize)<<" "<<
					//									(CameraExtremeUp + SCREEN_HEIGHT / 2.f / scaleSize)<<" "<<
					//									(CameraExtremeRight + SCREEN_WIDTH / 2.f / scaleSize);
					
					world->Step((float) 1/theTimeHowFast , 8, 3);
					world->ClearForces();
				}
			
			if(((USERDATA*)edge->contact->GetFixtureA()->GetBody()->GetUserData())->name == "hero")
			{
				//if it is touching the ground
				if (normal1.y < 0 )//&& isOnLeftWall == false && isOnRightWall == false)
								   //if the normal is negative/ the hero is being pushed up/ sitting on top of another object
				{
					canJumpVertically = true;
					isOnGround = true;
					pressedJumpSecond = false;
					isInAir = false;
					
					///retin daca tocmai a atins pamantul
					if(wasInAir)
					{
						justHitTheGround = true;
					}
				}
				
				//if it touches a wall
				if(normal1.x != 0)
				{
					//if it touches the left wall
					if(normal1.x < 0)
					{
						isOnLeftWall = true;
						isOnRightWall = false;
					}
					else
						//if it touches the right wall
					{
						isOnLeftWall = false;
						isOnRightWall = true;
					}
					pressedJumpSecond = false;
					
					canJumpHorizontally = true;
					variableWall = normal1.x;//-1 for left, 1 for right
					isInAir = false;
					
					
					///retin daca tocmai a atins pamantul
					if(wasInAir)
					{
						justHitTheGround = true;
					}
				}
				
			}
		}
		
		
		delete a;
		///a = NULL;
		
		//std::cout<<normal1.x<<" "<<normal1.y<<"   "<<' ';
		
		edge = edge->next;
	}
	
	//verfic daca se afla in colt (si pe pamant si pe perete)
	if(isOnGround && (isOnLeftWall || isOnRightWall))
	{
		isInCorner = true;
		isOnLeftWall = false;
		isOnRightWall = false;
		//std::cout<<"is in corner"<<'\n';
	}
	
	delete edge;
	///edge = NULL;
}








bool BSActionStuff::CanGoAwayFromWall(float timeToMatch)
{
	//currentTime = timp->getTime();
	//if(currentTime != -1)
	currentTime = SDL_GetTicks();
	std::cout<<currentTime<<" "<<timeToMatch<<" "<<timeToStayOnWall * (theTimeHowFast / 60)<<'\n';
	{
		//std::cout<<currentTime<<" "<<OriginalTimeOnWall<<'\n';
		if(currentTime - timeToMatch > timeToStayOnWall * (theTimeHowFast / 60) )
		{
			return true;
		}
	}
	return false;
}



float BSActionStuff::easeIn (float t,float b , float c, float d)
{
	return c*(t/=d)*t*t*t*t + b;
}
float BSActionStuff::easeOut(float t,float b , float c, float d)
{
	return c*((t=t/d-1)*t*t*t*t + 1) + b;
}

float BSActionStuff::easeInOut(float t,float b , float c, float d)
{
	if ((t/=d/2) < 1)
		return c/2*t*t*t*t*t + b;
	
	return c/2*((t-=2)*t*t*t*t + 2) + b;
}

float BSActionStuff::radical(float x)
{
	return x - 1/2.f;
	//return pow(x,(1/2.f));
}
