/*
 * Blast.cpp
 *
 *  Created on: Jun 26, 2012
 *      Author: Nikhil
 */
#include "blast.h"

void Blast::setup(int playerIndex, int size)
{
	index = playerIndex;
	decay = 1;
	IsEnabled = false;
	startingSize = size * 8;
	str = 0;
}

//--------------------------------------------------------------
void Blast::update()
{
	physics();
}
//--------------------------------------------------------------
void Blast::physics()
{
	pos += vel;

	str = decay;

	decay -= 0.05;

	if(decay < 0)
	{
		IsEnabled = false;
		vel = ofVec2f(0, 0);
		str = 0;
		decay = 0;
	}

	//	radius = 10;
	radius = startingSize * str * 0.2;//(0.6 - str);
}

//--------------------------------------------------------------
void Blast::draw(Camera& cam)
{
	// set outer colour
	ofSetColor(0, 170, 250, 70);
	// only stroke
	ofNoFill();
	// outer circle
	ofSetLineWidth(radius * 0.4);
	ofCircle(cam.offset.x + pos.x, cam.offset.y + pos.y, radius);
	// inner circle
	ofFill();
	ofSetLineWidth(radius * 0.2);
	ofSetColor(0, 200, 200);
	ofCircle(cam.offset.x + pos.x, cam.offset.y + pos.y, radius * 0.7);
	//ofSetColor(0, 255, 0);
	//ofCircle(cam.offset.x + pos.x, cam.offset.y + pos.y, radius);
}
