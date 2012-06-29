/*
 * Player.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "player.h"

void Player::setup(int playerIndex, bool bot, float playerSize, float aggro, float max_blastPower)
{
	index = playerIndex;
	IsBot = bot;
	IsApprehending = false;
	chosenTarget = -1;
	size = playerSize;
	maxBlastPower = aggression * 2;
	blastStr = 0;
	IsPreppingBlast = false;
}
void Player::reset()
{
	pos = startingPos;
	IsOnArena = true;
}
//--------------------------------------------------------------
void Player::update(Environment& env)
{
	if(index != 0)
	{
		tracking(env);
	}
	tiles(env);
	physics();
	checkOnArena(env);
}
//--------------------------------------------------------------
void Player::tiles(Environment& env)
{
	for(int i = 0; i < env.numberOfTiles; i++)
	{
		if(env.tiles[i].collisionRect.inside(pos))
		{
			env.tiles[currentTile].HasPlayer[index] = false;
			currentTile = i;
			env.tiles[i].HasPlayer[index] = true;
		}
	}
}
//--------------------------------------------------------------
void Player::physics()
{
	vel += acc;
	pos += vel;

	acc *= 0.88;

	vel.interpolate(ofVec2f(0, 0), 0.6);

	if(!IsOnArena)
	{
		zPos--;
	}
}
//--------------------------------------------------------------
void Player::checkOnArena(Environment& env)
{
    //LEFT
    if(pos.x < env.tiles[0].pos.x - env.tileSize * 0.85){
      IsOnArena = false;
    }
    //RIGHT
    if(pos.x > env.tiles[env.numberOfTiles - 1].pos.x + env.tileSize * 0.85){
      IsOnArena = false;
    }
    //BOTTOM
    if(pos.y < env.tiles[env.numberOfTiles - 1].pos.y - env.tileSize * 0.85){
      IsOnArena = false;
    }
    //TOP
    if(pos.y > env.tiles[0].pos.y + env.tileSize * 0.85){
      IsOnArena = false;
    }

    if(!IsOnArena && zPos < -20){
      reset();
    }
}
//--------------------------------------------------------------
void Player::blastCollisions(BlastCollection& b)
{
	for(int i = 0; i < b.numberOfBlasts; i++)
	{
		if(b.blasts[i].pos.distance(pos) < b.blasts[i].radius)
		{
			if(index == 0 && i == 0)
			{
				//vel += b.blasts[i].vel * b.blasts[i].str * 2;
			}
			else
			{
				vel += b.blasts[i].vel * b.blasts[i].str * 0.5;
			}
		}
	}
}
//--------------------------------------------------------------
void Player::tracking(Environment& env)
{
	//if(!IsApprehending)
	//{
		target = ofVec2f (env.tiles[env.goalTile].pos.x,  env.tiles[env.goalTile].pos.y) ;
		dirToGoal = ((target - pos + ofVec2f(ofRandom(-10,10), ofRandom(-10,10))) * aggression).getNormalized();

		if(dirToGoal.x > 0){
			right(0.4 * aggression);
		}
		if(dirToGoal.x < 0){
			left(0.4 * aggression);
		}
		if(dirToGoal.y > 0){
			down(0.4 * aggression);
		}
		if(dirToGoal.y < 0){
			up(0.4 * aggression);
		}
	//}
}
//--------------------------------------------------------------
void Player::apprehension(int numberOfPlayers, Player players[], BlastCollection& b)
{
	if(chosenTarget < 0)
	{
		for(int i = 0; i < numberOfPlayers; i++)
		{
			if(i != index)
			{
				if(pos.distance(players[i].pos) < aggression * size * 10)
				{
					chosenTarget = i;
				}
				else
				{
					IsApprehending = false;
				}
			}
		}
	}
	else
	{
		attackTarget(players[chosenTarget].pos, b);
	}
}
//--------------------------------------------------------------
void Player::attackTarget(ofVec2f targetPos, BlastCollection& b)
{
	blastVel = (targetPos - pos + ofVec2f(ofRandom(-2, 2), ofRandom(-2, 2))).normalize();

	prepBlast(blastVel);

	if(blastStr >= maxBlastPower)
	{
		performBlast(b, blastVel);
		chosenTarget = -1;
	}

	IsApprehending = true;
}
//--------------------------------------------------------------
void Player::prepBlast(ofVec2f input)
{
	if(blastStr < maxBlastPower)
	{
		blastStr += aggression * 0.03;
	}

	inpTouch = input;

	IsPreppingBlast = true;
}
//--------------------------------------------------------------
void Player::performBlast(BlastCollection& b, ofVec2f inpTouch)
{
	if(!b.blasts[index].IsEnabled && IsPreppingBlast)
	{
		b.blasts[index].setup(index, size);
		b.blasts[index].IsEnabled = true;
		b.blasts[index].str = blastStr;
		b.blasts[index].spd = 25;
		b.blasts[index].vel = vel + inpTouch * blastStr * b.blasts[index].spd;
		b.blasts[index].pos = pos + b.blasts[index].vel * b.blasts[index].radius * 0.9;
		vel -= b.blasts[index].vel * 0.3;

		IsPreppingBlast = false;
		blastStr = 0;
	}
}
//--------------------------------------------------------------
void Player::input(float x, float y)
{
	inpAcc.x = x;
	inpAcc.y = y;

	if(x > 0){
		right(0.4 * aggression);
	}
	if(x < 0){
		left(0.4 * aggression);
	}
	if(y > 0){
		down(0.4 * aggression);
	}
	if(y < 0){
		up(0.4 * aggression);
	}
}
//--------------------------------------------------------------
void Player::up(float weight)
{
	acc.y -= weight;
}
void Player::down(float weight)
{
	acc.y +=  weight;
}
void Player::left(float weight)
{
	acc.x -= weight;
}
void Player::right(float weight)
{
	acc.x += weight;
}

//--------------------------------------------------------------
void Player::draw(Camera& cam, ofImage& img, int size)
{
	if(index == 0)
	{
		ofSetColor(200, 50, 0);
		ofFill();
		ofCircle(cam.offset.x + pos.x, cam.offset.y + pos.y, blastStr * 50);
	}

	ofSetColor(255, 255, 255);
	ofNoFill();
	img.draw(cam.offset.x + pos.x - size/2, cam.offset.y + pos.y - size/2, size, size);
	//ofCircle(cam.offset.x + pos.x, cam.offset.y +  pos.y, size);
	ofFill();
	ofCircle((inpAcc.x * 100 + cam.offset.x + pos.x), (inpAcc.y * 100 + cam.offset.y + pos.y), size / 8);
}
