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
		void setup(int deviceIndex, int playerIndex, bool bot, float playerSize, float max_blastPower);
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

		void handleInput(Environment& env, BlastCollection& b, float x1, float y1, bool IsTouch, float accx, float accy);
		void movePlayer(float x1, float y1);
		void input(float x, float y);

		void up(float weight);
		void down(float weight);
		void left(float weight);
		void right(float weight);

		int index, chosenTarget, size, currentTile, currentTileType;
		bool IsBot, IsApprehending, IsPreppingBlast, IsOnArena, IsScoring, HasControl;
		float score, blastStr, zPos, rotation;

		int device;
		// ATTRIBUTES
		float lineOfSight, aggression, maxBlastPower;

		ofVec2f pos, startingPos, vel, acc, inpAcc, inpTouch, target, dirToGoal, blastVel;	//inp = input value, in x and y
};

#endif /* PLAYER_H_ */
