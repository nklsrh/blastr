/*
 * env.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "environment.h"

void Environment::setup()
{
	goalTile = (numberOfTiles - 1) /2;
//
//	img_tile_white.loadImage(ofToDataPath("", true) + "/app/native/tile_white_128.png");
//	img_tile_goal.loadImage(ofToDataPath("", true) + "/app/native/tile_goal_128.png");
//	img_tile_sand.loadImage(ofToDataPath("", true) + "/app/native/tile_sand_128.png");
//	img_tile_glass.loadImage(ofToDataPath("", true) + "/app/native/tile_glass_128.png");
//	img_tile_spawn.loadImage(ofToDataPath("", true) + "/app/native/tile_spawn_128.png");

	img_tilesheet.loadImage(ofToDataPath("", true) + "/app/native/tiles_sheet.png");

	img_background_env.loadImage(ofToDataPath("", true) + "/app/native/backdrop.png");

	for(int i = 0; i < numberOfTiles; i++)
	{
		tiles[i].pos.x = (((i - (i % numberOfRows))/numberOfRows) * tileSize) + tileSize/2;
		tiles[i].pos.y = ((numberOfRows - (i % numberOfRows)) * tileSize) - tileSize/2;
		tiles[i].setup(i, goalTile, tileSize, numberOfRows, numberOfTiles);
		tiles[i].intervalLength = ofRandom(2000) + 500;
	}

	hillIntervalTime = 0;
}

//--------------------------------------------------------------
void Environment::update()
{
	for(int i = 0; i < numberOfTiles; i++)
	{
		tiles[i].update();
	}
	hillMovementTimer();
}
//--------------------------------------------------------------
void Environment::hillMovementTimer()
{
	if(hillIntervalTime >= hillIntervalLength)
	{
		hillIntervalTime = 0;
		ofSeedRandom();
		nextHillTile = floor(ofRandom(numberOfRows + 1, numberOfTiles - numberOfRows - 1));
		do
		{
			nextHillTile = floor(ofRandom(numberOfRows + 1, numberOfTiles - numberOfRows - 1));
		}
		while(tiles[nextHillTile].type != NORMAL);
		moveHill();
	}
	else
	{
		hillIntervalTime++;
	}
}

void Environment::moveHill()
{
	tiles[goalTile].changeType(NORMAL);
	goalTile = nextHillTile;
	tiles[goalTile].changeType(GOAL);
}
//--------------------------------------------------------------
void Environment::draw(Camera& cam)
{
	img_background_env.draw(tiles[0].rect.x - tiles[0].rect.width * numberOfRows/2, tiles[0].rect.y - tiles[0].rect.height * numberOfRows * 1.4, tiles[0].rect.width * numberOfRows * 2, tiles[0].rect.height * numberOfRows * 2);

	for(int i = 0; i < numberOfTiles; i++)
	{
		if(tiles[i].type != HOLE)
		{
			tiles[i].draw(cam, img_tilesheet);
		}
	}
}
