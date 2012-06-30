/*
 * HUD.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: Nikhil
 */
#include "hud.h"

void HUD::setup(int windowWidth, int windowHeight)
{
	verdana14.loadFont(ofToDataPath("", true) + "/app/native/verdana.ttf", 28, true, true);
	verdana14.setLineHeight(18.0f * float(windowHeight/600));
	verdana14.setLetterSpacing(1.037 * float(windowWidth/1024));
}

//--------------------------------------------------------------
void HUD::update()
{

}
//--------------------------------------------------------------
void HUD::draw(Rules& r, Environment& e, Glados& g)
{
	ofSetColor(250, 110, 0);
	verdana14.drawString("FPS: " + ofToString(ofGetFrameRate()) + ", Time: " + ofToString(r.gameTime), 30, 35);
	ofSetColor(255, 255, 255);
}
