#pragma once
//
// RGBColourPresetSystem.cpp - Responsible for managing the RGB Colour Preset data structure and class + system.
//
#include "../../Core/ZTFormattingDefinitions.h"

// RGBColourPresetSystem - System Responsible for managing the RGB Colour Presets in ZeeTerminal.
//
class RGBColourPresetSystem {
public:
	std::string sColourPresetForeground = LWHT;
	std::string sColourPresetBackground = BLK;

	std::string sPresetName = "EMPTY_PRESET";
	bool		bSetByUser = false;

	RGBColourPresetSystem();

	~RGBColourPresetSystem();

	// CheckIfAnsiPreset - Checks if the colours in the preset are in the ANSI RGB format.
	// Parameters: None
	// Return values: TRUE or 1 for ANSI RGB preset, FALSE or 0 for WIN32 16-colour preset.
	//
	inline bool CheckIfAnsiPreset() {
		if (sColourPresetForeground.find(';') != std::string::npos && sColourPresetBackground.find(';') != std::string::npos) {
			return true;
		}
		else return false;
	}

	// ResetIfNotSetByUser - Resets the RGB preset if it wasn't set by the user already. 
	//                     - This is usually for changing the preset from ANSI to WIN32 and vice versa if it's already default, so that it works properly in the current configuration.
	// Parameters: None
	// Return Values: None
	//
	inline void ResetIfNotSetByUser() {
		if (bSetByUser == false) {
			// Initialise values to default
			sColourPresetForeground = LWHT;
			sColourPresetBackground = BLK;
			sPresetName = "EMPTY_PRESET";

			return;
		}
	}

	// ResetPreset - Resets this RGB colour preset to the default values.
	// Parameters: None
	// Return Values: None
	inline void ResetPreset() {
		// Reset to default values
		std::string sColourPresetForeground = LWHT;
		std::string sColourPresetBackground = BLK;
		std::string sPresetName = "EMPTY_PRESET";
		bool bSetByUser = false;

		return;
	}

};