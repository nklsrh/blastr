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

		Player players[4];

		ofImage img_player;

		void setup(int numberOfRows, int tileSize);
		void update(Environment& env, BlastCollection& b);
		void draw(Camera& cam);
};

#endif /* GLADOS_H_ */
