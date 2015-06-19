package com.example.brainstormstudiosgameengine;

import org.jbox2d.collision.WorldManifold;
import org.jbox2d.common.Vec2;
import org.jbox2d.dynamics.Body;
import org.jbox2d.dynamics.contacts.ContactEdge;

import android.os.SystemClock;

class AlanNative 
{
    static {
        try {
            System.loadLibrary("ALAN");
        }
        catch (UnsatisfiedLinkError ule) {
        }
    }

    public static native long add(long a, long b);
}

public class ColidingBodies 
{
	public static boolean
	isOnGround = false,
	isInAir = true,
	isInCorner = false,
	isOnLeftWall = false,
	isOnRightWall = false,
	jumpsUpTheWall = false;
	public static int variableWall = 0;
	
	
	

	static int timpulCareTrece = 0, timpulCareAtrecut = 0, jumpedFromLeftOrRight = 0;
	static long OriginalTimeOnWall = 0, currentTime = 0, OriginalTimeToJumpUpTheWall = 0, timeToCreateParticles = 0;
	static boolean imprimeForceOnWall = false, heroCanTeleportAgain = true;
	static boolean justHitTheGround = false;
	
	static Vec2 vel = new Vec2(0, 0), velocity = new Vec2(0, 0);
	static float desiredVelX = 0, desiredVelY = 0;
	static float velChangeX, velChangeY;
	static float impulseX, impulseY, turnMultiplier = 1.f, turnMultiplierInAir = 5.5f, timeE = 0;
	
	static int nnrr = 0;
	int currentTexture = 0;
	
	
					boolean aCreat = false;
					int indexCurent = 0;
					int currentParticleNr = 0;
					int pozitivSauNegativ = 0;
	

	public static void controlAir(Body theBody, float T)
	{
		//System.loadLibrary("ALAN");
		///ALAN.create();
		// Abort jump if user lets go of button
	    if (velocity.y < 0 && !Values.ButtonJump)
	    {
	    	velocity.y = 0;
	    }
	
	    // Air walk
	    if(!itWalksInAir(theBody, T * 0.2f))
	    {
	    }
	}
	
