#pragma once

//
// ScreenNavigateEngine.cpp - Interface for the ScreenNavigateEngine class.
//
#include <string>

//
// ZT ScreenNavigateEngine - Class for ScreenNavigate function.
//
class ScreenNavigateEngine
{
protected:

	// Directions text to forward to DirectionsDisplay()
	std::string sDirectionsText = "Press the 'A' key or left arrow key to move left.\nPress the 'D' key or right arrow key to move right.\nPress ESC to exit.";

	// Object ID
	int nObjectID;

public:

	int nSizeOfScreens = 0;
	std::string* sScreens{};

	ScreenNavigateEngine();

	~ScreenNavigateEngine();

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

	// ScreenNavigate - An interactive display UI that allows for quick and easy screen switching in commands, using easy arrow-key OR A/D-key navigation.
	//
	// Pressing ESC leads to returning to previous command. Nothing else is used- this is just an interactive display UI.
	void ScreenNavigate(std::string sTitle);

};