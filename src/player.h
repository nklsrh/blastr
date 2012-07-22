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
#include "notify.h"

#include "ofMain.h"

struct Player {
	public:
		void setup(int deviceIndex, int playerIndex, bool bot, float playerSize, float max_blastPower, string playerTeam);
		void update(Environment& env, Notify& n);
		void draw(Camera& cam, Environment& env, ofImage& img, ofImage& img_arrow);

		void reset();

		void physics();
		void checkOnArena(Environment& env, Notify& n);
		void tracking(Environment& env);
		void tiles(Environment& env);
		void fall(Notify& n);
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

		int index, chosenTarget, startingSize, currentTile, currentTileType;
		bool IsBot, IsApprehending, IsPreppingBlast, IsOnArena, IsScoring, HasControl;
		float score, blastStr, zPos, rotation, size;

		//TEAMS
		string team;

		//PLAYER LAYERS
		ofImage img_base, img_body, img_highlight;

		int device;
		// ATTRIBUTES
		float lineOfSight, aggression, maxBlastPower;

		ofVec2f pos, startingPos, vel, acc, inpAcc, inpTouch, inpTouchRaw, target, dirToGoal, blastVel;	//inp = input value, in x and y
};

#endif /* PLAYER_H_ */
