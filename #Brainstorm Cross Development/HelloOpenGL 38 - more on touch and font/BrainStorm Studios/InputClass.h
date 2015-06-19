//
//  InputClass.h
//  HelloOpenGL
//
//  Created by Alex Buicescu on 5/25/13.
//
//

#ifndef __HelloOpenGL__InputClass__
#define __HelloOpenGL__InputClass__

#include <iostream>
#include "BSValues.h"

class InputClass
{
public:
	
	void getTouch();
	void ControlAnyMenuEnter();
	void ControlAnyMenuEscape();
	void ControlAnyMenuLeftRightUpDown(int upOrDown);
};


#endif /* defined(__HelloOpenGL__InputClass__) */
