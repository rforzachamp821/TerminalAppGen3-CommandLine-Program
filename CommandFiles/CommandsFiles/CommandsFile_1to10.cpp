//
// CommandsFile_1to10.cpp - All command code, from command numbers 1 to 10, is here.
//
#include "Commands.h"


// Commands1To10 function - all command interfaces/start menus will go here
// returns TRUE if command found based on sCommand, and FALSE if not found.
bool commands::Commands1To10(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer) {

	// Before checking commands, check for anything other than a command
	if (sCommand[0] == '#') return true;


	// Help
	if (sCommand == "help" || sCommand == "1") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			// help message
			if (cCommandArgs[i] == 'h') {
				helpmsgs::HelpHelp();
				return true;
			}
		}

		help(false);
		return true;
	}

	// Tutorial
	else if (sCommand == "tutorial" || sCommand == "3") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::TutorialHelp();
				return true;
			}
		}

		CentreColouredText(" ___TUTORIAL___ ", 1);
		std::cout << "\n";

		// Start the tutorial
		if (YesNoInput("Are you sure you want to start the tutorial? [y/n] > ")) {
			Tutorial();
		}
		else {
			Exiting();
		}

		return true;
	}

	// Echo
	else if (sCommand == "echo" || sCommand == "4") {
		std::string sEchoString = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::EchoHelp();
				return true;
			}

			// Concatenate all data argument strings
			sEchoString += sStringDataCommandArgs[i];
		}



		// Output what user wants to input within echo
		if (sEchoString == "") {
			CentreColouredText(" ___ECHO___ ", 1);
			std::cout << "\n";

			sEchoString = StrInput("Input what you would like ZeeTerminal to echo (output): > ");

			// Output the input
			std::cout << sEchoString << std::endl;
		}
		else {
			// Output the input
			std::cout << sEchoString;
		}

		return true;
	}

	// CLS
	else if (sCommand == "cls" || sCommand == "5") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::ClsHelp();
				return true;
			}
		}

		cls();
		return true;
	}

	// DevTools
	else if (sCommand == "devtools" || sCommand == "6") {

		// Arguments
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::DevToolsHelp();
				return true;
			}
			else if (cCommandArgs[i] == '1') {
				DevTools(1);
				return true;
			}
			else if (cCommandArgs[i] == '2') {
				DevTools(2);
				return true;
			}
			else if (cCommandArgs[i] == '3') {
				DevTools(3);
				return true;
			}
			else if (cCommandArgs[i] == '4') {
				DevTools(4);
				return true;
			}
			else if (cCommandArgs[i] == '5') {
				DevTools(5);
				return true;
			}
			else if (cCommandArgs[i] == '6') {
				DevTools(6);
				return true;
			}
			else if (cCommandArgs[i] == '7') {
				DevTools(7);
				return true;
			}
			else if (cCommandArgs[i] == '8') {
				DevTools(8);
				return true;
			}
			else if (cCommandArgs[i] == '9') {
				DevTools(9);
				return true;
			}
		}

		OptionSelectEngine oseDev;

		oseDev.nSizeOfOptions = 9;
		std::string sOptions[] = // Options
		{
			"Colour Tester",
			"Beep Sound Test",
			"Colour Numbers",
			"Test The OptionSelect Engine",
			"Test the ScreenNavigate Engine",
			"Test the Table Engine",
			"High-Res Nanosecond Stopwatch",
			"ANSI Testing Environment",
			"MMSYSTEM API Sound Test"
		};

		oseDev.sOptions = sOptions;

		while (true) {
			// Call OptionSelectEngine::OptionSelect() for option strings set.
			int nInput = oseDev.OptionSelect("Please select your desired developer tool below:", " ___DEVELOPER TOOLS___ ");

			switch (nInput)
			{
			case -1:
				Exiting();
				return true;
			case 1:
				DevTools(1);
				break;
			case 2:
				DevTools(2);
				break;
			case 3:
				DevTools(3);
				break;
			case 4:
				DevTools(4);
				break;
			case 5:
				DevTools(5);
				break;
			case 6:
				DevTools(6);
				break;
			case 7:
				DevTools(7);
				break;
			case 8:
				DevTools(8);
				break;
			case 9:
				DevTools(9);
				break;
			default:
				VerbosityDisplay("In commands::Commands1To10() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
				break;
			}
		}

		return true;
	}

	// CPUStress
	else if (sCommand == "cpustress" || sCommand == "7") {

		CentreColouredText(" ___CPUSTRESS___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::CpuStressHelp();
				return true;
			}
			else if (cCommandArgs[i] == '1') {
				std::cout << '\n';
				// First, check if it's a number
				if (isNumberll(sStringDataCommandArgs[0]) == true) {
					CpuBenchmark(1, std::stoll(sStringDataCommandArgs[0]));
				}
				else {
					CpuBenchmark(1, -1);
				}

				return true;
			}
			else if (cCommandArgs[i] == '2') {
				std::cout << '\n';
				if (isNumberll(sStringDataCommandArgs[0]) == true) {
					CpuBenchmark(2, std::stoll(sStringDataCommandArgs[0]));
				}
				else {
					CpuBenchmark(2, -1);
				}

				return true;
			}
			else if (cCommandArgs[i] == '3') {
				std::cout << '\n';
				CpuStressTest(1, true);
				return true;
			}
			else if (cCommandArgs[i] == '4') {
				std::cout << '\n';
				CpuStressTest(2, true);
				return true;
			}
		}

		OptionSelectEngine CpuStress;

		while (true) {

			std::cout << "\n";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("You can stop a test at any time by pressing the ESC key on the keyboard.");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			CpuStress.nSizeOfOptions = 4;
			std::string sOptions[] = {
				"CPU Benchmark - Single Core",
				"CPU Benchmark - Multi Core",
				"CPU Stress Test - Single Core",
				"CPU Stress Test - Multi Core"
			};
			CpuStress.sOptions = sOptions;

			int nChoice = CpuStress.OptionSelect("Please select your desired option (single core is less intensive, multi core is more intensive):", "");

			if (nChoice == 1) {
				std::cout << '\n';
				CpuBenchmark(1);
			}
			else if (nChoice == 2) {
				std::cout << '\n';
				CpuBenchmark(2);
			}
			else if (nChoice == 3) {
				std::cout << '\n';
				CpuStressTest(1);
			}
			else if (nChoice == 4) {
				std::cout << '\n';
				CpuStressTest(2);
			}
			else if (nChoice == -1) {
				Exiting();
				return true;
			}
			else {
				VerbosityDisplay("In commands::Commands1To10() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

				return true;
			}
		}

		return true;
	}

	// Colour
	else if (sCommand == "colour" || sCommand == "8") {
		bool bForeUserArg = false;
		bool bBackUserArg = false;

		int nChoiceFirst = 0;
		int nForeArg = 0; // 0 is not from argument, anything else means from argument
		int nBackArg = 0; // 0 is not from argument, anything else means from argument

		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::ColourHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'f') {

				if (isNumberi(sStringDataCommandArgs[i]) == true) {
					nChoiceFirst = 1;
					nForeArg = std::stoi(sStringDataCommandArgs[i]);
				}
				else {
					// Can't process a non-number
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured while processing your foreground argument. Make sure your argument syntax is correct, and try again.\nSee \"colour -h\" for more info.\n");
					Exiting();
					return true;
				}

				bForeUserArg = true;
			}
			else if (cCommandArgs[i] == 'b') {

				// Check if argument is a number
				if (isNumberi(sStringDataCommandArgs[i]) == true) {
					nChoiceFirst = 2;
					nBackArg = std::stoi(sStringDataCommandArgs[i]);
				}
				else {
					// Can't process a non-number
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured while processing your background argument. Make sure your argument syntax is correct, and try again.\nSee \"colour -h\" for more info.\n");
					Exiting();
					return true;
				}

				bBackUserArg = true;
			}
			else if (cCommandArgs[i] == 'r') {
				nChoiceFirst = 4;
			}
		}

		// First menu
		OptionSelectEngine oseColour;
		oseColour.nSizeOfOptions = 4;
		std::string sOptions[] = {
			"Foreground Colour",
			"Background Colour",
			"Custom RGB Colour Presets",
			"Reset Colours to Default"
		};
		oseColour.sOptions = sOptions;

		while (true) {
			bool bArgumentForFirstOption = nChoiceFirst; // indicates that the user interface will be triggered

			// User Interface
			if (nChoiceFirst == 0) {
				std::cout << '\n';
				nChoiceFirst = oseColour.OptionSelect("Please choose the colour that you want to change below:", " ___COLOUR___ ");
			}

			if (nChoiceFirst == 1) {
				ColourForeground(nForeArg);
				if (bBackUserArg) ColourBackground(nBackArg); // in case of user-set argument

				// in case of argument
				if (nForeArg != 0) return true;
				else nChoiceFirst = 0;
			}
			else if (nChoiceFirst == 2) {
				ColourBackground(nBackArg);
				if (bForeUserArg) ColourForeground(nForeArg); // in case of user-set argument

				// in case of argument
				if (nBackArg != 0) return true;
				else nChoiceFirst = 0;
			}
			else if (nChoiceFirst == 3) {
				RGBColourPresets();

				if (bArgumentForFirstOption) return true;
				else nChoiceFirst = 0;
			}
			else if (nChoiceFirst == 4) {
				// Reset colours prompt
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\nTHIS WILL RESET ALL SET COLOURS TO DEFAULT VALUES.\nRGB Colour presets will NOT be affected.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (YesNoInput(wordWrap("Are you sure you would like to proceed? [y/n] > "))) {
					// Reset colours and update config file with new colours
					ResetColour();
					ConfigObjMain.WriteConfigFile();
					cls(); // To apply default colours to whole terminal screen

					// Output success message
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("Colours successfully reset.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "\nAborted.\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}

				if (bArgumentForFirstOption) return true;
				else nChoiceFirst = 0;
			}
			else if (nChoiceFirst == -1) {
				Exiting();
				break;
			}
			else {
				VerbosityDisplay("In commands::Commands1To10() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
				return true;
			}
		}

		return true;
	}

	// Settings
	else if (sCommand == "settings" || sCommand == "9") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::SettingsHelp();
				return true;
			}
			else if (sStringOptionCommandArgs[0] == "highlightfore") {

				// Check if argument is a number, post error message if not and call function if yes
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					HighlightColourSettings(1, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "highlightback") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					HighlightColourSettings(2, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "titlefore") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					TitleColourSettings(1, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}
				return true;
			}
			else if (sStringOptionCommandArgs[0] == "titleback") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					TitleColourSettings(2, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}
				return true;
			}
			else if (sStringOptionCommandArgs[0] == "subheadingfore") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					SubheadingColourSettings(1, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}
				return true;
			}
			else if (sStringOptionCommandArgs[0] == "subheadingback") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					SubheadingColourSettings(2, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "verbose") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					VerboseMessagesSettings(1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					VerboseMessagesSettings(2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "directions") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					DirectionMessagesSettings(1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					DirectionMessagesSettings(2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "ansi") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					AnsiSettings(1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					AnsiSettings(2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "wordwrap") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					WordWrapSettings(1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					WordWrapSettings(2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "cursorblink") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					CursorSettings(1, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					CursorSettings(1, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "showcursor") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					CursorSettings(2, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					CursorSettings(2, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "cursorstyle") {
				if (sStringDataCommandArgs[0] == "block") {
					CursorSettings(3, 0, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "underline") {
					CursorSettings(3, 0, 0, 2);
				}
				else if (sStringDataCommandArgs[0] == "bar") {
					CursorSettings(3, 0, 0, 3);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct 'block', 'underline' or 'bar' value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's either 'block', 'underline', or 'bar'. Type \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "slowcharspeed") {
				if (isNumberll(sStringDataCommandArgs[0])) {
					OtherSettings(1, std::stoll(sStringDataCommandArgs[0]), true);
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "randcolstartup") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					OtherSettings(2, 0, true, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					OtherSettings(2, 0, true, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "customtheme") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					OtherSettings(3, 0, true, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					OtherSettings(3, 0, true, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "autocontrast") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					OtherSettings(4, 0, true, 0, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					OtherSettings(4, 0, true, 0, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "tempconfigdir") {
				if (sStringDataCommandArgs[0] != "") {
					OtherSettings(5, 0, true, 0, 0, 0, sStringDataCommandArgs[0]);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect any argument string after option.\n");
					UserErrorDisplay("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again. Type \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "enablelogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(1, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(1, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "vmessagelogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(2, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(2, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "usrerrorlogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(3, 0, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(3, 0, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "commandlogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(4, 0, 0, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(4, 0, 0, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "usrinputlogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(5, 0, 0, 0, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(5, 0, 0, 0, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "newoptionselect") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					OtherSettings(6, 0, true, 0, 0, 0, "", 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					OtherSettings(6, 0, true, 0, 0, 0, "", 2);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "cdcarturnspeed") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					CarDodgeGameSettings(1, std::stoi(sStringDataCommandArgs[0]), 0, 0, 0);
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "cdstartupcar") {
				if (sStringDataCommandArgs[0] == "kartcar") {
					CarDodgeGameSettings(2, 0, 1, 0, 0);
				}
				else if (sStringDataCommandArgs[0] == "thehoverrocket") {
					CarDodgeGameSettings(2, 0, 2, 0, 0);
				}
				else if (sStringDataCommandArgs[0] == "thesweeper") {
					CarDodgeGameSettings(2, 0, 3, 0, 0);
				}
				else if (sStringDataCommandArgs[0] == "theslicer") {
					CarDodgeGameSettings(2, 0, 4, 0, 0);
				}
				else if (sStringDataCommandArgs[0] == "gtspeed") {
					CarDodgeGameSettings(2, 0, 5, 0, 0);
				}
				else if (sStringDataCommandArgs[0] == "xtraaero") {
					CarDodgeGameSettings(2, 0, 6, 0, 0);
				}
				else {
					VerbosityDisplay("ERROR: In commands::Commands1To10() - Could not detect correct 'kartcar', 'thehoverrocket', 'thesweeper', 'theslicer', 'gtspeed' or 'xtraaero' value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's either: 'kartcar', 'thehoverrocket', 'thesweeper', 'theslicer', 'gtspeed' or 'xtraaero'. Type \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "cdforeground") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;

					}

					CarDodgeGameSettings(3, 0, 0, std::stoi(sStringDataCommandArgs[0]), 0);
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "cdbackground") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					CarDodgeGameSettings(4, 0, 0, 0, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "gtnforeground") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					GuessTheNumberGameSettings(1, std::stoi(sStringDataCommandArgs[0]), 0);
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "gtnbackground") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					GuessTheNumberGameSettings(2, 0, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "gtneforeground") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					GuessTheNumberExtremeGameSettings(1, std::stoi(sStringDataCommandArgs[0]), 0);
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
			else if (sStringOptionCommandArgs[0] == "gtnebackground") {
				if (isNumberi(sStringDataCommandArgs[0])) {
					// Check if colour number is beyond limits - alert user if so
					if (std::stoi(sStringDataCommandArgs[0]) < 1 || std::stoi(sStringDataCommandArgs[0]) > 16) {
						VerbosityDisplay("In commands::Commands1To10() - ERROR: The colour number specified is beyond the acceptable colour number range (1 <= x <= 16).");
						UserErrorDisplay("ERROR - The specified colour number argument is less than 1 or above 16. Please ensure that the argument is within the acceptable range, and try again later.\n");
						return true;
					}

					GuessTheNumberExtremeGameSettings(2, 0, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In commands::Commands1To10() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
				}

				return true;
			}
		}

		OptionSelectEngine oseSettings;
		oseSettings.nSizeOfOptions = 13;
		std::string sOptions[] = {
			"Highlight Colour Settings",
			"Title Colour Settings",
			"Subheading Colour Settings",
			"Disable/Enable Verbose Messages",
			"Disable/Enable Direction Messages",
			"Disable/Enable ANSI",
			"Disable/Enable Word Wrapping",
			"Cursor Settings",
			"LogFile System Settings",
			"CarDodge Game Settings",
			"Guess The Number Game Settings",
			"Guess The Number Extreme Game Settings",
			"Other Settings"
		};
		oseSettings.sOptions = sOptions;

		// Leave only when the user decides to press the ESC key
		while (true) {
			std::cout << std::endl;
			int nChoice = oseSettings.OptionSelect("Please select the setting you would like to modify:", " ___SETTINGS___ ");

			switch (nChoice) {
			case -1:
				Exiting();
				return true;
			case 1:
				HighlightColourSettings();
				break;
			case 2:
				TitleColourSettings();
				break;
			case 3:
				SubheadingColourSettings();
				break;
			case 4:
				VerboseMessagesSettings();
				break;
			case 5:
				DirectionMessagesSettings();
				break;
			case 6:
				AnsiSettings();
				break;
			case 7:
				WordWrapSettings();
				break;
			case 8:
				CursorSettings();
				break;
			case 9:
				LogFileSystemSettings();
				break;
			case 10:
				CarDodgeGameSettings();
				break;
			case 11:
				GuessTheNumberGameSettings();
				break;
			case 12:
				GuessTheNumberExtremeGameSettings();
				break;
			case 13:
				OtherSettings();
				break;

			default:
				VerbosityDisplay("In commands::Commands1To10() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
				return true;
			}
		}

		return true;
	}

	// Title
	else if (sCommand == "title" || sCommand == "10") {
		std::string sTitle = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::TitleHelp();
				return true;
			}

			// Concatenate all data arguments
			sTitle += sStringDataCommandArgs[i];
		}

		// User UI
		if (sTitle == "") {
			CentreColouredText(" ___TITLE___ ", 1);
			std::cout << "\n";

			// Take title input
			sTitle = StrInput("Please input your desired title (65535 characters max): > ");
		}

		// Set the window title
		if (SetWindowTitle(sTitle)) {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Setting console window title succeeded!\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else {
			// Failed - too long of a string
			UserErrorDisplay("Setting console window title failed!\nPlease check if your title is too long. It cannot be longer than 65535 characters.\n");
		}

		return true;
	}
	else return false;

	return true;
}