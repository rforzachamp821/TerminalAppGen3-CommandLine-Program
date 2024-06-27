//
// FileParse-System.cpp - Responsible for housing the variables and functions associated with the FileParse system.
//
#include "FileParse-System.h"
#include <fstream>
#include "../../Core/ZeeTerminalCore.h"


namespace fparse {
	// FileParse runtime variables
	std::vector<std::string> vsFileParseCommands;
	bool                     bRunningFromScriptOrArgCommand = false; // Sets the scripting mode. Can affect UI elements and some specific commands. FALSE is no scripting/argcommand, TRUE is otherwise.
	bool                     bExitOnScriptCompletion = false;
	bool                     bLastCommandWasFileParse = false; // Switch that gets set to TRUE if FileParse is activated from a user-entered command.

	// Functions

	// UninitialiseFileParse
	void UninitialiseFileParse() {

		// Clear the command string vector
		vsFileParseCommands.clear();

		// Set all switches/variables to default
		bRunningFromScriptOrArgCommand = false;
		bExitOnScriptCompletion = false;

		// exit and return
		return;
	}

	// InitialiseFileParse
	bool InitialiseFileParse(std::string sFilePath, bool bExitOnCompletionParam)
	{
		// Before anything, check for speechmarks and remove them
		if (sFilePath[0] == '"' && sFilePath[sFilePath.length() - 1] == '"') {
			sFilePath = sFilePath.substr(1, (sFilePath.length() - 2));
		}
		else sFilePath = sFilePath;

		// 1. Open test file stream
		std::ifstream LineParseTest(sFilePath);

		// 2. Check file stream
		if (LineParseTest.fail()) {
			VerbosityDisplay("In InitialiseFileParse(): ERROR - Failed to initialise FileParse System due to bad file path, lack of permissions or out of memory.\n");
			LineParseTest.close();
			UninitialiseFileParse();
			return false;
		}

		// 3. All is good - close test stream and open main stream
		LineParseTest.close();
		std::ifstream LineParseIn(sFilePath);

		// 4. In a loop, get all lines and parse them into string vector
		std::string sLineBuffer = "";
		while (!LineParseIn.eof())
		{
			// Clear sLineBuffer for next run
			sLineBuffer = "";

			// Exit on fail()
			if (LineParseIn.fail()) {
				VerbosityDisplay("In InitialiseFileParse(): ERROR - Failed to initialise FileParse System due to unknown error while parsing lines (possibly lost access to script file).\n");
				LineParseIn.close();
				UninitialiseFileParse();
				return false;
			}

			std::getline(LineParseIn, sLineBuffer, '\n');

			// Ignore all spaces and tabs by removing them in for loops
			for (;;) {
				if (sLineBuffer[0] == '\t') {
					sLineBuffer.erase(0, 1);
				}
				else break;
			}

			for (;;) {
				if (sLineBuffer[0] == ' ') {
					sLineBuffer.erase(0, 1);
				}
				else break;
			}

			// Then, check if the line is empty after all that. If so, skip string pushback
			if (sLineBuffer.length() <= 0) continue;

			// Then, check if the line is a comment (denoted by #). If so, skip string pushback
			if (sLineBuffer[0] == '#') continue;

			// Push back string
			vsFileParseCommands.push_back(sLineBuffer);
		}

		// 5. Set indicator booleans to indicate that FileParse is being used.
		bRunningFromScriptOrArgCommand = true;
		bExitOnScriptCompletion = bExitOnCompletionParam;

		// 7. Exit and post true
		LineParseIn.close();
		return true;
	}
}
