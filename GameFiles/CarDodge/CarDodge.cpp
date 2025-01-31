#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include "../../RyRyCryptor/RyRyCryptor.h"
#include <Windows.h>
#include <iomanip>
#include <fstream>
#include <random>
bool VerifyIfGameIsRunnable(bool, bool);
#include "CarDodge_CodeFiles\CarInfo\CarInfo.h"
#include "CarDodge_CodeFiles\CarDodgeCore\CarDodgeCore.h"
#include "CarDodge_CodeFiles\CarDodgeMain\CarDodgeMain.h"

extern CarInfo EnemyCars[128];
extern CarInfo UserCar;
extern const int nEnemyCarArraySize;

// Menu colours
std::string sMenuColourFore = LWHT;
std::string sMenuColourBack = LBLU;


// InitialiseCarDodge - Initialises the game elements that are external of the core system (colour system, etc)
//
void InitialiseCarDodge() 
{
	// Initialise menu colours using the colour formats that were just initialised
	sMenuColourFore = LWHT;
	sMenuColourBack = LBLU;

	// Initialise EnemyCars array
	for (int i = 0; i < nEnemyCarArraySize; i++) {
		EnemyCars[i].CarStyle = CarStyles::EnemyCar;
	}

	// Initialise user car style to what configuration object indicates
	switch (ConfigObjMain.nCarDodgeGameStartupCar) {
	case 1:
		UserCar.CarStyle = CarStyles::UserCarDefault;
		break;
	case 2:
		UserCar.CarStyle = CarStyles::HoverRocket;
		break;
	case 3:
		UserCar.CarStyle = CarStyles::TheSweeper;
		break;
	case 4:
		UserCar.CarStyle = CarStyles::TheSlicer;
		break;
	case 5:
		UserCar.CarStyle = CarStyles::GTSpeed;
		break;
	case 6:
		UserCar.CarStyle = CarStyles::XtraAero;
		break;
	}

	// Menu screen colours
	colour(sMenuColourFore, sMenuColourBack);

	// Clear screen to set colours to whole screen
	cls();
}

// VerifyIfGameIsRunnable - Verify if game is runnable with current terminal attributes and settings.
//
bool VerifyIfGameIsRunnable(bool bInMainGame, bool bDisplayErrorMessage) {
	CONSOLE_SCREEN_BUFFER_INFO csbiMainMenu;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiMainMenu);

	// Check console height and width
	if ((csbiMainMenu.srWindow.Bottom - csbiMainMenu.srWindow.Top + 1 < 30) || (csbiMainMenu.srWindow.Right - csbiMainMenu.srWindow.Left + 1 < 120)) {
		std::cout << '\r';
		if (bDisplayErrorMessage)
			UserErrorDisplay("Failed to " + std::string((bInMainGame ? "continue operation of " : "start ")) + "game. The game window is too small in height and/or width to run the game."
				"\nPlease ensure that it is at least 30 character cells in height and 120 character cells in width, and try again.\n");
		return false; // Game is not runnable with current height
	}

	return true;
}

// GetWindowWidthInChars - Returns the console window width, in character cells.
//
int GetWindowWidthInChars() {
	CONSOLE_SCREEN_BUFFER_INFO csbiWidth;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiWidth);
	return csbiWidth.srWindow.Right - csbiWidth.srWindow.Left;
}

// RenderCar - Renders a car specified by CarInfo argument.
//
void RenderCar(CarInfo ciCarToRender) {
	// Set starting point
	SetCursorPosition(ciCarToRender.bottomLeft.X, ciCarToRender.bottomLeft.Y - 3);

	// Render all 4 rows
	for (int i = 0; i < 4; i++) {
		// Render car character on screen
		std::cout.write(ciCarToRender.CarStyle[i].data(), 4);
		// Move to next position down for render
		if (i < 3) SetCursorPosition(ciCarToRender.bottomLeft.X, ciCarToRender.bottomLeft.Y + (i - 2));
	}

	return;
}

