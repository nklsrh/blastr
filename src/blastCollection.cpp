/*
 * BlastCollection.cpp
 *
 *  Created on: Jun 26, 2012
 *      Author: Nikhil
 */
#include "blastCollection.h"

void BlastCollection::setup(int playerCount, int playerSize)
{
	numberOfBlasts = playerCount;

	for(int i = 0; i < numberOfBlasts; i++)
	{
		blasts[i].setup(i, playerSize);
	}
}

//--------------------------------------------------------------
void BlastCollection::update()
{
	for(int i = 0; i < numberOfBlasts; i++)
	{
		blasts[i].update();
	}
}

//--------------------------------------------------------------
void BlastCollection::draw(Camera& cam)
{
	for(int i = 0; i < numberOfBlasts; i++)
	{
		blasts[i].draw(cam);
	}
}
