#pragma once

// Include
#include "ZTConstDefinitions.h"
#include "ZTFormattingDefinitions.h"
#include "..\Engine\ConfigFile-System\ConfigFile-System.h"
#include "..\Engine\LogFile-System\LogFile-System.h"
#include "..\Engine\RGBColourPresetSystem\RGBColourPresetSystem.h"
#include "..\Engine\TerminalDefaultAttributes\TerminalDefaultAttributes.h"
#include "..\Engine\NotesSystem\NotesSystem.h"

// Other Libraries
#include <vector>
#include <iostream>

// Declare all core ZeeTerminal global variables
extern bool					bAnsiVTSequences;
extern bool					bConfigAndLogSystemsInitialised; // Switch to symbolise that the config and log systems have been initialised
extern bool					bDisp; // Switch for showing the start command screen ("Command: > "), similar to CMD's @echo off. 
extern std::string				sCommandInputRAW;
extern std::string				sStringOptionCommandArgs[]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
// on multi-argument commands.
extern std::string				sStringDataCommandArgs[]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
// on multi-argument commands.
extern uint64_t				nNumOfInputtedCommands; // Counter for number of inputted commands since the start of the ZeeTerminal session.
extern uint64_t				nNumOfSuccessfulInputtedCommands; // Counter for number of successful inputted commands since the start of the ZeeTerminal session.

extern std::string				sLastColourFore; // Last set colour of any kind - foreground
extern std::string				sLastColourBack; // Last set colour of any kind - background

extern bool bToFileFeatureActivated; // ToFile feature

extern TerminalDefaultAttributes	DefaultAttributesObj;
extern RGBColourPresetSystem	RGBPreset[3]; // Possibly [5] in a future update?
extern ConfigFileSystem		ConfigObjMain; // Configuration Object
extern LogFileSystem			LogFileMain; // LogFile System Object
extern NotesSystem				NotesMain; // Notes Object

namespace zt {

	// All common platform function definitions - done to prevent the need for defining them in every file
	std::string wordWrap(std::string, long long int = -1, long long int = 0);
	void SetCursorAttributes();

	// Function that hides console cursor and returns value of previous setting to set later.
	// Commonly used for progress bars to prevent cursor flickering
	//
	inline bool DisableCursorVisibility() {
		bool bPreviousSetting = ConfigObjMain.bShowCursor;

		// Set to FALSE and write cursor attributes
		ConfigObjMain.bShowCursor = false;
		SetCursorAttributes();

		// Return previous setting in case user wants to put back to normal
		return bPreviousSetting;
	}

	void colour(std::string, std::string);

	// colourHighlight - Sets the colour from value inside nColourHighlight(Back).
	inline void colourHighlight()
	{
		// Use the default colour function; custom solution not needed
		colour(ConfigObjMain.sColourHighlight, ConfigObjMain.sColourHighlightBack);
		return;
	}

	// Be sure to change back to no underline AND no bold when done
	inline void colourTitle()
	{
		// Use the default colour function; custom solution not needed
		colour(ConfigObjMain.sColourTitle, ConfigObjMain.sColourTitleBack);
		if (bAnsiVTSequences) std::cout << "\x1b[" << ULINE << "m";

		return;
	}

	// Be sure to change back to no underline when done
	inline void colourSubheading()
	{
		// Use the default colour function; custom solution not needed
		colour(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack);
		if (bAnsiVTSequences) std::cout << "\x1b[" << ULINE << "m";

		return;
	}

	inline void sleep(long long int);
	long double RandNumld(long double max, long double min);
	int64_t RandNumll(int64_t max, int64_t min);
	bool LogWindowsEvent(std::vector<std::string>, DWORD, LPVOID);
	void OutputBoxWithText(std::string sText, std::string, std::string, std::string, std::string, bool = false);
	std::string ws2s(const std::wstring& wstr);
	std::wstring s2ws(const std::string& str);
	std::string BoolToString(bool);
	bool isNumberld(const std::string sNumberTest);
	bool isNumberll(const std::string sNumberTest);
	bool isNumberl(const std::string sNumberTest);
	bool isNumberi(const std::string sNumberTest, bool bSetErrorsAsVerbose = true);
	bool isNumberull(const std::string sNumberTest);
	bool isNumberul(const std::string sNumberTest);
	void ClearKeyboardBuffer();
	inline void SetCursorPosition(int x, int y);
	void DirectionsDisplay(std::string sPrompt, bool = false);
	void VerbosityDisplay(std::string sPrompt, int nObjectID = 10000, bool bForceDontDisplayMessage = false, bool bForceDontLog = false);

	// Function to display error messages at specific times
	inline void UserErrorDisplay(std::string sError, int nObjectID = 10000) {

		// Output user-space error in red text with word wrapping
		colour(RED, ConfigObjMain.sColourGlobalBack);
		std::cerr << wordWrap(sError);
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserSpaceErrorLogging) {
			LogFileMain.AddLogLine(sError, 2, nObjectID);
		}

		return;
	}

	long double NumInputld(std::string sPrompt);
	long long int NumInputll(std::string sPrompt);
	long int NumInputl(std::string sPrompt);
	int NumInputi(std::string sPrompt);
	uint64_t PositiveNumInputull(std::string sPrompt);
	unsigned long int PositiveNumInputul(std::string sPrompt);
	std::string StrInput(std::string sPrompt);
	bool YesNoInput(std::string sPrompt);
	bool SetWindowTitle(std::string sTitle);
	void cls();
	void RandomColourOutput(std::string sText, std::string sBackgroundColour);
	void CentreColouredText(std::string sText, short int nTypeOfText);
	std::string CentreText(std::string sText);
	void slowcharCentredFn(bool bNewLine, std::string sText);
	void slowcolourfn(std::string nColourFore, std::string nColourBack, std::string sSlowchar);
	void slowcharfn(bool nline, std::string sSlowchar);
	void SlowCharColourful(std::string sText, bool bIncludeBackground);

	// A function to display an exiting message without typing too much.
	inline void Exiting() {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nExiting...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}

	// A function designated for resetting the global colours.
	inline void ResetColour()
	{
		// Reset all RGB to default
		ConfigObjMain.sColourGlobal = LWHT;
		ConfigObjMain.sColourGlobalBack = BLK;

		// Optional reset-everything command for ANSI VT Sequence-supporting terminals
		if (bAnsiVTSequences) {
			std::cout << "\x1b[" << RESETALL << "m";
		}

		// Output reset message with default colours
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nColours have been reset to default.\n";

		return;
	}

	bool EnableVTMode();
	bool EnableShutdownPrivileges();
	bool CheckIfCursorExceedScreenBufferHeight();
	void ColourTypeSwitch();

	// Colour conversion/adaptor functions namespace
	// colour() is not a converter/adaptor, which is why it's not in this namespace
	namespace colconv {
		std::string NumberToColour(int);
		int ColourToNumber(std::string);
		std::string ColourToLogicalDisplayName(std::string);
		std::string Win32ToAnsiColours(std::string);
		std::string AnsiToWin32Colours(std::string);
		bool ValidateColourStringsWin32();
		bool VerifyANSIColourString(std::string);
		bool ValidateColourStringsANSI();
	}

}

using namespace zt;