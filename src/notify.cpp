/*
* notify.cpp
*
*  Created on: Jul 9, 2012
*      Author: Nikhil
*/
#include "notify.h"

void Notify::setup()
{
	announcementText = "";

	time = 0;
	timeLength = 30;
	alpha = 0;
}

void Notify::update()
{
	 timer();
	 showOrHide();
}

void Notify::begin(int timeLength, string text)
{
	if(time == 0)
	{
		time = timeLength;

		this->timeLength = time;
		announcementText = text;

		showOrHide();
	}
}

void Notify::timer()
{
	if(time > 0){
		 time--;
	}
}

void Notify::showOrHide()
{
	 alpha = time / float(timeLength);
}

void Notify::draw(ofTrueTypeFont& font, int windowWidth, int windowHeight)
{
	if(alpha > 0)
	{
		ofSetColor(0, 0, 0, 200);
		//(1-alpha) means downwards, alpha means upwards (since alpha decreases)
		// we're specifying the top left point, so we multiply alpha by 0.3 so you can see the text when alpha is 1
		font.drawString( announcementText,  windowWidth * (0.4-alpha*0.3),  windowHeight * 0.4);
		ofSetColor(250, 0, 51, ofClamp(alpha, 0.4, 1) * 255);
		font.drawString( announcementText,  windowWidth * (0.4-alpha*0.3),  windowHeight * 0.4 + 10);
		ofSetColor(255,255,255,255);
	}
}