	public static void controlWall(Body body)
	{
		//std::cout<<"touches the wall  "<<SystemClock.uptimeMillis()<<" "<<OriginalTimeOnWall<<'\n';
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
	    //body.ApplyLinearImpulse( new Vec2(0,0), body.GetWorldCenter() );
	    //velocity.x = 0;
	
		//verifica daca vrea sa  sara de pe perete pe alt perete
		if(Values.canJumpHorizontally && ((Values.ButtonRight && Values.isOnLeftWall) || 
				(Values.ButtonLeft && Values.isOnRightWall)) && Values.ButtonJump)
		{
			//alSourcePlay(SourceSoundJump);
			//*-1 pentru ca atunci cand e pe peretele din stanga (de exemplu) va trebui sa ii imprim
			//o forta pozitiva, dar variableWall are val -1 pe peretele din stanga
			velocity.x = Values.speedJumpToSide * variableWall * (-1);
			float velChangeX = velocity.x - Values.hero.theBody.getLinearVelocity().x;
			float impulseX = body.getMass() * velChangeX;
	
	
			velocity.y = Values.speedJumpUp * 1.2f;// * variableWall * (-1);
			float velChangeY = velocity.y - Values.hero.theBody.getLinearVelocity().y;
			float impulseY = body.getMass() * velChangeY;
	
	
			//body.SetLinearVelocity(velocity);
			body.applyLinearImpulse(new Vec2(impulseX,impulseY), body.getWorldCenter() );
		}
		else
			//verific daca vrea sa sara pe acelasi perete in sus
			if(Values.canJumpHorizontally && ((Values.ButtonLeft && Values.isOnLeftWall) || 
					(Values.ButtonRight && Values.isOnRightWall)) && Values.ButtonJump)
			{
			//alSourcePlay(SourceSoundJump);
				velocity.x = Values.speedJumpToTheSameSide * variableWall * (-1);
				float velChangeX = velocity.x - Values.hero.theBody.getLinearVelocity().x;
				float impulseX = body.getMass() * velChangeX;
	
	
				velocity.y = Values.speedJumpUpOnWall;// * variableWall * (-1);
				float velChangeY = velocity.y - Values.hero.theBody.getLinearVelocity().y;
				float impulseY = body.getMass() * velChangeY;
	
	
				//body.SetLinearVelocity(velocity);
				body.applyLinearImpulse(new Vec2(impulseX,impulseY), body.getWorldCenter() );
				imprimeForceOnWall = true;
				//std::cout<<"jumped"<<'\n';
				nnrr = 1;
	
				OriginalTimeToJumpUpTheWall = SystemClock.uptimeMillis();//SystemClock.uptimeMillis();
	
				//salvez de pe care perete a sarit
				if(isOnLeftWall)
				{
					jumpedFromLeftOrRight = -1;
				}
				else
				{
					jumpedFromLeftOrRight = 1;
				}
			}
			else
				//verific daca vrea sa sara de pe perete
				if(Values.canJumpHorizontally && Values.ButtonJump)
				{
			//alSourcePlay(SourceSoundJump);
					velocity.x = (Values.speedJumpToSide / 2.f) * variableWall * (-1);
					float velChangeX = velocity.x - Values.hero.theBody.getLinearVelocity().x;
					float impulseX = body.getMass() * velChangeX;
	
	
					velocity.y = Values.speedJumpUp;// * variableWall * (-1);
					float velChangeY = velocity.y - Values.hero.theBody.getLinearVelocity().y;
					float impulseY = body.getMass() * velChangeY;
	
	
					//body.SetLinearVelocity(velocity);
					body.applyLinearImpulse( new Vec2(impulseX,impulseY), body.getWorldCenter() );
				}
		//CanGoAwayFromWall(12);
	
		//verifica daca vrea sa se indeparteze de perete fara sa sara
		if(((Values.ButtonRight && Values.isOnLeftWall) || (Values.ButtonLeft && Values.isOnRightWall)) 
				&& OriginalTimeOnWall == 0)
		{
			//float verifyTime = timp.getTime();
			//if(verifyTime != -1)
			{
				OriginalTimeOnWall = SystemClock.uptimeMillis();
			}
		}
		else
			//verifica timpul scurs pe perete cand apasa sa sara de pe el
			if(((Values.ButtonRight && Values.isOnLeftWall) || (Values.ButtonLeft && Values.isOnRightWall)) && 
					CanGoAwayFromWall(OriginalTimeOnWall))
			{
				//std::cout<<"goes off\n";
				itWalksInAir(body, 1.1f);
				OriginalTimeOnWall = 0;
			}
			else
			//in cazul in care renunta sa sara, va reseta timpul in care sa sara
				if(	((Values.ButtonRight == false && Values.isOnLeftWall) || 
						(Values.ButtonLeft == false && Values.isOnRightWall))
					&& OriginalTimeOnWall != 0)
				{
					OriginalTimeOnWall = 0;
				}
			//std::cout<<"        is on wall\n";
	}
	
	public static void controlGround(Body body, float T)
	{
		imprimeForceOnWall = false;
		//if(body.GetLinearVelocity().x || body.GetLinearVelocity().y)
		//std::cout<<body.GetLinearVelocity().x<<" "<<body.GetLinearVelocity().y<<'\n';
		if (Values.ButtonJump && Values.canJumpVertically)
		{
			//alSourcePlay(SourceSoundJump);
	
			Values.canJumpVertically = false;
			Values.ButtonJump = false;
			
			velocity.y = Values.speedJumpUp;
			body.setLinearVelocity(velocity);
			return;
		}
	
		// Run on ground
		///velocity.y = 0;
		if (!itWalks(body, T))
		{
			velocity.x = 0;
			body.setLinearVelocity(velocity);
		}
	}
	
