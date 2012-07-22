/*
 * Tile.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "tile.h"
#include "environment.h"

void Tile::setup(int index, int goalTile, int size, int numberOfRows, int numberOfTiles)
{
	this->numberOfRows = numberOfRows;
	this->numberOfTiles = numberOfTiles;
	this->index = index;

	if(index == goalTile)
	{
		changeType(GOAL);
	}
	else if (index == numberOfRows - 1 || index == (numberOfRows - 1) * numberOfRows || index == numberOfTiles - 1 || index == 0)
	{
		changeType(SPAWN);
	}
	else
	{
		changeType(NORMAL);
		randomizeType();
	}

	rect.width = size;
	rect.height = size;

	anim_frame = 0;

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

	// NEW: tiles near spawn zones never change
	// if x is 0,1 or 5,6 && if y is 0,1 or 5,6

	if((index % numberOfRows > 1 || index % numberOfRows < 5) && (int(index / 10) % numberOfRows > 1 || int(index / 10) % numberOfRows < 5))
	{
		if(type == NORMAL){
			int randomInt = ofRandom(26);

			// BONUS TILES! //
			switch(randomInt){
				case 0:
					changeType(HOLE);
				break;
				case 1:
					changeType(SAND);
				break;
				case 2:
					changeType(SAND);
				break;
				case 3:
					changeType(GLASS);
				break;
				case 4:
					changeType(NORMAL);
				break;
			}

			// INCREASE CHANCE OF GETTING A NORMAL TILE (around 1/3)
			if(randomInt > 4){
				changeType(NORMAL);
			}
		}
		else
		{
			//	IF it was PowerTile, change back to NORMAL state before powering up again
			changeType(NORMAL);
		}
	}
}
void Tile::changeType(int typeTo)
{
	this->type = typeTo;
	setAnimLength(typeTo);
}
void Tile::setAnimLength(int typeTo)
{
	switch(typeTo)
	{
		case NORMAL:
			anim_length = 1;
			break;
		case GOAL:
			anim_length = 7;
			break;
		case SAND:
			anim_length = 6;
			break;
		case GLASS:
			anim_length = 8;
			break;
		case SPAWN:
			anim_length = 12;
			break;
		case HOLE:
			anim_length = 0;
			break;
	}
	anim_frame = 0;
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

	Timer();
}

void Tile::Timer()
{
	intervalTime++;

	if(type != GOAL && type != SPAWN)
	{
		if(intervalTime >= intervalLength)
		{
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

	animation();
}

void Tile::animation()
{
	anim_frame++;

	if(anim_frame >= anim_length)
	{
		anim_frame = 0;
	}
}
//--------------------------------------------------------------
void Tile::draw(Camera& cam, ofImage& img)
{
    rect.x = cam.offset.x + (pos.x - rect.width/2);
    rect.y = cam.offset.y + (pos.y - rect.height/2);

    //due to player confusion, spawn tiles are scrapped for now
    if(type != SPAWN)
    {
    	img.drawSubsection(rect.x, rect.y, 0, rect.width, rect.height, (type * 128), anim_frame * 128, 128, 128);
    }
    else
    {
    	img.drawSubsection(rect.x, rect.y, 0, rect.width, rect.height, (NORMAL * 128), 0, 128, 128); // NORMAL TILE
    }
}


//		old way of drawing tiles


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

//img.draw(rect.x, rect.y, rect.width, rect.height);
//ofRect(rect.x * 1.05, rect.y * 1.05, 0.0f, rect.width * 0.9, rect.height * 0.9);
//ofRect(pos.x  - 0.9*(rect.width/2), pos.y - 0.9*(rect.width/2), 0, rect.width * 0.9, rect.height * 0.9);
