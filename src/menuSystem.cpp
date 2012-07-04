/*
 * menu_main.cpp
 *
 *  Created on: Jul 2, 2012
 *      Author: Nikhil
 */


#include "menuSystem.h"

void MenuSystem::setup(int gameplayDevice)
{
	ofTrueTypeFont::setGlobalDpi(72);
	ofRegisterTouchEvents(this);

	device = gameplayDevice;
	switch(device)
	{
		case DEV_ALPHA:
			deviceWidth = 1280;
			deviceHeight = 768;
		break;
		case PLAYBOOK:
			deviceWidth = 1024;
			deviceHeight = 600;
		break;
	}

	// one font to rule them all
	font.loadFont(ofToDataPath("", true) + "/app/native/verdana.ttf", 26, true, true);
	font.setLineHeight(18.0f);
	font.setLetterSpacing(1.037);

	IsInGame = false;
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

	menu_main.setup(menu_MAIN, deviceWidth, deviceHeight);
	menu_startGame.setup(menu_STARTGAME, deviceWidth, deviceHeight);
	menu_inGame.setup(menu_INGAME, deviceWidth, deviceHeight);
	menu_myBot.setup(menu_MYBOT, deviceWidth, deviceHeight);
	menu_career.setup(menu_CAREER, deviceWidth, deviceHeight);
	menu_options.setup(menu_OPTIONS, deviceWidth, deviceHeight);
	menu_upgrade.setup(menu_UPGRADE, deviceWidth, deviceHeight);
	menu_store.setup(menu_STORE, deviceWidth, deviceHeight);

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
			// when we END a match
			if(activeMenu.name == menu_INGAME)
			{
				IsInGame = false;
			}
			activeMenu.menuOffset = deviceHeight;
			activeMenu.menuTransition = 1;
			activeMenu = nextMenu;
			// when we actually start a match
			if(activeMenu.name == menu_INGAME)
			{
				IsInGame = true;
				//game.setup(device);
				IsStartGame = true;
			}
		}
	}
}

void MenuSystem::draw()
{
	this->activeMenu.draw(activeMenu.menuOffset, activeMenu.horizontalOffset);
}

//------------------------------------------------------------------------

//this is where all the actual logic goes

void MenuSystem::touchUp(ofTouchEventArgs &touch)
{
	//this->activeMenu.touchUp(touch.x, touch.y);

	//Check to prevent scrolling onto a button and end up triggering touchUp on that button
	if (abs(initialTouch.x - touch.x) < 40 * (deviceWidth/1024) && abs(initialTouch.y - touch.y) < 40 * (deviceHeight/600))
	{
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
				if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_store;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[2].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_options;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[3].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_myBot;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_STARTGAME:
				if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_career;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_inGame;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[2].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_MYBOT:
				if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_upgrade;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_store;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[2].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_CAREER:
				if (activeMenu.buttons[6].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_startGame;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_OPTIONS:
				if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_UPGRADE:
				if (activeMenu.buttons[2].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_STORE:
				if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.menuOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
		}
	}
}

void MenuSystem::touchDown(ofTouchEventArgs &touch)
{
	initialTouch.x = touch.x;
	currentTouch.x = touch.x;
	initialTouch.y = touch.y;
	currentTouch.y = touch.y;
}

void MenuSystem::touchMoved(ofTouchEventArgs &touch)
{
	previousTouch = currentTouch;
	currentTouch.x = touch.x;
	currentTouch.y = touch.y;
	if (activeMenu.name == menu_CAREER)
	{
		activeMenu.horizontalOffset += currentTouch.x - previousTouch.x ;
		if (activeMenu.horizontalOffset > 0) activeMenu.horizontalOffset = 0;
		else if (activeMenu.horizontalOffset < -1.25 * deviceWidth) activeMenu.horizontalOffset = -1.25 * deviceWidth;
	}
	else if (activeMenu.name == menu_STORE)
	{
		activeMenu.menuOffset += currentTouch.y - previousTouch.y;
	}
}

void MenuSystem::touchCancelled(ofTouchEventArgs &touch){}
void MenuSystem::touchDoubleTap(ofTouchEventArgs &touch){}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// MENU ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// this is where you specify all the buttons
void Menu::setup(MenuName menuName, int deviceWidth, int deviceHeight)
{
	heightMultiplier = 0.14;
	widthMultiplier = 0.2;
	this->name = menuName;
	switch(menuName)
	{
		case menu_MAIN:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.55, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonPlay.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.7, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonStore.png");
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.85, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonOptions.png");
			buttons[3].IsShown = true;
			buttons[3].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[3].img.loadImage(ofToDataPath("", true) + "/app/native/buttonMyBot.png");
			buttons[4].IsShown = false;
			buttons[4].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[4].img.loadImage(ofToDataPath("", true) + "/app/native/buttonMyBot.png");
			this->itemCount = 5;
		break;
		case menu_STARTGAME:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonCareer.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.55, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonQuickMatch.png");
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			this->itemCount = 3;
		break;
		case menu_MYBOT:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonUpgrades.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.55, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonStore.png");
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			this->itemCount = 3;
		break;
		case menu_CAREER:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.35, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[3].IsShown = true;
			buttons[3].rect = ofRectangle(deviceWidth * 0.85, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[3].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[4].IsShown = true;
			buttons[4].rect = ofRectangle(deviceWidth * 1.1, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[4].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[5].IsShown = true;
			buttons[5].rect = ofRectangle(deviceWidth * 1.35, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[5].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[6].IsShown = true;
			buttons[6].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[6].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			this->itemCount = 7;
		break;
		case menu_OPTIONS:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			this->itemCount = 1;
		break;
		case menu_UPGRADE:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.7, deviceHeight * 0.3, deviceWidth * 0.04, deviceHeight * 0.2);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/button+.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.3, deviceHeight * 0.3, deviceWidth * 0.04, deviceHeight * 0.2);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/button-.png");
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			this->itemCount = 3;
		break;
		case menu_STORE:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.3, deviceHeight * 0.1, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonItem.png");
			buttons[0].type = 69;
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			this->itemCount = 2;
		break;
		case menu_INGAME:
			this->itemCount = 0;
		break;
	}
}

//-------------------------------------------------------------------

void Menu::draw(int menuOffset, int horizontalOffset)
{
	for(int i = 0; i < this->itemCount - 1; i++)
	{
		this->buttons[i].draw(menuOffset, horizontalOffset);
	}
	this->buttons[this->itemCount - 1].draw(0, 0); //Draw the back button with no offset
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// BUTTON /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void Button::draw(int menuOffset, int horizontalOffset)
{
	if (this->IsShown)
	{
		if (this->type == 69)
		{
			for (int x = 0; x < 10; x++)
			{
				this->img.draw(this->rect.x, this->rect.y + menuOffset + x * 100, this->rect.width, this->rect.height);
			}
		}
		else
		{
			this->img.draw(this->rect.x + horizontalOffset, this->rect.y + menuOffset, this->rect.width, this->rect.height);
		}
	}
}
