//
//  InputClass.cpp
//  HelloOpenGL
//
//  Created by Alex Buicescu on 5/25/13.
//
//

#include "InputClass.h"
#include "BSObstacles.h"
#include "BSLevelMenu.h"

BSObstacles *objClassObstacle = new BSObstacles();
BSLevelMenu *objClassLevelMenu = new BSLevelMenu();
//, enterPressed = false, escapePressed = false,
//backspacePressed = false, speedChangedBoostHigh = false;

void controlJump()
{
	//if presses jump the first time
	if(!jumpPressed && (isOnGround || isOnLeftWall || isOnRightWall))
	{
		isSpaceDown = true;
		ButtonJump = true;
		jumpPressed = true;
	}
	else
		///if he presses jump the second time
		if(!jumpPressed &&
		   isInAir && !isInCorner && !isOnLeftWall && !isOnRightWall &&
		   ((!pressedJumpSecond && hero->heroIsBerserk1) || hero->heroIsBerserk2 || hero->heroIsBerserk3 ))
		{
			isSpaceDown = true;
			pressedJumpSecond = true;
			jumpSecondSpinned = false;
			ButtonJump = true;
			jumpPressed = true;
		}
		else
			///if he presses jump, but is not the first time
			///put !jumpPressed for unlimited jumps
			if(!jumpPressed && pressedJumpSecond)
			{
				isSpaceDown = true;
				ButtonJump = false;
				jumpPressed = true;
			}
			else
			{
				isSpaceDown = true;
				ButtonJump = false;
				jumpPressed = true;
			}
}

