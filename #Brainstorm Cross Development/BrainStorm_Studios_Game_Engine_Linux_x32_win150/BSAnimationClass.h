#ifndef BSANIMATIONCLASS_H_INCLUDED
#define BSANIMATIONCLASS_H_INCLUDED

#include "BSValues.h"
#include "BSTexture.h"

class BSAnimationClass
{
public:

	void AddAnimationForObject(BSTheSquareBodies *squareBody, BSTheRoundBodies *roundBody,
								BSNewList* &theList,
								std::string name, int nrOfAnimations1, int nrOfAnimations2, int nrOfAnimations3,
								int AnimationTime1, int AnimationTime2, int AnimationTime3,
								int AnimationIndex);

	///Pun corpul pe care vreau sa il randez, si pe celalalt il pun null, eg: hero, null, 13, "player"
	void AddObjectInAnimationList(BSTheSquareBodies *squareBody, BSTheRoundBodies *roundBody,
									int nrOfAnimations1, int nrOfAnimations2, int nrOfAnimations3,
									int AnimationTime1, int AnimationTime2, int AnimationTime3,
                                    std::string nameOfTexture, bool isOnLoopAnimation1, bool isOnLoopAnimation2, bool isOnLoopAnimation3,
                                    int AnimationIndex);


	void updateAnimationCoordinates(BSTheSquareBodies *theSquareBody, BSTheRoundBodies *theRoundBody, BSAnimation *theAnimation);


};


#endif // BSANIMATIONCLASS_H_INCLUDED
