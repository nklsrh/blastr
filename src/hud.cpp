/*
 * HUD.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: Nikhil
 */
#include "hud.h"

void HUD::setup(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

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
//	if(e.tiles[e.goalTile].rect.x > windowWidth || e.tiles[e.goalTile].rect.x < -e.tiles[e.goalTile].rect.width || e.tiles[e.goalTile].rect.y > windowHeight || e.tiles[e.goalTile].rect.y < -e.tiles[e.goalTile].rect.height)
//	{
//		// direction ellipse
//		ofFill();
//		ofCircle();
//	}
	ofSetColor(250, 110, 0);
	verdana14.drawString("FPS: " + ofToString(ofGetFrameRate()) + ", Time: " + ofToString(r.gameTime), 30, 35);
	verdana14.drawString("Player: 1, Score: " + ofToString(floor(g.players[0].score)), 30, 85);
	verdana14.drawString("Player: 2, Score: " + ofToString(floor(g.players[1].score)), 30, 135);
	verdana14.drawString("Player: 3, Score: " + ofToString(floor(g.players[2].score)), 30, 185);
	verdana14.drawString("Player: 4, Score: " + ofToString(floor(g.players[3].score)), 30, 235);
	ofSetColor(255, 255, 255);
}
