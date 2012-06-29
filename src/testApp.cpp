#include "testApp.h"
//--------------------------------------------------------------

void testApp::setup()
{
	// Setup multitouch input listener
	ofRegisterTouchEvents(this);
	ofEnableAlphaBlending();
	ofBackground(40,40,40);
	ofSetFrameRate(60);

	ofxAccelerometer.setup();

	game.setup();
}

//--------------------------------------------------------------
void testApp::update()
{
	game.update(x1, y1, IsTouch, ofxAccelerometer.getForce().x, ofxAccelerometer.getForce().y);
}

//--------------------------------------------------------------
void testApp::draw()
{
	game.draw();
}


//-----------------------------------------------------------------
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch)
{
	if(touch.id == 0)
	{
		x1 = touch.x;
		y1 = touch.y;
	}

	IsTouch = true;
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch)
{
	if(touch.id == 0)
	{
		x1 = touch.x;
		y1 = touch.y;
	}

	IsTouch = true;
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch)
{
	if(touch.id == 0)
	{
		x1 = touch.x;
		y1 = touch.y;
	}

	IsTouch = false;
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch){
	// Not implemented in listener
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs &touch){
	// Not implemented in listener
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