// RenderMainMenuCars - Renders the main menu cars (decorative).
//
inline void RenderMainMenuCars() {
	CONSOLE_SCREEN_BUFFER_INFO csbiMainMenu;
	CarInfo ciMainMenuUserCar;
	CarInfo ciMainMenuEnemyCar;
	short int nScreenCentre = 0;
	short int nDirectionsTextLeftColumn = 0;
	short int nDirectionsTextRightColumn = 0;

	// Initialise console info struct
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiMainMenu);

	// Get screen centre
	nScreenCentre = (csbiMainMenu.srWindow.Right - csbiMainMenu.srWindow.Left) / 2;

	// Get left and right columns of directions text that will come up in menu, derivin off of nScreenCentre
	nDirectionsTextLeftColumn = nScreenCentre - 26; // 26 to count for the centre column
	nDirectionsTextRightColumn = nScreenCentre + 27; // 27 is half of 54

	// Set car styles
	ciMainMenuUserCar.CarStyle = CarStyles::UserCarDefault;
	ciMainMenuEnemyCar.CarStyle = CarStyles::EnemyCar;

	// Set up left side of main menu
	ciMainMenuUserCar.bottomLeft = { short(nDirectionsTextLeftColumn - 10), 14 };
	ciMainMenuEnemyCar.bottomLeft = { short(nDirectionsTextLeftColumn - 13), 9 };

	// Render left side of main menu
	colour(LYLW, sMenuColourBack);
	RenderCar(ciMainMenuEnemyCar);
	RenderCar(ciMainMenuUserCar);

	// Set up right side of main menu
	ciMainMenuUserCar.bottomLeft = { short(nDirectionsTextRightColumn + 6), 14 };
	ciMainMenuUserCar.CarStyle = CarStyles::XtraAero;

	ciMainMenuEnemyCar.bottomLeft = { short(nDirectionsTextRightColumn + 11), 11 };

	// Render left side of main menu
	RenderCar(ciMainMenuEnemyCar);
	RenderCar(ciMainMenuUserCar);

	// Render annotations for the cars on both sides of the main menu
	colour(LGRN, sMenuColourBack);
	SetCursorPosition(nDirectionsTextRightColumn + 12, 13);
	std::cout << "||";
	SetCursorPosition(nDirectionsTextRightColumn + 12, 14);
	std::cout << "VV";

	SetCursorPosition(nDirectionsTextRightColumn + 7, 8);
	std::cout << "^^";
	SetCursorPosition(nDirectionsTextRightColumn + 7, 9);
	std::cout << "||";

	colour(LMAG, sMenuColourBack);
	SetCursorPosition(nDirectionsTextLeftColumn - 3, 9);
	std::cout << "\\/";
	SetCursorPosition(nDirectionsTextLeftColumn - 3, 11);
	std::cout << "/\\";
	SetCursorPosition(nDirectionsTextLeftColumn - 9, 10);
	std::cout << "<-- CRASH";

	// Set colours back to normal
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Set cursor back to original place
	SetCursorPosition(0, 4);
}

void CarDodgeMainMenu() 
{
	std::cout << "Getting ready...\n";
	
	// Initialise game
	InitialiseCarDodge();

	// Ensure that previous user colours are saved so they don't get erased
	const std::string sUserColourGlobal = ConfigObjMain.sColourGlobal;
	const std::string sUserColourGlobalBack = ConfigObjMain.sColourGlobalBack;

	// Set menu colours as defaults - the actual game engine will change those automatically
	ConfigObjMain.sColourGlobal = sMenuColourFore;
	ConfigObjMain.sColourGlobalBack = sMenuColourBack;

	// Main menu loop
	while (true) {
		CarDodgeMain Main;
		OptionSelectEngine oseCarDodgeMenu;

		// Ensure that terminal is suitable for playing the game
		if (!VerifyIfGameIsRunnable(true, true)) {
			std::cout << "Take your time to resize the main menu window. The CarDodge main menu will reappear when the window is resized.\nPress any key to exit the game.\n";
			bool bExitGame = false;
			while (true) {
				// Check if user inputted anything
				if (_kbhit()) {
					_getch();
					bExitGame = true;
					break;
				}

				// Check window size repeatedly
				if (VerifyIfGameIsRunnable(true, false)) {
					// Exit loop - the window has been resized.
					break;
				}

				sleep(1);
			}

			// Game needs to be exited as user pressed a key - break out of main while loop
			if (bExitGame) break;

			// Clear screen to start terminal afresh from any error messages
			cls();
		}

		// Display title with background
		std::cout << "\n\n";
		OutputBoxWithText("Welcome to Car Dodge!", RED, YLW, LWHT, YLW, true);
		colour(sMenuColourFore, sMenuColourBack);

		// Render the decorative main menu cars
		RenderMainMenuCars();

		oseCarDodgeMenu.nSizeOfOptions = 5;
		std::string sOptions[] = {
			"Play",
			"Change Car",
			"How To Play",
			"High Score",
			"Exit"
		};
		oseCarDodgeMenu.sOptions = sOptions;

		// Prompt
		oseCarDodgeMenu.SetDirectionsText("Press the 'W' key or up arrow key to move up.\nPress the 'S' key or down arrow key to move down.\nPress ENTER to continue, or ESC to exit game.");
		int nInput = oseCarDodgeMenu.OptionSelect("Please select what you want to do:", "", true, true, true);

		if (nInput != 1) cls(); // optimisation for not executing too many cls() function calls, otherwise clear screen

		// Play main game
		if (nInput == 1) {
			Main.CarDodgeMainGame();
		}

		// Change car
		else if (nInput == 2) {
			Main.CarDodgeChangeUserCar();
		}

		// Instructions
		else if (nInput == 3) {
			Main.CarDodgeInstructions();
		}

		// High Scores
		else if (nInput == 4) {
			Main.CarDodgeHighScore();
		}

		// Exit
		else if (nInput == 5 || nInput == -1) {
			break;
		}

		// Incorrect input
		else {
			UserErrorDisplay("ERROR - Incorrect input. Please try again.\n");
			continue;
		}

		cls();
	}
	
	// Reset global colours back to user-set
	ConfigObjMain.sColourGlobal = sUserColourGlobal;
	ConfigObjMain.sColourGlobalBack = sUserColourGlobalBack;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	cls();

	return;
}