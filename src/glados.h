/*
 * GlaDOS.h
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */

#ifndef GLADOS_H_
#define GLADOS_H_

#include "environment.h"
#include "player.h"
#include "blastCollection.h"
#include "camera.h"
#include "notify.h"

#include "ofMain.h"

struct Glados {
	public:
		int numberOfPlayers, playerSize;
		int device;

		Player players[4];

		ofImage img_player, img_arrows;

		void setup(int deviceIndex, int numberOfRows, int tileSize, float difficulty);
		void update(Environment& env, BlastCollection& b, Notify& n, float x1, float y1, bool IsTouch, float accx, float accy);
		void draw(Camera& cam, Environment& env);
};

#endif /* GLADOS_H_ */
