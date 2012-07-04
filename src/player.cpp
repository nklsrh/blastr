/*
 * Player.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "player.h"

void Player::setup(int deviceIndex, int playerIndex, bool bot, float playerSize, float max_blastPower)
{
	device = deviceIndex;
	index = playerIndex;
	IsBot = bot;
	IsApprehending = false;
	chosenTarget = -1;
	size = playerSize;
	maxBlastPower = aggression * 2;
	lineOfSight = aggression * 1.3 * 20;
	blastStr = 0;
	score = 0;
	IsPreppingBlast = false;
	HasControl = false;
}
void Player::reset()
{
	pos = startingPos;
	IsOnArena = true;
	IsScoring = false;
	rotation = 0;
	HasControl = true;
}
//--------------------------------------------------------------
void Player::update(Environment& env)
{
	if(IsOnArena)
	{
		if(index != 0 && HasControl)
		{
			tracking(env);
		}
		tiles(env);
	}
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

	switch(env.tiles[currentTile].type)
	{
		case SAND:
			HasControl = true;
			vel += (env.tiles[currentTile].pos - pos) * 0.04 * aggression;
			IsScoring = false;
			currentTileType = SAND;
		break;
		case GLASS:
			HasControl = false;
			acc *= 1.2;
			IsScoring = false;
			currentTileType = GLASS;
		break;
		case HOLE:
			HasControl = false;
			IsOnArena = false;
			IsScoring = false;
			currentTileType = HOLE;
		break;
		case GOAL:
			HasControl = true;
			IsScoring = true;
			currentTileType = GOAL;
		break;
		case NORMAL:
			HasControl = true;
			currentTileType = NORMAL;
			IsScoring = false;
		break;
	}
}
//--------------------------------------------------------------
void Player::physics()
{
	vel += acc;
	pos += vel;

	acc *= 0.88;

	vel.interpolate(ofVec2f(0, 0), 0.6);

    if (vel.y > 0) //FOR POSITIVE VALUES OF Y, FIRST 2 QUADRANTS OF MOTION, USING ASTC
    {
        rotation = (180/3.14 * atan(vel.x / -vel.y));
    }
    else//FOR NEGATIVE VALUES OF Y, NEXT 2 QUADRANTS OF MOTION
    {
        rotation = (180/3.14 * atan(vel.x / -vel.y)) + 180;
    }

	if(!IsOnArena)
	{
		zPos--;
	}
	else
	{
		zPos = 0;
	}
}
//--------------------------------------------------------------
void Player::checkOnArena(Environment& env)
{
	double marginOfError;
	if(index != 0)
	{
		marginOfError = 0.0;
	}
	else
	{
		marginOfError = 0.1;
	}
    //LEFT
    if(pos.x < env.tiles[0].pos.x - env.tileSize/2 - env.tileSize * marginOfError){
      IsOnArena = false;
    }
    //RIGHT
    if(pos.x > env.tiles[env.numberOfTiles - 1].pos.x + env.tileSize/2 + env.tileSize * marginOfError){
      IsOnArena = false;
    }
    //TOP
    if(pos.y < env.tiles[env.numberOfTiles - 1].pos.y - env.tileSize/2 - env.tileSize * marginOfError){
      IsOnArena = false;
    }
    //BOTTOM
    if(pos.y > env.tiles[0].pos.y + env.tileSize/2 + env.tileSize/2 * marginOfError){
      IsOnArena = false;
    }

    if(!IsOnArena)
    {
    	IsScoring = false;
    }

    if(!IsOnArena && zPos < -100)
    {
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
			if(index == 0 && i == 0 && !IsOnArena)
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
//-------------------------------------------------------------
void Player::handleInput(Environment& env, BlastCollection& b, float x1, float y1, bool IsTouch, float accx, float accy)
{
	// prepping and blasting
	if(IsTouch)
	{
		prepBlast(3 * ofVec2f((x1-(env.windowWidth/2))/(env.windowWidth/2), (y1-(env.windowHeight/2))/(env.windowWidth/2)));
	}
	else
	{
		performBlast(b, 3 * ofVec2f((x1-(env.windowWidth/2))/(env.windowWidth/2), (y1-(env.windowHeight/2))/(env.windowWidth/2)));
	}
	if(HasControl)
	{
		// the accelerometers act differently on each device
		if(device == DEV_ALPHA)
		{
			//movePlayer((-accy * env.windowWidth/2) + env.windowWidth/2, (-accx * env.windowHeight/2) + env.windowHeight/2);
			input(-accy, -accx);
		}
		else if(device == PLAYBOOK)
		{
			//movePlayer((accx * env.windowWidth/2) + env.windowWidth/2, (-accy * env.windowHeight/2) + env.windowHeight/2);
			input(accx, -accy);
		}
	}
}
void Player::movePlayer(float x1, float y1)
{
	//input((x1-(windowWidth/2))/(windowWidth/2), (y1-(windowHeight/2))/(windowWidth/2));
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
				if(pos.distance(players[i].pos) < lineOfSight * size  && players[i].IsOnArena)
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
	if(blastStr < maxBlastPower && IsOnArena)
	{
		blastStr += aggression * 0.03;
	}

	inpTouch = input;

	IsPreppingBlast = true;
}
//--------------------------------------------------------------
void Player::performBlast(BlastCollection& b, ofVec2f inpTouch)
{
	if(!b.blasts[index].IsEnabled && IsPreppingBlast && IsOnArena)
	{
		b.blasts[index].setup(index, size);
		b.blasts[index].IsEnabled = true;
		b.blasts[index].str = blastStr;
		b.blasts[index].spd = 25;
		b.blasts[index].vel = vel + inpTouch * blastStr * b.blasts[index].spd;
		b.blasts[index].pos = pos + b.blasts[index].vel * b.blasts[index].radius * 6;

		acc.x = ofClamp(-b.blasts[index].vel.x * 0.5, -10, 0);
		acc.y = ofClamp(-b.blasts[index].vel.y * 0.5, -10, 0);

		IsPreppingBlast = false;
		blastStr = 0;
	}
}
//--------------------------------------------------------------
void Player::input(float x, float y)
{
	if(IsOnArena)
	{
		inpAcc.x = x;
		inpAcc.y = y;

	//	if(x > 0){
	//		right(0.4 * aggression);
	//	}
	//	if(x < 0){
	//		left(0.4 * aggression);
	//	}
	//	if(y > 0){
	//		down(0.4 * aggression);
	//	}
	//	if(y < 0){
	//		up(0.4 * aggression);
	//	}

		acc += inpAcc * aggression * 0.4;
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

	ofPushMatrix();
	ofTranslate((cam.offset.x + pos.x), (cam.offset.y + pos.y));
	ofRotateZ(rotation);
	img.draw(0, 0, size, size);
	ofPopMatrix();

	ofFill();
	ofCircle((inpAcc.x * 100 + cam.offset.x + pos.x), (inpAcc.y * 100 + cam.offset.y + pos.y), size / 8);
}
