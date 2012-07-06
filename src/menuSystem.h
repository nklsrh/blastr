/*
 * menu_main.h
 *
 *  Created on: Jul 2, 2012
 *      Author: Nikhil
 *      BASED ON THE MENU SYSTEM BY LOUIE SONG
 */

#ifndef MENUMAIN_H_
#define MENUMAIN_H_

#include "ofMain.h"

enum ButtonType
{
	buttonTypeNORMAL,
	buttonTypePLUSMINUS
};

enum MenuName
{
	menu_MAIN,
	menu_STARTGAME,
	menu_MYBOT,
	menu_CAREER,
	menu_OPTIONS,
	menu_UPGRADE,
	menu_STORE,
	menu_QUICKTEAMSELECT,
	menu_QUICKBOTSETUP,
	menu_QUICKCALIBRATION,
	menu_POSTMATCH,
	menu_INGAME
};

struct Button
{
	ofImage img;
	ofRectangle rect;
	ofRectangle rectOriginal;
	bool IsShown;
	bool isDown;
	int type;

	void draw(int menuOffset, int horizontalOffset);
};

struct Menu
{
	int menuTransition, menuOffset;
	int horizontalOffset, snapGoal, currentSnap; //For horizontal scrolling selection
	int valueOffset[3]; //for stuff like difficulty, bot stats etc
	float heightMultiplier, widthMultiplier;
	int itemCount;
	MenuName name;

	Button buttons[10];
	Button buttonsDown[10];
	Menu* nextMenu;


	void setup(MenuName menuName, int deviceWidth, int deviceHeight);
	void draw(int menuOffset, int horizontalOffset);
	void touchUp(float x, float y);
};

class MenuSystem
{
	public:
		void setup(int gameplayDevice);
		void update();
		void draw();

		void touchDown(ofTouchEventArgs &touch);
		void touchMoved(ofTouchEventArgs &touch);
		void touchUp(ofTouchEventArgs &touch);
		void touchCancelled(ofTouchEventArgs &touch);
		void touchDoubleTap(ofTouchEventArgs &touch);

		ofTrueTypeFont font;

		int device; // PLAYBOOK, DEV_ALPHA

		int deviceWidth;
		int deviceHeight;

		// switch this to TRUE when ready to play a match
		bool IsInGame, IsStartGame;

		//For scrolling career event selection
		ofVec2f previousTouch;
		ofVec2f currentTouch;
		ofVec2f initialTouch;

		Menu activeMenu, nextMenu;

		//list of menus in game
		Menu menu_main, menu_startGame, menu_inGame;
		Menu menu_myBot, menu_career, menu_options;
		Menu menu_upgrade, menu_store, menu_postmatch;
		Menu menu_quickTeamselect, menu_quickBotsetup, menu_quickCalibration;
};

#endif /* MENUMAIN_H_ */

