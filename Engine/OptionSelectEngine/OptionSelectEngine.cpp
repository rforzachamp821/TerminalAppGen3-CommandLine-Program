//
// OptionSelectEngine.cpp - Contains everything to do with the OptionSelect engine, including its class.
//
#include "OptionSelectEngine.h"
#include <iomanip>
#include <conio.h>

// Function to handle +/- number input - int
int OptionSelectEngine::OSENumInputi(std::string sPrompt, bool bCentrePromptText) {
	int num;

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputi(): Input session begin with prompt: {" + sPrompt + "}.", 4);
	}

	while (true) {
		// Centre prompt text if boolean says so
		if (bCentrePromptText == true) {
			CONSOLE_SCREEN_BUFFER_INFO csbiOptionSelect;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiOptionSelect);
			MoveCursorToXCoord(((csbiOptionSelect.srWindow.Right - csbiOptionSelect.srWindow.Left) - sPrompt.length()) / 2);
		}

		std::cout << wordWrap(sPrompt);
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::cin >> num;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			continue;
		}
		else {
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		}
	}

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputi(): Input session end with return value: " + std::to_string(num) + ".", 4);
	}

	return num;
}

// MoveCursorToXCoord
bool OptionSelectEngine::MoveCursorToXCoord(short int xArg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiConsole;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbiConsole)) {
		return false;
	}

	if (hConsole == INVALID_HANDLE_VALUE) return false;
	if (!SetConsoleCursorPosition(hConsole, { xArg, csbiConsole.dwCursorPosition.Y })) return false;

	return true;
}

// SimpleOptionSelect
int OptionSelectEngine::SimpleOptionSelect(std::string sPrompt, std::string sTitle, bool bCentreOptions, bool bCentrePrompt)
{
	int nInput = 0;
	int nOptionsLeftPaddingWidth = 0;
	int nPromptLeftPaddingWidth = 0;
	std::vector<std::string> vsOptionIndicatorColours{};
	CONSOLE_SCREEN_BUFFER_INFO csbiOptionSelect;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiOptionSelect);

	// Check if this function is meant to be used
	if (ConfigObjMain.bUseNewOptionSelect == true) {
		// Exit - not really an error.
		return -1;
	}

	// Calculate padding width for centring options
	if (bCentreOptions) {
		// Get largest option length
		int nLargestOptionLength = 0;
		for (int i = 0; i < nSizeOfOptions; i++) {
			if (sOptions[i].length() > nLargestOptionLength) {
				nLargestOptionLength = sOptions[i].length();
			}
		}
		// Calculate padding width
		nOptionsLeftPaddingWidth = ((csbiOptionSelect.srWindow.Right - csbiOptionSelect.srWindow.Left) - (nLargestOptionLength + 3)) / 2; // +3 because of the "[x] " that is appended to each option
	}

	if (bCentrePrompt) {
		// Calculate padding width for prompt
		nPromptLeftPaddingWidth = ((csbiOptionSelect.srWindow.Right - csbiOptionSelect.srWindow.Left) - sPrompt.length()) / 2;
	}

	// Initialise option indicator colour vector
	for (int i = 0; i < nSizeOfOptions; i++) {
		// Calculate another random colour
		vsOptionIndicatorColours.push_back(colconv::NumberToColour(RandNumld(16, 1)));
	}

	// Output a newline to prevent errors with overwriting cells of text
	std::cout << '\n';

	// Display centred title
	CentreColouredText(sTitle, 1);

	// Display prompt message for selection options with underline
	if (sPrompt != "") {
		std::cout << "\n";
		MoveCursorToXCoord(nPromptLeftPaddingWidth);
		std::cout << wordWrap(sPrompt) << "\n\n";
	}

	// Log that session is starting
	LogFileMain.AddLogLine("In OptionSelectEngine::SimpleOptionSelect(): OptionSelect Session starting with " + std::to_string(nSizeOfOptions) + " options and prompt {\"" + sPrompt + "\"}.", 4, nObjectID);

	// Render options
	for (int i = 0; i < nSizeOfOptions; i++)
	{
		// Output number of spaces based on padding
		MoveCursorToXCoord(nOptionsLeftPaddingWidth);

		// Set brackets to option indicator colour
		colour(vsOptionIndicatorColours[i], ConfigObjMain.sColourGlobalBack);
		std::cout << '[';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		std::cout << i + 1;

		// Set brackets to option indicator colour
		colour(vsOptionIndicatorColours[i], ConfigObjMain.sColourGlobalBack);
		std::cout << "] ";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		std::cout << sOptions[i] << "\n";
	}

	std::cout << '\n';
	while (true) {
		// Input centred when options are centred - avoids overcomplication
		std::string sInputPrompt = "Please input a desired option number (input 0 to exit): > ";

		// Move prompt to centre if centring prompt is enabled
		nInput = OSENumInputi(sInputPrompt, bCentrePrompt);

		if (nInput == 0) {
			// Log that session is ending
			LogFileMain.AddLogLine("In OptionSelectEngine::SimpleOptionSelect(): OptionSelect Session manually exited with nInput option number " + std::to_string(nInput) + ".", 4, nObjectID);

			return -1;
		}
		else if (nInput < 1 || nInput > nSizeOfOptions) {
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Sorry, but your input is below 1 or above " + std::to_string(nSizeOfOptions) + ".\nThere is no option associated with the inputted option number. Please try again.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else break;
	}

	// Log that session is ending
	LogFileMain.AddLogLine("In OptionSelectEngine::SimpleOptionSelect(): OptionSelect Session ended with nInput option number " + std::to_string(nInput) + " (" + sOptions[nInput - 1] + ").", 4, nObjectID);

	return nInput;
}

