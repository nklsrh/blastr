#ifndef TESTAPP_H_
#define TESTAPP_H_

#include "control.h"

#include "ofMain.h"
#include "ofxQNX.h"
#include "ofxAccelerometer.h"

class testApp : public ofxQNXApp
{
	public:
		float x1, y1, x2, y2, sensitivity;
		bool IsTouch;

		Control control;
		//Game game;

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

#endif /* TESTAPP_H_ */
