//
// RGBColourPresetSystem.cpp - Responsible for managing the RGB Colour Preset data structure and class + system.
//
#include "RGBColourPresetSystem.h"
#include "../../Core/ZeeTerminalCore.h"

// Constructor
RGBColourPresetSystem::RGBColourPresetSystem() {
	VerbosityDisplay("RGBColourPreset Object Created.\n");
	// Initialise values to default
	sColourPresetForeground = LWHT;
	sColourPresetBackground = BLK;
	sPresetName = "EMPTY_PRESET";
	bSetByUser = false;
}

// Destructor
RGBColourPresetSystem::~RGBColourPresetSystem() {
	// Display message that object destroyed
	VerbosityDisplay("RGBColourPreset Object Destroyed.\n");
}
