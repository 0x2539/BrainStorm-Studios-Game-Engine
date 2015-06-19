//
//  BSInputClass.cpp
//  HelloOpenGL
//
//  Created by Alex Buicescu on 5/25/13.
//
//

#include "BSInputClass.h"
#include "BSObstacles.h"
#include "BSLevelMenu.h"

BSObstacles *objClassObstacle = new BSObstacles();
BSLevelMenu *objClassLevelMenu = new BSLevelMenu();
//, enterPressed = false, escapePressed = false,
//backspacePressed = false, speedChangedBoostHigh = false;
BSTexture *someRender = new BSTexture();

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
		if(!jumpPressed && isInAir && !isInCorner && !isOnLeftWall && !isOnRightWall &&
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

void BSInputClass::getTouch()
{
	if(isButtonDown)
	{
		if(backBtn->canClick)
		{
			ControlAnyMenuEscape();
			backBtn->canClick = false;
			isButtonDown = false;
		}
		else
			if(btnDarkLevels->canClick)
			{
				//LOGI("%s", "is actioning the dark");
				if(DarkLevels)
				{
					DarkLevels = false;
				}
				else
				{
					DarkLevels = true;
				}
				btnDarkLevels->canClick = false;
				isButtonDown = false;
			}
			else
				if(btnTimeControl->canClick)
				{
					//LOGI("%s", "is actioning the time");
					if(theTimeHowFast == 120)
					{
						theTimeHowFast = 60;
					}
					else
					{
						theTimeHowFast = 120;
					}
					btnTimeControl->canClick = false;
					isButtonDown = false;
				}
				else
			if(btnPowerUp1->canClick)
			{
				///if hero is not berserk, then berserk it and unberserk the other 2 powers
				if(!hero->heroIsBerserk1)
				{
					if(hero->heroIsBerserk2)
					{
						listOfActiveAnimations[2]->finish = true;
					}
					else
						if(hero->heroIsBerserk3)
						{
							listOfActiveAnimations[3]->finish = true;
						}

					hero->heroIsBerserk1 = true;
							listOfActiveAnimations[1]->indexOfAnimation = hero->animationIndexPlayerAura1;
							listOfActiveAnimations[1]->setPlayableStatus(true);
					hero->animationIndexCurrentAnimationBerserk = hero->animationIndexPlayerAura1;
				}
				else
					if(hero->heroIsBerserk1)
					{
						hero->heroIsBerserk1 = false;
						listOfActiveAnimations[1]->finish = true;
					}

				btnPowerUp1->canClick = false;
				hero->heroIsBerserk2 = false;
				hero->heroIsBerserk3 = false;
				isButtonDown = false;
			}
			else
				if(btnPowerUp2->canClick)
				{
					if(!hero->heroIsBerserk2)
					{
						if(hero->heroIsBerserk1)
						{
							listOfActiveAnimations[1]->finish = true;
						}
						else
							if(hero->heroIsBerserk3)
							{
								listOfActiveAnimations[3]->finish = true;
							}
						hero->heroIsBerserk2 = true;
							listOfActiveAnimations[2]->indexOfAnimation = hero->animationIndexPlayerAura2;
							listOfActiveAnimations[2]->setPlayableStatus(true);
							listOfActiveAnimations[4]->indexOfAnimation = hero->animationIndexPlayerAuraElectricity;
							listOfActiveAnimations[4]->setPlayableStatus(true);
						hero->animationIndexCurrentAnimationBerserk = hero->animationIndexPlayerAura2;
					}
					else
						if(hero->heroIsBerserk2)
						{
							hero->heroIsBerserk2 = false;
							listOfActiveAnimations[2]->finish = true;
						}

					btnPowerUp2->canClick = false;
					hero->heroIsBerserk1 = false;
					hero->heroIsBerserk3 = false;
					isButtonDown = false;
				}
				else
					if(btnPowerUp3->canClick)
					{
						if(!hero->heroIsBerserk3)
						{
							if(hero->heroIsBerserk1)
							{
								listOfActiveAnimations[1]->finish = true;
							}
							else
								if(hero->heroIsBerserk2)
								{
									listOfActiveAnimations[2]->finish = true;
								}

							hero->heroIsBerserk3 = true;
								listOfActiveAnimations[3]->indexOfAnimation = hero->animationIndexPlayerAura3;
								listOfActiveAnimations[3]->setPlayableStatus(true);
							hero->animationIndexCurrentAnimationBerserk = hero->animationIndexPlayerAura3;

						}
						else
						{
							hero->heroIsBerserk3 = false;
							listOfActiveAnimations[3]->finish = true;
						}

						btnPowerUp3->canClick = false;
						hero->heroIsBerserk1 = false;
						hero->heroIsBerserk2 = false;
						isButtonDown = false;
					}
	}
	else
		if(!isButtonDown)
		{
			//LOGI("%s", "after checking buttons");

			/*
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
		*/
			//LOGI("%s", "before1");
			if(currentMenu->indexOfMenu == 3)
			{
				//LOGI("%s", "before2");
			}
			else
			{
				//LOGI("%s", "before3");
				////LOGI("%s", "here1");
				///Check if presses left or right, so I can change sound
				ControlAnyMenuLeftRightUpDown(0);

				if(movedY > 0 && abs(movedY / movedX) > 2 && moved == true) //keystates[heroKeyboard->Up] && !pressedKeys[heroKeyboard->Up])
				{
					//LOGI("%s", "before4");
					////LOGI("%s", "here2");
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
						//LOGI("%s", "before5");
						////LOGI("%s", "here3");
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
						//LOGI("%s", "before6");
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
			//LOGI("%s", "before9");


			///Left - Right - Jump
			if(currentMenu->indexOfMenu == 3 && !isButtonDown)
			{
				//daca se misca
				if(lastMovementPosition.x != -1 || lastMovementPosition.y != -1)
				{
					//daca apasa dreapta-sus
					if(lastMovementPosition.x - SCREEN_WIDTH / 2 > 0 && lastMovementPosition.y - SCREEN_HEIGHT / 2 > 0)
					{
						quadrantIndex = 2;
						//std::cout<<"bottom right"<<'\n';
						ButtonRight = true;
						ButtonJump = false;
						ButtonLeft = false;
						isSpaceDown = false;
						justJumped = false;
						justJumped2 = false;
					}
					else
						if(lastMovementPosition.x - SCREEN_WIDTH / 2 > 0 && lastMovementPosition.y - SCREEN_HEIGHT / 2 < 0)
						{
							quadrantIndex = 4;
							//std::cout<<"top right"<<'\n';
							controlJump();
							ButtonRight = true;
							ButtonLeft = false;
						}
						else
							if(lastMovementPosition.x - SCREEN_WIDTH / 2 < 0 && lastMovementPosition.y - SCREEN_HEIGHT / 2 > 0)
							{
								quadrantIndex = 1;
								//std::cout<<"bottom left"<<'\n';
								ButtonLeft = true;
								ButtonJump = false;
								isSpaceDown = false;
								ButtonRight = false;
								justJumped = false;
								justJumped2 = false;
							}
							else
								if(lastMovementPosition.x - SCREEN_WIDTH / 2 < 0 && lastMovementPosition.y - SCREEN_HEIGHT / 2 < 0)
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
}



void BSInputClass::ControlAnyMenuEnter()
{
	///Daca nu se afla in meniul de selectat nivele atunci poate face orice
	if(currentMenu->indexOfMenu != 4 && currentMenu->indexOfMenu != 5)
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

				//alSourcef(SourceSoundMusic1, AL_GAIN, newVolumeAudio);
				//alSourcef(SourceSoundMusic2, AL_GAIN, newVolumeAudio);
				//alSourcef(SourceSoundMusic3, AL_GAIN, newVolumeAudio);
				//alSourcef(SourceSoundJump, AL_GAIN, newVolumeSFX);
				//alSourcef(SourceSoundDies, AL_GAIN, newVolumeSFX);
				//alSourcef(SourceSoundBeginningGame, AL_GAIN, newVolumeSFX);
                //alSourcef(SourceSoundPowerUp, AL_GAIN, newVolumeSFX);
                //alSourcef(SourceSoundTeleport, AL_GAIN, newVolumeSFX );
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
								for(int it = 0; it < listOfCoins.size(); it++)
								{
									listOfCoins[it]->available = true;
									listOfCoins[it]->deleteIt = false;
									coinsThisLevel = 0;
												listOfCoins[it]->sinValue = 90;
												listOfCoins[it]->sinValue2 = 0;
												listOfCoins[it]->color.a = 1.0f;
												listOfCoins[it]->xCord = listOfCoins[it]->xInit;
												listOfCoins[it]->yCord = listOfCoins[it]->yInit;
								}

                            someRender->resetDustBodies();

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
					for(int i = 0; i < listOfMenus.size(); i++)
					{
						if(settingsFromFirstOrGame)
						{
							if(listOfMenus[i]->indexOfMenu == 0)
							{
								currentMenu = listOfMenus[i];
								currentButton = listOfMenus[i]->listOfButtons.front();
								break;
							}
						}
						else
						{
							if(listOfMenus[i]->indexOfMenu == 1)
							{
								currentMenu = listOfMenus[i];
								currentButton = listOfMenus[i]->listOfButtons.front();
								break;
							}

						}
					}
				}
				else
					///Daca se afla in oricare parte a meniului
				{
					std::cout<<"the Menu: "<<currentMenu->indexOfMenu<<"; current button: "<<currentButton->indexOfButton<<
							 "; next menu from button: "<<currentButton->NextMenuIndex<<"; found: ";

					//daca e in pause menu
					if(currentMenu->indexOfMenu == 1 && currentButton->NextMenuIndex == 4)
					{
                        //alSourcePlay(SourceSoundBeginningGame);
                        //refac coinsurile
                        for(int it = 0; it < listOfCoins.size(); it++)
                        {
                            if(listOfCoins[it]->alreadyHadIt == false)
                            {
                                listOfCoins[it]->available = true;
                                listOfCoins[it]->deleteIt = false;
                                coinsThisLevel = 0;
                                            listOfCoins[it]->sinValue = 90;
                                            listOfCoins[it]->sinValue2 = 0;
                                            listOfCoins[it]->color.a = 1.0f;
                                            listOfCoins[it]->xCord = listOfCoins[it]->xInit;
                                            listOfCoins[it]->yCord = listOfCoins[it]->yInit;
                            }
                        }
					}

					for(int i = 0; i < listOfMenus.size(); i++)
					{
						if(listOfMenus[i]->indexOfMenu == currentButton->NextMenuIndex)
						{
							currentMenu = listOfMenus[i];
							if(listOfMenus[i]->listOfButtons.size())
							{
							    currentButton = listOfMenus[i]->listOfButtons.front();
							}
							else
                            {
                                currentButton = NULL;
                            }
							break;
						}
					}
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

			//alSourcePlay(SourceSoundBeginningGame);

			objClassObstacle->destroyLevel();
			objClassObstacle->incarcaHarta(nameChar);

			for(int i = 0; i < listOfMenus.size(); i++)
			{
				if(listOfMenus[i]->indexOfMenu == 3)
				{
					currentMenu = listOfMenus[i];

					for(int j = 0; j < currentMenu->listOfButtons.size(); j++)
					{
						if(currentMenu->listOfButtons[j]->indexOfButton == 0)
						{
							currentButton = currentMenu->listOfButtons[j];
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
				for(int i = 0; i < listOfMenus.size(); i++)
				{
					if(listOfMenus[i]->indexOfMenu == 4)
					{
						currentMenu = listOfMenus[i];

						for(int j = 0; j < currentMenu->listOfButtons.size(); j++)
						{
							if(currentMenu->listOfButtons[j]->indexOfButton == 0)
							{
								currentButton = currentMenu->listOfButtons[j];
							}

							break;
						}

						break;
					}
				}

				levelChoserPlayer->xCord = chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter[0]->xCord;
				levelChoserPlayer->yCord = chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->levelFromChapter[0]->yCord;
			}
}

void changeMenuAndButtonsIndexes(int wantedMenuIndex, int wantedButtonIndex)
{
    for(int i = 0; i < listOfMenus.size(); i++)
    {
        if(listOfMenus[i]->indexOfMenu == wantedMenuIndex)
        {
            currentMenu = listOfMenus[i];

            for(int j = 0; j < currentMenu->listOfButtons.size(); j++)
            {
                if(currentMenu->listOfButtons[j]->indexOfButton == wantedButtonIndex)
                {
                    currentButton = currentMenu->listOfButtons[j];
                }
                break;
            }
            break;
        }
    }
}

void BSInputClass::ControlAnyMenuEscape()
{
	///Daca e in joc, trece in Pause Menu
	if(currentMenu->indexOfMenu == 3)
	{
	    changeMenuAndButtonsIndexes(1, 0);
	}
	else
		///Daca e in Levels, trece in Chapters
		if(currentMenu->indexOfMenu == 4)
		{
		    changeMenuAndButtonsIndexes(5, 0);

			levelChoserPlayer->xCord = chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->xCord;
			levelChoserPlayer->yCord = chaptere[levelChoserPlayer->indexOfChapterThatItIsOn]->yCord;

			levelChoserPlayer->indexOfLevelThatItIsOn = 0;
		}
		else
			///Daca e in Chapters, trece in Levels
			if(currentMenu->indexOfMenu == 5)
			{
			    changeMenuAndButtonsIndexes(0, 0);
			}
			else
				///Daca e in Pause Menu, trece in joc
				if(currentMenu->indexOfMenu == 1)
				{
				    changeMenuAndButtonsIndexes(3, 0);
				}
				else
					///Daca e in Settings
					if(currentMenu->indexOfMenu == 2)
					{
                        if(settingsFromFirstOrGame)
                        {
                            changeMenuAndButtonsIndexes(0, 0);
                        }
                        else
                        {
                            changeMenuAndButtonsIndexes(1, 0);
                        }

						newVolumeAudio = currentVolumeAudio;
						newVolumeSFX = currentVolumeSFX;

						//alSourcef(SourceSoundMusic1, AL_GAIN, newVolumeAudio);
						//alSourcef(SourceSoundMusic2, AL_GAIN, newVolumeAudio);
						//alSourcef(SourceSoundMusic3, AL_GAIN, newVolumeAudio);
						//alSourcef(SourceSoundJump, AL_GAIN, newVolumeSFX);
						//alSourcef(SourceSoundDies, AL_GAIN, newVolumeSFX);
						//alSourcef(SourceSoundBeginningGame, AL_GAIN, newVolumeSFX);
						//alSourcef(SourceSoundPowerUp, AL_GAIN, newVolumeSFX);
                        //alSourcef(SourceSoundTeleport, AL_GAIN, newVolumeSFX );
					}
}

void BSInputClass::ControlAnyMenuLeftRightUpDown(int upOrDown)
{
	///Daca nu se afla in meniul de selectat nivele atunci poate face orice
	if(currentMenu->indexOfMenu != 4 && currentMenu->indexOfMenu != 5)
	{
		if(upOrDown == 1)
		{
            currentButton->value1 = 0;
            currentButton->value2 = 0;

			if(currentButton->indexOfButton > 0)
			{
				for(int i = 0; i < currentMenu->listOfButtons.size(); i++)
				{
					if(currentMenu->listOfButtons[i]->indexOfButton == currentButton->indexOfButton - 1)
					{
						currentButton = currentMenu->listOfButtons[i];
						break;
					}
				}
			}
		}
		else
			if(upOrDown == -1)
			{
                currentButton->value1 = 0;
                currentButton->value2 = 0;

				if(currentButton->indexOfButton < currentMenu->numberOfButtons - 1)
				{
					for(int i = 0; i < currentMenu->listOfButtons.size(); i++)
					{
						if(currentMenu->listOfButtons[i]->indexOfButton == currentButton->indexOfButton + 1)
						{
							currentButton = currentMenu->listOfButtons[i];
							break;
						}
					}
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