	public static void controlCorner(Body body)
	{
		//std::cout<<"corner\n";
	
		//pun vel.x =0, pentru ca altfel ar sari la inceput putin, dupa care sare mult
		velocity.x = 0;
		body.setLinearVelocity(velocity);
	
		velocity.y = 0;
		if (Values.ButtonJump && Values.canJumpVertically)
		{
			//alSourcePlay(SourceSoundJump);
			Values.canJumpVertically = false;
			Values.ButtonJump = false;
			velocity.y = -Values.speedJumpUpOnWall;
			body.setLinearVelocity(velocity);
			return;
		}
		itWalks(Values.hero.theBody, 0.1f);
	}
	
	
	public static boolean itWalks(Body body, float T)
	{
		float sign = 0;
	
		if (Values.ButtonRight && Values.ButtonLeft == false)
		{
			sign = 1;
		}
		else
			if (Values.ButtonRight == false && Values.ButtonLeft)
			{
				sign = -1;
			}
			else
				return false;
	
		float currentSign = 0;
		if(body.getLinearVelocity().x < 0)
		{
			currentSign = -1;
		}
		else
			if(body.getLinearVelocity().x > 0)
			{
				currentSign = 1;
			}
	
		float v = Values.speedWalk;
		if (currentSign != 0 && currentSign != sign)
		{
			//iau pozitia ca sa stiu cum misc camera
			//startPositionCameraX = hero.theBody.getPosition().x;
	
			v *= turnMultiplier;
			//body.SetLinearVelocity(new Vec2(0, 0));
			//std::cout<<v<<'\n';
		}
	
		//verific daca viteza curenta este mai mica decat viteza maxima, altfel nu mai maresc viteza
		if(sign < 0)
		{
			if(velocity.x > 0)
			{
				velocity.x *= -1 * T;
			}
			if(velocity.x > -Values.speedWalk)
			{
				velocity.x += v * sign * T;
			}
			else
			{
				velocity.x = -Values.speedWalk;
			}
		}
		else
			if(sign > 0)
			{
				if(velocity.x < 0)
				{
					velocity.x *= -1 * 0.1f;
				}
				if(velocity.x < Values.speedWalk)
				{
					velocity.x += v * sign * T;
				}
				else
				{
					velocity.x = Values.speedWalk;
				}
			}
	    float velChangeX = velocity.x - Values.hero.theBody.getLinearVelocity().x;
	    float impulseX = body.getMass() * velChangeX;
		//body.SetLinearVelocity(velocity);
	    body.applyLinearImpulse( new Vec2(impulseX,0), body.getWorldCenter() );
	
		//std::cout<<" "<<hero.theBody.GetLinearVelocity().x<<'\n';
	
		return true;
	}
	
	public static boolean itWalksInAir(Body body, float T)
	{
		if(imprimeForceOnWall == false)
		{
			float sign = 0;
			if (Values.ButtonRight && Values.ButtonLeft == false)
			{
				sign = 1;
			}
			else
				if (Values.ButtonRight == false && Values.ButtonLeft)
				{
					sign = -1;
				}
				else
					return false;
	
			float currentSign = 0;
			if(body.getLinearVelocity().x < 0)
			{
				currentSign = -1;
			}
			else
				if(body.getLinearVelocity().x > 0)
				{
					currentSign = 1;
				}
	
			float v = Values.speedWalkInAir;
			if (currentSign != 0 && currentSign != sign)
			{
				//iau pozitia ca sa stiu cum misc camera
				//startPositionCameraX = hero.theBody.getPosition().x;
				v *= turnMultiplierInAir;
			}
	
			//verific daca viteza curenta este mai mica decat viteza maxima, altfel nu mai maresc viteza
			if(sign < 0)
			{
				if(velocity.x > -Values.speedWalkInAir)
				{
					velocity.x += v * sign * T;
				}
				else
				{
					velocity.x = -Values.speedWalkInAir;
				}
			}
			else
			{
				if(velocity.x < Values.speedWalkInAir)
				{
					velocity.x += v * sign * T;
				}
				else
				{
					velocity.x = Values.speedWalkInAir;
				}
			}
	
			float velChangeX = velocity.x - Values.hero.theBody.getLinearVelocity().x;
			float impulseX = body.getMass() * velChangeX;
			//body.SetLinearVelocity(velocity);
			body.applyLinearImpulse( new Vec2(impulseX,0), body.getWorldCenter() );
	
			//std::cout<<hero.theBody.GetLinearVelocity().x<<"     "<<hero.theBody.GetLinearVelocity().y<<"   "<<sign<<'\n';
	
			return true;
		}
		else
		{
			if( (jumpedFromLeftOrRight < 0 && Values.ButtonRight) || (jumpedFromLeftOrRight > 0 && Values.ButtonLeft))
			{
				imprimeForceOnWall = false;
				//std::cout<<"a apasat\n";
			}
				//std::cout<<"jumps us"<<'\n';
			//if(body.GetLinearVelocity().x > 0)
	
			if(SystemClock.uptimeMillis() - OriginalTimeToJumpUpTheWall > 
				Values.timeToStayInAirWhenJumpsOnTheSameWall * (Values.theTimeHowFast / 60))
			{
				if(jumpedFromLeftOrRight < 0)
				{
					velocity.x = -Values.speedJumpToTheSameSide;
				}
				else
				{
					velocity.x = Values.speedJumpToTheSameSide;
					//body.ApplyForce(new Vec2(100 , 0), body.GetWorldCenter());
				}
				float velChangeX = velocity.x - Values.hero.theBody.getLinearVelocity().x;
				float impulseX = body.getMass() * velChangeX * 0.07f * 1.2f;
				//body.SetLinearVelocity(velocity);
	
	
				body.applyLinearImpulse( new Vec2(impulseX,0), body.getWorldCenter() );
				//body.ApplyForce(new Vec2(-500 , 0), body.GetWorldCenter());
			}
			else
			{
				if(jumpedFromLeftOrRight < 0)
				{
					velocity.x = -Values.speedJumpToTheSameSide;
				}
				else
				{
					velocity.x = Values.speedJumpToTheSameSide;
					//body.ApplyForce(new Vec2(100 , 0), body.GetWorldCenter());
				}
				float velChangeX = velocity.x - Values.hero.theBody.getLinearVelocity().x;
				float impulseX = body.getMass() * velChangeX * 0.07f * 0.7f;
				//body.SetLinearVelocity(velocity);
	
	
				body.applyLinearImpulse( new Vec2(impulseX,0), body.getWorldCenter() );
				//body.ApplyForce(new Vec2(-500 , 0), body.GetWorldCenter());
			}
			return true;
		}
	}
	
	
	
	
	