void InputClass::getTouch()
{
	if(backBtn->canClick)
	{
		ControlAnyMenuEscape();
		backBtn->canClick = false;
	}
	else
		if(btnDarkLevels->canClick)
		{
			if(DarkLevels)
			{
				DarkLevels = false;
			}
			else
			{
				DarkLevels = true;
			}
			btnDarkLevels->canClick = false;
		}
		else
			if(btnTimeControl->canClick)
			{
				if(theTimeHowFast == 120)
				{
					theTimeHowFast = 60;
				}
				else
				{
					theTimeHowFast = 120;
				}
				btnTimeControl->canClick = false;
			}
    
	if(btnPowerUp1->canClick && !hero->heroIsBerserk1)
	{
		std::cout<<"powerd up 1"<<'\n';
        btnPowerUp1->canClick = false;
        
		hero->heroIsBerserk1 = true;
        hero->heroIsBerserk2 = false;
        hero->heroIsBerserk3 = false;
        
        listOfActiveAnimations[1]->indexOfAnimation = hero->animationIndexPlayerAura1;
        listOfActiveAnimations[1]->canPlayIt = true;
        listOfActiveAnimations[1]->isAtStepOfAnimation1 = true;
        listOfActiveAnimations[1]->isAtStepOfAnimation2 = false;
        listOfActiveAnimations[1]->isAtStepOfAnimation3 = false;
        
		hero->animationIndexCurrentAnimationBerserk = hero->animationIndexPlayerAura1;
        //		hero->IsAtStepOfAnimation21 = true;
        //		hero->IsAtStepOfAnimation22 = false;
        //		hero->IsAtStepOfAnimation23 = false;
        
	}
	else
        if(btnPowerUp2->canClick && !hero->heroIsBerserk2)
        {
			std::cout<<"powerd up 2"<<'\n';
            btnPowerUp2->canClick = false;
            
            hero->heroIsBerserk1 = false;
            hero->heroIsBerserk2 = true;
            hero->heroIsBerserk3 = false;
            
            ///play the last power up ending animation
            /*listOfActiveAnimations[4]->indexOfAnimation = hero->animationIndexPlayerAura2;
            listOfActiveAnimations[4]->canPlayIt = true;
            listOfActiveAnimations[4]->isAtStepOfAnimation1 = true;
            listOfActiveAnimations[4]->isAtStepOfAnimation2 = false;
            listOfActiveAnimations[4]->isAtStepOfAnimation3 = false;
            */
            
            ///play the 2nd aura
            listOfActiveAnimations[1]->indexOfAnimation = hero->animationIndexPlayerAura2;
            listOfActiveAnimations[1]->canPlayIt = true;
            listOfActiveAnimations[1]->isAtStepOfAnimation1 = true;
            listOfActiveAnimations[1]->isAtStepOfAnimation2 = false;
            listOfActiveAnimations[1]->isAtStepOfAnimation3 = false;
            
            ///play the electricity
            listOfActiveAnimations[2]->indexOfAnimation = hero->animationIndexPlayerAuraElectricity;
            listOfActiveAnimations[2]->canPlayIt = true;
            listOfActiveAnimations[2]->isAtStepOfAnimation1 = true;
            listOfActiveAnimations[2]->isAtStepOfAnimation2 = false;
            listOfActiveAnimations[2]->isAtStepOfAnimation3 = false;
            
            hero->animationIndexCurrentAnimationBerserk = hero->animationIndexPlayerAura2;
            //            hero->IsAtStepOfAnimation21 = true;
            //            hero->IsAtStepOfAnimation22 = false;
            //            hero->IsAtStepOfAnimation23 = false;
            
            ///pressedKeys[SDLK_b] = true;
        }
        else
            if(btnPowerUp3->canClick && !hero->heroIsBerserk3)
            {
				std::cout<<"powerd up 3"<<'\n';
                btnPowerUp3->canClick = false;
                
                listOfActiveAnimations[2]->canPlayIt = false;
                
                hero->heroIsBerserk1 = false;
                hero->heroIsBerserk2 = false;
                hero->heroIsBerserk3 = true;
                
                listOfActiveAnimations[1]->indexOfAnimation = hero->animationIndexPlayerAura3;
                listOfActiveAnimations[1]->canPlayIt = true;
                listOfActiveAnimations[1]->isAtStepOfAnimation1 = true;
                listOfActiveAnimations[1]->isAtStepOfAnimation2 = false;
                listOfActiveAnimations[1]->isAtStepOfAnimation3 = false;
                
                hero->animationIndexCurrentAnimationBerserk = hero->animationIndexPlayerAura3;
                //                hero->IsAtStepOfAnimation21 = true;
                //                hero->IsAtStepOfAnimation22 = false;
                //                hero->IsAtStepOfAnimation23 = false;
                
                ///pressedKeys[SDLK_b] = true;
            }
            else
                if((btnPowerUp1->canClick && hero->heroIsBerserk1) ||
                   (btnPowerUp2->canClick && hero->heroIsBerserk2) ||
                   (btnPowerUp3->canClick && hero->heroIsBerserk3))
                {
					std::cout<<"no more power up"<<'\n';
					listOfActiveAnimations[1]->isAtStepOfAnimation1 = false;
					listOfActiveAnimations[1]->isAtStepOfAnimation3 = true;
                    //listOfActiveAnimations[1]->canPlayIt = false;
                    listOfActiveAnimations[2]->canPlayIt = false;
                    hero->heroIsBerserk1 = false;
                    hero->heroIsBerserk2 = false;
                    hero->heroIsBerserk3 = false;
                    btnPowerUp1->canClick = false;
                    btnPowerUp2->canClick = false;
                    btnPowerUp3->canClick = false;
                }
	
	if(currentMenu->indexOfMenu == 3)
	{
	}
	else
	{
		///Check if presses left or right, so I can change sound
		ControlAnyMenuLeftRightUpDown(0);
		
		if(movedY > 0 && abs(movedY / movedX) > 2 && moved == true) //keystates[heroKeyboard->Up] && !pressedKeys[heroKeyboard->Up])
		{
			ControlAnyMenuLeftRightUpDown(1);
			///In caz ca se misca in nivele
			objClassLevelMenu->walkThroughLevels(0, 1, chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter);
			///In caz ca se misca in chaptere
			objClassLevelMenu->walkThroughChapters(0, 1);
			//pressedKeys[heroKeyboard->Up] = true;
			moved = false;
		}
		else
			if(movedY < 0 && abs(movedY / movedX) > 2 && moved == true)
				//keystates[heroKeyboard->Down] && !pressedKeys[heroKeyboard->Down])
			{
				ControlAnyMenuLeftRightUpDown(-1);
				///In caz ca se misca in meniu
				objClassLevelMenu->walkThroughLevels(0, -1, chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter);
				///In caz ca se misca in chaptere
				objClassLevelMenu->walkThroughChapters(0, -1);
				//pressedKeys[heroKeyboard->Down] = true;
				moved = false;
			}
        
		///Schimb sunetul daca pot
        //			if(canChangeVolumeAudioSfx || canChangeVolumeMusic)
		{
			if(movedX > 0 && abs(movedX / movedY) > 2 && moved == true)
				//keystates[heroKeyboard->Right] && !pressedKeys[heroKeyboard->Right])
			{
				///In caz ca se misca in meniu
				objClassLevelMenu->walkThroughLevels(1, 0, chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter);
				///In caz ca se misca in chaptere
				objClassLevelMenu->walkThroughChapters(1, 0);
                
				if(canChangeVolumeMusic && newVolumeAudio < 1)
				{
					newVolumeAudio += 0.1f;
					//alSourcef(SourceSoundMusic, AL_GAIN, newVolumeAudio);
				}
				else
					if(canChangeVolumeAudioSfx && newVolumeSFX < 1)
					{
						newVolumeSFX += 0.1f;
						/*alSourcef(SourceSoundDies, AL_GAIN, newVolumeSFX);
						 alSourcef(SourceSoundJump, AL_GAIN, newVolumeSFX);
						 alSourcef(SourceSoundBeginningGame, AL_GAIN, newVolumeSFX );
						 alSourcePlay(SourceSoundJump);*/
                    }
                
				//pressedKeys[heroKeyboard->Right] = true;
				moved = false;
			}
			else
				if(movedX < 0 && abs(movedX / movedY) > 2 && moved == true)
				   //keystates[heroKeyboard->Left] && !pressedKeys[heroKeyboard->Left])
				{
					///In caz ca se misca in meniu
					objClassLevelMenu->walkThroughLevels(-1, 0, chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter);
					///In caz ca se misca in chaptere
					objClassLevelMenu->walkThroughChapters(-1, 0);
                    
					if(canChangeVolumeMusic && newVolumeAudio > 0)
					{
						newVolumeAudio -= 0.1f;
						//alSourcef(SourceSoundMusic, AL_GAIN, newVolumeAudio);
					}
					else
						if(canChangeVolumeAudioSfx && newVolumeSFX > 0)
						{
							newVolumeSFX -= 0.1f;
							/*alSourcef(SourceSoundDies, AL_GAIN, newVolumeSFX);
							 alSourcef(SourceSoundJump, AL_GAIN, newVolumeSFX);
							 alSourcef(SourceSoundBeginningGame, AL_GAIN, newVolumeSFX );
							 alSourcePlay(SourceSoundJump);*/
						}
                    
					//pressedKeys[heroKeyboard->Left] = true;
					moved = false;
				}
		}
	}
    
    
	///Left - Right - Jump
	if(currentMenu->indexOfMenu == 3 && !isButtonDown)
	{
		//daca se misca
		if(lastMovementPosition.x != 0 || lastMovementPosition.y != 0)
		{
			//daca apasa dreapta-sus
			if(lastMovementPosition.x - 240 > 0 && lastMovementPosition.y - 160 > 0)
			{
				quadrantIndex = 2;
				//std::cout<<"bottom right"<<'\n';
				ButtonRight = true;
				ButtonJump = false;
				ButtonLeft = false;
                justJumped = false;
                justJumped2 = false;
			}
			else
				if(lastMovementPosition.x - 240 > 0 && lastMovementPosition.y - 160 < 0)
                {
					quadrantIndex = 4;
					//std::cout<<"top right"<<'\n';
                    controlJump();
					ButtonRight = true;
					ButtonLeft = false;
				}
				else
					if(lastMovementPosition.x - 240 < 0 && lastMovementPosition.y - 160 > 0)
					{
						quadrantIndex = 1;
						//std::cout<<"bottom left"<<'\n';
						ButtonLeft = true;
						ButtonJump = false;
						ButtonRight = false;
                        justJumped = false;
                        justJumped2 = false;
					}
					else
						if(lastMovementPosition.x - 240 < 0 && lastMovementPosition.y - 160 < 0)
						{
							quadrantIndex = 3;
							//std::cout<<"top left"<<'\n';
                            controlJump();
							ButtonLeft = true;
							ButtonRight = false;
						}
		}
		else
		{
			isSpaceDown = false;
			jumpPressed = false;
			ButtonJump = false;
			ButtonLeft = false;
			ButtonRight = false;
			quadrantIndex = 0;
		}
	}
	else
	{
		//daca a apasat
		if(tapped == true)
		{
			ControlAnyMenuEnter();
			tapped = false;
		}
	}
}


