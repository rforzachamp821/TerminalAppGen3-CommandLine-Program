//
// CommandsFile_31to40.cpp - All command code, from command numbers 31 to 40, is here.
//

#include "Commands.h"

// Commands function - all command interfaces/start menus will go here
bool commands::Commands31To40(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer)
{
	// Shutdown
	if (sCommand == "shutdown" || sCommand == "31") {
		unsigned long int nTimeBeforeShutdown = 10;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::ShutdownHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'c') {
				// Abort system shutdown
				AbortSystemShutdownA(NULL);
				
				// Output success message
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Shutdown successfully aborted.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				return true;
			}
			else if (cCommandArgs[i] == 't') {
				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberul(sStringDataCommandArgs[0]) == false) {
						UserErrorDisplay("ERROR - Time argument is not a number.\nPlease try again later, or see 'shutdown -h' for more details.\n");

						return true;
					}
					else nTimeBeforeShutdown = std::stoul(sStringDataCommandArgs[0]);
				}
				else {
					UserErrorDisplay("ERROR - No time argument found.\nPlease try again later, or see 'shutdown -h' for more details.\n");

					return true;
				}
			}
		}

		InitiateSystemShutdownExA(NULL, (LPSTR)"User decided to shut down the computer through the ZeeTerminal program.", nTimeBeforeShutdown, false, false, SHTDN_REASON_MINOR_ENVIRONMENT);
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Computer will shut down in " << nTimeBeforeShutdown << " seconds.\nExecute 'shutdown -c' to abort.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// Reboot
	else if (sCommand == "reboot" || sCommand == "restart" || sCommand == "32") {
		unsigned long int nTimeBeforeReboot = 10;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::RebootHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'c') {
				// Abort system shutdown
				AbortSystemShutdownA(NULL);

				// Output success message
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Reboot successfully aborted.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				return true;
			}
			else if (cCommandArgs[i] == 't') {
				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberul(sStringDataCommandArgs[0]) == false) {
						UserErrorDisplay("ERROR - Time argument is not a number.\nPlease try again later, or see 'reboot -h' for more details.\n");

						return true;
					}
					else nTimeBeforeReboot = std::stoul(sStringDataCommandArgs[0]);
				}
				else {
					UserErrorDisplay("ERROR - No time argument found.\nPlease try again later, or see 'reboot -h' for more details.\n");

					return true;
				}
			}
		}

		InitiateSystemShutdownExA(NULL, (LPSTR)"User decided to reboot the computer through the ZeeTerminal program.", nTimeBeforeReboot, false, true, SHTDN_REASON_MINOR_ENVIRONMENT);
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Computer will reboot in " << nTimeBeforeReboot << " seconds.\nExecute 'reboot -c' to abort.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// Hibernate
	else if (sCommand == "hibernate" || sCommand == "33") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::HibernateHelp();
				return true;
			}
		}

		// Hibernate
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Hibernate process initiated.\nHibernating...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		SetSuspendState(true, false, true);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Hibernation successful.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;

	}

	// ResetExpl
	else if (sCommand == "resetexpl" || sCommand == "34") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::ResetExplHelp();
				return true;
			}
		}

		// Reset explorer.exe
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Resetting explorer.exe...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (ResetExpl() == true) {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Explorer.exe reset successful!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else {
			UserErrorDisplay("Explorer.exe reset failed.\nSee the Verbosity Messages for more info (you can enable them in the settings).\n");
		}

		return true;
	}

	// MemTest
	else if (sCommand == "memtest" || sCommand == "35") {

		int nChoice = 0;
		uint64_t nNumOfPasses = 0; // -b: 100, -l: 10, -e: 2
		bool bKeypressBeforeDeallocation = false;
		bool bUseFullMemory = false;
		bool bSuccess = true;
		bool bMultiThreaded = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {

			if (cCommandArgs[i] == 'h') {
				helpmsgs::MemTestHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'f') {
				nChoice = 1;
			}
			else if (cCommandArgs[i] == 'k') {
				bKeypressBeforeDeallocation = true;
			}
			else if (cCommandArgs[i] == 'a') {
				bUseFullMemory = true;
			}
			else if (cCommandArgs[i] == 'm') {
				bMultiThreaded = true;
			}
			else if (cCommandArgs[i] == 'b') {

				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == false) {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("ERROR - Passes argument is not a number.\nPlease try again later, or see 'memtest -h' for more details.\n");

						return true;
					}
					else nNumOfPasses = std::stoull(sStringDataCommandArgs[0]);
				}

				nChoice = 2;

			}
			else if (cCommandArgs[i] == 'l') {

				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == false) {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("ERROR - Passes argument is not a number.\nPlease try again later, or see 'memtest -h' for more details.\n");

						return true;
					}
					else nNumOfPasses = std::stoull(sStringDataCommandArgs[0]);
				}

				nChoice = 4;
			}
			else if (cCommandArgs[i] == 'e') {

				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == false) {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("ERROR - Passes argument is not a number.\nPlease try again later, or see 'memtest -h' for more details.\n");

						return true;
					}
					else nNumOfPasses = std::stoull(sStringDataCommandArgs[0]);
				}

				nChoice = 6;
			}
		}

		// User Interface
		if (nChoice == 0) {
			OptionSelectEngine oseMemtest;
			oseMemtest.nSizeOfOptions = 7;
			std::string sOptions[] = {
				"Simple fill up and deallocate memory",
				"Fill up memory and perform binary search",
				"Fill up memory and perform binary search (Multithreaded)",
				"Fill up memory and perform linear check search",
				"Fill up memory and perform linear check search (Multithreaded)",
				"Fill up memory and perform extended linear check search",
				"Fill up memory and perform extended linear check search (Multithreaded)",
			};
			oseMemtest.sOptions = sOptions;

			nChoice = oseMemtest.OptionSelect("Please select how you would like to test your computer's memory:", " ___MEMTEST___ ");

			if (nChoice == -1) {
				// Exit
				Exiting();
				return true;
			}
		}

		// Multithreaded options setter
		if (nChoice == 3) {
			bMultiThreaded = true;
			nChoice = 2;
		}
		else if (nChoice == 5) {
			bMultiThreaded = true;
			nChoice = 4;
		}
		else if (nChoice == 7) {
			bMultiThreaded = true;
			nChoice = 6;
		}

		// Simple fill up and deallocate memory
		if (nChoice == 1) {
			CentreColouredText(" ___MEMTEST SIMPLE ALLOCATE & DEALLOCATE___ ", 1);

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\n\nStarting a simple fill-up and memory deallocation process...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			MemoryTestEngine mteFillUpDeallocate;
			mteFillUpDeallocate.bUseTotalPhysicalCapacity = bUseFullMemory;
			bSuccess = mteFillUpDeallocate.FillMemoryToMaximum(bKeypressBeforeDeallocation);
		}

		// Fill up memory and perform x binary searches
		else if (nChoice == 2) 
		{
			CentreColouredText(" ___MEMTEST BINARY SEARCH___ ", 1);

			// When not inputted as an argument
			if (nNumOfPasses == 0) {
				std::cout << "\n\n";
				colourHighlight();
				std::cout << wordWrap("Welcome to the Binary Search Memory Test!");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				std::cout << wordWrap("\n\nThis will fill up the memory on your computer and perform binary search tests on it.\n");
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("NOTE: You can stop the test at any time by pressing any key in the duration of the test.\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (bMultiThreaded == true) {
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("NOTE: This test will run with multithreading. Beware of CPU throttling and temperatures.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				std::cout << '\n';
				nNumOfPasses = PositiveNumInputull("Please input the number of binary search passes (100 is default, 0 to exit): > ");

				if (nNumOfPasses <= 0) {
					Exiting();
					return true;
				}
			}

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nStarting a memory fill-up and binary search test...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			MemoryTestEngine mteBinarySearch;
			mteBinarySearch.bUseTotalPhysicalCapacity = bUseFullMemory;
			bSuccess = mteBinarySearch.PerformBinarySearchOnMemory(nNumOfPasses, bMultiThreaded);
		}

		// Fill up memory and perform x linear check searches
		else if (nChoice == 4) 
		{
			CentreColouredText(" ___MEMTEST LINEAR CHECK SEARCH___ ", 1);

			// When not inputted as an argument
			if (nNumOfPasses == 0) {
				std::cout << "\n\n";
				colourHighlight();
				std::cout << wordWrap("Welcome to the Linear Check Search Memory Test!");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				std::cout << wordWrap("\n\nThis will fill up the memory on your computer and perform linear check search tests on it.\n");
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("NOTE: This test may take some time.\nNOTE: You can stop the test at any time by pressing any key during the test.\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (bMultiThreaded == true) {
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("NOTE: This test will run with multithreading. Beware of CPU throttling and temperatures.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				std::cout << '\n';
				
				nNumOfPasses = PositiveNumInputull("Please input the number of linear check search passes (10 is default, 0 to exit): > ");

				if (nNumOfPasses <= 0) {
					Exiting();
					return true;
				}
			}

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nStarting a memory fill-up and linear check search test...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			MemoryTestEngine mteLinearSearch;
			mteLinearSearch.bUseTotalPhysicalCapacity = bUseFullMemory;
			bSuccess = mteLinearSearch.PerformLinearSearchOnMemory(nNumOfPasses, bMultiThreaded);
		}

		// Fill up memory and perform x extended linear check searches
		else if (nChoice == 6) 
		{
			CentreColouredText(" ___MEMTEST EXTENDED LINEAR CHECK SEARCH___ ", 1);

			// When not inputted as an argument
			if (nNumOfPasses == 0) {
				std::cout << "\n\n";
				colourHighlight();
				std::cout << wordWrap("Welcome to the Extended Linear Check Search Memory Test!");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				std::cout << wordWrap("\n\nThis will fill up the memory on your computer and perform extended linear check search tests on it.")
					<< wordWrap("\nThis won't only comprise of checking digits only (like the non-extended test), but also performing operations on memory, before reiterating to the next memory block.\n");
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("NOTE: This test may take a lot of time.\nNOTE: You can stop the test at any time by pressing any key during the test.\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (bMultiThreaded == true) {
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("NOTE: This test will run with multithreading. Beware of CPU throttling and temperatures.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				std::cout << '\n';
				nNumOfPasses = PositiveNumInputull("Please input the number of extended linear check search passes (2 is default, 0 to exit): > ");

				if (nNumOfPasses <= 0) {
					Exiting();
					return true;
				}
			}

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nStarting a memory fill-up and extended linear check search test...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			MemoryTestEngine mteLinearSearch;
			mteLinearSearch.bUseTotalPhysicalCapacity = bUseFullMemory;
			bSuccess = mteLinearSearch.PerformExtendedLinearSearchOnMemory(nNumOfPasses, bMultiThreaded);
		}

		// Failed, unknown return value
		else {
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR: An unknown error occured. Please try again later.\n");

			return true;
		}

		if (bSuccess == true) {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Memory Test or Allocation & Deallocation Complete!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return true;
	}

	// RandCol
	else if (sCommand == "randcol" || sCommand == "36") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::RandColHelp();
				return true;
			}
		}

		std::cout << "Setting random colours...\n";

		// Calculate random numbers
		ConfigObjMain.sColourGlobal = colconv::NumberToColour(RandNum(16, 1));
		ConfigObjMain.sColourGlobalBack = colconv::NumberToColour(RandNum(16, 1));
		
		// Write new values to config file
		ConfigObjMain.WriteConfigFile();

		// Finally, set colours
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Random colours successfully set!") << '\n';

		return true;
	}

	// Pause
	else if (sCommand == "pause" || sCommand == "37") {

		bool bEnterKeypressLimit = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::PauseHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'e') {
				bEnterKeypressLimit = true;
			}
		}

		if (bEnterKeypressLimit == false) {
			std::cout << "Press any key to continue...";
			_getch();
			std::cout << '\n';
		}
		else {
			std::cout << "Press ENTER to continue...: "; // Use the colon character, similar to Powershell
			std::cin.get();
		}

		return true;
	}

	// CommandNum
	else if (sCommand == "commandnum" || sCommand == "38") {
		
		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::CommandNumHelp();
				return true;
			}
		}

		// Output number of inputted commands
		std::cout << '\n';
		colourSubheading();
		std::cout << wordWrap("Since the start of the session, including this command, you have inputted:") << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		std::cout << wordWrap("\nNumber of total commands: " + std::to_string(nNumOfInputtedCommands) + '\n');
		std::cout << wordWrap("Number of commands that were genuine and registered: " + std::to_string(nNumOfSuccessfulInputtedCommands) + '\n');
		std::cout << wordWrap("Number of commands that were unsuccessful and undefined: " + std::to_string(nNumOfInputtedCommands - nNumOfSuccessfulInputtedCommands) + '\n');

		return true;
	}

	// SlowChar
	else if (sCommand == "slowchar" || sCommand == "39") {

		bool bUseRandomColours = false;
		std::string sText = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::SlowCharHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'r') {
				bUseRandomColours = true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sText = sStringDataCommandArgs[0];
			}
		}

		// User Interface
		if (sText == "") {
			CentreColouredText(" ___SLOWCHAR___ ", 1);

			sText = StrInput("\n\nPlease input the text that you want to be outputted slowly (0 to exit): > ");
			if (sText == "0") {
				Exiting();
				return true;
			}
			else std::cout << '\n';
		}

		// Output slow characters depending on colours
		std::cout << "Slow Character Text:\n";
		if (bUseRandomColours == true) {
			SlowCharColourful(sText, false);
		}
		else {
			slowcharfn(true, sText);
		}

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nOutput successful!\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// ReverseText
	else if (sCommand == "reversetext" || sCommand == "40") {

		bool bUseSlowChar = false;
		std::string sText = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::ReverseTextHelp();
				return true;
			}
			else if (cCommandArgs[i] == 's') {
				bUseSlowChar = true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sText = sStringDataCommandArgs[0];
			}
		}

		if (sText == "") {
			CentreColouredText(" ___REVERSETEXT___ ", 1);

			sText = StrInput("\n\nPlease input text that you want to output in reverse (0 to exit): > ");
			if (sText == "0") {
				Exiting();
				return true;
			}
		}

		// Output text in reverse
		std::cout << "Reversed Text:\n\n";
		std::reverse(sText.begin(), sText.end());
		if (bUseSlowChar == true) {
			slowcharfn(true, sText);
		}
		else {
			std::cout << sText;
		}
		
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nOutput successful!\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		
		return true;
	} 
	else return false;

	return true;
}
