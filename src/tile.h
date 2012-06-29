	/*
 * Tile.h
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */

#ifndef TILE_H_
#define TILE_H_

#include "camera.h"
#include "ofMain.h"

class Tile {
	public:
		void setup(int index, int goal, int size);
		void update();
		void draw(Camera& cam, ofImage& img);
		void randomizeType();
		void Timer();

		ofRectangle rect, collisionRect;
		ofVec2f pos;		//position

		int type, index, intervalTime, intervalLength;
		bool HasPlayer[10];
};

#endif /* TILE_H_ */
