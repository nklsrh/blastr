/*
 * control.h
 *
 *  Created on: Jul 2, 2012
 *      Author: Nikhil
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "menuSystem.h"
#include "game.h"

#include "ofMain.h"
#include "ofxQNX.h"
#include "ofxAccelerometer.h"

class Control : public ofxQNXApp {
	public:
		MenuSystem menuSystem;
		Game game;

		int device;

		float x1, y1, x2, y2, sensitivity;
		bool IsTouch;

		void touchDown(ofTouchEventArgs &touch);
		void touchMoved(ofTouchEventArgs &touch);
		void touchUp(ofTouchEventArgs &touch);
		void touchDoubleTap(ofTouchEventArgs &touch);
		void touchCancelled(ofTouchEventArgs &touch);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void setup();
		void update();
		void draw();
};


#endif /* CONTROL_H_ */
