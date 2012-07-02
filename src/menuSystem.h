/*
 * menu_main.h
 *
 *  Created on: Jul 2, 2012
 *      Author: Nikhil
 *      BASED ON THE MENU SYSTEM BY LOUIE SONG
 */

#ifndef MENUMAIN_H_
#define MENUMAIN_H_

#include "game.h"

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
	menu_INGAME
};

struct Button
{
	ofImage img;
	ofRectangle rect;
	bool IsShown;
	int type;

	void draw();
};

struct Menu
{
	int menuTransition, menuOffset;
	int align, gap;
	int itemCount;
	MenuName name;

	Button buttons[10];
	Menu* nextMenu;

	void setup(MenuName menuName, int deviceWidth, int deviceHeight);
	void draw();
	void touchUp(float x, float y);
};

class MenuSystem
{
	public:
		void setup(Game& game, int gameplayDevice);
		void update(Game& game);
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
		bool IsInGame;

		Menu activeMenu, nextMenu;

		//list of menus in game
		Menu menu_main, menu_startGame, menu_inGame;
};

#endif /* MENUMAIN_H_ */

