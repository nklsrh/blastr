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
#include "notify.h"

#include "ofMain.h"

struct Rules {
	public:
		float gameTime, scoreMultiplier, deathPenalty, marginOfError;
		bool IsGameRunning, IsGameOver;

		void scorePlayers(Glados& g);
		void checkTimer(Glados& g);
		void checkWinner(Glados& g, Notify& n);

		void setup(double gameLength, Glados& g, Notify& n);
		void update(Glados& g, Environment& e, Notify& n);
		void draw();

		string teams[4];
		int positionsIndex[4], teamScores[4];

		int playerPositionBefore, state;
};


#endif /* RULES_H_ */
