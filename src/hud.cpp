/*
 * HUD.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: Nikhil
 */
#include "hud.h"

void HUD::setup()
{
	verdana14.loadFont(ofToDataPath("", true) + "/app/native/verdana.ttf", 28, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);
}

//--------------------------------------------------------------
void HUD::update()
{

}
//--------------------------------------------------------------
void HUD::draw(Rules& r, Environment& e, Glados& g)
{
	ofSetColor(250, 110, 0);
	verdana14.drawString(ofToString(ofGetFrameRate()), 30, 35);
	ofSetColor(255, 255, 255);
}
