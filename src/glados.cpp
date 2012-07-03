/*
 * GlaDOS.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "glados.h"

void Glados::setup(int deviceIndex, int numberOfRows, int tileSize)
{
	this->device = deviceIndex;

	playerSize = tileSize * 0.3;
	numberOfPlayers = 4;

	for(int i = 0; i < numberOfPlayers; i++)
	{
		bool bot = false;
		if(i != 0)
		{
			bot = true;
			players[i].aggression = ofRandom(0.1, 0.9);
		}
		else
		{
			players[i].aggression = 1;
		}

		players[i].setup(device, i, bot, playerSize, 1);

		players[i].startingPos.x = (i % (numberOfPlayers/2)) * (numberOfRows - 1) * tileSize + tileSize/2;
		players[i].startingPos.y = floor(i % numberOfPlayers/2) * (numberOfRows - 1) * tileSize + tileSize/2;

		players[i].reset();
	}

	img_player.loadImage(ofToDataPath("", true) + "/app/native/hydrogen.png");
	img_player.setAnchorPercent(0.5, 0.5);
}

//--------------------------------------------------------------
void Glados::update(Environment& env, BlastCollection& b, float x1, float y1, bool IsTouch, float accx, float accy)
{
	for(int i = 0; i < numberOfPlayers; i++)
	{
		players[i].update(env);

		if(players[i].IsOnArena)
		{
			if(players[i].IsBot)
			{
				players[i].apprehension(numberOfPlayers, players, b);
			}
			else
			{
				players[i].handleInput(env, b, x1, y1, IsTouch, accx, accy);
			}
			players[i].blastCollisions(b);
		}
	}
}

//--------------------------------------------------------------
void Glados::draw(Camera& cam)
{
	ofSetColor(255,255,255);
	ofFill();
	for(int i = 0; i < numberOfPlayers; i++)
	{
		players[i].draw(cam, img_player, playerSize);
	}
}
