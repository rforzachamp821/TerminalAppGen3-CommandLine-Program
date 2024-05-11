//
// CommandsFile_21to30.cpp - All command code, from command numbers 21 to 30, is here.
//

#include "Commands.h"

// Commands function - all command interfaces/start menus will go here
bool commands::Commands21To30(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer)
{
	// Copy
	if (sCommand == "copy" || sCommand == "21") {

		int nFlagOverwrite = static_cast<int>(std::filesystem::copy_options::none);
		int nFlagDirectoryCopy = static_cast<int>(std::filesystem::copy_options::none);
		std::string sFileToCopyPath = "";
		std::string sDestinationPath = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::CopyHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'o') {
				nFlagOverwrite = static_cast<int>(std::filesystem::copy_options::overwrite_existing);
			}
			else if (cCommandArgs[i] == 'd') {
				nFlagDirectoryCopy = static_cast<int>(std::filesystem::copy_options::recursive);
			}

			if (sStringDataCommandArgs[0] != "") {
				if (sStringDataCommandArgs[1] == "") {
					// Error message
					VerbosityDisplay("In Commands() - ERROR: Vital argument not found.\n");
					UserErrorDisplay("ERROR: You need to have both the file location AND destination file directories included in your arguments.\nSee \"copy -h\" for more info.\n");

					return true;
				}

				sFileToCopyPath = sStringDataCommandArgs[0];
				sDestinationPath = sStringDataCommandArgs[1];
			}
		}

		// User Interface for filepath
		if (sFileToCopyPath == "") {
			CentreColouredText(" ___COPY___ ", 1);
			std::cout << wordWrap("\nThis command copies files or folder contents recursively, from one location to another destination location.\n");
			colour(LBLU, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Input 0 to exit, and \"*open\" without quotes to use the Windows File Dialogue.\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			sFileToCopyPath = StrInput("Please input the path to the file/folder that is to be copied: > ");
			if (sFileToCopyPath == "0") {
				Exiting();
				return true;
			}
		}

		if (sFileToCopyPath == "*open") {
			// Use the Windows File Dialogue
			std::cout << wordWrap("Opening the Windows File Dialogue Box...\n");
			FileOpenGUIEngine FileCopyDialogue;
			FileCopyDialogue.FileOpenDialogue(nFlagDirectoryCopy == 0 ? "Select a File To Copy" : "Select a Folder to Copy Contents From", (bool)nFlagDirectoryCopy);
			sFileToCopyPath = FileCopyDialogue.GetRetrievedPathName();
			if (sFileToCopyPath == "") {
				Exiting();
				return true;
			}
		}

		// User Interface for destination path
		if (sDestinationPath == "") {
			sDestinationPath = StrInput("Please input the path to the directory to copy the file(s) to: > ");
			if (sDestinationPath == "0") {
				Exiting();
				return true;
			}
		}

		if (sDestinationPath == "*open") {
			// Use the Windows File Dialogue
			std::cout << wordWrap("Opening the Windows File Dialogue Box...\n");
			FileOpenGUIEngine FileCopyDialogue;
			FileCopyDialogue.FileOpenDialogue("Select the Destination Path for File Copy", true);
			sDestinationPath = FileCopyDialogue.GetRetrievedPathName();
			if (sDestinationPath == "") {
				Exiting();
				return true;
			}
		}

		// Remove quotes if there are any, in case of copy from File Explorer
		// In other words, check for any speechmarks that might accidentally get passed to copy operation
		if (sFileToCopyPath[0] == '\"') {
			size_t nFirstMarkPos = sFileToCopyPath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sFileToCopyPath.find('\"', nFirstMarkPos) - 1;
			sFileToCopyPath = sFileToCopyPath.substr(nFirstMarkPos, nFinalMarkPos);
		}
		if (sDestinationPath[0] == '\"') {
			size_t nFirstMarkPos = sDestinationPath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sDestinationPath.find('\"', nFirstMarkPos) - 1;
			sDestinationPath = sDestinationPath.substr(nFirstMarkPos, nFinalMarkPos);
		}

		// Copy files/folder contents
		std::cout << wordWrap("\nCopying file(s)...\n");
		std::error_code ecTestZone;
		try {
			std::filesystem::copy_options CopyOptions = static_cast<std::filesystem::copy_options>(nFlagOverwrite) | static_cast<std::filesystem::copy_options>(nFlagDirectoryCopy);
			std::filesystem::copy(sFileToCopyPath, sDestinationPath, CopyOptions, ecTestZone);
		}
		
		// Catch bad memory allocation to avoid exception
		catch (const std::bad_alloc&) {
			VerbosityDisplay("In Commands(): ERROR - Memory allocation failed when copying using std::filesystem::copy (std::bad_alloc).\n");
			UserErrorDisplay("ERROR - Failed to allocate memory before copy operation. Please try again later.\n");

			return true;
		}

		// Error codes output
		if (ecTestZone.value() != 0) {
			if (ecTestZone == std::errc::file_exists) {
				VerbosityDisplay("In Commands(): ERROR - File exists in the destination location already. -o flag not specified, so copy failed. STDC++ error details: " + ecTestZone.message() + " (std::errc::file_exists).\n");
				UserErrorDisplay("Sorry, but the file exists in the copy location already. Please try again later.\n");
			}
			else if (ecTestZone == std::errc::permission_denied) {
				VerbosityDisplay("In Commands(): ERROR - No sufficient permissions available for file access. STDC++ error details: " + ecTestZone.message() + " (std::errc::permission_denied).\n");
				UserErrorDisplay("Sorry, but there aren't any sufficient permissions to access the file. Please try again with elevated permissions.\n");
			}
			else if (ecTestZone == std::errc::is_a_directory) {
				VerbosityDisplay("In Commands(): ERROR - Source argument is a directory, and -d flag not specified, so copy failed. STDC++ error details: " + ecTestZone.message() + " (std::errc::is_a_directory).\n");
				UserErrorDisplay("Sorry, but the specified source argument is a directory, not a file.\nIf you want to copy the contents of a directory, use the -d argument.\nPlease try again later.\n");
			}
			else if (ecTestZone == std::errc::io_error) {
				VerbosityDisplay("In Commands(): ERROR - Unknown I/O error occured when copying. STDC++ error details: " + ecTestZone.message() + " (std::errc::io_error).\n");
				UserErrorDisplay("Sorry, but an unknown I/O error occured when copying.\nThis could possibly relate to losing access to the source file or destination directory, or even a hardware error.\nPlease try again later.\n");
			}
			else if (ecTestZone == std::errc::no_such_file_or_directory) {
				VerbosityDisplay("In Commands(): ERROR - No such file or directory exists in either the source or destination argument paths. STDC++ error details: " + ecTestZone.message() + " (std::errc::no_such_file_or_directory).\n");
				UserErrorDisplay("Sorry, but the specified source filepath or destination directory path does not exist.\nPlease check the specified arguments and try again later.\n");
			}
			else {
				// Unknown error
				VerbosityDisplay("In Commands(): ERROR - Unknown error when copying file. STDC++ error details: " + ecTestZone.message() + " (Error Code " + std::to_string(ecTestZone.value()) + ").\n");
				UserErrorDisplay("Sorry, but an unknown error of code " + std::to_string(ecTestZone.value()) + " occured when copying. Please try again later.\n");
			}
		}
		else {
			// Copy operation success message
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Copy operation successful!\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
	
		return true;
	}

	// CopyFile
	else if (sCommand == "copyfile" || sCommand == "22") {

		std::string sOriginalFilePath = "";
		std::string sDestinationFilePath = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::CopyFileHelp();
				return true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				if (sStringDataCommandArgs[1] != "") {
					sOriginalFilePath = sStringDataCommandArgs[0];
					sDestinationFilePath = sStringDataCommandArgs[1];
				}
				else {
					// Error message
					VerbosityDisplay("In Commands() - ERROR: Vital argument not found.\n");
					UserErrorDisplay("ERROR: You need to have both the file location AND destination file directories included in your arguments.\nSee \"copyfile -h\" for more info.\n");
					
					return true;
				}
			}
		}
		
		// Output title when user input
		if (sOriginalFilePath == "" || sDestinationFilePath == "") {
			CentreColouredText(" ___COPYFILE___ ", 1);
			std::cout << "\n\n";
			colour(LBLU, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Type \"*open\" without quotes to use the Windows File Dialogue to find necessary copy files.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Prompts
		if (sOriginalFilePath == "") {
			sOriginalFilePath = StrInput("Please input directory of original file (0 to exit): > ");
			if (sOriginalFilePath == "0") {
				Exiting();
				return true;
			}
		}

		if (sOriginalFilePath == "*open") {
			// Use the Windows File Dialogue
			std::cout << wordWrap("Opening the Windows File Dialogue Box...\n");
			FileOpenGUIEngine FileCopyDialogue;
			FileCopyDialogue.FileOpenDialogue("Select a File to Copy Contents From");
			sOriginalFilePath = FileCopyDialogue.GetRetrievedPathName();
			if (sOriginalFilePath == "") {
				Exiting();
				return true;
			}
		}

		if (sDestinationFilePath == "") {
			sDestinationFilePath = StrInput("Please input directory of new destination file (0 to exit): > ");
			if (sDestinationFilePath == "0") {
				Exiting();
				return true;
			}
		}

		if (sDestinationFilePath == "*open") {
			// Use the Windows File Dialogue
			std::cout << wordWrap("Opening the Windows File Dialogue Box...\n");
			FileOpenGUIEngine FileCopyDialogue;
			FileCopyDialogue.FileOpenDialogue("Select a File to Copy Contents From");
			sDestinationFilePath = FileCopyDialogue.GetRetrievedPathName();
			if (sDestinationFilePath == "") {
				Exiting();
				return true;
			}
		}

		// Check for any speechmarks that might accidentally get passed to copy operation
		if (sOriginalFilePath[0] == '\"') {
			size_t nFirstMarkPos = sOriginalFilePath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sOriginalFilePath.find('\"', nFirstMarkPos) - 1;
			sOriginalFilePath = sOriginalFilePath.substr(nFirstMarkPos, nFinalMarkPos);
		}
		if (sDestinationFilePath[0] == '\"') {
			size_t nFirstMarkPos = sDestinationFilePath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sDestinationFilePath.find('\"', nFirstMarkPos) - 1;
			sDestinationFilePath = sDestinationFilePath.substr(nFirstMarkPos, nFinalMarkPos);
		}

		// Copy file
		VerbosityDisplay("Copying file " + sOriginalFilePath + " to " + sDestinationFilePath + "...");
		std::cout << "Copying file...\n";
		if (!CopyFileA(sOriginalFilePath.c_str(), sDestinationFilePath.c_str(), false)) {
			VerbosityDisplay("In Commands() - ERROR: Existing file when copying to file directory detected. File copy operation has failed. GetLastError() error code: " + std::to_string(GetLastError()) + "\n");
			UserErrorDisplay("An error occured while copying the file.\nPossibly the original file is nonexistent?\n");
		}
		else {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("File successfully copied!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return true;
	}

	// TextInfo
	else if (sCommand == "textinfo" || sCommand == "23") {
		std::string sText = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::TextInfoHelp();
				return true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				// Assign sText to sStringDataCommandArgs[0] to be used after the argument checking
				sText = sStringDataCommandArgs[0];
			}
		}

		// if not assigned by argument
		if (sText == "") {
			CentreColouredText(" ___TEXTINFO___ ", 1);
			std::cout << "\n\n";

			sText = StrInput("Please input the text string for the info (0 to exit): > ");
			if (sText == "0") {
				// Exit
				Exiting();
				return true;
			}
		}
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nReading text and finalising data...\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		//
		// Check string for spaces, '.', and so on
		//

		int nNumOfWords = 0, nNumOfSentences = 0, nNumOfLetters = 0;
		// Add a space so the last word gets counted
		sText += ' ';

		// Count spaces, words, sentences
		for (int i = 0; i < sText.length(); i++) {
			// Spaces/Words
			if (sText[i] == ' ') {
				if (i - 1 > 0) {
					if (sText[i - 1] != ' ') nNumOfWords++;
				}
			}
			// Sentences
			else if (sText[i] == '.' || sText[i] == '?' || sText[i] == '!') nNumOfSentences++;
			// Letters
			else if (std::isalpha(sText[i])) nNumOfLetters++;
		}
		if (nNumOfSentences == 0) nNumOfSentences++; // because technically, it's one sentence

		// Display results
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\n\nNumber of characters: ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << sText.length() - 1 << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Number of letters: ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nNumOfLetters << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Number of words: ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nNumOfWords << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Number of sentences: ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nNumOfSentences << "\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// ConfigAction
	else if (sCommand == "configaction" || sCommand == "24") {
		int nOption = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++)
		{
			if (cCommandArgs[i] == 'h') 
			{
				helpmsgs::ConfigActionHelp();
				return true;
			}
			else if (sStringOptionCommandArgs[0] == "readconfigfile") {
				nOption = 1;
			}
			else if (sStringOptionCommandArgs[0] == "writeconfigfile") {
				nOption = 2;
			}
			else if (sStringOptionCommandArgs[0] == "createconfigfile") {
				nOption = 3;
			}
			else if (sStringOptionCommandArgs[0] == "displayconfigobj") {
				nOption = 4;
			}
			else if (sStringOptionCommandArgs[0] == "displayconfigfile") {
				nOption = 5;
			}
		}

		// User-end UI if no arguments used
		if (nOption == 0) {
			OptionSelectEngine oseConfigAction;
			oseConfigAction.nSizeOfOptions = 5;
			std::string sOptions[] = {
				"Read from Configuration File to Memory",
				"Write from Memory to Configuration File",
				"Create new Configuration File",
				"Display Main Configuration Object Contents",
				"Display Configuration File Contents"
			};
			oseConfigAction.sOptions = sOptions;

			nOption = oseConfigAction.OptionSelect("Please select what you would like to interact with in the Configuration File System:", " ___CONFIGACTION___ ");
		}

		switch (nOption) {
		case 1:
			if (ConfigObjMain.ReadConfigFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Function has returned TRUE. No error has occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				colour(RED, ConfigObjMain.sColourGlobalBack);
				std::cerr << "Function has returned FALSE. An error occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

			break;

		case 2:
			if (ConfigObjMain.WriteConfigFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Function has returned TRUE. No error has occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				colour(RED, ConfigObjMain.sColourGlobalBack);
				std::cerr << "Function has returned FALSE. An error occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

			break;

		case 3:
			if (ConfigObjMain.CreateConfigFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Function has returned TRUE. No error has occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				colour(RED, ConfigObjMain.sColourGlobalBack);
				std::cerr << "Function has returned FALSE. An error occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

			break;

		case 4:
			std::cout << '\n';
			colourSubheading();
			std::cout << "Contents of Main Configuration Object:" << NOULINE_STR;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\n" << ConfigObjMain.GetConfigObjectContents() << '\n';

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Main configuration object contents output complete!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			break;

		case 5:
			std::cout << '\n';
			colourSubheading();
			std::cout << "Contents of Configuration File:" << NOULINE_STR;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\n" << ConfigObjMain.GetConfigFileContents();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Configuration file contents output complete!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			break;

		case -1:
			Exiting();
			return true;

		default:
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
			break;
		}

		return true;
	}

	// BeepSounds
	else if (sCommand == "beepsounds" || sCommand == "25") {
		bool bArgumentExecuted = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::BeepSoundsHelp();
				return true;
			}
			else if (sStringOptionCommandArgs[i] == "missionimpossible") {
				RandomColourOutput("Playing Mission Impossible Theme...", ConfigObjMain.sColourGlobalBack);
				std::cout << '\n';
				MissionImpossibleTheme();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "happybirthday") {
				RandomColourOutput("Playing Happy Birthday Song...", ConfigObjMain.sColourGlobalBack);
				std::cout << '\n';
				HappyBirthdaySong();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "supermario") {
				RandomColourOutput("Playing Super Mario Theme...", ConfigObjMain.sColourGlobalBack);
				std::cout << '\n';
				SuperMarioTheme();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "dundundun") {
				RandomColourOutput("Playing DunDunDun Sound...", ConfigObjMain.sColourGlobalBack);
				std::cout << '\n';
				DunDunDunSound();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "imperialmarch") {
				RandomColourOutput("Playing Star Wars Imperial March Song...", ConfigObjMain.sColourGlobalBack);
				std::cout << '\n';
				StarWarsImperialMarch();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "tetris") {
				RandomColourOutput("Playing Tetris Theme Song...", ConfigObjMain.sColourGlobalBack);
				std::cout << '\n';
				TetrisTheme();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "dramatic") {
				RandomColourOutput("Playing A Dramatic Song...", ConfigObjMain.sColourGlobalBack);
				std::cout << '\n';
				DramaticSong();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "rickroll") {
				RandomColourOutput("Playing RickRoll Song...", ConfigObjMain.sColourGlobalBack);
				std::cout << '\n';
				RickRollSong();
				bArgumentExecuted = true;
			}

		}

		// Something already executed in this command
		if (bArgumentExecuted == true) return true;

		OptionSelectEngine oseBeepSounds;

		oseBeepSounds.nSizeOfOptions = 8;
		std::string sOptions[] = {
			"Mission Impossible Theme",
			"Happy Birthday Song",
			"Super Mario Theme",
			"DunDunDun Sound",
			"Star Wars Imperial March Song",
			"Tetris Theme Song",
			"A Dramatic Song",
			"RickRoll Song"
		};
		oseBeepSounds.sOptions = sOptions;

		int nChoice = oseBeepSounds.OptionSelect("Please select which beep-sound you would like to output:", " ___BEEP SOUNDS___ ");
		std::cout << '\n';
		
		switch (nChoice) {
		case 1:
			RandomColourOutput("Playing Mission Impossible Theme...", ConfigObjMain.sColourGlobalBack);
			std::cout << '\n';
			MissionImpossibleTheme();
			break;
		case 2:
			RandomColourOutput("Playing Happy Birthday Song...", ConfigObjMain.sColourGlobalBack);
			std::cout << '\n';
			HappyBirthdaySong();
			break;
		case 3:
			RandomColourOutput("Playing Super Mario Theme...", ConfigObjMain.sColourGlobalBack);
			std::cout << '\n';
			SuperMarioTheme();
			break;
		case 4:
			RandomColourOutput("Playing DunDunDun Sound...", ConfigObjMain.sColourGlobalBack);
			std::cout << '\n';
			DunDunDunSound();
			break;
		case 5:
			RandomColourOutput("Playing Star Wars Imperial March Song...", ConfigObjMain.sColourGlobalBack);
			std::cout << '\n';
			StarWarsImperialMarch();
			break;
		case 6:
			RandomColourOutput("Playing Tetris Theme Song...", ConfigObjMain.sColourGlobalBack);
			std::cout << '\n';
			TetrisTheme();
			break;
		case 7:
			RandomColourOutput("Playing A Dramatic Song...", ConfigObjMain.sColourGlobalBack);
			std::cout << '\n';
			DramaticSong();
			break;
		case 8:
			RandomColourOutput("Playing RickRoll Song...", ConfigObjMain.sColourGlobalBack);
			std::cout << '\n';
			RickRollSong();
			break;
		case -1:
			Exiting();
			return true;
		default:
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
			Exiting();
			return true;
		}

		return true;
	}

	// RickRoll
	else if (sCommand == "rickroll" || sCommand == "26") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::RickRollHelp();
				return true;
			}
		}

		// Rickroll
		// Props to Hell's Channel for keeping this youtube link alive!
		ShellExecuteA(0, 0, "https://www.youtube.com/watch?v=z4JJ270xx98", 0, 0, SW_HIDE);

		return true;
	}

	// ShellExecute
	else if (sCommand == "shellexecute" || sCommand == "27") {

		std::string sCommandText = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::ShellExecuteHelp();
				return true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sCommandText = sStringDataCommandArgs[0];
			}
		}

		// User Interface
		if (sCommandText == "") {
			CentreColouredText("___SHELLEXECUTE___", 1);
			std::cout << "\n\n";

			sCommandText = StrInput("Please input your desired CMD command to run (0 to exit): > ");

			// Exit on 0
			if (sCommandText == "0") {
				Exiting();
				return true;
			}
		}

		// Display messages and execute command
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Executing command...\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Execute command
		system(sStringDataCommandArgs[0].c_str());

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nCommand execution successful!\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// Hacker
	else if (sCommand == "hacker" || sCommand == "28") {

		// 1 for display, 2 for typing
		int nChoice = 0;
		// For custom file hacker type
		std::string sFileName = "";
		// Speed of characters
		uint64_t nOutputSpeed = 0;
		// Start immediately and skip messages
		bool bStartImmediately = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::HackerHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'i') {
				// Set start immediately to true
				bStartImmediately = true;
			}
			
			if (sStringOptionCommandArgs[i] == "display") {
				nChoice = 1;
			}
			else if (sStringOptionCommandArgs[i] == "type") {
				// Firstly, validate string to be a number
				// Don't check empty strings
				if (sStringDataCommandArgs[i] != "")
				{
					if (isNumberull(sStringDataCommandArgs[i]) == false) {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("ERROR: The speed argument given is not a number.\nPlease try again later, or see 'hacker -h' for more details.\n");
						return true;
					}
					else nOutputSpeed = std::stoull(sStringDataCommandArgs[i]);
				}

				nChoice = 2;
			}
			else if (sStringOptionCommandArgs[i] == "typecustom") {
				sFileName = sStringDataCommandArgs[i];

				// If statements for safety
				if (i + 1 < 128) {
					// Firstly, validate string to be a number
					// Don't check empty strings
					if (sStringDataCommandArgs[i + 1] != "") 
					{
						if (isNumberull(sStringDataCommandArgs[i + 1]) == false) {
							VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
							UserErrorDisplay("ERROR: The speed argument given is not a number.\nPlease try again later, or see 'hacker -h' for more details.\n");
							return true;
						}
						else nOutputSpeed = std::stoull(sStringDataCommandArgs[i + 1]);
					}
				}

				nChoice = 3;
			}
		}

		// User interface
		if (nChoice == 0) {
			OptionSelectEngine oseHacker;
			oseHacker.nSizeOfOptions = 3;
			std::string sOptions[] = {
				"Hacker Display",
				"Hacker Type",
				"Hacker Type (Custom File)"
			};
			oseHacker.sOptions = sOptions;

			nChoice = oseHacker.OptionSelect("Please select what type of hacker experience you want:", " ___HACKER___ ");

			if (nChoice == -1) {
				Exiting();
				return true;
			}
		}
		else {
			CentreColouredText(" ___HACKER___ ", 1);
			std::cout << '\n';
		}

		// Display
		if (nChoice == 1) {

			// Display prompt if start immediately is false
			if (bStartImmediately == false) {
				// Warn user on how to stop before starting
				std::cout << wordWrap("\nThe program will output random numbers in green text to simulate a hacking-like environment.\nYou can press any key in the middle of the operation to stop.")
					<< wordWrap("\n\nPress any key to begin, or ESC to exit...\n");

				// 27 is ESC key
				if (_getch() == 27) {
					Exiting();
					return true;
				}
			}

			// Set colour to light green - hacking colour
			colour(LGRN, ConfigObjMain.sColourGlobalBack);

			// Loop for outputting random numbers
			while (!_kbhit()) {
				std::cout << RandNum(std::numeric_limits<int>::max(), std::numeric_limits<int>::min()) << ' ';
			}

			// Clear keyboard buffer to erase key from buffer
			ClearKeyboardBuffer();

			std::cout << "\n\n";
			Exiting();
			return true;
		}

		// Typing
		else if (nChoice == 2) {
			
			if (bStartImmediately == false) {
				std::cout << wordWrap("\nWelcome to Hacker Type!\nThis will allow you to type like a hacker and impress your friends.\nThe idea was taken from https://www.hackertyper.net/. Type with any random keys to output text, and ESC to exit.\n\n");

				if (nOutputSpeed == 0) {
					nOutputSpeed = PositiveNumInputull("Please input desired character output speed (default is 3) (0 to exit): > ");
					if (nOutputSpeed <= 0) {
						Exiting();
						return true;
					}
				}
			}
			else nOutputSpeed = 3; // Default

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Starting...\n\n";

			HackerTyper(nOutputSpeed);
			return true;
		}

		// Typing with custom file
		else if (nChoice == 3) {

			if (bStartImmediately == false) {
				std::cout << wordWrap("\nWelcome to Hacker Type with Custom File support!\nThis will allow you to type like a hacker and impress your friends.\nThe idea was taken from https://www.hackertyper.net/. Type with any random keys to output text, and ESC to exit.\n\n");
			}

			if (sFileName == "") {
				sFileName = StrInput("Please input the filepath for the custom file (0 to exit, *open for Windows File Dialogue): > ");
				if (sFileName == "0") {
					Exiting();
					return true;
				}
			}

			// Open file with Windows File Dialogue
			if (sFileName == "*open") {
				// Use the Windows File Dialogue
				std::cout << wordWrap("Opening with the Windows File Dialogue...\n");
				FileOpenGUIEngine HackerFileOpen;
				HackerFileOpen.FileOpenDialogue("Open a File to Use for Hacker Type");
				sFileName = HackerFileOpen.GetRetrievedPathName();
				if (sFileName == "") {
					Exiting();
					return true;
				}
			}
			
			if (bStartImmediately == false) {
				std::cout << '\n';

				if (nOutputSpeed == 0) {
					nOutputSpeed = PositiveNumInputull("Please input desired character output speed (default is 3) (0 to exit): > ");
					if (nOutputSpeed <= 0) {
						Exiting();
						return true;
					}
				}
			}
			else nOutputSpeed = 3; // Default

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Starting...\n\n";

			HackerTyperFile(sFileName, nOutputSpeed);
			return true;
		}

		// Error occured
		else {
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		}

		return true;
	}

	// Calculator
	else if (sCommand == "calculator" || sCommand == "29") {

		// Declare variables
		bool bWorkingOut = false;
		bool bWorkingOutArgumentSet = false;
		bool bUseEuropeanMathNotation = false;
		std::string sCalculationInput = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::CalculatorHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'w') {
				// Set switch to true
				bWorkingOut = true;

				bWorkingOutArgumentSet = true;
			}
			else if (cCommandArgs[i] == 'n') {
				// Set switch to false
				bWorkingOut = false;

				bWorkingOutArgumentSet = true;
			}
			else if (cCommandArgs[i] == 'e') {
				// Set EU Math Notation switch to true
				bUseEuropeanMathNotation = true;
			}
			
			if (sStringDataCommandArgs[i] != "") {
				sCalculationInput = sStringDataCommandArgs[i];
			}
		}

		// Only output title if bWorkingOutArgumentSet is true AND sCalculationInput has nothing, OR if bWorkingOutArgumentSet is false AND sCalculationInput has nothing.
		if ((bWorkingOutArgumentSet == true && sCalculationInput == "") || (bWorkingOutArgumentSet == false && sCalculationInput == "")) {
			CentreColouredText(" ___CALCULATOR___ ", 1);
			std::cout << "\n\n";
		}

		// No working out is default
		if (bWorkingOutArgumentSet == false && sCalculationInput != "") 
			bWorkingOut = false;
		// If the working out wasn't user-set
		else if (bWorkingOutArgumentSet == false) {
			bWorkingOut = YesNoInput("Would you like the calculator to display working out steps? [y/n] > ");
			std::cout << '\n';
		}

		// Start the Calculation Algorithm
		CalculationAlgorithm caCalculator;
		caCalculator.bDisplayWorkingOutProcess = bWorkingOut;
		caCalculator.UseEuropeanNotation(bUseEuropeanMathNotation);
		
		// Before loop, check if calculation string was brought in as an argument
		if (sCalculationInput != "") {

			// Calculate answer using SafeCalculate
			long double dCalculatedVal = caCalculator.SafeCalculate(sCalculationInput);

			// Output depending on if error occured
			if (caCalculator.GetLastCalculationErrorValue() > 0) {
				colour(LRED, ConfigObjMain.sColourGlobalBack);
				std::cout << " " << caCalculator.GetLastCalculationErrorInfo();
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n See 'calculator -h' for more info.\n";
			}
			else {
				std::cout << " Calculated Answer: ";
				colour(LCYN, ConfigObjMain.sColourGlobalBack);

				// Output result
				if (bUseEuropeanMathNotation) {
					std::cout << FormatValueForEuropeanNotation(dCalculatedVal) << "\n";
				}
				else {
					// Send all floating-point information and formatting information to stringstream
					std::ostringstream ossFinalAns;
					ossFinalAns << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10 - GetWholeNumberDigitLength(dCalculatedVal) - 1) << dCalculatedVal;

					std::cout << EradicateTrailingZeroes(ossFinalAns.str()) << "\n";
				}

				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

			return true;
		}

		// Loop calculator, with exit possibility
		while (sCalculationInput != "exit") {
			sCalculationInput = StrInput("Input calculation (type \"exit\" to exit): > ");

			// Exit on exit input
			if (sCalculationInput == "exit") {
				Exiting();
				break;
			}
			else std::cout << '\n';

			// Calculate answer using SafeCalculate
			long double dCalculatedVal = caCalculator.SafeCalculate(sCalculationInput);

			// Output depending on if error occured
			if (caCalculator.GetLastCalculationErrorValue() > 0) {
				colour(LRED, ConfigObjMain.sColourGlobalBack);
				std::cout << " " << caCalculator.GetLastCalculationErrorInfo();
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n See 'calculator -h' for more info.\n\n";
			}
			else {
				std::cout << " Calculated Answer: ";
				colour(LCYN, ConfigObjMain.sColourGlobalBack);

				// Open stringstream
				std::ostringstream ossFinalAns;
				// Send all floating-point information and formatting information
				ossFinalAns << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10 - GetWholeNumberDigitLength(dCalculatedVal) - 1) << dCalculatedVal;

				// Finally, output result
				if (bUseEuropeanMathNotation) {
					std::cout << FormatValueForEuropeanNotation(dCalculatedVal) << "\n\n";
				}
				else {
					std::cout << EradicateTrailingZeroes(ossFinalAns.str()) << "\n\n";
				}

				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
		}

		return true;
	}

	// Logoff
	else if (sCommand == "logoff" || sCommand == "30") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::LogoffHelp();
				return true;
			}
		}

		// Log off
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Logging-off process initiated.\nLogging off...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		ExitWindowsEx(EWX_LOGOFF, SHTDN_REASON_MINOR_ENVIRONMENT);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Log-off successful.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}
	else return false;

	return true;
}
