#pragma once
//
// OptionSelectEngine.h - Contains interface for the OptionSelect engine class.
//
#include <string>
#include "../../Core/ZeeTerminalCore.h"
#include <iostream>

//
// ZT OptionSelectEngine - Class for OptionSelect function, allows for easy debugging too.
//
class OptionSelectEngine
{
private:
	// MoveCursorToXCoord - Moves the cursor position to the same Y-axis co-ordinate that it is currently in, but to also an argument-specified X co-ordinate.
	// Parameters: xArg - The X co-ordinate parameter.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	bool MoveCursorToXCoord(short int xArg);

	// OSENumInputi - Function to handle user input of 32-bit integers, with a parameter for centring the prompt text all the time.
	// Parameters: sPrompt - The prompt text to be used.
	//             bCentrePromptText - Boolean for toggling centring the prompt text.
	// Return Values: int value containing inputted user value.
	//
	int OSENumInputi(std::string sPrompt, bool bCentrePromptText);

	// Object ID
	int nObjectID;
protected:

	// Directions text to forward to DirectionsDisplay()
	std::string sDirectionsText = "Press the 'W' key or up arrow key to move up.\nPress the 'S' key or down arrow key to move down.\nPress ENTER to continue with selection, or ESC to exit.";

	// The indicator string for options
	const std::string sOptionIndicator = "~| ";

	// DisplayOptionsIndicator - Displays the options indicator at calltime.
	// Arguments: sColour - The foreground colour to display for the options indicator, in RGB units.
	// Return values: None
	//
	inline void DisplayOptionsIndicator(std::string sColour) {
		// 1. Set colour
		colour(sColour, ConfigObjMain.sColourGlobalBack);
		// 2. Display indicator
		std::cout << sOptionIndicator;
		// 3. Set colours back to normal and exit
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}

	// SimpleOptionSelect - A simple selection UI that allows for easy number-typing input.
	// 	
	// nLeftPaddingWidth - Specify padding width for the options, in characters. Default is 0 (no padding).
	// 
	// Pressing ESC (exit) leads to returning code -1, error returns -2, and the index of the option when input is finished is returned otherwise.
	//
	int SimpleOptionSelect(std::string sPrompt, std::string sTitle, bool bCentreOptions = false, bool bCentrePrompt = false);

public:

	int nSizeOfOptions = 0;
	std::string* sOptions{};

	OptionSelectEngine();

	~OptionSelectEngine();

	// SetDirectionsText - Sets the direction text to a custom text, and replaces the default text.
	//                   - Because there is a default directions text, this function is optional to call.
	// Arguments: sText - The text to replace the default direction text with.
	// Return values: None
	//
	inline void SetDirectionsText(std::string sText)
	{
		// Set directions text
		sDirectionsText = sText;

		return;
	}

	// OptionSelect - A selection UI that allows for easy arrow-key OR W/S-key navigation.
	// 
	// nLeftPaddingWidth - Specify padding width for the options, in characters. Default is 0 (no padding).
	// 
	// Pressing ESC (exit) leads to returning code -1, error returns -2, and the index of the option when ENTER is pressed is returned otherwise.
	//
	int OptionSelect(std::string sPrompt, std::string sTitle, bool bCentreOptions = false, bool bCentrePrompt = false, bool bCentreDirections = false);

};