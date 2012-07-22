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

	smallFont.loadFont(ofToDataPath("", true) + "/app/native/akashi.ttf", 48 * float(windowHeight/600), true, true);
	smallFont.setLineHeight(18.0f * float(windowHeight/600));
	smallFont.setLetterSpacing(1.037 * float(windowWidth/1024));

	mediumFont.loadFont(ofToDataPath("", true) + "/app/native/akashi.ttf", 72 * float(windowHeight/600), true, true);
	mediumFont.setLineHeight(18.0f * float(windowHeight/600));
	mediumFont.setLetterSpacing(1.037 * float(windowWidth/1024));

	largeFont.loadFont(ofToDataPath("", true) + "/app/native/akashi.ttf", 128 * float(windowHeight/600), true, true);
	largeFont.setLineHeight(18.0f * float(windowHeight/600));
	largeFont.setLetterSpacing(1.037 * float(windowWidth/1024));

	axon.loadImage(ofToDataPath("", true) + "/app/native/HUDaxon.png");
	arc.loadImage(ofToDataPath("", true) + "/app/native/HUDarc.png");
	aquila.loadImage(ofToDataPath("", true) + "/app/native/HUDaquila.png");
	hydrogen.loadImage(ofToDataPath("", true) + "/app/native/HUDhydrogen.png");
}

//--------------------------------------------------------------
void HUD::update()
{

}
//--------------------------------------------------------------
void HUD::draw(Rules& r, Environment& e, Glados& g)
{
	ofSetColor(255, 255, 255);
	axon.draw(0, 0, e.windowWidth * 0.3, e.windowHeight * 0.15);
	aquila.draw(e.windowWidth * 0.7, 0, e.windowWidth * 0.3, e.windowHeight * 0.15);
	hydrogen.draw(0, e.windowHeight * 0.85, e.windowWidth * 0.3, e.windowHeight * 0.15);
	arc.draw(e.windowWidth * 0.7, e.windowHeight * 0.85, e.windowWidth * 0.3, e.windowHeight * 0.15);

	//verdana14.drawString("FPS: " + ofToString(ofGetFrameRate()) + ", Time: " + ofToString(r.gameTime), 30, 35);
	ofSetColor(255, 50, 0);
	if(g.players[0].IsScoring)
	{
		largeFont.drawString(ofToString(floor(g.players[0].score)), e.windowWidth * 0.2, e.windowHeight * 0.13);
		ofSetColor(190,0,0);
		largeFont.drawString(ofToString(floor(g.players[0].score)), e.windowWidth * 0.2, e.windowHeight * 0.135);
	}
	else
	{
		smallFont.drawString(ofToString(floor(g.players[0].score)), e.windowWidth * 0.2, e.windowHeight * 0.115);
		ofSetColor(180,20,0);
		smallFont.drawString(ofToString(floor(g.players[0].score)), e.windowWidth * 0.2, e.windowHeight * 0.12);
	}

	ofSetColor(255, 255, 255);
	smallFont.drawString(ofToString(floor(g.players[1].score)), e.windowWidth * 0.9, e.windowHeight * 0.11);
	smallFont.drawString(ofToString(floor(g.players[2].score)), e.windowWidth * 0.2, e.windowHeight * 0.96);
	smallFont.drawString(ofToString(floor(g.players[3].score)), e.windowWidth * 0.9, e.windowHeight * 0.96);

	ofSetColor(150, 150, 150);
	smallFont.drawString(ofToString(floor(g.players[1].score)), e.windowWidth * 0.9, e.windowHeight * 0.115);
	smallFont.drawString(ofToString(floor(g.players[2].score)), e.windowWidth * 0.2, e.windowHeight * 0.965);
	smallFont.drawString(ofToString(floor(g.players[3].score)), e.windowWidth * 0.9, e.windowHeight * 0.965);

	if(r.gameTime > 5)
	{
		ofSetColor(0,0,0);
		mediumFont.drawString(ofToString(floor(r.gameTime)), e.windowWidth * 0.45, e.windowHeight * 0.106);
		ofSetColor(255,255,255);
		mediumFont.drawString(ofToString(floor(r.gameTime)), e.windowWidth * 0.45, e.windowHeight * 0.1);
	}
	else
	{
		ofSetColor(255,0,0);
		largeFont.drawString(ofToString(floor(r.gameTime)), e.windowWidth * 0.45, e.windowHeight * 0.206);
		ofSetColor(200,0,0);
		largeFont.drawString(ofToString(floor(r.gameTime)), e.windowWidth * 0.45, e.windowHeight * 0.2);
	}
	ofSetColor(255,255,255);
}
