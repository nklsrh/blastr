/*
 * Tile.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "tile.h"
#include "environment.h"

void Tile::setup(int index, int goalTile, int size)
{
	if(index == goalTile)
	{
	  type = GOAL;
	}
	else
	{
	  type = NORMAL;
	}

	rect.width = size;
	rect.height = size;

	for(int i = 0; i < 10; i++)
	{
		HasPlayer[index] = false;
	}
}

//--------------------------------------------------------------
void Tile::update()
{
	//x += game.x1; // 3* sin(ofGetElapsedTimef() * 0.1);
	//y += game.y1; //3* sin(ofGetElapsedTimef() * 0.1);
	collisionRect.x = pos.x - rect.width/2;
	collisionRect.y = pos.y - rect.height/2;
	collisionRect.width = rect.width;
	collisionRect.height = rect.height;
}

//--------------------------------------------------------------
void Tile::draw(Camera& cam, ofImage& img)
{
    rect.x = cam.offset.x + (pos.x - rect.width/2);
    rect.y = cam.offset.y + (pos.y - rect.height/2);

	// ============== BORDERS AND HIGHLIGHTS
//	ofSetColor(40, 40, 40);	// dark grey
//  ofRect(rect.x, rect.y + rect.height * 0.98, rect.width, rect.height * 0.02);	// bottom line
//  ofSetColor(255, 255, 255);	// white
//  ofRect(rect.x + rect.width * 0.98, rect.y, rect.width * 0.02, rect.height);	// right line

    // ============== TILE TYPES
	if(type == GOAL)
	{
		ofSetColor(255, 110, 0);	//orange
	}
	else
	{
		ofSetColor(255, 255, 255);	//white
	}
	//ofRect(rect.x, rect.y, 0.0f, rect.width, rect.height);	// actual base tile

    //	============= PLAYER TILE CURRENT (override)
	if(HasPlayer[0])
	{
		ofSetColor(170, 0, 200);	// purple
		//ofRect(rect.x, rect.y, 0.0f, rect.width, rect.height);	// purple overlay tile
	}

	// ============= EXTRA CRAP
    //ofSetColor(255, 255, 255);
    img.draw(rect.x, rect.y, rect.width, rect.height);
    //ofRect(rect.x * 1.05, rect.y * 1.05, 0.0f, rect.width * 0.9, rect.height * 0.9);
    //ofRect(pos.x  - 0.9*(rect.width/2), pos.y - 0.9*(rect.width/2), 0, rect.width * 0.9, rect.height * 0.9);
}
