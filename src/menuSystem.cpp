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
	IsStartGame = false;
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
	//menu_startGame.setup(menu_STARTGAME, deviceWidth, deviceHeight);
	menu_inGame.setup(menu_INGAME, deviceWidth, deviceHeight);
	//menu_myBot.setup(menu_MYBOT, deviceWidth, deviceHeight);
	//menu_career.setup(menu_CAREER, deviceWidth, deviceHeight);
	//menu_options.setup(menu_OPTIONS, deviceWidth, deviceHeight);
	//menu_upgrade.setup(menu_UPGRADE, deviceWidth, deviceHeight);
	//menu_store.setup(menu_STORE, deviceWidth, deviceHeight);
	menu_quickTeamselect.setup(menu_QUICKTEAMSELECT, deviceWidth, deviceHeight);
	menu_quickCalibration.setup(menu_QUICKCALIBRATION, deviceWidth, deviceHeight);
	menu_quickBotsetup.setup(menu_QUICKBOTSETUP, deviceWidth, deviceHeight);
	menu_postmatch.setup(menu_POSTMATCH, deviceWidth, deviceHeight);

	//we set active Menu
	activeMenu = menu_main;

	activeMenu.menuTransition = 1;

	//activeMenu.menuOffset = deviceHeight;
	activeMenu.horizontalOffset = deviceWidth;
}

//--------------------------------------------------------------------------------

