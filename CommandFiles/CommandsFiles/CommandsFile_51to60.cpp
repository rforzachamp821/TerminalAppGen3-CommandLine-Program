//
// CommandsFile_51to60.cpp - All command code, from command numbers 51 to 60, is here.
//

#include "Commands.h"
#include "../PiConstant/PiConstant.h"

// Undefine EncryptFile macro defined in Windows.h for FileCryptor command
#ifdef EncryptFile
#undef EncryptFile
#endif // ENCRYPTFILE

// Undefine DecryptFile macro defined in Windows.h for FileCryptor command
#ifdef DecryptFile
#undef DecryptFile
#endif // DECRYPTFILE

bool commands::Commands51To60(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer)
{
	// Game
	if (sCommand == "game" || sCommand == "51") {
		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::GameHelp();
				return true;
			}
			
			if (sStringOptionCommandArgs[i] == "cardodge") {
				CarDodgeMainMenu();
				return true;
			}
			else if (sStringOptionCommandArgs[i] == "gtn") {
				// Start Guess The Number
				GuessTheNumber GameLoader;
				GameLoader.GuessTheNumber_MainMenu();
				return true;
			}
			else if (sStringOptionCommandArgs[i] == "gtne") {
				// Start Guess The Number Extreme
				GuessTheNumberExtreme GameLoader;
				GameLoader.GuessTheNumberExtreme_MainMenu();
				return true;
			}
		}

		// Standard user interface
		OptionSelectEngine oseGame;
		oseGame.nSizeOfOptions = 3;
		std::string sOptions[] = {
			"Car Dodge",
			"Guess The Number",
			"Guess The Number Extreme"
		};
		oseGame.sOptions = sOptions;
		
		while (true) {
			// Get input
			int nInput = oseGame.OptionSelect("Please select which game you would like to play:", " ___GAME___ ");

			if (nInput == 1) {
				// Start Car Dodge
				CarDodgeMainMenu();
			}

			else if (nInput == 2) {
				// Start Guess The Number
				GuessTheNumber GameLoader;
				GameLoader.GuessTheNumber_MainMenu();
			}

			else if (nInput == 3) {
				// Start Guess The Number Extreme
				GuessTheNumberExtreme GameLoader;
				GameLoader.GuessTheNumberExtreme_MainMenu();
			}

			// Exit
			else if (nInput == -1) {
				Exiting();
				break;
			}

			// Error
			else {
				VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
			}
		}

		return true;
	}

	// FileCryptor
	else if (sCommand == "filecryptor" || sCommand == "52") {
		bool bUseWindowsEncryption = true; // true for windows encryption, false for RyRy encryption
		std::string sFileName = "";
		RYRYKEY rKey1 = 0;
		RYRYKEY rKey2 = 0;
		int nOption = 0; // 0 is reserved, 1 is encrypt, 2 is decrypt

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::FileCryptorHelp();
				return true;
			}
			// Windows encryption
			else if (cCommandArgs[i] == 'w') {
				bUseWindowsEncryption = true;
			}
			// RyRy encryption
			else if (cCommandArgs[i] == 'r') {
				bUseWindowsEncryption = false;
			}

			if (cCommandArgs[i] == 'e' || sStringOptionCommandArgs[i] == "encrypt") {
				nOption = 1;

				if (sStringDataCommandArgs[i] != "") {
					sFileName = sStringDataCommandArgs[i];
				}
				
				if (bUseWindowsEncryption == false) {
					if (i + 1 < nArgArraySize && sStringDataCommandArgs[i + 1] != "") {
						if (isNumberull(sStringDataCommandArgs[i + 1])) {
							rKey1 = std::stoull(sStringDataCommandArgs[i + 1]);
						}
					}
					if (i + 2 < nArgArraySize && sStringDataCommandArgs[i + 2] != "") {
						if (isNumberull(sStringDataCommandArgs[i + 2])) {
							rKey2 = std::stoull(sStringDataCommandArgs[i + 2]);
						}
					}
				}
			}
			else if (cCommandArgs[i] == 'd' || sStringOptionCommandArgs[i] == "decrypt") {
				nOption = 2;

				if (sStringDataCommandArgs[i] != "") {
					sFileName = sStringDataCommandArgs[i];
				}

				if (bUseWindowsEncryption == false) {
					if (i + 1 < nArgArraySize && sStringDataCommandArgs[i + 1] != "") {
						if (isNumberull(sStringDataCommandArgs[i + 1])) {
							rKey1 = std::stoull(sStringDataCommandArgs[i + 1]);
						}
					}
					if (i + 2 < nArgArraySize && sStringDataCommandArgs[i + 2] != "") {
						if (isNumberull(sStringDataCommandArgs[i + 2])) {
							rKey2 = std::stoull(sStringDataCommandArgs[i + 2]);
						}
					}
				}
			}
		}

		// Output title if there will be input
		if (nOption == 0 || sFileName == "" || (bUseWindowsEncryption == false && rKey1 == 0) || (bUseWindowsEncryption == false && rKey2 == 0)) {
			CentreColouredText(" ___FILECRYPTOR___ ", 1);
			std::cout << "\n";
		}

		// User UI (main prompt screen)
		if (nOption == 0) {
			OptionSelectEngine oseFileCryptor;
			oseFileCryptor.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Encrypt File/Folder",
				"Decrypt File/Folder"
			};
			oseFileCryptor.sOptions = sOptions;
			nOption = oseFileCryptor.OptionSelect("Please select what you want to do now:", "");
		}

		if (nOption == -1) {
			Exiting();
			return true;
		}
		else if (nOption < -1 || nOption == 0 || nOption > 2) {
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
			return true;
		}


		// Encryption and decryption both require only keys and file/folderpath
		if (sFileName == "") {
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Type in \"*open\" for Windows File Dialogue, or \"*openfolder\" for Windows Folder Dialogue.\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			sFileName = StrInput("Please input path to desired file/folder (0 to exit): > ");
			if (sFileName == "0") {
				Exiting();
				return true;
			}
		}

		if (sFileName == "*open") {
			FileOpenGUIEngine FileCryptorOpen;
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Opening the Windows File Dialogue...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			FileCryptorOpen.FileOpenDialogue("Open a File For Encryption", false);
			sFileName = FileCryptorOpen.GetRetrievedPathName();
			if (sFileName == "") {
				Exiting();
				return true;
			}
		}
		else if (sFileName == "*openfolder") {
			FileOpenGUIEngine FileCryptorOpen;
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Opening the Windows File Dialogue for Folder Selection...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			FileCryptorOpen.FileOpenDialogue("Open a Folder For Encryption", true);
			sFileName = FileCryptorOpen.GetRetrievedPathName();
			if (sFileName == "") {
				Exiting();
				return true;
			}
		}

		if (bUseWindowsEncryption == false && rKey1 == 0) {
			std::string sPrompt = "Please input the first key for ";
			if (nOption == 1) sPrompt += "encryption";
			else if (nOption == 2) sPrompt += "decryption";
			rKey1 = PositiveNumInputull(sPrompt + ": > ");
		}
		if (bUseWindowsEncryption == false && rKey2 == 0) {
			std::string sPrompt = "Please input the second key for ";
			if (nOption == 1) sPrompt += "encryption";
			else if (nOption == 2) sPrompt += "decryption";
			rKey2 = PositiveNumInputull(sPrompt + ": > ");
		}

		// Use the retrieved data about execution to encrypt or decrypt file(s)
		if (nOption == 1) {
			if (bUseWindowsEncryption) {
				if (!EncryptFileA(sFileName.c_str())) {
					VerbosityDisplay("In Commands(): ERROR - EncryptFileA() function failed, with error code " + std::to_string(GetLastError()) + ".\n");
					UserErrorDisplay("ERROR - An error occured when encrypting data. Failed with error code " + std::to_string(GetLastError()) + ".\n");
				}
				else {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << CentreText("File/folder encryption successful!") << "\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
			}
			else {
				RyRyCryptor FileCryptorObj;
				uint64_t nNumberOfFailedFiles = 0;

				// Check if directory; if directory, iterate through all files and directories in the directory. Else just encrypt the file.
				std::chrono::steady_clock::time_point TimePointStart = std::chrono::steady_clock::now();
				if (std::filesystem::is_directory(sFileName)) {
					for (const std::filesystem::directory_entry& sDirectoryEntry : std::filesystem::recursive_directory_iterator(sFileName))
					{
						if (sDirectoryEntry.is_regular_file()) {
							if (!FileCryptorObj.EncryptFile(sDirectoryEntry.path().string(), rKey1, rKey2)) {
								UserErrorDisplay("When encrypting " + sDirectoryEntry.path().string() + ": ERROR - " + FileCryptorObj.GetErrorLevelInfo() + "\n");
								nNumberOfFailedFiles++;
							}
						}
					}

				}
				else {
					if (!FileCryptorObj.EncryptFile(sFileName, rKey1, rKey2)) {
						UserErrorDisplay("When encrypting " + sFileName + ": ERROR - " + FileCryptorObj.GetErrorLevelInfo() + "\n");
						nNumberOfFailedFiles++;
					}
				}
			
				std::chrono::steady_clock::time_point TimePointEnd = std::chrono::steady_clock::now();
				std::chrono::duration<long double> ElapsedSeconds = TimePointEnd - TimePointStart;

				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				if (nNumberOfFailedFiles > 0) {
					std::cout << "File/folder encryption complete!\n" << nNumberOfFailedFiles << " files have not been encrypted due to an error. Errors have been displayed above.\nElapsed Time: " << ElapsedSeconds.count() << " seconds.\n\n";
				}
				else {
					std::cout << "File/folder encryption successfully completed!\nElapsed Time: " << ElapsedSeconds.count() << " seconds.\n\n";
				}
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
		}
		else if (nOption == 2) {
			if (bUseWindowsEncryption) {
				if (!DecryptFileA(sFileName.c_str(), NULL)) {
					VerbosityDisplay("In Commands(): ERROR - DecryptFileA() function failed, with error code " + std::to_string(GetLastError()) + ".\n");
					UserErrorDisplay("ERROR - An error occured when decrypting data. Failed with error code " + std::to_string(GetLastError()) + ".\n");
				}
				else {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << CentreText("File/folder decryption successful!") << "\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
			}
			else {
				RyRyCryptor FileCryptorObj;
				uint64_t nNumberOfFailedFiles = 0;

				// Check if directory; if directory, iterate through all files and directories in the directory. Else just encrypt the file.
				std::chrono::steady_clock::time_point TimePointStart = std::chrono::steady_clock::now();
				if (std::filesystem::is_directory(sFileName)) {
					for (const std::filesystem::directory_entry& sDirectoryEntry : std::filesystem::recursive_directory_iterator(sFileName))
					{
						if (sDirectoryEntry.is_regular_file()) {
							if (!FileCryptorObj.DecryptFile(sDirectoryEntry.path().string(), rKey1, rKey2)) {
								UserErrorDisplay("When decrypting " + sDirectoryEntry.path().string() + ": ERROR - " + FileCryptorObj.GetErrorLevelInfo() + "\n");
								nNumberOfFailedFiles++;
							}
						}
					}

				}
				else {
					if (!FileCryptorObj.DecryptFile(sFileName, rKey1, rKey2)) {
						UserErrorDisplay("When decrypting " + sFileName + ": ERROR - " + FileCryptorObj.GetErrorLevelInfo() + "\n");
						nNumberOfFailedFiles++;
					}
				}
				std::chrono::steady_clock::time_point TimePointEnd = std::chrono::steady_clock::now();
				std::chrono::duration<long double> ElapsedSeconds = TimePointEnd - TimePointStart;

				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				if (nNumberOfFailedFiles > 0) {
					std::cout << "File/folder decryption complete!\n" << nNumberOfFailedFiles << " files have not been decrypted due to an error. Errors have been displayed above.\nElapsed Time: " << ElapsedSeconds.count() << " seconds.\n\n";
				}
				else {
					std::cout << "File/folder decryption successfully completed!\nElapsed Time: " << ElapsedSeconds.count() << " seconds.\n\n";
				}
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
		}

		return true;
	}

	// Delete
	else if (sCommand == "delete" || sCommand == "53") {
		std::string sFileName = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::DeleteHelp();
				return true;
			}

			if (sStringDataCommandArgs[i] != "") {
				sFileName = sStringDataCommandArgs[i];
			}
		}

		if (sFileName == "") {
			// Output title, prompt input
			CentreColouredText(" ___DELETE___ ", 1);

			std::cout << wordWrap("\n\nThis command allows you to delete files or folders permanently.\n");
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Type in \"*open\" for Windows File Dialogue, or \"*openfolder\" for Windows Folder Dialogue.\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			sFileName = StrInput("Please input the path to the file/folder you want to delete (0 to exit): > ");
			if (sFileName == "0") {
				Exiting();
				return true;
			}
		}


		if (sFileName == "*open") {
			FileOpenGUIEngine DeleteOpen;
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Opening the Windows File Dialogue...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			DeleteOpen.FileOpenDialogue("Open a File For Encryption", false);
			sFileName = DeleteOpen.GetRetrievedPathName();
			if (sFileName == "") {
				Exiting();
				return true;
			}
		}
		else if (sFileName == "*openfolder") {
			FileOpenGUIEngine DeleteOpen;
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Opening the Windows File Dialogue for Folder Selection...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			DeleteOpen.FileOpenDialogue("Open a Folder For Encryption", true);
			sFileName = DeleteOpen.GetRetrievedPathName();
			if (sFileName == "") {
				Exiting();
				return true;
			}
		}

		// Delete file/folder
		try {
			std::error_code ecDelete{};
			uintmax_t nReturnCode = std::filesystem::remove_all(sFileName, ecDelete);

			// 0 means no files have been deleted
			if (nReturnCode == 0) {
				VerbosityDisplay("In Commands(): ERROR - Failed to delete file/folder. Error code: 2. Error info: File/folder not found.\n");
				UserErrorDisplay("ERROR - An error occured when deleting file/folder. Error info: File/folder not found.\n");
				return true;
			}
			// -1 means error
			else if (nReturnCode == -1) {
				VerbosityDisplay("In Commands(): ERROR - Failed to delete file/folder. Error code: " + std::to_string(ecDelete.value()) + ". Error info: " + ecDelete.message() + ".\n");
				UserErrorDisplay("ERROR - An error occured when deleting file/folder. Error code: " + std::to_string(ecDelete.value()) + ".\n");
				return true;
			}
		}

		catch (std::bad_alloc&) {
			VerbosityDisplay("In Commands(): ERROR - Memory allocation failed for std::filesystem::remove_all().\n");
			UserErrorDisplay("ERROR - Failed to allocate memory. Please try again later.\n");
			return true;
		}

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n' << CentreText("File/folder deletion successful!") << "\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	} 

	// Factorial
	else if (sCommand == "factorial" || sCommand == "54") {
		uint64_t nNumberToCalculate = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::FactorialHelp();
				return true;
			}

			if (sStringDataCommandArgs[i] != "") {
				// Assign argument to number to calculate variable
				if (isNumberull(sStringDataCommandArgs[i])) {
					nNumberToCalculate = std::stoull(sStringDataCommandArgs[i]);
				}
			}
		}

		// Display user interface if nothing recieved from argument/parameter
		if (nNumberToCalculate == 0) {
			CentreColouredText(" ___FACTORIAL___ ", 1);
			std::cout << "\n\n";
			colour(LBLU, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("This command calculates the factors and prime factors of a positive integer.\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Prompt
			nNumberToCalculate = PositiveNumInputull("Please input the number you want to find factors of (0 to exit): > ");

			// Exit on 0
			if (nNumberToCalculate == 0) {
				Exiting();
				return true;
			}
		}

		// Calculate and output results
		std::cout << "\n";
		colourSubheading();
		std::cout << " Results: " << NOULINE_STR;

		colour(RED, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nPrime Factors of " << nNumberToCalculate << ": ";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << GetNumPrimeFactorsAsString(nNumberToCalculate) << "\n";
		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Factors of " << nNumberToCalculate << ": ";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << GetNumFactorsAsString(nNumberToCalculate) << "\n";

		// Complete - exit
		return true;
	}

	// CalcQuadratic
	else if (sCommand == "calcquadratic" || sCommand == "55") {
		long double dAValue = 0;
		long double dBValue = 0;
		long double dCValue = 0;
		bool bFromArgument = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::CalcQuadraticHelp();
				return true;
			}

			// Calculate from argument
			if (sStringDataCommandArgs[0] != "" || sStringDataCommandArgs[1] != "" || sStringDataCommandArgs[2] != "") {
				// Report error if not all necessary arguments are given
				if (sStringDataCommandArgs[0] == "" || sStringDataCommandArgs[1] == "" || sStringDataCommandArgs[2] == "") {
					VerbosityDisplay("In commands::Commands51To60(): ERROR - Vital arguments not found. User may have not supplied them properly.\n");
					UserErrorDisplay("ERROR - An A, B or C argument has been detected to be missing when attempting to calculate. Please ensure that the arguments are there or properly formatted, and try again.\nSee \"calcquadratic -h\" for more info.\n");
					return true;
				}
				else {
					if (isNumberld(sStringDataCommandArgs[0])) {
						// Assign A-value
						dAValue = std::stold(sStringDataCommandArgs[0]);
						bFromArgument = true;
					}
					else {
						// Error - bad argument
						VerbosityDisplay("In commands::Commands51To60(): ERROR - A argument is not a usable/recognisable number. Unable to continue quadratic calculation.\n");
						UserErrorDisplay("ERROR - The supplied C argument is not a number. Please ensure that the A argument that has been supplied is numerical, and try again.\nSee \"calcquadratic -h\" for more info.\n");
						return true;
					}
					if (isNumberld(sStringDataCommandArgs[1])) {
						// Assign B-value
						dBValue = std::stold(sStringDataCommandArgs[1]);
						bFromArgument = true;
					}
					else {
						// Error - bad argument
						VerbosityDisplay("In commands::Commands51To60(): ERROR - B argument is not a usable/recognisable number. Unable to continue quadratic calculation.\n");
						UserErrorDisplay("ERROR - The supplied C argument is not a number. Please ensure that the B argument that has been supplied is numerical, and try again.\nSee \"calcquadratic -h\" for more info.\n");
						return true;
					}
					if (isNumberld(sStringDataCommandArgs[2])) {
						// Assign C-value
						dCValue = std::stold(sStringDataCommandArgs[2]);
						bFromArgument = true;
					}
					else {
						// Error - bad argument
						VerbosityDisplay("In commands::Commands51To60(): ERROR - C argument is not a usable/recognisable number. Unable to continue quadratic calculation.\n");
						UserErrorDisplay("ERROR - The supplied C argument is not a number. Please ensure that the C argument that has been supplied is numerical, and try again.\nSee \"calcquadratic -h\" for more info.\n");
						return true;
					}
				}
			}
		}

		// User interface
		if (bFromArgument == false) {
			CentreColouredText(" ___CALCQUADRATIC___ ", 1);
			colour(LBLU, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\n\nThis command allows you to calculate the values of a quadratic expression quickly and easily, by only asking for A, B and C values to do so.\nThis is based on the expression form: Ax^2 + Bx + C = 0.\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Get A-value
			while (true) {
				std::string sInput = StrInput("Please input the A-value for the expression (\"exit\" to exit): > ");
				if (sInput == "exit") {
					Exiting();
					return true;
				}
				// Convert sInput to long double, assign to corresponding variable
				if (isNumberld(sInput)) {
					dAValue = std::stold(sInput);
					break;
				}
				else {
					colour(RED, ConfigObjMain.sColourGlobalBack);
					std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					continue;
				}
			}


			// Get B-value
			while (true) {
				std::string sInput = StrInput("Please input the B-value for the expression (\"exit\" to exit): > ");
				if (sInput == "exit") {
					Exiting();
					return true;
				}
				// Convert sInput to long double, assign to corresponding variable
				if (isNumberld(sInput)) {
					dBValue = std::stold(sInput);
					break;
				}
				else {
					colour(RED, ConfigObjMain.sColourGlobalBack);
					std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					continue;
				}
			}

			// Get C-value
			while (true) {
				std::string sInput = StrInput("Please input the C-value for the expression (\"exit\" to exit): > ");
				if (sInput == "exit") {
					Exiting();
					return true;
				}
				// Convert sInput to long double, assign to corresponding variable
				if (isNumberld(sInput)) {
					dCValue = std::stold(sInput);
					break;
				}
				else {
					colour(RED, ConfigObjMain.sColourGlobalBack);
					std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					continue;
				}
			}
		}

		// Compute values
		long double dFinalValue1 = (-(dBValue)+sqrtl(std::powl(dBValue, 2) - 4 * dAValue * dCValue)) / (2 * dAValue);
		long double dFinalValue2 = (-(dBValue)-sqrtl(std::powl(dBValue, 2) - 4 * dAValue * dCValue)) / (2 * dAValue);

		// Output results
		std::cout << "\n";
		colourSubheading();
		std::cout << " Results: " << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Only output both values if they do not equal each other
		if (dFinalValue1 == dFinalValue2) {
			std::cout << wordWrap("\n\nCalculated Value: ");
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap(std::to_string(dFinalValue1) + "\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Otherwise, output both computed values
		else {
			std::cout << wordWrap("\n\nFirst Calculated Value: ");
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap(std::to_string(dFinalValue1));
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nSecond Calculated Value: ");
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap(std::to_string(dFinalValue2) + "\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return true;
	}

	// Y2038
	else if (sCommand == "y2038" || sCommand == "56") {
		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::Y2038Help();
				return true;
			}
		}

		// Get current time since epoch, calculate time until Y2038 bug
		const time_t nTimeSinceEpoch = time(0);
		time_t nTimeUntilY2038WorkingVar = std::numeric_limits<int32_t>::max() - nTimeSinceEpoch;

		// Calculate years and days and hours and minutes and seconds (all in one) until crisis occurence
		// Calculate years
		time_t nTimeUntilY2038Years = nTimeUntilY2038WorkingVar / 31536000;
		nTimeUntilY2038WorkingVar -= nTimeUntilY2038Years * 31536000;

		// Calculate days
		time_t nTimeUntilY2038Days = nTimeUntilY2038WorkingVar / 86400;
		nTimeUntilY2038WorkingVar -= nTimeUntilY2038Days * 86400;

		// Calculate hours
		time_t nTimeUntilY2038Hours = nTimeUntilY2038WorkingVar / 3600;
		nTimeUntilY2038WorkingVar -= nTimeUntilY2038Hours * 3600;

		// Calculate minutes
		time_t nTimeUntilY2038Minutes = nTimeUntilY2038WorkingVar / 60;
		nTimeUntilY2038WorkingVar -= nTimeUntilY2038Minutes * 60;

		// Finally, use remaining as seconds (which it is correct).
		time_t nTimeUntilY2038Seconds = nTimeUntilY2038WorkingVar;

		// Display the time left in seconds
		std::cout << wordWrap("Raw seconds left until Y2038 crisis: ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << std::numeric_limits<int32_t>::max() - nTimeSinceEpoch;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " sec\n\n";
		
		// Display time left in a more readable format (years, months, days, hours, seconds left, etc)
		std::cout << wordWrap("Time left (in a more readable format): ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nTimeUntilY2038Years;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(" years, ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nTimeUntilY2038Days;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(" days, ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nTimeUntilY2038Hours;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(" hours, ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nTimeUntilY2038Minutes;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(" minutes, ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nTimeUntilY2038Seconds;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(" seconds.\n");

		return true;
	}

	// PiOutput
	else if (sCommand == "pioutput" || sCommand == "57") {
		int nNumOfDPOutput = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::PiOutputHelp();
				return true;
			}
			
			if (sStringDataCommandArgs[i] != "") {
				// Incorrect argument type
				if (!isNumberi(sStringDataCommandArgs[i])) {
					VerbosityDisplay("In CommandsFile51To60() - ERROR: Number argument (in the form of string) is invalid or out of range.\n");
					UserErrorDisplay("ERROR - Your number argument seems to be incorrect. Make sure it is an integer, and try again later.\n");

					return true;
				}
				// Argument check successful - Convert and check for size of number
				else {
					nNumOfDPOutput = std::stoi(sStringDataCommandArgs[i]);
					if (nNumOfDPOutput < 1 || nNumOfDPOutput > 1000000) {
						VerbosityDisplay("In CommandsFile51To60() - ERROR: Number argument is less than 1 or more than 1000000, which exceeds the allowed range for the PiOutput command.\n");
						UserErrorDisplay("ERROR - Your number argument seems to be out of range of acceptable arguments of decimal places. Please ensure that the argument is not less than 1 or more than 1 million, and try again.\nSee \"pioutput -h\" for more info.\n");

						return true;
					}
				}
			}
		}

		// User Interface
		if (nNumOfDPOutput == 0) {
			CentreColouredText(" ___PIOUTPUT___ ", 1);

			colour(CYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\n\nThis command allows you to output Pi to any number of decimal places between 1 and 1 million.\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Loop until desired input is given
			while (true) 
			{
				// Prompt for decimal place input
				nNumOfDPOutput = NumInputi("Please input the number of decimal places you want (min 1, max 1 million) (0 to exit): > ");

				// Exiting
				if (nNumOfDPOutput == 0) {
					Exiting();
					return true;
				}

				// Range check to ensure number is between 1 and 1 million
				if (nNumOfDPOutput < 1 || nNumOfDPOutput > 1000000) {
					UserErrorDisplay("ERROR: The number that has just been inputted is not in between 1 and 1 million. Please try again with a number that is within range.\n");
					continue;
				}
				else break; // Start pi output
			}
		}

		// Output
		// 2 + nNumOfDPOutput to include the beginning "3." as it isn't part of the decimal places
		std::cout << "\n" << ULINE_STR << wordWrap("Pi truncated to " + std::to_string(nNumOfDPOutput) + " decimal places:") << NOULINE_STR << "\n\n" << piconstant::sPiConstantString.substr(0, 2 + nNumOfDPOutput) << "\n\n";

		// Output success message
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Output successfully completed.\n");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// Spam
	else if (sCommand == "spam" || sCommand == "58") {
		std::string sSpamString = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::SpamHelp();
				return true;
			}

			if (sStringDataCommandArgs[i] != "") {
				sSpamString = sStringDataCommandArgs[i];
			}
		}

		// User interface
		if (sSpamString == "") {
			CentreColouredText(" ___SPAM___ ", 1);
			colour(CYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\n\nThis command allows you to spam any string indefinitely, until the ESC keyboard key is pressed.\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Prompt for string
			sSpamString = StrInput("Please input your desired string to spam (0 to exit): > ");

			// Exit on 0
			if (sSpamString == "0") {
				Exiting();
				return true;
			}
		}

		// Spam string with a whitespace character in between
		std::cout << "\n";
		while (true) {
			if (_kbhit()) {
				if (_getch() == 27) {
					break;
				}
			}

			std::cout << sSpamString << " ";
		}

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\n\nESC key pressed. Spam successful.\n");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	// FAQ
	else if (sCommand == "faq" || sCommand == "59") {
		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::FAQHelp();
				return true;
			}
		}

		// Output title and subheading for FAQ QA output
		CentreColouredText(" ___FAQ___ ", 1);
		std::cout << "\n\n";
		colourSubheading();
		std::cout << "___Questions___" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Output questions and answers
		std::cout << wordWrap("\n\n1) I can't see the terminal text. How can I zoom in?\n  1a) You can zoom in, of course. Press and hold the Ctrl button and scroll with the mouse to your desired text size.\n"
			"\n\n2) The error messages shown aren't detailed enough. How do I get better-quality error messages?\n  2a) To get better quality error messages, just enable the Verbosity Messages setting in the Settings command.\n"
			"\n\n3) I'm using the Windows 7 terminal. How do I scroll up and down in the terminal without using the mouse?\n  3a) To scroll up and down without the mouse, press Alt + Space and then the keys 'E' and 'L', and then scroll with the up/down arrow keys. Use the PageUp/PageDown keys to scroll full pages in the terminal.\n"
			"\n\n4) What is the difference between the 'old' and 'new' OptionSelect Session styles?\n  4a) The 'old' style is an inspiration from the TerminalAppGen2, the previous iteration of this program. It is very robust, simple and works by associating a number with each option, which you type in and press ENTER to select.\nThe 'new' style isn't exactly new, and has been in ZeeTerminal since v0.1.0. However, it is newer than the 'old' style, hence it's referred to as 'new'. It relies on using the arrow/WS keys to move a highlight up and down, to select an option.\n\n");

		return true;
	}

	// About
	else if (sCommand == "about" || sCommand == "60") {
		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::AboutHelp();
				return true;
			}
		}

		About(false);

		return true;
	}

	else return false;

	return true;
}
