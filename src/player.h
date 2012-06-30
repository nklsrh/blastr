/*
 * Player.h
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "environment.h"
#include "camera.h"
#include "blast.h"
#include "blastCollection.h"

#include "ofMain.h"

class Player {
	public:
		void setup(int playerIndex, bool bot, float playerSize, float aggro, float max_blastPower);
		void update(Environment& env);
		void draw(Camera& cam, ofImage& img, int size);

		void reset();

		void physics();
		void checkOnArena(Environment& env);
		void tracking(Environment& env);
		void tiles(Environment& env);
		void apprehension(int numberOfPlayers, Player players[], BlastCollection& b);
		void attackTarget(ofVec2f targetPos, BlastCollection& b);
		void prepBlast(ofVec2f input);
		void performBlast(BlastCollection& b, ofVec2f inputDirection);
		void blastCollisions(BlastCollection& b);
		void input(float x, float y);
		void up(float weight);
		void down(float weight);
		void left(float weight);
		void right(float weight);

		int index, chosenTarget, size, currentTile, currentTileType;
		bool IsBot, IsApprehending, IsPreppingBlast, IsOnArena, IsScoring;
		float aggression, maxBlastPower, score, blastStr, zPos;
		ofVec2f pos, startingPos, vel, acc, inpAcc, inpTouch, target, dirToGoal, blastVel;	//inp = input value, in x and y
};

#endif /* PLAYER_H_ */
