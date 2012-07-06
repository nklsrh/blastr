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

#include "ofMain.h"

class Glados {
	public:
		int numberOfPlayers, playerSize;
		int device;

		Player players[4];

		ofImage img_player, img_arrows;

		void setup(int deviceIndex, int numberOfRows, int tileSize);
		void update(Environment& env, BlastCollection& b, float x1, float y1, bool IsTouch, float accx, float accy);
		void draw(Camera& cam);
};

#endif /* GLADOS_H_ */
