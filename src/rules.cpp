/*
 * rules.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: Nikhil
 */
#include "rules.h"

void Rules::setup(double gameLength)
{
	gameTime = gameLength;
}

//--------------------------------------------------------------
void Rules::update()
{
	gameTime -= ofGetLastFrameTime() * 0.1;
}

//--------------------------------------------------------------
void Rules::draw()
{
}
