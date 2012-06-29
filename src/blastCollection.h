/*
 * BlastCollection.h
 *
 *  Created on: Jun 26, 2012
 *      Author: Nikhil
 */

#ifndef BLASTCOLLECTION_H_
#define BLASTCOLLECTION_H_

#include "blast.h"

class BlastCollection {
	public:
		int numberOfBlasts;

		Blast blasts[4];

		void setup(int playerCount, int playerSize);
		void update();
		void draw(Camera& cam);
};

#endif /* BLASTCOLLECTION_H_ */
