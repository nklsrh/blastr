/*
 * Player.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "player.h"

void Player::setup(int deviceIndex, int playerIndex, bool bot, float playerSize, float max_blastPower, string playerTeam)
{
	device = deviceIndex;
	index = playerIndex;
	IsBot = bot;
	IsApprehending = false;
	chosenTarget = -1;
	startingSize = playerSize;
	maxBlastPower = 3;
	lineOfSight = playerSize * 2;
	blastStr = 0;
	score = 0;
	IsPreppingBlast = false;
	HasControl = false;

	team = playerTeam;

	img_base.loadImage(ofToDataPath("", true) + "/app/native/" + team + "/base.png");
	img_base.setAnchorPercent(0.5, 0.5);
	img_body.loadImage(ofToDataPath("", true) + "/app/native/" + team + "/body.png");
	img_body.setAnchorPercent(0.5, 0.5);
	img_highlight.loadImage(ofToDataPath("", true) + "/app/native/" + team + "/highlight.png");
}
void Player::reset()
{
	pos = startingPos;
	IsOnArena = true;
	IsScoring = false;
	rotation = 0;
	HasControl = true;
	size = startingSize;
}
//--------------------------------------------------------------
void Player::update(Environment& env, Notify& n)
{
	if(IsOnArena)
	{
//		if(index != 0 && HasControl)
//		{
//			//tracking(env);
//		}
		tiles(env);
	}
	physics();
	checkOnArena(env, n);
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
		size *= 0.9;
	}
	else
	{
		zPos = 0;
		size = startingSize;
	}
}
//--------------------------------------------------------------
void Player::checkOnArena(Environment& env, Notify& n)
{
	double marginOfError;
	if(index != 0)
	{
		marginOfError = 0.0;
	}
	else
	{
		marginOfError = 0.2;
	}
    //LEFT
    if(pos.x < env.tiles[0].pos.x - env.tileSize/2 - env.tileSize * marginOfError){
      fall(n);
    }
    //RIGHT
    if(pos.x > env.tiles[env.numberOfTiles - 1].pos.x + env.tileSize/2 + env.tileSize * marginOfError){
    	fall(n);
    }
    //TOP
    if(pos.y < env.tiles[env.numberOfTiles - 1].pos.y - env.tileSize/2 - env.tileSize * marginOfError){
    	fall(n);
    }
    //BOTTOM
    if(pos.y > env.tiles[0].pos.y + env.tileSize/2 + env.tileSize/2 * marginOfError){
    	fall(n);
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
void Player::fall(Notify& n)
{
	IsOnArena = false;
	if(index == 0)
	{
		n.begin(60, "FALL");
	}
}
//--------------------------------------------------------------
void Player::blastCollisions(BlastCollection& b)
{
	for(int i = 0; i < b.numberOfBlasts; i++)
	{
		if(b.blasts[i].pos.distance(pos) < b.blasts[i].radius)
		{
			if((index != i) && IsOnArena)	// dont get pwnd by ur own blast lmao
			{
				vel -= b.blasts[i].vel * b.blasts[i].str * 2;
			}
		}
		// if blast meets blast, then cancel out depending on strength
		if(b.blasts[i].pos.distance(b.blasts[index].pos) < b.blasts[index].radius * 2)
		{
			float temp = b.blasts[i].str;
			b.blasts[i].str -= b.blasts[index].str;
			b.blasts[i].str -= temp;
		}
	}
}
//-------------------------------------------------------------
void Player::handleInput(Environment& env, BlastCollection& b, float x1, float y1, bool IsTouch, float accx, float accy)
{
	inpTouchRaw = ofVec2f(x1, y1);
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
				if(pos.distance(players[i].pos) < lineOfSight && players[i].IsOnArena)
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
		blastStr += aggression * 0.2;
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
		b.blasts[index].str = blastStr * 0.5;
		b.blasts[index].spd = aggression * 8;
		b.blasts[index].vel = vel + inpTouch.normalized() * blastStr * b.blasts[index].spd;
		b.blasts[index].pos = pos + b.blasts[index].vel;

		vel -= b.blasts[index].vel * 0.15;

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
void Player::draw(Camera& cam, Environment& env, ofImage& img, ofImage& img_arrow)
{
	if(index == 0 && IsOnArena)
	{
		// the blast perpping circle
		ofSetColor(0, 170, 250, 80);
		ofFill();
		ofCircle(cam.offset.x + pos.x, cam.offset.y + pos.y, blastStr * 30);

		if(IsPreppingBlast){
			//on tap, draw this amazing line to the amazing circle
			ofSetLineWidth(20);
			//ofEnableSmoothing();
			ofSetColor(0, 100, 100, 80);
			ofLine(cam.offset.x + pos.x, cam.offset.y + pos.y, inpTouchRaw.x, inpTouchRaw.y);
			//ofDisableSmoothing();
			//on tap, draw this amazing circle of amazing
			ofSetColor(0, 170, 250, 80);
			ofNoFill();
			// outer circle
			ofSetLineWidth(30);
			ofCircle(inpTouchRaw.x, inpTouchRaw.y, blastStr * 30);
			// inner circle
			ofSetLineWidth(10);
			ofSetColor(0, 100, 100, 80);
			ofCircle(inpTouchRaw.x, inpTouchRaw.y, blastStr * 10);
			ofSetLineWidth(0);
		}

		// direction ellipse
		ofFill();
		ofSetColor(10, 10, 10, 50);
		ofCircle((inpAcc.x * 100 + cam.offset.x + pos.x), (inpAcc.y * 100 + cam.offset.y + pos.y), size / 8);

		// goal indicator
		if(pos.distance(env.tiles[env.goalTile].pos) > env.tileSize / 2)
		{
			ofSetColor(0, 240, 0);
			ofCircle((env.tiles[env.goalTile].pos - pos).normalized().x * size/2 + cam.offset.x + pos.x, (env.tiles[env.goalTile].pos - pos).normalized().y * size/2.4 + cam.offset.y + pos.y, size/9);
		}
	}
	ofSetColor(255, 255, 255);
	// images
	ofNoFill();

	// highlight
	img_highlight.draw(cam.offset.x + pos.x - size/2, cam.offset.y + pos.y - size/2, size, size);

	// base and body (and arrow)
	ofPushMatrix();
	ofTranslate((cam.offset.x + pos.x), (cam.offset.y + pos.y));
	ofRotateZ(rotation);
	// DRAWING THE STUPID DIRECTIONAL ARROW
	//ofTranslate(inpAcc.x * 10 - size/2 * 0.2, inpAcc.y * 10 - size/2 * 0.2);
	//img_arrow.draw(0, sqrt(inpAcc.x*inpAcc.x + inpAcc.y*inpAcc.y) * 30, size * 0.2, size * 0.2);
	//ofTranslate(-inpAcc.x * 10 + size/2 * 0.2, -inpAcc.y * 10 + size/2 * 0.2);
	// DRAWING THE BASE AND BODY
	img_base.draw(0, 0, size, size);
	img_body.draw(0, 0, size, size);
	ofPopMatrix();
}
