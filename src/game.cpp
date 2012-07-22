/*
 * Game.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "game.h"

void Game::setup(int gameplayDevice, float difficulty)
{
	device = gameplayDevice;
	this->difficulty = difficulty;

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
	notify.setup();
	env.setup();
	glados.setup(device, env.numberOfRows, env.tileSize, difficulty);
	blastCol.setup(glados.numberOfPlayers, glados.playerSize);
	cam.setup(env.zoomLevel);

	rules.setup(gameLength, glados, notify);
	hud.setup(env.windowWidth, env.windowHeight);
}
//----------------------------------------------------------------
void Game::endGame(MenuSystem& menu)
{
	if(rules.IsGameOver)
	{
		//restart();
		menu.nextMenu = menu.menu_postmatch;
		menu.activeMenu.horizontalOffset = 1;
		menu.activeMenu.menuTransition = -1;
		for(int i = 0; i < 4; i++)
		{
			menu.teams[i] = rules.teams[i];
			menu.scores[i] = rules.teamScores[i];
			menu.teamIndex[i] = rules.positionsIndex[i];
		}
		menu.IsInGame = false;
		menu.IsStartGame = false;
	}
}
//--------------------------------------------------------------
void Game::update(MenuSystem& menu, float x1, float y1, bool IsTouch, float accx, float accy)
{
	rules.update(glados, env, notify);
	env.update();
	glados.update(env, blastCol, notify, x1, y1, IsTouch, accx, accy);
	blastCol.update();
	hud.update();
	notify.update();

	cam.update(glados.players[0].pos, env.windowWidth, env.windowHeight);

	endGame(menu);
}
//--------------------------------------------------------------
void Game::draw()
{
	env.draw(cam);
	blastCol.draw(cam);
	glados.draw(cam, env);
	hud.draw(rules, env, glados);
	notify.draw(hud.mediumFont, env.windowWidth, env.windowHeight);
}