void InputClass::ControlAnyMenuEnter()
{
	///Daca nu se afla in meniul de selectat nivele atunci poate face orice
	if(currentMenu->indexOfMenu != 4 && currentMenu->indexOfMenu != 5 && currentMenu->indexOfMenu != 3)
	{
		///Verific daca sunt in meniul de SETTINGS ca sa stiu daca salvez sau nu datele
		if(currentMenu->indexOfMenu != 2)
		{
			currentVolumeAudio = newVolumeAudio;
			currentVolumeSFX = newVolumeSFX;
		}
		else
		{
			///Verific daca apasa pe SAVE sau CANCEL
			if(currentButton->indexOfButton == 3)//Cancel
			{
				newVolumeAudio = currentVolumeAudio;
				newVolumeSFX = currentVolumeSFX;
                /*
				 alSourcef(SourceSoundMusic, AL_GAIN, newVolumeAudio);
				 alSourcef(SourceSoundJump, AL_GAIN, newVolumeSFX);
				 alSourcef(SourceSoundDies, AL_GAIN, newVolumeSFX);
				 alSourcef(SourceSoundBeginningGame, AL_GAIN, newVolumeSFX);*/
			}
			else
				if(currentButton->indexOfButton == 4)//Save
				{
					currentVolumeAudio = newVolumeAudio;
					currentVolumeSFX = newVolumeSFX;
				}
		}
        
		///Daca apasa pe butonul de EXIT
		if(currentButton->NextMenuIndex == -3)
		{
			quit = true;
		}
		else
            
			///Daca se plimba prin meniuri
			if(currentButton->NextMenuIndex >= 0)
			{
				///Vad din ce meniu ajunge in SETTINGS ca sa stiu unde ma intorc
				if(currentMenu->indexOfMenu == 0 && currentButton->indexOfButton == 1)//Din First Menu
				{
					settingsFromFirstOrGame = true;
				}
				else
					if(currentMenu->indexOfMenu == 1 && currentButton->indexOfButton == 2)//Din Pause Menu
					{
						settingsFromFirstOrGame = false;
					}
					else
						if(currentMenu->indexOfMenu == 1 && currentButton->indexOfButton == 1)//Daca da Restart
						{
                            std::list<BSCoins*>::iterator it;
                            for(it = listOfCoins.begin(); it != listOfCoins.end(); it++)
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
                            
							hero->heroIsDead = false;
							hero->texture = playerTexture;
							canJumpHorizontally = false;
							canJumpVertically = false;
							isOnGround = false;
							isInAir = true;
							isOnLeftWall = false;
							isOnRightWall = false;
							hero->theBody->SetTransform(b2Vec2(HeroInitialX, HeroInitialY), 0);
							hero->theBody->ApplyLinearImpulse(b2Vec2(0, 0.1f), hero->theBody->GetWorldCenter());
						}
                
				///Setez in ce meniu se duce din cel de SETTINGS, exemplu: ori in First Menu, ori Pause Menu
				if(currentMenu->indexOfMenu == 2 && (currentButton->indexOfButton == 3 || currentButton->indexOfButton == 4))
				{
					std::list<BSMenuStructure*>::iterator i;
                    
					for(i = listOfMenus.begin(); i != listOfMenus.end(); i++)
					{
						if(settingsFromFirstOrGame)
						{
							if((*i)->indexOfMenu == 0)
							{
								currentMenu = (*i);
								currentButton = (*i)->listOfButtons.front();
								break;
							}
                            
							///currentMenuIndex = 0;//Se duce in First Menu
						}
						else
						{
							if((*i)->indexOfMenu == 1)
							{
								currentMenu = (*i);
								currentButton = (*i)->listOfButtons.front();
								break;
							}
                            
							///currentMenuIndex = 1;//Se duce in Pause Menu
						}
					}
                    
					///currentButtonIndex = 0;
				}
				else
					///Daca se afla in oricare parte a meniului
				{
					std::cout<<"the Menu: "<<currentMenu->indexOfMenu<<"; current button: "<<currentButton->indexOfButton<<
                    "; next menu from button: "<<currentButton->NextMenuIndex<<"; found: ";
					std::list<BSMenuStructure*>::iterator i;
                    
					if(currentMenu->indexOfMenu == 1)//daca e in pause menu
					{
						if(currentButton->NextMenuIndex == 4)//daca vrea sa iasa din level
						{
							//refac coinsurile
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
						}
					}
                    
					for(i = listOfMenus.begin(); i != listOfMenus.end(); i++)
					{
						if((*i)->indexOfMenu == currentButton->NextMenuIndex)
						{
							std::cout<<"yup"<<'\n';
							currentMenu = (*i);
							currentButton = (*i)->listOfButtons.front();
							break;
						}
						else
						{
							std::cout<<(*i)->indexOfMenu<<'\n';
						}
					}
                    
					///currentMenuIndex = TheMenus[currentMenuIndex]->Buttons[currentButtonIndex]->NextMenuIndex;
					///currentButtonIndex = 0;
				}
			}
	}
	else
		if(currentMenu->indexOfMenu == 4 && levelChoserPlayer->canMove)
		{
			std::string nameString = "Menu Of Levels/Chapter" +
            BStoString(levelChoserPlayer->indexOfChapterThatItIsOn + 1) + "/The Levels objects/level" +
            BStoString(levelChoserPlayer->indexOfLevelThatItIsOn + 1) + ".xml";
			char nameChar[100] = "";
            
			strcpy(nameChar, nameString.c_str());
            
			objClassObstacle->destroyLevel();
			objClassObstacle->incarcaHarta(nameChar);
            
			std::list<BSMenuStructure*>::iterator iteratorMenus;
            
			for(iteratorMenus = listOfMenus.begin(); iteratorMenus != listOfMenus.end(); iteratorMenus++)
			{
				if((*iteratorMenus)->indexOfMenu == 3)
				{
					currentMenu = (*iteratorMenus);
					std::list<BSButtonStructure*>::iterator iteratorButtons;
                    
					for(iteratorButtons = currentMenu->listOfButtons.begin();
                        iteratorButtons != currentMenu->listOfButtons.end(); iteratorButtons++)
					{
						if((*iteratorButtons)->indexOfButton == 0)
						{
							currentButton = (*iteratorButtons);
						}
                        
						break;
					}
                    
					break;
				}
			}
		}
		else
			if(currentMenu->indexOfMenu == 5 && levelChoserPlayer->canMove)
			{
				std::list<BSMenuStructure*>::iterator iteratorMenus;
                
				for(iteratorMenus = listOfMenus.begin(); iteratorMenus != listOfMenus.end(); iteratorMenus++)
				{
					if((*iteratorMenus)->indexOfMenu == 4)
					{
						currentMenu = (*iteratorMenus);
						std::list<BSButtonStructure*>::iterator iteratorButtons;
                        
						for(iteratorButtons = currentMenu->listOfButtons.begin();
                            iteratorButtons != currentMenu->listOfButtons.end(); iteratorButtons++)
						{
							if((*iteratorButtons)->indexOfButton == 0)
							{
								currentButton = (*iteratorButtons);
							}
                            
							break;
						}
                        
						break;
					}
				}
                
                //				currentMenuIndex = 4;
                //				currentButtonIndex = 0;
                
				levelChoserPlayer->xCord = chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter[0]->xCord;
				levelChoserPlayer->yCord = chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter[0]->yCord;
			}
}

