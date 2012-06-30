/*
 * rules.h
 *
 *  Created on: Jun 28, 2012
 *      Author: Nikhil
 */

#ifndef RULES_H_
#define RULES_H_

#include "glados.h"
#include "environment.h"

#include "ofMain.h"

class Rules {
	public:
		float gameTime, scoreMultiplier, deathPenalty, marginOfError;

		void scorePlayers(Glados& g);

		void setup(double gameLength);
		void update(Glados& g, Environment& e);
		void draw();
};


#endif /* RULES_H_ */
