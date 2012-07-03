/*
 * Game.h
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */

#ifndef GAME_H_
#define GAME_H_

#include "glados.h"
#include "environment.h"
#include "camera.h"
#include "blastCollection.h"
#include "rules.h"
#include "hud.h"
#include "menuSystem.h"

#include "ofMain.h"

class Game {
	public:
		Rules rules;
		Environment env;
		Glados glados;
		Camera cam;
		BlastCollection blastCol;
		HUD hud;
		MenuSystem menu;

		int windowHeight, windowWidth;
		int device;
		int gameLength;

		void restart();

		void setup(int gameplayDevice);
		void update(MenuSystem& menu, float x1, float y1, bool IsTouch, float accx, float accy);
		void movePlayer(float x1, float y1);
		void playerBlast(float x1, float y1, bool IsTouch);
		void endGame(MenuSystem& menu);

		void draw();
};

#endif /* GAME_H_ */
