/*
 * Blast.h
 *
 *  Created on: Jun 26, 2012
 *      Author: Nikhil
 */

#ifndef BLAST_H_
#define BLAST_H_

#include "camera.h"

#include "ofMain.h"

struct Blast {
	public:
		void setup(int playerIndex, int startingSize);
		void update();
		void draw(Camera& cam);

		void physics();

		int index;
		float str, spd, decay, radius, startingSize;
		bool IsEnabled;
		ofVec2f pos, vel, acc;
		ofImage img;
};

#endif /* BLAST_H_ */