// louie's magnificent menu transition system, untouched
/*
 * use menuTransition = -2 when going back in menus (ie Back/Cancel)
 * use menuTransition = -1 when going forward in menus (ie Next/Continue)
*/
void MenuSystem::update() {
	//ofBackground(240);
	/* Vertical transition
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
			// toogle off
			if(activeMenu.name == menu_INGAME)
			{
				IsInGame = false;
			}
			activeMenu = nextMenu;
			activeMenu.menuTransition = 1;
			activeMenu.menuOffset = deviceHeight;
			// set up a READY FOR MATCH flag for control to see
			if(activeMenu.name == menu_INGAME)
			{
				IsInGame = true;
				IsStartGame = true;
			}
		}
	}
	*/
	if (activeMenu.menuTransition == 1) {
		activeMenu.horizontalOffset = activeMenu.horizontalOffset / 2;
		if (activeMenu.horizontalOffset <= 1) {
			activeMenu.horizontalOffset = 0;
			activeMenu.menuTransition = 0;
		}
		for (int x = 0; x < activeMenu.itemCount; x++)
		{
			activeMenu.buttons[x].rect.x = activeMenu.buttons[x].rectOriginal.x + activeMenu.horizontalOffset;
			activeMenu.buttonsDown[x].rect.x = activeMenu.buttonsDown[x].rectOriginal.x + activeMenu.horizontalOffset;
		}
	}
	//back animation
	if (activeMenu.menuTransition == 2) {
		activeMenu.horizontalOffset = activeMenu.horizontalOffset / 2;
		if (activeMenu.horizontalOffset <= 1) {
			activeMenu.horizontalOffset = 0;
			activeMenu.menuTransition = 0;
		}
		for (int x = 0; x < activeMenu.itemCount; x++)
		{
			activeMenu.buttons[x].rect.x = activeMenu.buttons[x].rectOriginal.x - activeMenu.horizontalOffset;
			activeMenu.buttonsDown[x].rect.x = activeMenu.buttonsDown[x].rectOriginal.x - activeMenu.horizontalOffset;
		}
	}
	else if (activeMenu.menuTransition == -1) {
		activeMenu.horizontalOffset = activeMenu.horizontalOffset * 2;
		if (activeMenu.horizontalOffset >= deviceWidth) {
			// toogle off
			if(activeMenu.name == menu_INGAME)
			{
				IsInGame = false;
			}
			activeMenu = nextMenu;
			activeMenu.menuTransition = 1;
			activeMenu.horizontalOffset = deviceWidth;
			// set up a READY FOR MATCH flag for control to see
			if(activeMenu.name == menu_INGAME)
			{
				IsInGame = true;
				IsStartGame = true;
			}
		}
		for (int x = 0; x < activeMenu.itemCount; x++)
		{
			activeMenu.buttons[x].rect.x = activeMenu.buttons[x].rectOriginal.x - activeMenu.horizontalOffset;
			activeMenu.buttonsDown[x].rect.x = activeMenu.buttonsDown[x].rectOriginal.x - activeMenu.horizontalOffset;
		}
	}
	//back animation, going towards the right.
	else if (activeMenu.menuTransition == -2) {
		activeMenu.horizontalOffset = activeMenu.horizontalOffset * 2;
		if (activeMenu.horizontalOffset >= deviceWidth) {
			// toogle off
			if(activeMenu.name == menu_INGAME)
			{
				IsInGame = false;
			}
			activeMenu = nextMenu;
			activeMenu.menuTransition = 2;
			activeMenu.horizontalOffset = deviceWidth;
			// set up a READY FOR MATCH flag for control to see
			if(activeMenu.name == menu_INGAME)
			{
				IsInGame = true;
				IsStartGame = true;
			}
		}
		for (int x = 0; x < activeMenu.itemCount; x++)
		{
			activeMenu.buttons[x].rect.x = activeMenu.buttons[x].rectOriginal.x + activeMenu.horizontalOffset;
			activeMenu.buttonsDown[x].rect.x = activeMenu.buttonsDown[x].rectOriginal.x + activeMenu.horizontalOffset;
		}
	}
	//commence snapping
	if (activeMenu.name == menu_QUICKTEAMSELECT && activeMenu.currentSnap != 0)
	{
		//ease in. wtb lerp
		activeMenu.currentSnap /= 2;
		if (abs(activeMenu.currentSnap) <= 1)
		{
			activeMenu.currentSnap = 0;
		}
		for (int x = 0; x < activeMenu.itemCount - 4; x++)
		{
			activeMenu.buttons[x].rect.x -= activeMenu.currentSnap;
			activeMenu.buttonsDown[x].rect.x -= activeMenu.currentSnap;
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
	for (int x = 0; x < activeMenu.itemCount; x++)
	{
		activeMenu.buttons[x].isDown = false;
	}
	//if (activeMenu.name == menu_CAREER)
	if (activeMenu.name == menu_QUICKTEAMSELECT)
	{
		//snapping to selection closest to centre of screen
		int min = deviceWidth;
		//4 items we don't need to check, back/next button and the two difficulty slide images
		for (int x = 0; x < activeMenu.itemCount - 4; x++)
		{
			//finding the closest selection to centre of screen, (deviceWidth * 0.4) is the distance between each event button, change it as needed
			if (abs(activeMenu.buttons[x].rect.x - (deviceWidth * 0.4)) < min)
			{
				//sets the amount needed to snap to the distance of closest selection to centre of screen
				min = abs(activeMenu.buttons[x].rect.x - (deviceWidth * 0.4));
				activeMenu.snapGoal = activeMenu.buttons[x].rect.x - (deviceWidth * 0.4);
			}
		}
		activeMenu.currentSnap = activeMenu.snapGoal;
	}

	//Check to prevent scrolling onto a button and end up triggering touchUp on that button
	if (abs(initialTouch.x - touch.x) < 30 && abs(initialTouch.y - touch.y) < 30)
	{
		switch(activeMenu.name)
		{
			// add menus here
			case menu_MAIN:
				// add specific buttons here
				if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
				{
					//nextMenu = menu_startGame;
					nextMenu = menu_quickTeamselect;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
				/*if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
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
				}*/
			break;
			case menu_STARTGAME:
				if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_career;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_inGame;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[2].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_MYBOT:
				if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_upgrade;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_store;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
				if (activeMenu.buttons[2].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_CAREER:
				if (activeMenu.buttons[6].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_startGame;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_OPTIONS:
				if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_UPGRADE:
				if (activeMenu.buttons[2].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_STORE:
				if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_QUICKTEAMSELECT:
				if (activeMenu.buttons[9].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -2;
				}
				if (activeMenu.buttons[6].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_quickBotsetup;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_QUICKBOTSETUP:
				if (activeMenu.buttons[6].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_quickTeamselect;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -2;
				}
				else if (activeMenu.buttons[5].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_quickCalibration;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
			break;
			case menu_QUICKCALIBRATION:
				if (activeMenu.buttons[0].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_inGame;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -1;
				}
				else if (activeMenu.buttons[1].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_quickBotsetup;
					activeMenu.horizontalOffset = 1;
					activeMenu.menuTransition = -2;
				}
			break;
			case menu_POSTMATCH:
				if (activeMenu.buttons[5].rect.inside(touch.x, touch.y))
				{
					nextMenu = menu_main;
					activeMenu.horizontalOffset = 1;
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

	for (int x = 0; x < activeMenu.itemCount; x++)
	{
		if (activeMenu.buttons[x].rect.inside(touch.x, touch.y))
		{
			activeMenu.buttons[x].isDown = true;
		}
	}
}

void MenuSystem::touchMoved(ofTouchEventArgs &touch)
{
	previousTouch = currentTouch;
	currentTouch.x = touch.x;
	currentTouch.y = touch.y;
	//scrolling shit
	if (activeMenu.name == menu_CAREER)
	{
		activeMenu.horizontalOffset += currentTouch.x - previousTouch.x;
		for (int x = 0; x < activeMenu.itemCount - 1; x++)
		{
			activeMenu.buttons[x].rect.x -= activeMenu.horizontalOffset;
			activeMenu.buttonsDown[x].rect.x -= activeMenu.horizontalOffset;
		}
		//if (activeMenu.horizontalOffset > 0) activeMenu.horizontalOffset = 0;
		//else if (activeMenu.horizontalOffset < -1.25 * deviceWidth) activeMenu.horizontalOffset = -1.25 * deviceWidth;
	}
	else if (activeMenu.name == menu_STORE)
	{
		activeMenu.menuOffset += currentTouch.y - previousTouch.y;
		for (int x = 0; x < activeMenu.itemCount - 1; x++)
		{
			activeMenu.buttons[x].rect.y = activeMenu.buttons[x].rectOriginal.y + activeMenu.menuOffset;
			activeMenu.buttonsDown[x].rect.y = activeMenu.buttonsDown[x].rectOriginal.y + activeMenu.menuOffset;
		}
	}
	else if (activeMenu.name == menu_QUICKTEAMSELECT)
	{
		if (activeMenu.buttons[7].isDown)
		{
			activeMenu.valueOffset[0] += currentTouch.x - previousTouch.x;
			if (activeMenu.valueOffset[0] > deviceWidth * 0.46) activeMenu.valueOffset[0] = deviceWidth * 0.46;
			if (activeMenu.valueOffset[0] < deviceWidth * 0) activeMenu.valueOffset[0] = 0;
			activeMenu.buttons[7].rect.x = activeMenu.buttons[7].rectOriginal.x + activeMenu.valueOffset[0];
			activeMenu.buttonsDown[7].rect.x = activeMenu.buttonsDown[7].rectOriginal.x + activeMenu.valueOffset[0];
		}
		else
		{
			activeMenu.horizontalOffset += currentTouch.x - previousTouch.x;
			for (int x = 0; x < activeMenu.itemCount- 4; x++)
			{
				activeMenu.buttons[x].rect.x += currentTouch.x - previousTouch.x;
				activeMenu.buttonsDown[x].rect.x += currentTouch.x - previousTouch.x;

			}
		}
	}
	else if (activeMenu.name == menu_QUICKBOTSETUP)
	{
		if (activeMenu.buttons[1].isDown)
		{
			activeMenu.valueOffset[0] += currentTouch.x - previousTouch.x;
			if (activeMenu.valueOffset[0] > deviceWidth * 0.26) activeMenu.valueOffset[0] = deviceWidth * 0.26;
			if (activeMenu.valueOffset[0] < deviceWidth * 0) activeMenu.valueOffset[0] = 0;
			activeMenu.buttons[1].rect.x = activeMenu.buttons[1].rectOriginal.x + activeMenu.valueOffset[0];
			activeMenu.buttonsDown[1].rect.x = activeMenu.buttonsDown[1].rectOriginal.x + activeMenu.valueOffset[0];
		}
		else if (activeMenu.buttons[3].isDown)
		{
			activeMenu.valueOffset[1] += currentTouch.x - previousTouch.x;
			if (activeMenu.valueOffset[1] > deviceWidth * 0.26) activeMenu.valueOffset[1] = deviceWidth * 0.26;
			if (activeMenu.valueOffset[1] < deviceWidth * 0) activeMenu.valueOffset[1] = 0;
			activeMenu.buttons[3].rect.x = activeMenu.buttons[3].rectOriginal.x + activeMenu.valueOffset[1];
			activeMenu.buttonsDown[3].rect.x = activeMenu.buttonsDown[3].rectOriginal.x + activeMenu.valueOffset[1];
		}
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
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonQuickMatch.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.7, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonStore.png");
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.85, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonOptions.png");
			//buttons[3].IsShown = true;
			//buttons[3].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			//buttons[3].img.loadImage(ofToDataPath("", true) + "/app/native/buttonMyBot.png");
			buttons[3].IsShown = false;
			buttons[3].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.4, 0, 0); //fake back button with 0 size
			buttons[3].img.loadImage(ofToDataPath("", true) + "/app/native/buttonMyBot.png");

			//touchdown mouse button images (currently just the same placeholder image for all buttons)
			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.55, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.7, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[2].IsShown = true;
			buttonsDown[2].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.85, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[2].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//buttonsDown[3].IsShown = true;
			//buttonsDown[3].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			//buttonsDown[3].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			this->itemCount = 4;
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

			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.55, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[2].IsShown = true;
			buttonsDown[2].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[2].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
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

			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0.8, deviceHeight * 0.55, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[2].IsShown = true;
			buttonsDown[2].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[2].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			this->itemCount = 3;
		break;
		case menu_CAREER:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.4, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.65, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0.9, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[3].IsShown = true;
			buttons[3].rect = ofRectangle(deviceWidth * 1.15, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[3].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[4].IsShown = true;
			buttons[4].rect = ofRectangle(deviceWidth * 1.4, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[4].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[5].IsShown = true;
			buttons[5].rect = ofRectangle(deviceWidth * 1.65, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[5].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[6].IsShown = true;
			buttons[6].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[6].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");

			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0.35, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[2].IsShown = true;
			buttonsDown[2].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[3].IsShown = true;
			buttonsDown[3].rect = ofRectangle(deviceWidth * 0.85, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[3].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[4].IsShown = true;
			buttonsDown[4].rect = ofRectangle(deviceWidth * 1.1, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[4].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[5].IsShown = true;
			buttonsDown[5].rect = ofRectangle(deviceWidth * 1.35, deviceHeight * 0.4, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[5].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[6].IsShown = true;
			buttonsDown[6].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[6].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			this->itemCount = 7;
		break;
		case menu_OPTIONS:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");

			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
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

			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0.7, deviceHeight * 0.3, deviceWidth * 0.04, deviceHeight * 0.2);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0.3, deviceHeight * 0.3, deviceWidth * 0.04, deviceHeight * 0.2);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[2].IsShown = true;
			buttonsDown[2].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[2].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
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

			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0.3, deviceHeight * 0.1, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[0].type = 69;
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			this->itemCount = 2;
		break;
		case menu_QUICKTEAMSELECT:
			//replace these with your team/bot images
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.4, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.65, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0.9, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[3].IsShown = true;
			buttons[3].rect = ofRectangle(deviceWidth * 1.15, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[3].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[4].IsShown = true;
			buttons[4].rect = ofRectangle(deviceWidth * 1.4, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[4].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[5].IsShown = true;
			buttons[5].rect = ofRectangle(deviceWidth * 1.65, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttons[5].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttons[6].IsShown = true;
			buttons[6].rect = ofRectangle(deviceWidth * (1 - widthMultiplier), deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[6].img.loadImage(ofToDataPath("", true) + "/app/native/buttonNext.png");
			//the vertical difficulty slider button thing
			buttons[7].IsShown = true;
			buttons[7].rect = ofRectangle(deviceWidth * 0.25, deviceHeight * 0.65, deviceWidth * 0.04, deviceHeight * 0.2);
			buttons[7].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//the horizontal slide track thing
			buttons[8].IsShown = true;
			buttons[8].rect = ofRectangle(deviceWidth * 0.25, deviceHeight * 0.75, deviceWidth * 0.5, deviceHeight * 0.04);
			buttons[8].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttons[9].IsShown = true;
			buttons[9].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[9].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");

			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0.4, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0.65, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[2].IsShown = true;
			buttonsDown[2].rect = ofRectangle(deviceWidth * 0.9, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[2].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[3].IsShown = true;
			buttonsDown[3].rect = ofRectangle(deviceWidth * 1.15, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[3].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[4].IsShown = true;
			buttonsDown[4].rect = ofRectangle(deviceWidth * 1.4, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[4].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[5].IsShown = true;
			buttonsDown[5].rect = ofRectangle(deviceWidth * 1.65, deviceHeight * 0.3, deviceWidth * widthMultiplier, deviceHeight * 0.3);
			buttonsDown[5].img.loadImage(ofToDataPath("", true) + "/app/native/buttonEvent.png");
			buttonsDown[6].IsShown = true;
			buttonsDown[6].rect = ofRectangle(deviceWidth * (1 - widthMultiplier), deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[6].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[7].IsShown = true;
			buttonsDown[7].rect = ofRectangle(deviceWidth * 0.25, deviceHeight * 0.65, deviceWidth * 0.04, deviceHeight * 0.2);
			buttonsDown[7].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[8].IsShown = true;
			buttonsDown[8].rect = ofRectangle(deviceWidth * 0.25, deviceHeight * 0.75, deviceWidth * 0.5, deviceHeight * 0.04);
			buttonsDown[8].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[9].IsShown = true;
			buttonsDown[9].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[9].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			this->itemCount = 10;
		break;
		case menu_QUICKBOTSETUP:
			//image of bot
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.2, deviceWidth * 0.4, deviceHeight * 0.6);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//the vertical difficulty slider button thing
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.2, deviceWidth * 0.04, deviceHeight * 0.2);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//the horizontal slide track thing
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.3, deviceWidth * 0.3, deviceHeight * 0.04);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//the vertical difficulty slider button thing
			buttons[3].IsShown = true;
			buttons[3].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.4, deviceWidth * 0.04, deviceHeight * 0.2);
			buttons[3].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//the horizontal slide track thing
			buttons[4].IsShown = true;
			buttons[4].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.5, deviceWidth * 0.3, deviceHeight * 0.04);
			buttons[4].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttons[5].IsShown = true;
			buttons[5].rect = ofRectangle(deviceWidth * (1 - widthMultiplier), deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[5].img.loadImage(ofToDataPath("", true) + "/app/native/buttonNext.png");
			buttons[6].IsShown = true;
			buttons[6].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[6].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");

			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.2, deviceWidth * 0.4, deviceHeight * 0.6);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.2, deviceWidth * 0.04, deviceHeight * 0.2);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[2].IsShown = true;
			buttonsDown[2].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.3, deviceWidth * 0.3, deviceHeight * 0.04);
			buttonsDown[2].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[3].IsShown = true;
			buttonsDown[3].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.4, deviceWidth * 0.04, deviceHeight * 0.2);
			buttonsDown[3].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[4].IsShown = true;
			buttonsDown[4].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.5, deviceWidth * 0.3, deviceHeight * 0.04);
			buttonsDown[4].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[5].IsShown = true;
			buttonsDown[5].rect = ofRectangle(deviceWidth * (1 - widthMultiplier), deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[5].img.loadImage(ofToDataPath("", true) + "/app/native/buttonNext.png");
			buttonsDown[6].IsShown = true;
			buttonsDown[6].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[6].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			this->itemCount = 7;
		break;
		case menu_QUICKCALIBRATION:
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * (1 - widthMultiplier), deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonNext.png");
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * (1 - widthMultiplier), deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/buttonNext.png");
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0, deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/buttonBack.png");
			this->itemCount = 2;
		break;
		case menu_POSTMATCH:
			//you can create a temp img to use so when you display the postmatch screen,
			//switch around the images in the buttons array so they're in order of first place to last place
			//First place
			buttons[0].IsShown = true;
			buttons[0].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.2, deviceWidth * 0.4, deviceHeight * 0.2);
			buttons[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//second place
			buttons[1].IsShown = true;
			buttons[1].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.4, deviceWidth * 0.2, deviceHeight * 0.1);
			buttons[1].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//third place
			buttons[2].IsShown = true;
			buttons[2].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.5, deviceWidth * 0.2, deviceHeight * 0.1);
			buttons[2].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//forth place
			buttons[3].IsShown = true;
			buttons[3].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.6, deviceWidth * 0.2, deviceHeight * 0.1);
			buttons[3].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			//winnings, not sure what exactly you're trying to display yet so just a giant box for now
			buttons[4].IsShown = true;
			buttons[4].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.2, deviceWidth * 0.4, deviceHeight * 0.7);
			buttons[4].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttons[5].IsShown = true;
			buttons[5].rect = ofRectangle(deviceWidth * (1 - widthMultiplier), deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttons[5].img.loadImage(ofToDataPath("", true) + "/app/native/buttonNext.png");

			buttonsDown[0].IsShown = true;
			buttonsDown[0].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.2, deviceWidth * 0.4, deviceHeight * 0.2);
			buttonsDown[0].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[1].IsShown = true;
			buttonsDown[1].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.4, deviceWidth * 0.2, deviceHeight * 0.1);
			buttonsDown[1].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[2].IsShown = true;
			buttonsDown[2].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.5, deviceWidth * 0.2, deviceHeight * 0.1);
			buttonsDown[2].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[3].IsShown = true;
			buttonsDown[3].rect = ofRectangle(deviceWidth * 0.1, deviceHeight * 0.6, deviceWidth * 0.2, deviceHeight * 0.1);
			buttonsDown[3].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[4].IsShown = true;
			buttonsDown[4].rect = ofRectangle(deviceWidth * 0.6, deviceHeight * 0.2, deviceWidth * 0.4, deviceHeight * 0.7);
			buttonsDown[4].img.loadImage(ofToDataPath("", true) + "/app/native/bar.png");
			buttonsDown[5].IsShown = true;
			buttonsDown[5].rect = ofRectangle(deviceWidth * (1 - widthMultiplier), deviceHeight * 0.86, deviceWidth * widthMultiplier, deviceHeight * heightMultiplier);
			buttonsDown[5].img.loadImage(ofToDataPath("", true) + "/app/native/buttonNext.png");
		break;
		case menu_INGAME:
			this->itemCount = 0;
		break;
	}
	for (int x = 0; x < this->itemCount; x++)
	{
		buttons[x].rectOriginal = buttons[x].rect;
		buttonsDown[x].rectOriginal = buttonsDown[x].rect;
	}
}

//-------------------------------------------------------------------

void Menu::draw(int menuOffset, int horizontalOffset)
{
		for(int i = 0; i < this->itemCount; i++)
		{
			if (this->buttons[i].isDown)
			{
				this->buttonsDown[i].draw(menuOffset, horizontalOffset);
			}
			else
			{
				this->buttons[i].draw(menuOffset, horizontalOffset);
			}
		}
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
		/*
		if (this->type == 69)
		{
			for (int x = 0; x < 10; x++)
			{
				this->img.draw(this->rect.x + horizontalOffset, this->rect.y + menuOffset + x * 100, this->rect.width, this->rect.height);
			}
		}
		else
		{*/
			this->img.draw(this->rect.x, this->rect.y, this->rect.width, this->rect.height);
		//}
	}
}