	public static void moveThePlayer()
	{
		///Kill the hero if goes over the boundaries
//		if(Values.hero.theBody.getPosition().x < Values.CameraExtremeLeft - Values.SCREEN_WIDTH / 2.f / Values.scaleSize - 1 ||
//			Values.hero.theBody.getPosition().x > Values.CameraExtremeRight + Values.SCREEN_WIDTH / 2.f / Values.scaleSize + 1 ||
//			Values.hero.theBody.getPosition().y < Values.CameraExtremeDown - Values.SCREEN_HEIGHT / 2.f / Values.scaleSize - 1 ||
//			Values.hero.theBody.getPosition().y > Values.CameraExtremeUp + Values.SCREEN_HEIGHT / 2.f / Values.scaleSize + 1)
//		{
//			///alSourcePlay(SourceSoundDies);
//	
//			//Values.hero.heroIsDead = true;
//			//Values.hero.textureOfBody = playerTextureDead;
//			//Values.hero.heroWasDead = true;
//		}
	
	    desiredVelX = 0;
	
	    ///Also Set the animation index for when it stops
	    if(Values.hero.theBody.getPosition().x != Values.lastPositionOfHeroX)
		{
	    	Values.itMovedX = true;
		}
		else
		{
			Values.itMovedX = false;
		}
	
	    if(Values.hero.theBody.getPosition().y != Values.lastPositionOfHeroY)
		{
	    	Values.itMovedY = true;
		}
		else
		{
			Values.itMovedY = false;
		}
	
	    Values.lastPositionOfHeroX = Values.hero.theBody.getPosition().x;
	    Values.lastPositionOfHeroY = Values.hero.theBody.getPosition().y;
	
	
//	    String theText1 = "states: " + String.valueOf(isInAir) + "; " + String.valueOf(isInCorner)
//	    		 + "; " + String.valueOf(isOnGround);
//		Values.textToShow = '\n' + theText1;

		
		if(isInAir)
		{
			controlAir(Values.hero.theBody, 0.1f);
		}
		else
			if(isInCorner)
			{
				controlCorner(Values.hero.theBody);
			}
			else
				if(isOnGround)
				{
					controlGround(Values.hero.theBody, 0.05f);
				}
					else
						if(isOnLeftWall || isOnRightWall)
						{
							controlWall(Values.hero.theBody);
						}
	
	}



