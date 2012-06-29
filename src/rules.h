/*
 * rules.h
 *
 *  Created on: Jun 28, 2012
 *      Author: Nikhil
 */

#ifndef RULES_H_
#define RULES_H_

#include "ofMain.h"

class Rules {
	public:
		float gameTime;

		void setup(double gameLength);
		void update();
		void draw();
};


#endif /* RULES_H_ */
