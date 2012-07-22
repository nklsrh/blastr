/*
 * rules.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: Nikhil
 */
#include "rules.h"

void Rules::setup(double gameLength, Glados& g, Notify& n)
{
	gameTime = gameLength;
	IsGameRunning = true;
	IsGameOver = false;

	state = 0;
	n.begin(300, "KING OF THE HILL");
	for(int i = 0; i < 4; i ++)
	{
		this->teamScores[i] = g.players[i].score;
		this->positionsIndex[i] = g.players[i].index;
	}
}

//--------------------------------------------------------------
void Rules::update(Glados& g, Environment& e, Notify& n)
{
	if(IsGameRunning)
	{
		checkTimer(g);
		scorePlayers(g);
		checkWinner(g, n);
	}
}
//--------------------------------------------------------------
void Rules::checkTimer(Glados& g)
{
	gameTime -= ofGetLastFrameTime();
	if(gameTime <= 0)
	{
		IsGameRunning = false;
		IsGameOver = true;
	}
}
void Rules::checkWinner(Glados& g, Notify& n)
{
	//	BUBLE SORTS!
	for(int i = 0; i < 4; i ++)
	{
		if(this->positionsIndex[i] == 0)
		{
			playerPositionBefore = i;
		}
	}
	for(int i = 0; i < 4; i ++)
	{
		this->teamScores[i] = g.players[i].score;
		this->positionsIndex[i] = g.players[i].index;
	}
	bool swap = false;
	do
	{
		swap = false;
		for(int i = 1; i < 4; i++)
		{
			if(teamScores[i - 1] > teamScores[i])
			{
				int temp = this->positionsIndex[i - 1];
				this->positionsIndex[i - 1] = this->positionsIndex[i];
				this->positionsIndex[i] = temp;

				temp = this->teamScores[i - 1];
				this->teamScores[i - 1] = this->teamScores[i];
				this->teamScores[i] = temp;
				swap = true;
			}
		}
	}
	while(swap);

	for(int i = 0; i < 4; i ++)
	{
		teams[i] = g.players[this->positionsIndex[i]].team;
	}

	// lower index is worse, 3 is top

	// for states, -1 means not in lead, -2 means leading, -3 means dominating (+100 pts)
	if(playerPositionBefore == g.numberOfPlayers - 1 && positionsIndex[g.numberOfPlayers-1] != 0)
	{
		if(state != -1)
		{
			n.begin(120, "LOST THE LEAD");
			state = -1;
		}
	}
	if(playerPositionBefore != g.numberOfPlayers - 1 && positionsIndex[g.numberOfPlayers-1] == 0)
	{
		if(state != -2 && state != -3)
		{
			n.begin(200, "LEADING THE MATCH");
			state = -2;
		}
	}
	if(state == -2)
	{
		if(g.players[0].score - this->teamScores[2] > 100)
		{
			n.begin(300, "!!! DOMINATION !!!");
			state = -3;
		}
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