void InputClass::ControlAnyMenuEscape()
{
	///Daca e in joc, trece in Pause Menu
	if(currentMenu->indexOfMenu == 3)
	{
		std::list<BSMenuStructure*>::iterator iteratorMenus;
        
		for(iteratorMenus = listOfMenus.begin(); iteratorMenus != listOfMenus.end(); iteratorMenus++)
		{
			if((*iteratorMenus)->indexOfMenu == 1)
			{
				currentMenu = (*iteratorMenus);
				std::list<BSButtonStructure*>::iterator iteratorButtons;
                
				for(iteratorButtons = currentMenu->listOfButtons.begin();
                    iteratorButtons != currentMenu->listOfButtons.end(); iteratorButtons++)
				{
					if((*iteratorButtons)->indexOfButton == 0)
					{
						currentButton = (*iteratorButtons);
					}
                    
					break;
				}
                
				break;
			}
		}
        
        //		currentMenuIndex = 1;
        //		currentButtonIndex = 0;
	}
	else
        
		///Daca e in Levels, trece in Chapters
		if(currentMenu->indexOfMenu == 4)
		{
			std::list<BSMenuStructure*>::iterator iteratorMenus;
            
			for(iteratorMenus = listOfMenus.begin(); iteratorMenus != listOfMenus.end(); iteratorMenus++)
			{
				if((*iteratorMenus)->indexOfMenu == 5)
				{
					currentMenu = (*iteratorMenus);
					std::list<BSButtonStructure*>::iterator iteratorButtons;
                    
					for(iteratorButtons = currentMenu->listOfButtons.begin();
                        iteratorButtons != currentMenu->listOfButtons.end(); iteratorButtons++)
					{
						if((*iteratorButtons)->indexOfButton == 0)
						{
							currentButton = (*iteratorButtons);
						}
                        
						break;
					}
                    
					break;
				}
			}
            
            //			currentMenuIndex = 5;
            //			currentButtonIndex = 0;
            
			levelChoserPlayer->xCord = chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->xCord;
			levelChoserPlayer->yCord = chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->yCord;
            
			levelChoserPlayer->indexOfLevelThatItIsOn = 0;
		}
		else
            
			///Daca e in Chapters, trece in Levels
			if(currentMenu->indexOfMenu == 5)
			{
				std::list<BSMenuStructure*>::iterator iteratorMenus;
                
				for(iteratorMenus = listOfMenus.begin(); iteratorMenus != listOfMenus.end(); iteratorMenus++)
				{
					if((*iteratorMenus)->indexOfMenu == 0)
					{
						currentMenu = (*iteratorMenus);
						std::list<BSButtonStructure*>::iterator iteratorButtons;
                        
						for(iteratorButtons = currentMenu->listOfButtons.begin();
                            iteratorButtons != currentMenu->listOfButtons.end(); iteratorButtons++)
						{
							if((*iteratorButtons)->indexOfButton == 0)
							{
								currentButton = (*iteratorButtons);
							}
                            
							break;
						}
                        
						break;
					}
				}
                
                //				currentMenuIndex = 0;
                //				currentButtonIndex = 0;
			}
			else
                
				///Daca e in Pause Menu, trece in joc
				if(currentMenu->indexOfMenu == 1)
				{
					std::list<BSMenuStructure*>::iterator iteratorMenus;
                    
					for(iteratorMenus = listOfMenus.begin(); iteratorMenus != listOfMenus.end(); iteratorMenus++)
					{
						if((*iteratorMenus)->indexOfMenu == 3)
						{
							currentMenu = (*iteratorMenus);
							std::list<BSButtonStructure*>::iterator iteratorButtons;
                            
							for(iteratorButtons = currentMenu->listOfButtons.begin();
                                iteratorButtons != currentMenu->listOfButtons.end(); iteratorButtons++)
							{
								if((*iteratorButtons)->indexOfButton == 0)
								{
									currentButton = (*iteratorButtons);
								}
                                
								break;
							}
                            
							break;
						}
					}
                    
                    //					currentMenuIndex = 3;
                    //					currentButtonIndex = 0;
				}
				else
                    
					///Daca e in Settings
					if(currentMenu->indexOfMenu == 2)
					{
						std::list<BSMenuStructure*>::iterator i;
                        
						for(i = listOfMenus.begin(); i != listOfMenus.end(); i++)
						{
							if(settingsFromFirstOrGame)
							{
								if((*i)->indexOfMenu == 0)
								{
									currentMenu = (*i);
									currentButton = (*i)->listOfButtons.front();
									break;
								}
                                
								///currentMenuIndex = 0;//Se duce in First Menu
							}
							else
							{
								if((*i)->indexOfMenu == 1)
								{
									currentMenu = (*i);
									currentButton = (*i)->listOfButtons.front();
									break;
								}
                                
								///currentMenuIndex = 1;//Se duce in Pause Menu
							}
						}
                        
						///currentButtonIndex = 0;
						newVolumeAudio = currentVolumeAudio;
						newVolumeSFX = currentVolumeSFX;
                        /*
						 alSourcef(SourceSoundMusic, AL_GAIN, newVolumeAudio);
						 alSourcef(SourceSoundJump, AL_GAIN, newVolumeSFX);
						 alSourcef(SourceSoundDies, AL_GAIN, newVolumeSFX);
						 alSourcef(SourceSoundBeginningGame, AL_GAIN, newVolumeSFX);*/
					}
}



