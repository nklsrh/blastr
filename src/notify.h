/*
 * notify.h
 *
 *  Created on: Jul 9, 2012
 *      Author: Nikhil
 */

#ifndef NOTIFY_H_
#define NOTIFY_H_

#include "ofMain.h"

struct Notify {
	public:

	string announcementText;

	int time, timeLength;
	float alpha;

	void setup();
	void update();
	void begin(int timeLength, string text);
	void timer();
	void showOrHide();
	void draw(ofTrueTypeFont& font, int windowWidth, int windowHeight);
};


#endif /* NOTIFY_H_ */
