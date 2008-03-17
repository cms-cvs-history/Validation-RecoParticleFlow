/*
 *  myMath.c
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 03.03.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "myMath.h"

float myMath::myFabs(float value)
{
	if(value<=0.0)
		return value*(-1);
	else
		return value;
}

