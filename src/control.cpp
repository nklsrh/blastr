/*
 * control.cpp
 *
 *  Created on: Jul 2, 2012
 *      Author: Nikhil
 */

#include "control.h"

void Control::setup()
{
	ofEnableAlphaBlending();
	ofBackground(40,40,40);
	ofSetFrameRate(60);
	// Setup multitouch input listener
	ofRegisterTouchEvents(this);
	sensitivity = 0.2;
	ofxAccelerometer.setup();

	menuSystem.setup(game, DEV_ALPHA);
}

void Control::update()
{
	menuSystem.update(game);
	if(menuSystem.IsInGame)
	{
		game.update(x1, y1, IsTouch, ofxAccelerometer.getForce().x * (sensitivity), ofxAccelerometer.getForce().y * (sensitivity));
	}
}

void Control::draw()
{
	menuSystem.draw();
	if(menuSystem.IsInGame)
	{
		game.draw();
	}
}

//--------------------------------------------------------------
void Control::touchDown(ofTouchEventArgs &touch)
{
	if(touch.id == 0)
	{
		x1 = touch.x;
		y1 = touch.y;
	}

	IsTouch = true;
}

//--------------------------------------------------------------
void Control::touchMoved(ofTouchEventArgs &touch)
{
	if(touch.id == 0)
	{
		x1 = touch.x;
		y1 = touch.y;
	}

	IsTouch = true;
}

//--------------------------------------------------------------
void Control::touchUp(ofTouchEventArgs &touch)
{
	if(touch.id == 0)
	{
		x1 = touch.x;
		y1 = touch.y;
	}

	IsTouch = false;
}

//--------------------------------------------------------------
void Control::touchDoubleTap(ofTouchEventArgs &touch){
	// Not implemented in listener
}

//--------------------------------------------------------------
void Control::touchCancelled(ofTouchEventArgs &touch){
	// Not implemented in listener
}

//--------------------------------------------------------------
void Control::keyPressed  (int key){

}

//--------------------------------------------------------------
void Control::keyReleased  (int key){

}

//--------------------------------------------------------------
void Control::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Control::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void Control::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Control::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Control::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Control::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Control::dragEvent(ofDragInfo dragInfo){

}
