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
	  randomizeType();
	}

	rect.width = size;
	rect.height = size;

	for(int i = 0; i < 10; i++)
	{
		HasPlayer[index] = false;
	}
}

//--------------------------------------------------------------
void Tile::randomizeType()
{
//	HOW THIS WORKS:
//		Each tile alternates between Powertile and non-Powertile
//	So it cannot go from SAND (for e.g.) to GLASS; it HAS to go back to NORMAL
//		If it is in the NORMAL state, a Powertile is generated
//	BUT THERE IS A 1/3 CHANCE OF IT STAYING NORMAL

	if(type == NORMAL){
		int randomInt = ofRandom(26);

		// BONUS TILES! //
		switch(randomInt){
			case 0:
				type = HOLE;
			break;
			case 1:
				type = SAND;
			break;
			case 2:
				type = SAND;
			break;
			case 3:
				type = GLASS;
			break;
			case 4:
				type = NORMAL;
			break;
		}

		// INCREASE CHANCE OF GETTING A NORMAL TILE (around 1/3)
		if(randomInt > 4){
			type = NORMAL;
		}
	}
	else
	{
		//	IF it was PowerTile, change back to NORMAL state before powering up again
		type = NORMAL;
	}
}

//--------------------------------------------------------------
void Tile::update()
{
	//x += game.x1; // 3* sin(ofGetElapsedTimef() * 0.1);
	//y += game.y1; // 3* sin(ofGetElapsedTimef() * 0.1);
	collisionRect.x = pos.x - rect.width/2;
	collisionRect.y = pos.y - rect.height/2;
	collisionRect.width = rect.width;
	collisionRect.height = rect.height;
}
void Tile::Timer()
{
	intervalTime++;

	if(type != GOAL && type != SPAWN){
		if(intervalTime >= intervalLength){
			randomizeType();
			intervalTime = 0;
		}
		else
		{
			// PLACEHOLDER FOR AWESOME TILECHANGING BLINKING ANIMATION/WHATEVER

//			if(this.IntervalTime >= this.IntervalLength - 30){
//				this.TimerBlink();
//				if(type != NORMAL)
//				this.TheoreticalRotationX = this.IntervalTime;
//			}
//			else
//			{
//				this.Alpha = 1;
//			}
		}
	}
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
//	if(type == GOAL)
//	{
//		ofSetColor(255, 110, 0);	//orange
//	}
//	else
//	{
//		ofSetColor(255, 255, 255);	//white
//	}
	//ofRect(rect.x, rect.y, 0.0f, rect.width, rect.height);	// actual base tile

    //	============= PLAYER TILE CURRENT (override)
//	if(HasPlayer[0])
//	{
//		ofSetColor(170, 0, 200);	// purple
//		//ofRect(rect.x, rect.y, 0.0f, rect.width, rect.height);	// purple overlay tile
//	}

	// ============= EXTRA CRAP
    //ofSetColor(255, 255, 255);
    img.draw(rect.x, rect.y, rect.width, rect.height);
    //ofRect(rect.x * 1.05, rect.y * 1.05, 0.0f, rect.width * 0.9, rect.height * 0.9);
    //ofRect(pos.x  - 0.9*(rect.width/2), pos.y - 0.9*(rect.width/2), 0, rect.width * 0.9, rect.height * 0.9);
}
