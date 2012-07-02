/*
 * rules.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: Nikhil
 */
#include "rules.h"

void Rules::setup(double gameLength)
{
	gameTime = gameLength;
	IsGameRunning = true;
	IsGameOver = false;
}

//--------------------------------------------------------------
void Rules::update(Glados& g, Environment& e)
{
	if(IsGameRunning)
	{
		checkTimer();
		scorePlayers(g);
	}
}
//--------------------------------------------------------------
void Rules::checkTimer()
{
	gameTime -= ofGetLastFrameTime();

	if(gameTime <= 0)
	{
		IsGameRunning = false;
		IsGameOver = true;
	}
}
//--------------------------------------------------------------
void Rules::scorePlayers(Glados& g)
{
	for (int i = 0; i < g.numberOfPlayers; i++)
	{
		if(g.players[i].IsScoring)
		{
			g.players[i].score += 0.2;
		}
	}
}

//--------------------------------------------------------------
void Rules::draw()
{
}
