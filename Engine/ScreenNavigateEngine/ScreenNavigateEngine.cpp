//
// ScreenNavigateEngine.cpp - Responsible for handling the Screen Navigate Engine, and contains its class.
//
#include "ScreenNavigateEngine.h"
#include "../../Core/ZeeTerminalCore.h"
#include <iostream>
#include <conio.h>

// Constructor
ScreenNavigateEngine::ScreenNavigateEngine() {
	static int nStaticID = 10000;
	// Wrap-around to prevent overflow
	if (nStaticID >= std::numeric_limits<int>::max() - 1) nStaticID = 10000;
	nObjectID = ++nStaticID;

	// Display verbosity message if corresponding boolean allows it
	VerbosityDisplay("New ScreenNavigateEngine Object Created.\n", nObjectID);
	// Set values to default
	nSizeOfScreens = 0;
	sDirectionsText = "Press the 'A' key or left arrow key to move left.\nPress the 'D' key or right arrow key to move right.\nPress ESC to exit.";
}

// Destructor
ScreenNavigateEngine::~ScreenNavigateEngine() {
	// Display destructor verbose message
	VerbosityDisplay("ScreenNavigateEngine Object has been destroyed.\n", nObjectID);
}

// ScreenNavigate - An interactive display UI that allows for quick and easy screen switching in commands, using easy arrow-key OR A/D-key navigation.
//
// Pressing ESC leads to returning to previous command. Nothing else is used- this is just an interactive display UI.
void ScreenNavigateEngine::ScreenNavigate(std::string sTitle) {
	int nNumberOfScreens = 0;
	int nIndex = 1;
	int nKey = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbiScreenNavigate;

	// Count the number of screens
	for (int i = 0; i < nSizeOfScreens; i++) {
		if (sScreens[i] != "") nNumberOfScreens++;
	}

	// 27 is ascii for ESC key
	while (nKey != 27) {

		// 77 is ascii for right arrow
		if (nKey == 100 || nKey == 77) {
			nIndex++;
		}

		// 75 is ascii for left arrow
		if (nKey == 97 || nKey == 75) {
			nIndex--;
		}

		// if statements to prevent overspill of nIndex
		if (nIndex > nNumberOfScreens) nIndex = 1;
		else if (nIndex < 1) nIndex = nNumberOfScreens;

		// Clear screen for space for next screen
		cls();

		// Output title of all combined screens, centred
		CentreColouredText(sTitle, 1);
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\n";

		// Output screen number out of total screen number
		std::string sPageNum = "~~PAGE NUMBER: " + std::to_string(nIndex) + "/" + std::to_string(nNumberOfScreens) + "~~\n";
		CentreColouredText(sPageNum, 2);

		// Output directions of use using DirectionsDisplay()
		if (ConfigObjMain.bDisplayDirections) {
			std::cout << '\n';
			DirectionsDisplay(sDirectionsText, true);
			std::cout << '\n';
		}

		// Output correct screen
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(sScreens[nIndex - 1]) << '\n';



		// Check ending cursor height to see if scroll-up message should be outputted
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiScreenNavigate);
		if (csbiScreenNavigate.dwCursorPosition.Y >= csbiScreenNavigate.srWindow.Bottom - csbiScreenNavigate.srWindow.Top) {
			std::cout << '\n';
			colourHighlight();
			std::cout << wordWrap(" /\\ /\\ /\\  SCROLL UP FOR MORE INFO  /\\ /\\ /\\ ");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << '\n';
		}

		// while loop to skip next code on wrong input, optimisation
		while (true) {
			// Get input
			nKey = _getch();
			if (nKey == 77 || nKey == 75 || nKey == 97 || nKey == 100) {
				break;
			}
			// exit if ESC is pressed
			else if (nKey == 27) {
				return;
			}
			else continue;
		}
	}

	// Clear screen before leaving
	cls();

	return;
}