/*
 * GlaDOS.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "glados.h"

void Glados::setup(int numberOfRows, int tileSize)
{
	playerSize = tileSize * 0.3;
	numberOfPlayers = 4;

	for(int i = 0; i < numberOfPlayers; i++)
	{
		bool bot = false;
		if(i != 0)
		{
			bot = true;
			players[i].aggression = 0.15;
		}
		else
		{
			players[i].aggression = 1;
		}

		players[i].setup(i, bot, playerSize, 0.6, 1);

		players[i].startingPos.x = (i % (numberOfPlayers/2)) * (numberOfRows - 1) * tileSize + tileSize/2;
		players[i].startingPos.y = floor(i % numberOfPlayers/2) * (numberOfRows - 1) * tileSize + tileSize/2;

		players[i].reset();
	}

	img_player.loadImage(ofToDataPath("", true) + "/app/native/hydrogen.png");
}

//--------------------------------------------------------------
void Glados::update(Environment& env, BlastCollection& b)
{
	for(int i = 0; i < numberOfPlayers; i++)
	{
		players[i].update(env);
		players[i].blastCollisions(b);

		if(players[i].IsBot)
		{
			players[i].apprehension(numberOfPlayers, players, b);
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
