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

#include "ofMain.h"

#define PLAYBOOK 0
#define DEV_ALPHA 1

class Game {
	public:
		Rules rules;
		Environment env;
		Glados glados;
		Camera cam;
		BlastCollection blastCol;
		HUD hud;

		int windowHeight, windowWidth;
		int device;

		void setup();
		void update(float x1, float y1, bool IsTouch, float accx, float accy);
		void movePlayer(float x1, float y1);
		void draw();
};

#endif /* GAME_H_ */
