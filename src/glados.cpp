/*
 * GlaDOS.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "glados.h"

void Glados::setup(int deviceIndex, int numberOfRows, int tileSize, float difficulty)
{
	this->device = deviceIndex;

	playerSize = tileSize * 0.5;
	numberOfPlayers = 4;

	for(int i = 0; i < numberOfPlayers; i++)
	{
		bool bot = false;
		if(i != 0)
		{
			bot = true;
			players[i].aggression = difficulty + ofRandom(-0.1, 0.1);
		}
		else
		{
			players[i].aggression = 1;
		}
	}

	players[0].setup(device, 0, false, playerSize, 1, "axon");
	players[1].setup(device, 1, true, playerSize, 1, "aquila");
	players[2].setup(device, 2, true, playerSize, 1, "hydrogen");
	players[3].setup(device, 3, true, playerSize, 1, "arc");

	for(int i = 0; i < numberOfPlayers; i++)
	{
		players[i].startingPos.x = (i % (numberOfPlayers/2)) * (numberOfRows - 1) * tileSize + tileSize/2;
		players[i].startingPos.y = floor(i % numberOfPlayers/2) * (numberOfRows - 1) * tileSize + tileSize/2;

		players[i].reset();
	}

	img_arrows.loadImage(ofToDataPath("", true) + "/app/native/arrows.png");
}

//--------------------------------------------------------------
void Glados::update(Environment& env, BlastCollection& b, Notify& n, float x1, float y1, bool IsTouch, float accx, float accy)
{
	for(int i = 0; i < numberOfPlayers; i++)
	{
		players[i].update(env, n);

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
void Glados::draw(Camera& cam, Environment& env)
{
	ofSetColor(255,255,255);
	ofFill();
	for(int i = 0; i < numberOfPlayers; i++)
	{
		players[i].draw(cam, env, img_player, img_arrows);
	}
}
