//
//  InputClass.h
//  HelloOpenGL
//
//  Created by Alex Buicescu on 5/25/13.
//
//

#ifndef BSINPUTCLASS
#define BSINPUTCLASS

#include <iostream>
#include "BSValues.h"

class BSInputClass
{
public:

	void getTouch();
	void ControlAnyMenuEnter();
	void ControlAnyMenuEscape();
	void ControlAnyMenuLeftRightUpDown(int upOrDown);
};


#endif /* defined(__HelloOpenGL__InputClass__) */