	public static boolean CanGoAwayFromWall(float timeToMatch)
	{
		//currentTime = timp->getTime();
		//if(currentTime != -1)
		currentTime = SystemClock.uptimeMillis();
		//std::cout<<currentTime<<" "<<timeToMatch<<" "<<timeToStayOnWall * (theTimeHowFast / 60)<<'\n';
		{
			//std::cout<<currentTime<<" "<<OriginalTimeOnWall<<'\n';
			if(currentTime - timeToMatch > Values.timeToStayOnWall * (Values.theTimeHowFast / 60) )
			{
				return true;
			}
		}
		return false;
	}

	
	
	
	public static void heroTouchesObjects()
	{
	    ContactEdge edge = Values.hero.theBody.getContactList(); //get all the objects the hero is contacting with
	
		///retin daca se afla in aer ca sa stiu daca creez particule pentru cand atinge pamantul
		boolean wasInAir = isInAir;
	
						Values.canJumpVertically = false;
						Values.canJumpHorizontally = false;
						isOnGround = false;
						isInAir = true;
						isInCorner = false;
						isOnLeftWall = false;
						isOnRightWall = false;
						jumpsUpTheWall = false;
						variableWall = 0;
	
	
	    while (edge != null)
	    {
	        WorldManifold a = new WorldManifold();
	        edge.contact.getWorldManifold(a);
	        Vec2 normal1 = a.normal;
	
	        //vad cu care obiecte intra in contact
	        if (edge.contact.isTouching())
	        {
				BodyUserData us = new BodyUserData();
				us = (BodyUserData)edge.contact.getFixtureA().getBody().getUserData();
//				anotherString = us.name;
	
				///Iau userdataul din corpul pe care il atinge jucatorul, ca sa vad daca il poate omori pe jucator
				BodyUserData us2 = (BodyUserData)edge.contact.getFixtureB().getBody().getUserData();

				///Daca este 1, inseamna ca a atins un obiect care il omoara, asa ca este mort, altfel nu este mort
				if(us2.canKillHero && Values.hero.heroWasDead == false)
				{
					//alSourcePlay(SourceSoundDies);
	
					Values.hero.heroIsDead = us2.canKillHero;
					//Values.hero.textureOfBody = playerTextureDead;
					Values.hero.heroWasDead = true;
					
					BSRenderer.restartGoUpOrDown = 1;
					
					float newColor[] = {3.0f, 0.0f, 0.0f, 1.0f};
					Values.hero.colorOfBody = newColor;
					
				}
				else
					if(us2.isToNextLevel &&
				Values.levelChoserPlayer.indexOfMenuThatItIsOn + 1 < Values.chaptere[Values.levelChoserPlayer.indexOfChapterThatItIsOn].nrOfLevels)// &&
//				Values.chaptere[LevelChooserPlayer.indexOfChapterThatItIsOn].levelFromChapter[LevelChooserPlayer.indexOfLevelThatItIsOn + 1].isAvailable)
					{
						Values.levelChoserPlayer.justFinished = 1;
	                    Values.chaptere[Values.levelChoserPlayer.indexOfChapterThatItIsOn].levelFromChapter[Values.levelChoserPlayer.indexOfMenuThatItIsOn].isFinished = 1;
						///nivele[levelChoserPlayer.indexOfMenuThatItIsOn].isFinished = true;
	
	                    ///Save level as complete
//	                    std::string nameOfLevel = "Menu Of Levels/Chapter" +
//								BStoString(levelChoserPlayer.indexOfChapterThatItIsOn + 1) + "/The Levels details/level" +
//								BStoString(levelChoserPlayer.indexOfMenuThatItIsOn + 1) + ".txt";
//	                    char nameOfLevelChar[100] = "";
//	                    for(int j = 0 ; j < nameOfLevel.size(); j++)
//	                    {
//	                        nameOfLevelChar[j] = nameOfLevel[j];
//	                    }
//	
//	                    std::ifstream citesteTerminat(nameOfLevelChar);
//	                    int term, available;
//	                    std::string name;
//	                    citesteTerminat>>term>>available>>name;
//	                    citesteTerminat.close();
//	
//	                    std::ofstream salveazaTerminat(nameOfLevelChar);
//	                    salveazaTerminat<<1<<" "<<available<<" "<<name<<" "<<
//	                        (CameraExtremeLeft - SCREEN_WIDTH / 2.f / scaleSize)<<" "<<
//	                        (CameraExtremeDown - SCREEN_HEIGHT / 2.f / scaleSize)<<" "<<
//	                        (CameraExtremeUp + SCREEN_HEIGHT / 2.f / scaleSize)<<" "<<
//	                        (CameraExtremeRight + SCREEN_WIDTH / 2.f / scaleSize);
					}
	
				if(us.name == "hero")
				{
					//if it is touching the ground
					if (normal1.y > 0 )//&& isOnLeftWall == false && isOnRightWall == false)
					//if the normal is negative/ the hero is being pushed up/ sitting on top of another object
					{
						//anotherString = "is on the ground";
						Values.canJumpVertically = true;
						isOnGround = true;
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
						//anotherString = "is touching " + toString(normal1.x) + " wall";
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
						Values.canJumpHorizontally = true;
						variableWall = (int) normal1.x;//-1 for left, 1 for right
						isInAir = false;
	
	
						///retin daca tocmai a atins pamantul
						if(wasInAir)
						{
							justHitTheGround = true;
						}
					}
					//anotherString = toString(normal1.x) + "  " + toString(normal1.y);
				}
	        }
	
	        //anotherString = toString(normal1.x) + "  " + toString(normal1.y);
	
	
				//std::cout<<normal1.x<<" "<<normal1.y<<"   "<<' ';
	
	        edge = edge.next;
	    }
	
	    //verfic daca se afla in colt (si pe pamant si pe perete)
		if(isOnGround && (isOnLeftWall || isOnRightWall))
		{
			isInCorner = true;
			isOnLeftWall = false;
			isOnRightWall = false;
			//std::cout<<"is in corner"<<'\n';
		}
	
	}


}
