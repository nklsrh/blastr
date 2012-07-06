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
		void setup(int index, int goalTile, int size, int numberOfRows, int numberOfTiles);
		void update();
		void draw(Camera& cam, ofImage& img);
		void randomizeType();
		void Timer();

		void changeType(int typeTo);
		void setAnimLength(int typeTo);

		void animation();

		ofRectangle rect, collisionRect;
		ofVec2f pos;		//position

		// animation spritesheet ints
		int anim_frame, anim_length;

		int type, index, intervalTime, intervalLength;
		int numberOfTiles, numberOfRows;
		bool HasPlayer[10];
};

#endif /* TILE_H_ */
