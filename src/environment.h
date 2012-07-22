/*
 * Environment.h
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "tile.h"
#include "camera.h"
#include "ofMain.h"

#define NORMAL 0
#define GOAL 1
#define SAND 2
#define GLASS 3
#define SPAWN 4
#define HOLE 5

struct Environment {
	public:
		int tileSize, numberOfRows, numberOfTiles, windowHeight, windowWidth, hillIntervalTime, hillIntervalLength, nextHillTile;
		float zoomLevel;

		Tile tiles[50];
		ofImage img_background_env, img_tilesheet;

		int goalTile;

		void setup();
		void update();
		void draw(Camera& cam);

		void hillMovementTimer();
		void moveHill();
};

#endif /* ENVIRONMENT_H_ */
