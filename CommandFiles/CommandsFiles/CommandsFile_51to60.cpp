//
// CommandsFile_51to60.cpp - All command code, from command numbers 51 to 60, is here.
//

#include "Commands.h"

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
		}

		// Standard user interface
		OptionSelectEngine oseGame;
		oseGame.nSizeOfOptions = 1;
		std::string sOptions[] = {
			"Car Dodge"
		};
		oseGame.sOptions = sOptions;
		
		while (true) {
			// Get input
			int nInput = oseGame.OptionSelect("Please select which game you would like to play:", " ___GAME___ ");

			if (nInput == 1) {
				CarDodgeMainMenu();
			}
			else if (nInput == -1) {
				Exiting();
				break;
			}
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
	else return false;

	return true;
}
