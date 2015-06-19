#include "BSAnimationClass.h"

BSTexture* renderAnimationClass = new BSTexture();


void BSAnimationClass::AddAnimationForObject(BSTheSquareBodies *squareBody, BSTheRoundBodies *roundBody,
											BSNewList* &theList,
										std::string name, int nrOfAnimations1, int nrOfAnimations2, int nrOfAnimations3,
										int AnimationTime1, int AnimationTime2, int AnimationTime3,
										int AnimationIndex)
{
//	primul->adresaAnterioara = NULL;
//	primul->adresaAnterioara = NULL;
//	primul->adresaUrmatoare = NULL;
//	primul = NULL;
//	ultimul->adresaAnterioara = NULL;
//	ultimul->adresaUrmatoare = NULL;
//	ultimul = NULL;
//	curent->adresaAnterioara = NULL;
//	curent->adresaUrmatoare = NULL;
//	curent = NULL;

	int totalNr = nrOfAnimations1 + nrOfAnimations2 + nrOfAnimations3;

	for(int i = 0 ; i < totalNr ; i++)
	{
		BSAnimation* newAnime = new BSAnimation;

		newAnime->indexOfAnimation = i;


		///Setez timpul dintre fiecare animatie
		if(i < nrOfAnimations1)
		{
			newAnime->timeUntilNext = AnimationTime1;
		}
		else
			if(i >= nrOfAnimations1 && i < nrOfAnimations1 + nrOfAnimations2)
			{
				newAnime->timeUntilNext = AnimationTime2;
			}
			else
				if(i >= nrOfAnimations1 + nrOfAnimations2 && i < nrOfAnimations1 + nrOfAnimations2 + nrOfAnimations3)
				{
					newAnime->timeUntilNext = AnimationTime3;
				}


		newAnime->animationNR = i;
		newAnime->itPlayedThisAnimation = false;

		if(squareBody)
		{
			newAnime->theSquareBodyBinded = squareBody;
			newAnime->theRoundBodyBinded = NULL;
		}
		else
			if(roundBody)
			{
				newAnime->theRoundBodyBinded = roundBody;
				newAnime->theSquareBodyBinded = NULL;
			}

		///Numele cu care voi incarca textura
		///Numele texturii + nr + extensie
		newAnime->nameOfTheAnimation = name + BStoString(i) + ".png";
		const char *nameOfTexture = newAnime->nameOfTheAnimation.c_str();

		///newAnime->timeUntilNext = 10;
		newAnime->timeToShow = 0;

		newAnime->animationIndex = AnimationIndex;

		///Incarca textura
		renderAnimationClass->loadATexture(nameOfTexture, newAnime->texture);

		newAnime->color = {1.0, 1.0, 1.0, 1.0};

		if(i < nrOfAnimations1)
		{
			theList->listForAnimations1.push_back(newAnime);
		}
		else
			if(i >= nrOfAnimations1 && i < nrOfAnimations1 + nrOfAnimations2)
			{
				theList->listForAnimations2.push_back(newAnime);
			}
			else
				if(i >= nrOfAnimations1 + nrOfAnimations2 && i < nrOfAnimations1 + nrOfAnimations2 + nrOfAnimations3)
				{
					theList->listForAnimations3.push_back(newAnime);
				}
		///Set the current animation as first
		if(!i)
		{
			theList->theCurrentAnimation = newAnime;
		}
		///std::cout<<newAnime->timeUntilNext<<' ';
	}
	///std::cout<<'\n';
	///curent = ultimul;
}


void BSAnimationClass::AddObjectInAnimationList(BSTheSquareBodies *squareBody, BSTheRoundBodies *roundBody,
												int nrOfAnimations1, int nrOfAnimations2, int nrOfAnimations3,
												int AnimationTime1, int AnimationTime2, int AnimationTime3,
                                                std::string nameOfTexture, bool isOnLoopAnimation1, bool isOnLoopAnimation2, bool isOnLoopAnimation3,
                                                int AnimationIndex)
{
	BSNewList *p = new BSNewList;
	//p->current = new BSAnimation;
	//p->primul = new BSAnimation;
	//p->ultimul = new BSAnimation;
	AddAnimationForObject(squareBody, roundBody, p, nameOfTexture,
							nrOfAnimations1, nrOfAnimations2, nrOfAnimations3,
							AnimationTime1, AnimationTime2, AnimationTime3,
							AnimationIndex);


	p->firstNR = nrOfAnimations1;
	p->secondNR = nrOfAnimations2;
	p->thirdNR = nrOfAnimations3;
	p->isOnLoopAnimation1 = isOnLoopAnimation1;
	p->isOnLoopAnimation2 = isOnLoopAnimation2;
	p->isOnLoopAnimation3 = isOnLoopAnimation3;

	p->animationIndex = nrOfListOfAnimations;///AnimationIndex;

	listOfAnimations[nrOfListOfAnimations] = p;///.push_back(p);
	nrOfListOfAnimations++;
}


void BSAnimationClass::updateAnimationCoordinates(BSTheSquareBodies *theSquareBody, BSTheRoundBodies *theRoundBody, BSAnimation *theAnimation)
{
	if(theSquareBody)
	{
		theAnimation->xCord = theSquareBody->theBody->GetPosition().x;
		theAnimation->yCord = theRoundBody->theBody->GetPosition().y;
	}
	else
		if(theRoundBody)
		{
			theAnimation->xCord = theSquareBody->theBody->GetPosition().x;
			theAnimation->yCord = theRoundBody->theBody->GetPosition().y;
		}
}




