//
// CommandsFile.cpp - All command code is here.
//

#pragma comment(lib, "powrprof.lib") // To access power profile libs

// Debug/release RyRyCryptor libs
#ifdef _DEBUG
#pragma comment(lib, "RyRyCryptor/Debug/RyRyCryptor.lib")
#else
#pragma comment(lib, "RyRyCryptor/Release/RyRyCryptor.lib")
#endif // _DEBUG

#include "..\Core\ZeeTerminalCore.h"
#include "..\Engine\ScreenNavigateEngine\ScreenNavigateEngine.h"
#include "..\Engine\SystemInfo\SystemInfo.h"
#include "..\Engine\TableEngine\TableEngine.h"
#include "..\Engine\MemoryTestEngine\MemoryTestEngine.h"
#include "..\Engine\MultimediaEngine\MultimediaEngine.h"
#include "..\Engine\NotesSystem\NotesSystem.h"
#include "..\Engine\OptionSelectEngine\OptionSelectEngine.h"
#include "..\Engine\FileOpenGUIEngine\FileOpenGUIEngine.h"
#include "..\Engine\FileParse-System\FileParse-System.h"
#include "..\RyRyCryptor\RyRyCryptor.h"
#include "CommandFileAssets.cpp"
#include "Settings.cpp"
#include "CPUStress.cpp"
#include "CommandHelpMessages.cpp"
#include "CalculationAlgorithm/CalculationAlgorithm.h"
#include "../GameFiles/CarDodge/CarDodge.cpp"
#include "../GameFiles/GuessTheNumber/GuessTheNumber.h"
#include "../GameFiles/GuessTheNumberExtreme/GuessTheNumberExtreme.h"

#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <filesystem>
#include <powrprof.h>


// External variable definitions
extern std::string				sCommandInputRAW;
extern std::string				sStringOptionCommandArgs[nArgArraySize]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
// on multi-argument commands.
extern std::string				sStringDataCommandArgs[nArgArraySize]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
// on multi-argument commands.
extern RGBColourPresetSystem	RGBPreset[3];
extern ConfigFileSystem			ConfigObjMain;
extern NotesSystem				NotesMain;
extern LogFileSystem			LogFileMain;
extern bool						bAnsiVTSequences;
extern bool						bDisp;

extern uint64_t					nNumOfInputtedCommands;
extern uint64_t					nNumOfSuccessfulInputtedCommands;

// Include commands namespace
#include "CommandsFiles\Commands.h"
#include "CommandsFiles\CommandsFile_1to10.cpp"
#include "CommandsFiles\CommandsFile_11to20.cpp"
#include "CommandsFiles\CommandsFile_21to30.cpp"
#include "CommandsFiles\CommandsFile_31to40.cpp"
#include "CommandsFiles\CommandsFile_41to50.cpp"
#include "CommandsFiles\CommandsFile_51to60.cpp"


// Commands function - all command interfaces/start menus will go here
void Commands(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer = "") 
{
	// Before checking commands, check for anything other than a command
	if (sCommand[0] == '#') return;

	// Move one-by-one through all command functions until command is reached and executed or until all command functions have been checked
	if (!commands::Commands1To10(sCommand, cCommandArgs, sCommandArgsBuffer)
		&& !commands::Commands11To20(sCommand, cCommandArgs, sCommandArgsBuffer)
		&& !commands::Commands21To30(sCommand, cCommandArgs, sCommandArgsBuffer)
		&& !commands::Commands31To40(sCommand, cCommandArgs, sCommandArgsBuffer)
		&& !commands::Commands41To50(sCommand, cCommandArgs, sCommandArgsBuffer)
		&& !commands::Commands51To60(sCommand, cCommandArgs, sCommandArgsBuffer)
		)
	{
		// Unknown command - fail
		colour(RED, ConfigObjMain.sColourGlobalBack);
		std::cout << "Unknown command ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\"' << sCommandInputRAW << "\"";
		colour(LRED, ConfigObjMain.sColourGlobalBack);
		std::cout << ".\nPlease make sure you have inputted a listed command, and try again.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Log the failed command if enabled
		if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bCommandInputInfoLogging) {
			LogFileMain.AddLogLine("Command execution [" + sCommand + "] failed. Command invalid or not found.", 3);
		}

		// Decrement number of successful commands, as it would have been incremented before entering this function
		nNumOfSuccessfulInputtedCommands--;
		return;
	}
	else {
		return; // Nothing needed - return back normally
	}
}
