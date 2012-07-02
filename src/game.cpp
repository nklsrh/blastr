/*
 * Game.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "game.h"

void Game::setup(int gameplayDevice)
{
	device = gameplayDevice;

	if(device == DEV_ALPHA)
	{
		env.windowHeight = 768;
		env.windowWidth = 1280;
		env.zoomLevel = 0.5;	//smaller is closer
	}
	else if(device == PLAYBOOK)
	{
		env.windowHeight = 600;
		env.windowWidth = 1024;
		env.zoomLevel = 0.6;	//smaller is closer
	}

	gameLength = 60;

	env.numberOfRows = 7;
	env.numberOfTiles = (env.numberOfRows * env.numberOfRows);
	env.tileSize = env.windowHeight / env.numberOfRows / env.zoomLevel;
	env.hillIntervalLength = gameLength * 10;

	restart();
}
//--------------------------------------------------------------------
void Game::restart()
{
	env.setup();
	glados.setup(env.numberOfRows, env.tileSize);
	blastCol.setup(glados.numberOfPlayers, glados.playerSize);
	cam.setup(env.zoomLevel);

	rules.setup(gameLength);
	hud.setup(env.windowWidth, env.windowHeight);
}
//----------------------------------------------------------------
void Game::endGame()
{
	if(rules.IsGameOver)
	{
		restart();
	}
}
//--------------------------------------------------------------
void Game::update(float x1, float y1, bool IsTouch, float accx, float accy)
{
	rules.update(glados, env);
	env.update();
	glados.update(env, blastCol);
	blastCol.update();
	hud.update();

	playerBlast(x1, y1, IsTouch);
	// the accelerometers act differently on each device
	if(device == DEV_ALPHA)
	{
		movePlayer((-accy * env.windowWidth/2) + env.windowWidth/2, (-accx * env.windowHeight/2) + env.windowHeight/2);
	}
	else if(device == PLAYBOOK)
	{
		movePlayer((accx * env.windowWidth/2) + env.windowWidth/2, (-accy * env.windowHeight/2) + env.windowHeight/2);
	}

	cam.update(glados.players[0].pos, env.windowWidth, env.windowHeight);

	endGame();
}

void Game::movePlayer(float x1, float y1)
{
	if(!glados.players[0].IsBot)
	{
		glados.players[0].input((x1-(env.windowWidth/2))/(env.windowWidth/2), (y1-(env.windowHeight/2))/(env.windowWidth/2));
	}
}

void Game::playerBlast(float x1, float y1, bool IsTouch)
{
	if(IsTouch)
	{
		glados.players[0].prepBlast(3 * ofVec2f((x1-(env.windowWidth/2))/(env.windowWidth/2), (y1-(env.windowHeight/2))/(env.windowWidth/2)));
	}
	else
	{
		glados.players[0].performBlast(blastCol, 3 * ofVec2f((x1-(env.windowWidth/2))/(env.windowWidth/2), (y1-(env.windowHeight/2))/(env.windowWidth/2)));
	}
}
//--------------------------------------------------------------
void Game::draw()
{
	env.draw(cam);
	blastCol.draw(cam);
	glados.draw(cam);
	hud.draw(rules, env, glados);
}
