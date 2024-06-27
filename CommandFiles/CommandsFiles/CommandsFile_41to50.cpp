//
// CommandsFile_41to50.cpp - All command code, from command numbers 41 to 50, is here.
//

#include "Commands.h"

// Commands function - all command interfaces/start menus will go here
bool commands::Commands41To50(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer)
{
	// Notes
	if (sCommand == "notes" || sCommand == "41") {

		// Declare necessary variables
		int nChoice = 0;
		std::string sNotesText = "";
		uint64_t nNotesLine = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::NotesHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'a') {
				if (sStringDataCommandArgs[0] != "") {
					sNotesText = sStringDataCommandArgs[0];
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands41To50() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of note text argument found.\nPlease make sure that's there, and try again.\nSee \"notes -h\" for more info.\n");

					return true;
				}

				nChoice = 6;
			}
			else if (cCommandArgs[i] == 'r') {
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == true) {
						nNotesLine = std::stoull(sStringDataCommandArgs[0]) - 1;
						if (nNotesLine > NotesMain.GetCurrentNotesCount() - 1) {
							// Line number too large
							VerbosityDisplay("In commands::Commands41To50() - ERROR: String-based number argument is too large/small in correlation to number of notes currently in notes array.\n");
							UserErrorDisplay("ERROR - Line number is too large/small, and is accessing a nonexistent note line. Please change the argument, and try again.\nSee \"notes -h\" for more info.\n");

							return true;
						}
					}
					else {
						// Not a number or it is negative
						VerbosityDisplay("In commands::Commands41To50() - ERROR: Could not detect numerical value in string-based number argument, or argument was negative.\n");
						UserErrorDisplay("ERROR - Line number is not a number, or it is negative. Please change the argument, and try again.\nSee \"notes -h\" for more info.\n");

						return true;
					}
				}
				else {
					// Last note indication
					nNotesLine = NotesMain.GetCurrentNotesCount() - 1;
				}

				nChoice = 7;
			}
			else if (cCommandArgs[i] == 'm') {

				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == true) {
						nNotesLine = std::stoull(sStringDataCommandArgs[0]) - 1;
					}
					else {
						// Not a number or it is negative
						VerbosityDisplay("In commands::Commands41To50() - ERROR: Could not detect numerical value in string-based number argument, or argument was negative.\n");
						UserErrorDisplay("ERROR - Line number is not a number, or it is negative. Please change the argument, and try again.\nSee \"notes -h\" for more info.\n");

						return true;
					}
				}
				else {
					// Last note indication
					nNotesLine = NotesMain.GetCurrentNotesCount() - 1;
				}

				// Notes text
				if (sStringDataCommandArgs[1] != "") {
					sNotesText = sStringDataCommandArgs[1];
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands41To50() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of note text argument found.\nPlease make sure that's there, and try again.\nSee \"notes -h\" for more info.\n");

					return true;
				}

				nChoice = 8;
			}
			else if (cCommandArgs[i] == 'e') {
				nChoice = 1;
			}
			else if (cCommandArgs[i] == 'o') {
				nChoice = 2;
			}
			else if (cCommandArgs[i] == 'c') {
				nChoice = 3;
			}
			else if (cCommandArgs[i] == 'u') {
				nChoice = 4;
			}
			else if (cCommandArgs[i] == 'f') {
				nChoice = 5;
			}
		}

		// User Interface
		if (nChoice == 0) {
			OptionSelectEngine oseNotes;
			oseNotes.nSizeOfOptions = 5;
			std::string sOptions[] = {
				"Edit Notes",
				"Output All Notes",
				"Clear All Notes",
				"Update Memory Notes with File Notes",
				"Update File Notes with Memory Notes"
			};
			oseNotes.sOptions = sOptions;

			nChoice = oseNotes.OptionSelect("Please select what you would like to do to the current notes setup:", " ___NOTES___ ");

			if (nChoice == -1) {
				Exiting();
				return true;
			}
		}

		// Add sNotesText
		else if (nChoice == 6) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Adding new note...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			if (NotesMain.AddNoteToArray(NotesMain.GetCurrentNotesCount(), sNotesText)) {
				if (NotesMain.WriteToNotesFile()) {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "Note addition successful!\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					VerbosityDisplay("In commands::Commands41To50() - ERROR: Failed to write to notes file and save notes.\n");
					UserErrorDisplay("ERROR - Failed to save new added notes. Exiting anyway...\n");

					return true;
				}

				return true;
			}
			else {
				UserErrorDisplay("Note addition failed. Possibly a bug.\n");

				return true;
			}
		}

		// Remove nNoteLine
		else if (nChoice == 7) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Removing note...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Modify
			if (NotesMain.AddNoteToArray(nNotesLine, ""))
			{
				if (NotesMain.WriteToNotesFile()) {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "Removal successful!\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					VerbosityDisplay("In commands::Commands41To50() - ERROR: Failed to write to notes file and save notes.\n");
					UserErrorDisplay("ERROR - Failed to remove the notes from the notes file. Exiting anyway...\n");

					return true;
				}
			}
			else {
				UserErrorDisplay("Removal failed. Possibly because no notes currently exist?\n");

				return true;
			}

			return true;
		}

		// Modify note nNoteLine
		else if (nChoice == 8) {

			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Modifying note with argument text...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Modify
			if (NotesMain.AddNoteToArray(nNotesLine, sNotesText))
			{
				if (NotesMain.WriteToNotesFile()) {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "Modifying successful!\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					VerbosityDisplay("In commands::Commands41To50() - ERROR: Failed to write to notes file and save notes.\n");
					UserErrorDisplay("ERROR - Failed to save modified notes. Exiting anyway...\n");

					return true;
				}

				return true;
			}
			else {
				UserErrorDisplay("Modifying failed. Possibly the note line is too high?\n");

				return true;
			}

			return true;
		}


		/* Main User Interface parts */
		//
		// Notes Editor
		if (nChoice == 1)
		{
			NotesSystemUI NotesUI;
			NotesUI.NotesEditor();
			return true;
		}

		// Notes Viewer
		else if (nChoice == 2) {
			NotesSystemUI NotesUI;
			NotesUI.NotesViewer();
			return true;
		}

		// Clear Notes
		else if (nChoice == 3) {

			std::cout << '\n';
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			if (YesNoInput("WARNING: ALL NOTES WILL BE LOST WHEN CLEARED, BOTH ON MEMORY AND ON STORAGE.\nAre you absolutely sure you want to continue? [y for yes, n for no]: > "))
			{
				// Clear all notes - confirmed
				if (NotesMain.ClearAllNotes()) {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "All notes have been successfully cleared!\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					UserErrorDisplay("ERROR - Failed to clear notes on file, but notes on memory has been fully cleared.\nThis is an unknown error. Please try again later.\n");
				}
			}
			else {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Note-clearing cancelled.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

		}

		// Update notes array with notes file
		else if (nChoice == 4) {

			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Updating Memory Notes (Notes Array)...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			if (NotesMain.ReadFromNotesFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("Memory notes (notes array) has successfully been updated with the Notes File's contents!\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				UserErrorDisplay("ERROR - Memory notes (notes array) has failed to update with the Notes File's contents.\nSee the Verbosity Messages for more info (settings?)\n");
			}

			return true;
		}

		// Update notes file with notes array
		else if (nChoice == 5) {

			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Updating Notes File...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			if (NotesMain.WriteToNotesFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("The Notes file has successfully been updated with the Memory notes' (notes array's) contents!\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				UserErrorDisplay("ERROR - The Notes File has failed to update with the Memory notes (notes array) contents.\nSee the Verbosity Messages for more info (settings?)\n");
			}

			return true;
		}

		// Error
		else {
			VerbosityDisplay("In commands::Commands41To50() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return true;
		}
	}

	// FileParse
	else if (sCommand == "fileparse" || sCommand == "42") {
		std::string sFilePath = "";
		bool bExitOnCompletion = false;

		// Do not run command if fileparse mode is already on and running
		if (fparse::bRunningFromScriptOrArgCommand) {
			UserErrorDisplay("ERROR - FileParse is already running, and another script cannot be run while this one is running.\nPlease try again when not running from a script.\n");
			return true;
		}

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::FileParseHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'e') {
				bExitOnCompletion = true;
			}

			if (sStringOptionCommandArgs[i] == "exit") {
				bExitOnCompletion = true;
			}

			if (sStringDataCommandArgs[0] != "") {
				sFilePath = sStringDataCommandArgs[0];
			}
		}

		if (sFilePath == "") {
			CentreColouredText(" ___FILEPARSE___ ", 1);
			std::cout << '\n';

			colour(colconv::NumberToColour(RandNumld(15, 1)), ConfigObjMain.sColourGlobalBack);
			slowcharfn(true, "Welcome to FileParse!");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << wordWrap("This is where you can run scripts on ZeeTerminal, where commands can be automatically executed.\n\n");

			sFilePath = StrInput("Please input filepath for custom script (0 to exit, '*open' to open file dialogue): > ");

			// Exit on 0
			if (sFilePath == "0") {
				Exiting();
				return true;
			}
		}

		// Windows File Dialogue command
		if (sFilePath == "*open") {
			// Open with the FileOpen GUI Engine
			std::cout << "\nOpening with the Windows File Dialogue...\n";
			FileOpenGUIEngine ReadCommand;
			ReadCommand.FileOpenDialogue("Open a Script File to Execute");
			sFilePath = ReadCommand.GetRetrievedPathName();
			// Cancelled
			if (sFilePath == "") {
				Exiting();
				return true;
			}
		}

		// Initialise FileParse system
		if (!fparse::InitialiseFileParse(sFilePath, bExitOnCompletion)) {
			UserErrorDisplay("ERROR - An error occured while initialising the FileParse System. Possibly a nonexistent file path, lack of permissions or out of memory? Please try again later.\n");
			return true;
		}
		else {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Executing FileParse Script...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		fparse::bLastCommandWasFileParse = true; // because this command IS the FileParse command.
		return true;
	}

	// Disp
	else if (sCommand == "disp" || sCommand == "43") {
		bool bDispSettingChoice = false;
		bool bDispSettingChoiceArgument = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::DispHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'y') {
				bDispSettingChoiceArgument = true;
				bDispSettingChoice = true;
			}
			else if (cCommandArgs[i] == 'n') {
				bDispSettingChoiceArgument = true;
				bDispSettingChoice = false;
			}

			if (sStringOptionCommandArgs[i] == "on") {
				bDispSettingChoiceArgument = true;
				bDispSettingChoice = true;
			}
			else if (sStringOptionCommandArgs[i] == "off") {
				bDispSettingChoiceArgument = true;
				bDispSettingChoice = false;
			}
		}

		if (!bDispSettingChoiceArgument) {
			OptionSelectEngine oseDisp;
			oseDisp.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"DISP On (Default)",
				"DISP Off"
			};
			oseDisp.sOptions = sOptions;

			int nChoice = 
				oseDisp.OptionSelect("This command allows you to turn command interface output on or off.\n"
									"The command interface is the starting screen where the \"Command: > \" text is shown.\n"
									"This also, when executing scripts, disables outputting the command that is about to run.\n\n"
									"Please select what you would like to set the DISP switch to:", " ___DISP___ ");

			if (nChoice == 1) {
				bDispSettingChoice = true;
			}
			else if (nChoice == 2) {
				bDispSettingChoice = false;
			}
			else if (nChoice == -1) {
				Exiting();
				return true;
			}
			else {
				// Unknown error
				VerbosityDisplay("In commands::Commands41To50() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
				return true;
			}
		}

		// Set bDisp switch
		bDisp = bDispSettingChoice;

		// Output success message
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "DISP has successfully been switched ";
		if (bDisp == true) {
			std::cout << "on.\n";
		}
		else std::cout << "off.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// SysInfo
	else if (sCommand == "sysinfo" || sCommand == "44") {
		SystemInfo siSysInfo;

		CentreColouredText(" ___SYSINFO___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				// Execute help function, exit
				helpmsgs::SysInfoHelp();
				return true;
			}
		}

		// Display system info //
		std::cout << wordWrap("\nBelow is some system information about this computer:\n\n");

		// OS Name
		std::cout << wordWrap("OS Name: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetOSName()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		std::cout << wordWrap("OS Build Info: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetOSBuildInfo()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// System memory
		std::cout << wordWrap("Total System Memory: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(EradicateTrailingZeroes(std::to_string(siSysInfo.GetSysMemorySizeInGiB()))) << " GiB\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// System virtual memory
		std::cout << wordWrap("Total System Virtual Memory: "); 
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(EradicateTrailingZeroes(std::to_string(siSysInfo.GetSysVirtualMemorySizeInGiB()))) << " GiB\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// System page file size
		std::cout << wordWrap("System Page File Size: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(EradicateTrailingZeroes(std::to_string(siSysInfo.GetSysPageSizeInGiB()))) << " GiB\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// CPU name
		std::cout << wordWrap("CPU Model Name: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetCPUModelName()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Cpu cores
		std::cout << wordWrap("CPU Logical Core Count: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(std::to_string(siSysInfo.GetCPUCoreCount())) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Cpu architecture
		std::cout << wordWrap("CPU Architecture: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetCPUArchitectureAsName()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Lowest memory address
		std::cout << wordWrap("Lowest Accessible Memory Address: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetLowestAccessibleMemoryAddress()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Highest memory address
		std::cout << wordWrap("Highest Accessible Memory Address: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetHighestAccessibleMemoryAddress()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// Einstein
	else if (sCommand == "einstein" || sCommand == "45") {

		bool bSlowcharOutput = false;
		bool bRandColourOutput = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::EinsteinHelp();
				return true;
			}
			else if (cCommandArgs[i] == 's') {
				bSlowcharOutput = true;
			}
			else if (cCommandArgs[i] == 'c') {
				bRandColourOutput = true;
			}
		}

		// Output depending on request
		std::string sQuote = "\"" + GetEinsteinQuote(RandNumld(50, 1)) + "\"";
		if (bSlowcharOutput && bRandColourOutput) {
			SlowCharColourful(sQuote, false);
		}
		else if (bSlowcharOutput && !bRandColourOutput) {
			slowcharfn(false, sQuote);
		}
		else if (bRandColourOutput && !bSlowcharOutput) {
			RandomColourOutput(sQuote, ConfigObjMain.sColourGlobalBack);
		}
		else {
			std::cout << wordWrap(sQuote);
		}

		std::cout << "\n";
		colour(colconv::NumberToColour(RandNumld(15, 1)), ConfigObjMain.sColourGlobalBack);
		std::cout << "- Albert Einstein\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// Edison
	else if (sCommand == "edison" || sCommand == "46") {

		bool bSlowcharOutput = false;
		bool bRandColourOutput = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::EdisonHelp();
				return true;
			}
			else if (cCommandArgs[i] == 's') {
				bSlowcharOutput = true;
			}
			else if (cCommandArgs[i] == 'c') {
				bRandColourOutput = true;
			}
		}

		// Output depending on request
		std::string sQuote = "\"" + GetEdisonQuote(RandNumld(50, 1)) + "\"";
		if (bSlowcharOutput && bRandColourOutput) {
			SlowCharColourful(sQuote, false);
		}
		else if (bSlowcharOutput && !bRandColourOutput) {
			slowcharfn(false, sQuote);
		}
		else if (bRandColourOutput && !bSlowcharOutput) {
			RandomColourOutput(sQuote, ConfigObjMain.sColourGlobalBack);
		}
		else {
			std::cout << wordWrap(sQuote);
		}

		std::cout << "\n";
		colour(colconv::NumberToColour(RandNumld(15, 1)), ConfigObjMain.sColourGlobalBack);
		std::cout << "- Thomas Edison\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// Tesla
	else if (sCommand == "tesla" || sCommand == "47") {

		bool bSlowcharOutput = false;
		bool bRandColourOutput = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::TeslaHelp();
				return true;
			}
			else if (cCommandArgs[i] == 's') {
				bSlowcharOutput = true;
			}
			else if (cCommandArgs[i] == 'c') {
				bRandColourOutput = true;
			}
		}

		// Output depending on request
		std::string sQuote = "\"" + GetTeslaQuote(RandNumld(50, 1)) + "\"";
		if (bSlowcharOutput && bRandColourOutput) {
			SlowCharColourful(sQuote, false);
		}
		else if (bSlowcharOutput && !bRandColourOutput) {
			slowcharfn(false, sQuote);
		}
		else if (bRandColourOutput && !bSlowcharOutput) {
			RandomColourOutput(sQuote, ConfigObjMain.sColourGlobalBack);
		}
		else {
			std::cout << wordWrap(sQuote);
		}

		std::cout << "\n";
		colour(colconv::NumberToColour(RandNumld(15, 1)), ConfigObjMain.sColourGlobalBack);
		std::cout << "- Nikola Tesla\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// Cow
	else if (sCommand == "cow" || sCommand == "48") {

		std::string sText = "";
		std::string sRandomColour = ConfigObjMain.sColourGlobal;
		int nChoice = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::CowHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'c') {
				sRandomColour = colconv::NumberToColour(RandNumld(16, 1));
			}
			else if (cCommandArgs[i] == 'o') {
				nChoice = 1;
			}

			if (sStringOptionCommandArgs[i] == "quote") {
				nChoice = 2;
			}
			else if (sStringOptionCommandArgs[i] == "saytext") {
				if (sStringDataCommandArgs[i] == "") {
					VerbosityDisplay("ERROR: In commands::Commands41To50() - Could not detect any argument string after option.\n");
					UserErrorDisplay("ERROR - No text data argument found. Please check for a text argument, and try again.\nType \"cow -h\" for more info.\n");
					return true;
				}
				else {
					sText = sStringDataCommandArgs[i];
					nChoice = 3;
				}
			}
		}

		if (nChoice == 0) {
			OptionSelectEngine oseAnimal;
			oseAnimal.nSizeOfOptions = 3;
			std::string sOptions[] = {
				"Output cow",
				"Output cow with quote",
				"Output cow with custom text"
			};
			oseAnimal.sOptions = sOptions;

			nChoice = oseAnimal.OptionSelect("Please select how you would like to output a cow:", " ___COW___ ");
		}

		if (nChoice == 1) {
			OutputCow("", sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 2) {
			int nRandQuoteSet = std::roundl(RandNumld(2, 0));
			if (nRandQuoteSet == 2) {
				sText = GetTeslaQuote(RandNumld(50, 1));
			}
			else if (nRandQuoteSet == 1) {
				sText = GetEdisonQuote(RandNumld(50, 1));
			}
			else if (nRandQuoteSet == 0) {
				sText = GetEinsteinQuote(RandNumld(50, 1));
			}

			OutputCow(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 3) {
			if (sText == "") {
				sText = StrInput("Please input desired custom text for the cow to output: > ");
			}

			OutputCow(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == -1) {
			Exiting();
			return true;
		}
		else {
			VerbosityDisplay("In commands::Commands41To50() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		}

		return true;
	}

	// Cat
	else if (sCommand == "cat" || sCommand == "49") {
		std::string sText = "";
		std::string sRandomColour = ConfigObjMain.sColourGlobal;
		int nChoice = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::CatHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'c') {
				sRandomColour = colconv::NumberToColour(RandNumld(16, 1));
			}
			else if (cCommandArgs[i] == 'o') {
				nChoice = 1;
			}

			if (sStringOptionCommandArgs[i] == "quote") {
				nChoice = 2;
			}
			else if (sStringOptionCommandArgs[i] == "saytext") {
				if (sStringDataCommandArgs[i] == "") {
					VerbosityDisplay("ERROR: In commands::Commands41To50() - Could not detect any argument string after option.\n");
					UserErrorDisplay("ERROR - No text data argument found. Please check for a text argument, and try again.\nType \"cat -h\" for more info.\n");
					return true;
				}
				else {
					sText = sStringDataCommandArgs[i];
					nChoice = 3;
				}
			}
		}

		if (nChoice == 0) {
			OptionSelectEngine oseAnimal;
			oseAnimal.nSizeOfOptions = 3;
			std::string sOptions[] = {
				"Output cat",
				"Output cat with quote",
				"Output cat with custom text"
			};
			oseAnimal.sOptions = sOptions;

			nChoice = oseAnimal.OptionSelect("Please select how you would like to output a cat:", " ___CAT___ ");
		}

		if (nChoice == 1) {
			OutputCat("", sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 2) {
			int nRandQuoteSet = std::roundl(RandNumld(2, 0));
			if (nRandQuoteSet == 2) {
				sText = GetTeslaQuote(RandNumld(50, 1));
			}
			else if (nRandQuoteSet == 1) {
				sText = GetEdisonQuote(RandNumld(50, 1));
			}
			else if (nRandQuoteSet == 0) {
				sText = GetEinsteinQuote(RandNumld(50, 1));
			}

			OutputCat(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 3) {
			if (sText == "") {
				sText = StrInput("Please input desired custom text for the cat to output: > ");
			}

			OutputCat(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == -1) {
			Exiting();
			return true;
		}
		else {
			VerbosityDisplay("In commands::Commands41To50() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		}

		return true;
	}
	   
	// Bunny
	else if (sCommand == "bunny" || sCommand == "50") {
		std::string sText = "";
		std::string sRandomColour = ConfigObjMain.sColourGlobal;
		int nChoice = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::BunnyHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'c') {
				sRandomColour = colconv::NumberToColour(RandNumld(16, 1));
			}
			else if (cCommandArgs[i] == 'o') {
				nChoice = 1;
			}

			if (sStringOptionCommandArgs[i] == "quote") {
				nChoice = 2;
			}
			else if (sStringOptionCommandArgs[i] == "saytext") {
				if (sStringDataCommandArgs[i] == "") {
					VerbosityDisplay("ERROR: In commands::Commands41To50() - Could not detect any argument string after option.\n");
					UserErrorDisplay("ERROR - No text data argument found. Please check for a text argument, and try again.\nType \"bunny -h\" for more info.\n");
					return true;
				}
				else {
					sText = sStringDataCommandArgs[i];
					nChoice = 3;
				}
			}
		}

		if (nChoice == 0) {
			OptionSelectEngine oseAnimal;
			oseAnimal.nSizeOfOptions = 3;
			std::string sOptions[] = {
				"Output bunny",
				"Output bunny with quote",
				"Output bunny with custom text"
			};
			oseAnimal.sOptions = sOptions;

			nChoice = oseAnimal.OptionSelect("Please select how you would like to output a bunny:", " ___BUNNY___ ");
		}

		if (nChoice == 1) {
			OutputBunny("", sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 2) {
			int nRandQuoteSet = std::roundl(RandNumld(2, 0));
			if (nRandQuoteSet == 2) {
				sText = GetTeslaQuote(RandNumld(50, 1));
			}
			else if (nRandQuoteSet == 1) {
				sText = GetEdisonQuote(RandNumld(50, 1));
			}
			else if (nRandQuoteSet == 0) {
				sText = GetEinsteinQuote(RandNumld(50, 1));
			}

			OutputBunny(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 3) {
			if (sText == "") {
				sText = StrInput("Please input desired custom text for the bunny to output: > ");
			}

			OutputBunny(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == -1) {
			Exiting();
			return true;
		}
		else {
			VerbosityDisplay("In commands::Commands41To50() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		}

		return true;
	}
	else return false;

	return true;
}
