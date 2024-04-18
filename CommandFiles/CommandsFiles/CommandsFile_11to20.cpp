//
// CommandsFile_11to20.cpp - All command code, from command numbers 11 to 20, is here.
//

#include "Commands.h"

// Commands function - all command interfaces/start menus will go here
bool commands::Commands11To20(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer)
{
	// Date
	if (sCommand == "date" || sCommand == "11") {

		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::DateHelp();
				return true;
			}
		}

		time_t currentTime = time(0);
		struct tm localTime {};

		time(&currentTime);
		localtime_s(&localTime, &currentTime);

		colourSubheading();
		std::cout << "Current Date/Time Info:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);


		std::cout << "\n\nLocal Date: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << localTime.tm_mday << "/" << (localTime.tm_mon + 1) << "/" << (localTime.tm_year + 1900); 
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " (DD/MM/YYYY)\n";
		std::cout << "Local Time: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << localTime.tm_hour << ":" << localTime.tm_min << ":" << localTime.tm_sec << "\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// ColourNumbers
	else if (sCommand == "colournumbers" || sCommand == "12") {
		CentreColouredText(" ___COLOURNUMBERS___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::ColourNumbersHelp();
				return true;
			}
		}

		// Display all colours in the colour array inside Settings.cpp
		std::cout << '\n';
		colourSubheading();
		std::cout << "Colour numbers are below:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n';

		for (int i = 0; i < 16; i++) {
			std::cout << '[' << (i + 1) << "] "<< sOptionsColour[i] << "\n";
		}
		std::cout << wordWrap("\nThe colour number for each colour is in between the square brackets.") << '\n';

		return true;
	}

	// MediaPlayer
	else if (sCommand == "mediaplayer" || sCommand == "13") {

		std::wstring wsFilePath = L"";

		CentreColouredText(" ___MEDIAPLAYER___ ", 1);
		std::cout << "\n";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::MediaPlayerHelp();
				return true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				wsFilePath = s2ws(sStringDataCommandArgs[0]);
			}
		}

		// Information
		if (wsFilePath == L"") {
			std::cout << "\n";
			colourSubheading();
			std::cout << wordWrap("The following file formats are supported:") << NOULINE_STR;
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nWMA, WMV, AIFF, AU, AVI, MIDI, SND, WAV, MP3(Only MPEG Audio Layer - 3 codec), JPG, JPEG, BMP\n\nYou can type in \"*open\" without quotes to use the Windows File Dialogue to open a file.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Prompt
			std::cout << "Enter your desired audio/video/image file path (0 to exit): > ";
			colour(LYLW, ConfigObjMain.sColourGlobalBack);
			std::getline(std::wcin, wsFilePath);
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Exit on 0
			if (wsFilePath == L"0") {
				Exiting();
				return true;
			}
		}

		// Open with the Windows File Dialogue
		if (wsFilePath == L"*open") {
			std::cout << "Opening with the Windows File Dialogue...\n";
			FileOpenGUIEngine MediaPlayer;
			MediaPlayer.FileOpenDialogue("Open a Media File to Play");
			wsFilePath = s2ws(MediaPlayer.GetRetrievedPathName());
			// Cancelled
			if (wsFilePath == L"") {
				Exiting();
				return true;
			}
		}

		// Execute multimedia player with the inputted file path
		VerbosityDisplay("Executing media file using MediaPlayer: \"" + ws2s(wsFilePath) + "\"...\n");
		MultimediaEngine meMediaPlayer;
		meMediaPlayer.DShowMultimediaPlayer(wsFilePath);

		return true;

	}

	// AudioPlayer
	else if (sCommand == "audioplayer" || sCommand == "14") {
		std::string sFilePath = "";

		CentreColouredText("___AUDIO PLAYER___", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::AudioPlayerHelp();
				return true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sFilePath = sStringDataCommandArgs[0];
			}
		}

		// Information
		if (sFilePath == "") {
			std::cout << "\n";
			colourSubheading();
			std::cout << wordWrap("The following file formats are supported:") << NOULINE_STR;
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nMP3, MP2, MP1, OGG, WAV, AIFF, FLAC, XM, IT, S3M, MOD, MTM, UMX, WMA, M4A, OPUS, AAC\n\nType \"*open\" without quotes to use the Windows File Dialogue to open an audio file.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Prompt
			sFilePath = StrInput("Enter your desired audio file path (0 to exit): > ");
			std::cout << '\n';

			// Exit on 0
			if (sFilePath == "0") {
				Exiting();
				return true;
			}
		}

		// Open the file dialogue on *open
		if (sFilePath == "*open") {
			// Open with the FileOpen GUI Engine
			std::cout << "Opening with the Windows File Dialogue...\n";
			FileOpenGUIEngine AudioPlayer;
			AudioPlayer.FileOpenDialogue("Open an Audio File to Play");
			sFilePath = AudioPlayer.GetRetrievedPathName();
			// Cancelled
			if (sFilePath == "") {
				Exiting();
				return true;
			}
		}

		VerbosityDisplay("Executing audio file using AudioPlayer: \"" + sStringDataCommandArgs[0] + "\"...\n");
		MultimediaEngine meAudioPlayer;
		meAudioPlayer.BASSAudioPlayer(sFilePath);

		return true;
	}

	// TTS
	else if (sCommand == "tts" || sCommand == "15") {
		
		std::string sText = "";

		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::TTSHelp();
				return true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sText = sStringDataCommandArgs[0];
			}
		}

		// User UI
		if (sText == "") {
			CentreColouredText(" ___TEXT TO SPEECH___ ", 1);
			std::cout << "\n\n";
			// Take input
			sText = StrInput("Please input your desired text (0 to exit): > ");
			if (sText == "0") {
				Exiting();
				return true;
			}
		}

		// Check for speechmarks; if so, remove them so they don't get pronounced
		if (sText[0] == '"' && sText[sText.length() - 1] == '"') {
			sText = sText.substr(1, (sText.length() - 2));
		}

		// Output using MultimediaEngine::TTS() //
		// Output message
		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n' << CentreText("Outputting TTS Message...") << '\n';

		MultimediaEngine meTTS;
		VerbosityDisplay("TTS starting with text \"" + sText + "\"...\n");
		meTTS.TTSOutput(s2ws(sText));

		// Output success message
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("TTS Message successfully outputted!") << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// Stopwatch
	else if (sCommand == "stopwatch" || sCommand == "16") {

		bool bSkipStartScreen = false;
		bool bUserCursorVisibilitySetting = true;

		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::StopwatchHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'i') {
				bSkipStartScreen = true;
			}
		}

		CentreColouredText(" ___STOPWATCH___ ", 1);
		
		if (!bSkipStartScreen) {
			std::cout << wordWrap("\n\nYou can exit the stopwatch at any time by pressing a key on the keyboard.\nPress any key to start, or ESC to exit now...\n");
			char c = _getch();

			// Exit on ESC key press
			if (c == 27) {
				Exiting();
				return true;
			}
		}
		else { 
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\nStopwatch starting immediately.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Start stopwatch
		std::cout << '\n';
		std::chrono::duration<long double> elapsedSeconds;

		// Disable cursor visibility
		bUserCursorVisibilitySetting = DisableCursorVisibility();

		auto start = std::chrono::steady_clock::now();

		while (!_kbhit()) { // exit on keypress
			elapsedSeconds = std::chrono::steady_clock::now() - start;
			std::cout << "Time: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << elapsedSeconds.count();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << " seconds...                \r"; // 16 spaces for decimal space buffer
			sleep(3); // Optimisation for CPU usage; puts CPU to sleep for 3ms
		}

		// Assume keyboard has been pressed
		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nKeyboard pressed.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Output final time
		std::cout << "Final time: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << elapsedSeconds.count();
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " seconds.\n\n";

		ClearKeyboardBuffer();
		// Reset cursor visibility to user settings
		ConfigObjMain.bShowCursor = bUserCursorVisibilitySetting;
		SetCursorAttributes();

		return true;
	}

	// Read
	else if (sCommand == "read" || sCommand == "17") {
		bool bOutputInBinaryMode = false;
		std::string sFilePath = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::ReadHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'b') {
				bOutputInBinaryMode = true;
			}

			if (sStringDataCommandArgs[0] != "") {
				sFilePath = sStringDataCommandArgs[0];
			}
		}
		
		if (sFilePath == "") {
			CentreColouredText(" ___READ___ ", 1);
			std::cout << "\n\n";
			sFilePath = StrInput("Please input file directory (0 to exit, \"*open\" without quotes to use the Windows File Dialogue): > ");
			if (sFilePath == "0") {
				Exiting();
				return true;
			}
		}

		// Open the file dialogue on *open
		if (sFilePath == "*open") {
			// Open with the FileOpen GUI Engine
			std::cout << "Opening with the Windows File Dialogue...\n";
			FileOpenGUIEngine ReadCommand;
			ReadCommand.FileOpenDialogue("Open a File to Read");
			sFilePath = ReadCommand.GetRetrievedPathName();
			// Cancelled
			if (sFilePath == "") {
				Exiting();
				return true;
			}
		}
		else std::cout << '\n';

		// Firstly, test if file is actually real
		std::ifstream fileTestIn;

		// Check if the start of the first argument has a speechmark; 
		// if there is one, use text from the start to the ending speechmark (if there is one)
		if (sFilePath[0] == '\"') {
			size_t nFirstMarkPos = sFilePath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sFilePath.find('\"', nFirstMarkPos) - 1;
			sFilePath = sFilePath.substr(nFirstMarkPos, nFinalMarkPos);
		}

		fileTestIn.open(sFilePath);
		if (fileTestIn.fail()) {
			VerbosityDisplay("In Commands() - ERROR: Unknown directory/file detected. Read operation failed.\n");
			UserErrorDisplay("ERROR - The directory or file doesn't exist. Please try again with a directory/file that exists.\n");

			fileTestIn.close();
			Exiting();
			return true;
		}
		fileTestIn.close();

		// Open a new stream for reading
		std::ifstream fileIn;
		if (bOutputInBinaryMode) {
			// Read file in binary mode
			fileIn.open(sFilePath, std::ios::binary);
		}
		else {
			// Read file in default text mode
			fileIn.open(sFilePath);
		}

		std::string* sFileContents = new std::string;
		std::string* sBuffer = new std::string;
		
		// Copy line by line using std::getline() using buffer
		while (!fileIn.eof()) {
			std::getline(fileIn, *sBuffer);
			*sFileContents += '\n';
			*sFileContents += *sBuffer;
			*sBuffer = "";
		}

		// Output file contents
		if (bAnsiVTSequences) {
			colourHighlight();
			std::cout << ULINE_STR << "File contents are below:" << NOULINE_STR;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\n" << *sFileContents << "\n\n";
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << ULINE_STR << "File Finished." << NOULINE_STR << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else std::cout << "File contents are below:\n\n" << *sFileContents << "\n\nFile Finished.\n";

		fileIn.close();
		delete sFileContents;
		return true;
	}

	// Timer
	else if (sCommand == "timer" || sCommand == "18") {
		long double dInput = 0;
		bool bUserCursorVisibilitySetting = true;

		CentreColouredText(" ___TIMER___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::TimerHelp();
				return true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				// Firstly, check if argument is a real and usable number
				if (isNumberld(sStringDataCommandArgs[0]) == false) {
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("ERROR - Number argument is either too big or not a number.\nPlease try again with a number between 0 and 2 billion.\n");

					return true;
				}

				// Convert string to integral value
				dInput = std::stold(sStringDataCommandArgs[0]);
				break;
			}
		}

		// Only display prompt if no input was provided
		if (dInput == 0) {
			std::cout << "\n";
			dInput = NumInputld("Please input the number of seconds for the timer (0 to exit): > ");
			// Exit on 0 input
			if (dInput <= 0.0) {
				Exiting();
				return true;
			}
		}

		// Start timer with prompts
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nPress any key to exit the timer.\n\n");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Disable cursor visibility
		bUserCursorVisibilitySetting = DisableCursorVisibility();

		std::chrono::duration<long double> elapsedTime{};
		auto start = std::chrono::steady_clock::now();
		auto time = std::chrono::steady_clock::now();

		for (; elapsedTime.count() < dInput; elapsedTime = time - start) {
			std::cout << "Timer: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << dInput - elapsedTime.count();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << " sec (out of ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << dInput;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << " sec)                      \r";
			// Check for keypress
			if (_kbhit()) {
				ClearKeyboardBuffer();
				std::cout << "\n";
				Exiting();
				return true;
			}
			// Check for pause press
			time = std::chrono::steady_clock::now();
			// Optimisation for cpu time/usage
			sleep(10);
		}

		// Make the final time appear as 0 seconds
		std::cout << "Timer: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << "0";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " sec (out of ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << dInput;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " sec)                      ";

		std::cout << '\n';
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Timer finished!") << '\n';
		MessageBeep(MB_OK);
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Reset cursor visibility to user settings
		ConfigObjMain.bShowCursor = bUserCursorVisibilitySetting;
		SetCursorAttributes();

		return true;

	}

	// Beep
	else if (sCommand == "beep" || sCommand == "19") {

		long double dFrequency = 0;
		long double dDuration = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::BeepHelp();
				return true;
			} 
			if (sStringDataCommandArgs[0] != "") {
				// Firstly, check if argument is a real and usable number
				if (isNumberld(sStringDataCommandArgs[0]) == false) {
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("ERROR - Your frequency argument is either too big or not a number.\nPlease try again with a number between 0 and 2 billion.\n");

					return true;
				}

				// Use the specified number in the BeepSound call.
				dFrequency = std::stold(sStringDataCommandArgs[0]);

				if (dFrequency < 0) {
					VerbosityDisplay("ERROR: In Commands() - Numerical value argument incorrect (negative number).\n");
					UserErrorDisplay("ERROR - Your frequency argument is a negative number.\nPlease try again with a number between 0 and 2 billion.\n");

					return true;
				}

				dDuration = 1; // just in case no time argument was passed, use the default 1 second beep
			}
			if (sStringDataCommandArgs[1] != "") {
				// Firstly, check if argument is a real and usable number
				if (isNumberld(sStringDataCommandArgs[1]) == false) {
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("ERROR - Your time argument is either too big or not a number.\nPlease try again with a number between 0 and 2 billion.\n");

					return true;
				}

				// Use the specified number in the BeepSound call.
				dDuration = std::stold(sStringDataCommandArgs[1]);

				// Negative numbers are not allowed.
				if (dDuration < 0) {
					VerbosityDisplay("ERROR: In Commands() - Numerical value argument incorrect (negative number).\n");
					UserErrorDisplay("ERROR - Your time argument is a negative number.\nPlease try again with a number between 0 and 2 billion.\n");

					return true;
				}
			}
		}

		// Only display prompt when command ran without arguments
		if (dFrequency <= 0 && dDuration <= 0) {
			CentreColouredText(" ___BEEP___ ", 1);

			std::cout << "\n\n";
			dFrequency = NumInputld("Please input frequency in Hertz (0 to exit): > ");
			if (dFrequency <= 0) {
				Exiting();
				return true;
			}
			dDuration = NumInputld("Please input duration in seconds (0 to exit): > ");
			if (dDuration <= 0) {
				Exiting();
				return true;
			}
		}
		

		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n' << CentreText("Beep is outputting...") << "\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Run the MultimediaEngine::BeepSound() function to output beep.
		MultimediaEngine meBeep;
		meBeep.BeepSound(dFrequency, (dDuration * 1000));

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Beep output operation complete.") << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// MessageBox
	else if (sCommand == "messagebox" || sCommand == "20") {
		std::string sCaption = "";
		std::string sText = "";
		int nButton = 0;
		int nIcon = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::MessageBoxHelp();
				return true;
			}
			else if (cCommandArgs[i] == 't') {
				if (sStringDataCommandArgs[i] != "") {
					sText = sStringDataCommandArgs[i];
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of text argument found.\nPlease make sure that's there, and try again.\n");

					return true;
				}

			}
			else if (cCommandArgs[i] == 'c') { 
				if (sStringDataCommandArgs[i] != "") {
					sCaption = sStringDataCommandArgs[i];
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of caption text argument found.\nPlease make sure that's there, and try again.\n");

					return true;
				}
			}
			else if (cCommandArgs[i] == 'i') {
				// Uses sStringCommandArgs because the only arguments in this function are string-based
				if (sStringDataCommandArgs[i] != "") {
					nIcon = MessageBoxIconSwitch(sStringDataCommandArgs[i]);
					if (nIcon == 1) return true;
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of icon argument found.\nPlease make sure that's there, and try again.\n");

					return true;
				}
			}
			else if (cCommandArgs[i] == 'b') {
				if (sStringDataCommandArgs[i] != "") {
					nButton = MessageBoxButtonSwitch(sStringDataCommandArgs[i]);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of button argument found.\nPlease make sure that's there, and try again.\n");

					return true;
				}
			}
		}

		if (sCaption == "" && sText == "" && nButton == 0 && nIcon == 0) {
			CentreColouredText(" ___MESSAGEBOX___ ", 1);
			std::cout << '\n';

			// Prompts
			// Icon Selection
			OptionSelectEngine oseMsgBox;
			oseMsgBox.nSizeOfOptions = 4;
			std::string sOptionsIcon[] = {
				"Error",
				"Question Mark",
				"Warning",
				"Information 'I'"
			};
			oseMsgBox.sOptions = sOptionsIcon;
			switch (oseMsgBox.OptionSelect("Please select what icon you want for the message box:", " ICON SELECTION ")) {
			case -1:
				Exiting();
				return true;
			case 1:
				nIcon = 16;
				break;
			case 2:
				nIcon = 32;
				break;
			case 3:
				nIcon = 48;
				break;
			case 4:
				nIcon = 64;
				break;
			default:
				UserErrorDisplay("An unknown error occured while processing your icon argument.\nPlease try again later.\n");
				return true;
			}

			// Button Selection
			oseMsgBox.nSizeOfOptions = 7;
			std::string sOptionsButton[] = {
				"OK",
				"OK + Cancel",
				"Abort + Retry + Ignore",
				"Yes + No + Cancel",
				"Yes + No",
				"Retry + Cancel",
				"Cancel + Try + Continue"
			};
			oseMsgBox.sOptions = sOptionsButton;
			nButton = oseMsgBox.OptionSelect("Please select the button layout for the message box:", " BUTTON SELECTION ") - 1;
			// Because -1 - 1 = -2, so exit
			if (nButton == -2) { 
				Exiting();
				return true;
			}

			// MessageBox Text
			sText = StrInput("Please input the text that you want in the message box (0 to exit): > ");
			std::cout << '\n';
			if (sText == "0") {
				Exiting();
				return true;
			}

			// MessageBox Caption Text
			sCaption = StrInput("Please input the caption text that you want in the message box (0 to exit): > ");
			std::cout << '\n';
			if (sCaption == "0") {
				Exiting();
				return true;
			}
		}

		// Display message box
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nDisplaying messagebox...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (MessageBoxA(NULL, sText.c_str(), sCaption.c_str(), nButton | nIcon) == false) {
			// An error occured
			VerbosityDisplay("In Commands() - ERROR: Possible unknown messagebox return value from OptionSelectEngine::OptionSelect(), or standard WIN32 Function Library error.\n");
			UserErrorDisplay("An error occured while displaying the message box.\nPlease try again later.\n");
		}
		else {
			// Success
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Messagebox successfully displayed!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return true;
	}
	else return false;

	return true;
}
