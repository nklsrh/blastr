/*
 * HUD.h
 *
 *  Created on: Jun 29, 2012
 *      Author: Nikhil
 */

#ifndef HUD_H_
#define HUD_H_

#include "rules.h"
#include "environment.h"
#include "glados.h"

#include "ofMain.h"

class HUD {
	public:
		void setup(int windowWidth, int windowHeight);
		void update();
		void draw(Rules& r, Environment& e, Glados& g);

		int windowWidth, windowHeight;
		ofTrueTypeFont verdana14;
};

#endif /* HUD_H_ */