void InputClass::ControlAnyMenuLeftRightUpDown(int upOrDown)
{
	///Daca nu se afla in meniul de selectat nivele atunci poate face orice
	if(currentMenu->indexOfMenu != 4 && currentMenu->indexOfMenu != 5)
	{
		if(upOrDown == 1)
		{
			if(currentButton->indexOfButton > 0)
			{
				std::list<BSButtonStructure*>::iterator i;
                
				for(i = currentMenu->listOfButtons.begin(); i != currentMenu->listOfButtons.end(); i++)
				{
					if((*i)->indexOfButton == currentButton->indexOfButton - 1)
					{
						currentButton = (*i);
						break;
					}
				}
                
				///currentButtonIndex--;
			}
		}
		else
			if(upOrDown == -1)
			{
				if(currentButton->indexOfButton < currentMenu->numberOfButtons - 1)
				{
					std::list<BSButtonStructure*>::iterator i;
                    
					for(i = currentMenu->listOfButtons.begin(); i != currentMenu->listOfButtons.end(); i++)
					{
						if((*i)->indexOfButton == currentButton->indexOfButton + 1)
						{
							currentButton = (*i);
							break;
						}
					}
                    
					///currentButtonIndex++;
				}
			}
        
		///Daca vrea sa modifice volumul sau rezolutia
		if(currentButton->NextMenuIndex == -2)
		{
			if(currentButton->indexOfButton == 0)
			{
				canChangeVolumeMusic = true;
				canChangeVolumeAudioSfx = false;
				canChangeResolution = false;
			}
			else
				if(currentButton->indexOfButton == 1)
				{
					canChangeVolumeMusic = false;
					canChangeVolumeAudioSfx = true;
					canChangeResolution = false;
				}
				else
					if(currentButton->indexOfButton == 2)
					{
						canChangeVolumeMusic = false;
						canChangeVolumeAudioSfx = false;
						canChangeResolution = true;
					}
		}
	}
}

