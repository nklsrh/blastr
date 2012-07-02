/*
 * menu_main.cpp
 *
 *  Created on: Jul 2, 2012
 *      Author: Nikhil
 */


#include "menuSystem.h"

void MenuSystem::setup(Game& game)
{
	ofTrueTypeFont::setGlobalDpi(72);
	ofRegisterTouchEvents(this);

	deviceWidth = 1024;
	deviceHeight = 600;

	// one font to rule them all
	font.loadFont(ofToDataPath("", true) + "/app/native/verdana.ttf", 26, true, true);
	font.setLineHeight(18.0f);
	font.setLetterSpacing(1.037);

	IsInGame = false;
	activeGame = game;
//	buttonBack.loadImage(ofToDataPath("", true) + "/app/native/images/buttonBack.png");
//	buttonPlay.loadImage(ofToDataPath("", true) + "/app/native/images/buttonPlay.png");
//	buttonOptions.loadImage(ofToDataPath("", true) + "/app/native/images/buttonOptions.png");
//	buttonCredits.loadImage(ofToDataPath("", true) + "/app/native/images/buttonCredits.png");
//	buttonMyBot.loadImage(ofToDataPath("", true) + "/app/native/images/buttonMyBot.png");
//	buttonUpgrades.loadImage(ofToDataPath("", true) + "/app/native/images/buttonUpgrades.png");
//	buttonTournament.loadImage(ofToDataPath("", true) + "/app/native/images/buttonTournament.png");
//	buttonQuickMatch.loadImage(ofToDataPath("", true) + "/app/native/images/buttonQuickMatch.png");
//
//	bgMain.loadImage(ofToDataPath("", true) + "/app/native/images/bgMain.png");
//	bgCredits.loadImage(ofToDataPath("", true) + "/app/native/images/bgCredits.png");
//	bgOptions.loadImage(ofToDataPath("", true) + "/app/native/images/bgOptions.png");
//	bgPlay.loadImage(ofToDataPath("", true) + "/app/native/images/bgPlay.png");
//	bgMyBot.loadImage(ofToDataPath("", true) + "/app/native/images/bgMyBot.png");
//	bgUpgrades.loadImage(ofToDataPath("", true) + "/app/native/images/bgUpgrades.png");
//	bgTournament.loadImage(ofToDataPath("", true) + "/app/native/images/bgTournament.png");
//	bgQuickMatch.loadImage(ofToDataPath("", true) + "/app/native/images/bgQuickMatch.png");
//
//	buttonPlus.loadImage(ofToDataPath("", true) + "/app/native/images/button+.png");
//	buttonMinus.loadImage(ofToDataPath("", true) + "/app/native/images/button-.png");

	menu_main.setup(menu_MAIN);
	menu_startGame.setup(menu_STARTGAME);
	menu_inGame.setup(menu_INGAME);
	//we set active Menu
	activeMenu = menu_main;
	activeMenu.menuTransition = 1;

	activeMenu.menuOffset = deviceHeight;
}

//--------------------------------------------------------------------------------

// louie's magnificent menu transition system, untouched
void MenuSystem::update() {
	//ofBackground(240);
	if (activeMenu.menuTransition == 1) {
		activeMenu.menuOffset = activeMenu.menuOffset / 2;
		if (activeMenu.menuOffset <= 1) {
			activeMenu.menuOffset = 0;
			activeMenu.menuTransition = 0;
		}
	}
	else if (activeMenu.menuTransition == -1) {
		activeMenu.menuOffset = activeMenu.menuOffset * 2;
		if (activeMenu.menuOffset >= deviceHeight) {
			activeMenu.menuOffset = deviceHeight;
			activeMenu.menuTransition = 1;
			activeMenu = nextMenu;
			// where do i put the code for when we actually start a match?
			if(activeMenu.name == menu_INGAME)
			{
				IsInGame = true;
				activeGame.setup();
			}
		}
	}
}

void MenuSystem::draw()
{
	this->activeMenu.draw();
}

//------------------------------------------------------------------------

//this is where all the actual logic goes

void MenuSystem::touchUp(ofTouchEventArgs &touch)
{
	//this->activeMenu.touchUp(touch.x, touch.y);
	switch(activeMenu.name)
	{
		// add menus here
		case menu_MAIN:
			// add specific buttons here
			if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
			{
				nextMenu = menu_startGame;
				activeMenu.menuOffset = 1;
				activeMenu.menuTransition = -1;
			}
		break;
		case menu_STARTGAME:
			if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
			{
				nextMenu = menu_inGame;
				activeMenu.menuOffset = 1;
				activeMenu.menuTransition = -1;
			}
			if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
			{
				nextMenu = menu_main;
				activeMenu.menuOffset = 1;
				activeMenu.menuTransition = -1;
			}
		break;
	}
}

void MenuSystem::touchDown(ofTouchEventArgs &touch){}
void MenuSystem::touchMoved(ofTouchEventArgs &touch){}
void MenuSystem::touchCancelled(ofTouchEventArgs &touch){}
void MenuSystem::touchDoubleTap(ofTouchEventArgs &touch){}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// MENU ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// this is where you specify all the buttons
void Menu::setup(MenuName menuName)
{
	this->name = menuName;
	switch(menuName)
	{
		case menu_MAIN:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(1024/2 - 100, 600/2 - 50, 200, 100);	//just centering it, is all
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonPlay.png");
			this->itemCount = 1;
		break;
		case menu_STARTGAME:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(1024/2 - 50, 600/2 - 50, 200, 100);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonPlay.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(500, 400, 100, 40);	//just centering it, is all
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			this->itemCount = 2;
		break;
		case menu_INGAME:
			this->itemCount = 0;
		break;
	}
}

//-------------------------------------------------------------------

void Menu::draw()
{
	for(int i = 0; i < this->itemCount; i++)
	{
		this->buttons[i].draw();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// BUTTON /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void Button::draw()
{
	this->img.draw(this->rect.x, this->rect.y, this->rect.width, this->rect.height);
}
