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
	glados.setup(device, env.numberOfRows, env.tileSize);
	blastCol.setup(glados.numberOfPlayers, glados.playerSize);
	cam.setup(env.zoomLevel);

	rules.setup(gameLength);
	hud.setup(env.windowWidth, env.windowHeight);
}
//----------------------------------------------------------------
void Game::endGame(MenuSystem& menu)
{
	if(rules.IsGameOver)
	{
		//restart();
		menu.nextMenu = menu.menu_startGame;
		menu.activeMenu.menuOffset = 1;
		menu.activeMenu.menuTransition = -1;
		menu.IsInGame = false;
	}
}
//--------------------------------------------------------------
void Game::update(MenuSystem& menu, float x1, float y1, bool IsTouch, float accx, float accy)
{
	rules.update(glados, env);
	env.update();
	glados.update(env, blastCol, x1, y1, IsTouch, accx, accy);
	blastCol.update();
	hud.update();

	cam.update(glados.players[0].pos, env.windowWidth, env.windowHeight);

	endGame(menu);
}
//--------------------------------------------------------------
void Game::draw()
{
	env.draw(cam);
	blastCol.draw(cam);
	glados.draw(cam);
	hud.draw(rules, env, glados);
}