OptionSelectEngine::OptionSelectEngine() {
	static int nStaticID = 10000;
	// Wrap-around to prevent overflow
	if (nStaticID >= std::numeric_limits<int>::max() - 1) nStaticID = 10000;
	nObjectID = ++nStaticID;

	// Display only when verbose messages are turned on
	VerbosityDisplay("New OptionSelectEngine Object Created.\n", nObjectID);

	// Set values to default
	nSizeOfOptions = 0;
	sDirectionsText = "Press the 'W' key or up arrow key to move up.\nPress the 'S' key or down arrow key to move down.\nPress ENTER to continue with selection, or ESC to exit.";
}

OptionSelectEngine::~OptionSelectEngine() {
	// Display verbose destructor message
	VerbosityDisplay("OptionSelectEngine Object has been destroyed.\n", nObjectID);
}


// OptionSelect
int OptionSelectEngine::OptionSelect(std::string sPrompt, std::string sTitle, bool bCentreOptions, bool bCentrePrompt, bool bCentreDirections) {
	int nNumberOfOptions = 0;
	int nIndex = 1;
	int nWindowHeight = 0;
	int nIndexHeight = 0; // Index option height
	int nEndingCursorHeight = 0;
	unsigned char nKey = 0;
	std::string sHighlightBuffer = "";

	// Console window info declaration
	CONSOLE_SCREEN_BUFFER_INFO csbiOptionSelect;
	HANDLE hOptionSelect = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);

	// Vector indicating colour for each option
	std::vector<std::string> sOptionIndicatorColours;

	// Centring padding variable declarations
	int nOptionsLeftPaddingWidth = 0;
	int nPromptLeftPaddingWidth = 0;

	// Use the simple optionselect engine mode.
	if (ConfigObjMain.bUseNewOptionSelect == false) {
		return SimpleOptionSelect(sPrompt, sTitle, bCentreOptions, bCentrePrompt);
	}

	// Calculate padding width for centring options
	if (bCentreOptions) {
		// Get largest option length
		int nLargestOptionLength = 0;
		for (int i = 0; i < nSizeOfOptions; i++) {
			if (sOptions[i].length() > nLargestOptionLength) {
				nLargestOptionLength = sOptions[i].length();
			}
		}
		// Calculate padding width
		GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
		nOptionsLeftPaddingWidth = ((csbiOptionSelect.srWindow.Right - csbiOptionSelect.srWindow.Left) - (nLargestOptionLength + sOptionIndicator.length())) / 2;
	}

	if (bCentrePrompt) {
		// Calculate padding width for prompt
		nPromptLeftPaddingWidth = ((csbiOptionSelect.srWindow.Right - csbiOptionSelect.srWindow.Left) - sPrompt.length()) / 2;
	}

	// Count the number of options
	for (int i = 0; i < nSizeOfOptions; i++) {
		if (sOptions[i] != "") nNumberOfOptions++;
	}

	// Cannot continue with 0 options
	if (nNumberOfOptions < 1) {
		VerbosityDisplay("In OptionSelectEngine::OptionSelect(): ERROR - Engine recieved sOptions with 0 valid members. Engine cannot operate with 0 options as crash may occur. Not enough information to display with stability. Exiting.\n", nObjectID);
		return -2; // error
	}

	// Initialise option indicator colour vector
	for (int i = 0; i < nSizeOfOptions; i++) {
		// Calculate another random colour
		sOptionIndicatorColours.push_back(colconv::NumberToColour(RandNumld(16, 1)));
	}

	// Output a newline to prevent errors with overwriting cells of text
	std::cout << '\n';

	// Check if cursor is exceeding the buffer height - if so, clear screen
	if (CheckIfCursorExceedScreenBufferHeight()) {
		if (bAnsiVTSequences) {
			std::cout << "\n\033[2J\033[1;1H";
		}
		else cls();
	}

	// Display centred title
	if (sTitle != "") {
		// Display centred title if title is there
		CentreColouredText(sTitle, 1);
	}

	// Display prompt message for selection options with underline
	if (sPrompt != "") {
		std::cout << "\n";
		if (bCentrePrompt) {
			GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
			SetCursorPosition(nPromptLeftPaddingWidth, csbiOptionSelect.dwCursorPosition.Y);
			// (bCentrePrompt ? std::string(nPromptLeftPaddingWidth, ' ') : "")
		}

		std::cout << wordWrap(sPrompt) << "\n"; // Check if everything is to be aligned with padding
	}

	// Get correct row position into nStartingRow
	GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
	int nStartingRow = csbiOptionSelect.dwCursorPosition.Y;

	// Log that session is starting
	LogFileMain.AddLogLine("In OptionSelectEngine::OptionSelect(): OptionSelect Session starting with " + std::to_string(nNumberOfOptions) + " options and prompt {\"" + sPrompt + "\"}.", 4, nObjectID);

	// Reiteration boolean
	bool bReiterated = false;
	int nIndexIncrease = 3; // 0 for decrease, 1 for increase, 2 for starting position, 3 for ending position, 4 for not set

	while (true) {

		// Get terminal height
		GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
		nWindowHeight = csbiOptionSelect.srWindow.Bottom - csbiOptionSelect.srWindow.Top;
		nWindowHeight = csbiOptionSelect.dwSize.Y - 1;

		/*Check if cursor is on the lowest row of the terminal screen buffer
		NOTE: THIS IS A WORKAROUND FOR THE WINDOWS TERMINAL GetConsoleScreenBufferInfo() AND SetConsoleCursorPosition() BUG.
			  THIS MAY ONLY BE TEMPORARY.
		*///////////////////////////////////////////////////////////
		if (CheckIfCursorExceedScreenBufferHeight()) {
			if (bAnsiVTSequences) {
				// Alert user that above selection has been duplicated below
				colour(BLK, YLW);
				std::cout << wordWrap("Please note that the above OptionSelect session has been duplicated below, to work around the Windows Terminal #14774 bug.");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				std::cout << "\n\033[2J\033[1;1H";
			}
			else {
				cls();
			}

			// Display centred title
			CentreColouredText(sTitle, 1);

			// Display prompt message for selection options with underline
			std::cout << "\n";
			std::cout << wordWrap(sPrompt) << "\n";

			GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
			nStartingRow = csbiOptionSelect.dwCursorPosition.Y;

			// Set bReiterated to false to tell the next while loop to redraw options
			bReiterated = false;
		}

		// 80 is ascii for down arrow
		bool bIndexIncreaseWasSet = false;
		if (nKey == 80 || nKey == 115) {
			nIndex++;
			nIndexIncrease = 1;
			bIndexIncreaseWasSet = true;
		}
		// 72 is ascii for up arrow
		else if (nKey == 72 || nKey == 119) {
			nIndex--;
			nIndexIncrease = 0;
			bIndexIncreaseWasSet = true;
		}

		// if statements to prevent overspill of nIndex
		if (nIndex > nNumberOfOptions) {
			nIndex = 1;
			nIndexIncrease = 2;
			bIndexIncreaseWasSet = true;
		}
		else if (nIndex < 1) {
			nIndex = nNumberOfOptions;
			nIndexIncrease = 3;
			bIndexIncreaseWasSet = true;
		}

		// Check if nIndex was set; if not, set it to 4 (4 means not set)
		if (!bIndexIncreaseWasSet) {
			nIndexIncrease = 4;
		}

		// 1. Using nIndex, create buffer with >> first, then sOptions[nIndex - 1], then <<
		sHighlightBuffer = ">> " + sOptions[nIndex - 1] + " <<";

		// 2. Get length of sBuffer. Put into nHighlightBuffer
		size_t nHighlightBuffer = sHighlightBuffer.length();

		// Only redraw options on first load - CPU optimisation, reduces flickering
		if (bReiterated == false)
		{
			SetCursorPosition(nOptionsLeftPaddingWidth, (nStartingRow));
			// 3. for loop
			for (int i = 0; i < nNumberOfOptions; i++) {
				// Set cursor position


				// Mitigation for a terminal colour bug on older-style Windows terminals (specifically Conhost.exe)
				//if (i <= 0) {
					/*
										GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
					std::cout << std::setw(csbiOptionSelect.srWindow.Right - csbiOptionSelect.srWindow.Left - nOptionsLeftPaddingWidth) << std::cout.fill(' ');
					SetCursorPosition(nOptionsLeftPaddingWidth, (nStartingRow + i + 1));
					*/

				//}
				//else {
					// 4. Measure size of sOptions[i] and output equal number of spaces, then go to the beginning of the line
					//std::cout << std::setw(sOptions[i].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' '); // + 6 because ">> " and " <<" combined are 6 chars
				std::cout << '\n';
				MoveCursorToXCoord(nOptionsLeftPaddingWidth);
				//}
				// 5. Output option
				if (i == (nIndex - 1)) {
					DisplayOptionsIndicator(sOptionIndicatorColours[i]);
					colourHighlight();
					std::cout << sHighlightBuffer;

					// Put index height into nIndexHeight for ESC keypress and nIndex-only redraw
					GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
					nIndexHeight = csbiOptionSelect.dwCursorPosition.Y;

					// Reset to default colour
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					DisplayOptionsIndicator(sOptionIndicatorColours[i]);
					std::cout << sOptions[i];
				}
			}
			std::cout << "\n";

			if (ConfigObjMain.bDisplayDirections) {
				// Add newlines for DirectionsDisplay
				std::cout << "\n\n";

				// Add directions on how to use using DirectionsDisplay()
				DirectionsDisplay(sDirectionsText, bCentreDirections);
			}

		}
		else // Only draw the new index option after first draw - CPU optimisation, reduces flickering
		{
			// 1. Go to index highlight height
			SetCursorPosition(nOptionsLeftPaddingWidth, nIndexHeight);

			// 2. Output spaces depending on previous nIndex option
			if (nIndexIncrease == 1) {
				std::cout << std::setw(sOptions[nIndex - 2].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' ');
				SetCursorPosition(nOptionsLeftPaddingWidth, nIndexHeight);

				DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 2]);
				std::cout << sOptions[nIndex - 2];
			}
			else if (nIndexIncrease == 0) {
				std::cout << std::setw(sOptions[nIndex].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' ');
				SetCursorPosition(nOptionsLeftPaddingWidth, nIndexHeight);

				DisplayOptionsIndicator(sOptionIndicatorColours[nIndex]);
				std::cout << sOptions[nIndex];
			}
			else if (nIndexIncrease == 2) {
				std::cout << std::setw(sOptions[nNumberOfOptions - 1].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' ');
				SetCursorPosition(nOptionsLeftPaddingWidth, nIndexHeight);

				DisplayOptionsIndicator(sOptionIndicatorColours[nNumberOfOptions - 1]);
				std::cout << sOptions[nNumberOfOptions - 1];
			}
			else if (nIndexIncrease == 3) {
				std::cout << std::setw(sOptions[0].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' ');
				SetCursorPosition(nOptionsLeftPaddingWidth, nIndexHeight);

				DisplayOptionsIndicator(sOptionIndicatorColours[0]);
				std::cout << sOptions[0];
			}

			// 3. Go to nIndex + nStartingRow
			SetCursorPosition(nOptionsLeftPaddingWidth, nIndex + nStartingRow);

			// 4. Output new sHighlightBuffer and sOptionsIndicator
			DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 1]);
			colourHighlight();
			std::cout << sHighlightBuffer;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// 5. Put index height into nIndexHeight for ESC keypress and next nIndex-only redraw
			GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
			nIndexHeight = csbiOptionSelect.dwCursorPosition.Y;

			// 6. Put cursor on the ending cursor height to make it work like normal whole-screen redraw
			SetCursorPosition(nOptionsLeftPaddingWidth, nEndingCursorHeight);
		}


		bool bIsEnter = false;
		// While loop to skip next code on wrong input, CPU optimisation
		while (true) {
			// Set nEndingCursorHeight to cursor height at this point
			GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
			nEndingCursorHeight = csbiOptionSelect.dwCursorPosition.Y;

			// Exit if ESC was pressed (from previous non-reiteration)
			if (nKey == 27) {
				// Darken the index highlight to indicate that this OptionSelect session isn't being used anymore
				GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
				SetCursorPosition(nOptionsLeftPaddingWidth, nIndexHeight);
				DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 1]);
				colour(LWHT, GRAY);
				std::cout << sHighlightBuffer;
				SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

				// Log that session is ending
				LogFileMain.AddLogLine("In OptionSelectEngine::OptionSelect(): OptionSelect Session manually exited with index " + std::to_string(nIndex) + " (" + sOptions[nIndex - 1] + "). Last key pressed was ASCII code " + std::to_string(nKey) + ".", 4, nObjectID);

				// Set colour back to default and exit
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				return -1;
			}

			// Exit if ENTER was pressed (from previous non-iteration around the ms console bug)
			else if (nKey == 13) {
				bIsEnter = true;

				break;
			}


			// Get input
			nKey = _getch();
			if (nKey == 80 || nKey == 72 || nKey == 119 || nKey == 115) {
				break;
			}
			// Enter key
			else if (nKey == 13) {
				// Break if ESC pressed immediately, without any reiterations - only if console cursor exceeds screen buffer size (or windows terminal bug #14774)
				if (bReiterated == false && CheckIfCursorExceedScreenBufferHeight()) {
					break;
				}

				bIsEnter = true;
			}
			// exit with code -1 if ESC is pressed
			else if (nKey == 27) {

				// Break if ESC pressed immediately, without any reiterations - only if console cursor exceeds screen buffer size (or windows terminal bug #14774)
				if (bReiterated == false && CheckIfCursorExceedScreenBufferHeight()) {
					break;
				}

				// Darken the index highlight to indicate that this OptionSelect session isn't being used anymore
				GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
				SetCursorPosition(nOptionsLeftPaddingWidth, nIndexHeight);
				DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 1]);
				colour(LWHT, GRAY);
				std::cout << sHighlightBuffer;
				SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

				// Log that session is ending
				LogFileMain.AddLogLine("In OptionSelectEngine::OptionSelect(): OptionSelect Session manually exited with index " + std::to_string(nIndex) + " (" + sOptions[nIndex - 1] + "). Last key pressed was ASCII code " + std::to_string(nKey) + ".", 4, nObjectID);

				// Set colour back to default and exit
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				return -1;
			}
			else continue;
		}

		// Exit on enter keypress
		if (bIsEnter == true) break;

		bReiterated = true;
	}

	// Darken the index highlight to indicate that this OptionSelect session isn't being used anymore
	GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
	SetCursorPosition(nOptionsLeftPaddingWidth, nIndexHeight);
	DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 1]);
	colour(LWHT, GRAY);
	std::cout << sHighlightBuffer;
	SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

	// Log that session is ending
	LogFileMain.AddLogLine("In OptionSelectEngine::OptionSelect(): OptionSelect Session ended with index " + std::to_string(nIndex) + " (" + sOptions[nIndex - 1] + "). Last key pressed was ASCII code " + std::to_string(nKey) + ".", 4, nObjectID);

	// Set colour back to default and exit
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	return nIndex;
}