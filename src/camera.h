/*
 * Camera.h
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "ofMain.h"

class Camera {
	public:
		void setup(float cameraZoom);
		void update(ofVec2f playerPosition, int windowWidth, int windowHeight);
		void draw();

		float zoom;
		ofVec2f offset, pos;
};

#endif /* CAMERA_H_ */
