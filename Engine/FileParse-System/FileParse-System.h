#pragma once
//
// FileParse-System.h - Interface namespace for the FileParse system.
//
#include <vector>
#include <string>

namespace fparse {
	// FileParse runtime variables
	extern std::vector<std::string> vsFileParseCommands;
	extern bool                     bRunningFromScriptOrArgCommand; // Sets the scripting mode. Can affect UI elements and some specific commands. FALSE is no scripting/argcommand, TRUE is otherwise.
	extern bool                     bExitOnScriptCompletion;
	extern bool                     bLastCommandWasFileParse; // Switch that gets set to TRUE if FileParse is activated from a user-entered command.

	// Functions

	// UninitialiseFileParse - Stop all FileParse operations, clear the command string vector and set all switches/variables to default.
	// There are no arguments or return values.
	//
	void UninitialiseFileParse();

	// InitialiseFileParse - Initialises the FileParse System.
	//                     - This function checks the file path validity, then parses the lines from the file and puts them into a string vector.
	//                     - Some global boolean values are set, and then exits.
	// Arguments: sFilePath - The filepath to the script.
	//            bExitOnCompletionParam - Exit on script completion. TRUE/1 for yes, FALSE/0 for no.
	// Return value: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool InitialiseFileParse(std::string sFilePath, bool bExitOnCompletionParam);
}
