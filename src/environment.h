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

class Environment {
	public:
		int tileSize, numberOfRows, numberOfTiles, windowHeight, windowWidth;
		float zoomLevel;

		Tile tiles[50];
		ofImage img_background_env, img_tile_white, img_tile_goal, img_tile_sand;

		int goalTile;

		void setup();
		void update();
		void draw(Camera& cam);
};

#endif /* ENVIRONMENT_H_ */
