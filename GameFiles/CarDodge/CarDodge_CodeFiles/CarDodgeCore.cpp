//
// CarDodgeCore.cpp - Houses the CarDodgeCore class.
//


CarInfo EnemyCars[128];
CarInfo UserCar;
const int nEnemyCarArraySize = sizeof(EnemyCars) / sizeof(CarInfo);

class CarDodgeCore 
{
private:
	// InitialiseCarDodgeCore - Initialises the whole core of the CarDodge game.
	//                        - This can include setting variables, attributes of terminal, etc.
	// Parameters - None
	// Return value: None
	//
	void InitialiseCarDodgeCore() {
		// Set session console window height - cannot be less than 30
		CONSOLE_SCREEN_BUFFER_INFO csbiTest;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiTest);
		nSessionConsoleHeight = csbiTest.srWindow.Bottom - csbiTest.srWindow.Top;
		if (nSessionConsoleHeight < 29) {
			nSessionConsoleHeight = 29;
		}

		// Initialise random engine
		std::random_device rdRandNum;
		RandEngine.seed(rdRandNum());

		// To improve performance, do not sync with stdio - it's not being used
		bSyncWithStdioPrevious = std::cout.sync_with_stdio(false);

		// Update high score global variable
		UpdateHighScoreFromFile();

		// Game Initialised - Set flag to true
		bCarDodgeCoreInitialised = true;

		return;
	}

	// GetNextEmptyEnemyCarIndex - This is for the EnemyCars array
	// Returns nEnemyCarArraySize + 1 when there are no more enemy car spaces left.
	int GetNextEmptyEnemyCarIndex() {
		int nEnemyCarIndexFind = 0;

		// Reiterate through whole enemy car array to find next empty cell
		for (; nEnemyCarIndexFind < nEnemyCarArraySize; nEnemyCarIndexFind++) {
			if (EnemyCars[nEnemyCarIndexFind].bInUse == false) {
				return nEnemyCarIndexFind;
			}
		}

		return nEnemyCarArraySize + 1; // This is to indicate that there are no more spaces left
	}

	short int nNumOfCurrentRenderedEnemyCars = 0; // Symbolises the number of rendered enemy cars currently being rendered on screen
	std::mt19937_64 RandEngine; // Random number generation engine
	bool bCarDodgeCoreInitialised = false; // Indicator to show if game is initialised or not

	bool bSyncWithStdioPrevious = true; // Previous stdio sync value

	// Keys for encryption and decryption for High Scores (This is just a small game - there is no need to go balls-to-the-wall with encrypting hardcoded keys)
	uint64_t nHighScoreKey1 = 19375937;
	uint64_t nHighScoreKey2 = 8452904164671;

	// High score file name
	static constexpr char sHighScoreFileName[] = "HighScore.dat";

protected:

	// Constants that define the dimensions of the gameplay experience
	short int nSessionConsoleHeight = 0;
	const short int nScreenWidth = 120;
	const short int nLeftBorderWidth = 5;
	const short int nRightBorderWidth = 25;
	const short int nGameplayScreenWidth = nScreenWidth - nRightBorderWidth - nLeftBorderWidth;

	// Border colours for CarDodgeMain::UpdatePanelInfo()
	std::string sBorderColourFore = "";
	std::string sBorderColourBack = "";

	uint64_t nCurrentPointsHighScore = 0;


	// UninitialiseCarDodgeCore - Uninitialise the CarDodge Core.
	// No parameters or return values.
	//
	void UninitialiseCarDodgeCore() {
		// Reset sync with stdio
		std::cout.sync_with_stdio(bSyncWithStdioPrevious);

		// Uninitialised - set flag to false
		bCarDodgeCoreInitialised = false;
	}

	// GetCurrentHighScore
	inline uint64_t GetCurrentHighScore() {
		return nCurrentPointsHighScore;
	}

	// SetHighScore
	// will only set new high score if argument is larger than what is returned by GetHighScore()
	void SetHighScore(uint64_t nNewHighScore) {
		if (nNewHighScore > nCurrentPointsHighScore) {
			nCurrentPointsHighScore = nNewHighScore;
		}

		return;
	}

	// RenderCar - Renders a car specified by CarInfo argument.
	//
	void RenderCar(CarInfo ciCarToRender) {
		// Set starting point
		SetCursorPosition(ciCarToRender.bottomLeft.X, ciCarToRender.bottomLeft.Y - 3);

		// Render all 4 rows
		for (int i = 0; i < 4; i++) {
			// Render car character on screen
			std::cout.write(ciCarToRender.CarStyle[i].data(), 4);
			// Move to next position down for render
			if (i < 3) SetCursorPosition(ciCarToRender.bottomLeft.X, ciCarToRender.bottomLeft.Y + (i - 2));
		}

		return;
	}

	// EraseCar - Erases a car specified by CarInfo argument.
	//
	void EraseCar(CarInfo ciCarToErase) {
		// Set starting point
		SetCursorPosition(ciCarToErase.bottomLeft.X, ciCarToErase.bottomLeft.Y - 3);

		// Erase all 4 rows
		for (int i = 0; i < 4; i++) {
			// 4 because cars are 4 cells in width
			std::cout.write("    ", 4);
			// Move to next position down for erase
			if (i < 3) SetCursorPosition(ciCarToErase.bottomLeft.X, ciCarToErase.bottomLeft.Y + (i - 2));
		}

		return;
	}

	// RenderBorders
	void RenderBorders(std::string sSetBorderColourFore = LWHT, std::string sSetBorderColourBack = BLU) 
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConsole == INVALID_HANDLE_VALUE) {
			// Error handling later
		}

		// Initialise game if not initialised
		if (!bCarDodgeCoreInitialised) {
			InitialiseCarDodgeCore();
		}

		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		cls(); // Set colours to whole screen, clear for gameplay
		SetCursorPosition(0, 0); // Ensure that the cursor position is at the top left of terminal

		// Set border colours for CarDodgeMain::UpdatePanelInfo()
		sBorderColourFore = sSetBorderColourFore;
		sBorderColourBack = sSetBorderColourBack;

		colour(sSetBorderColourFore, sSetBorderColourBack);

		// 1. Draw left side border
		for (short int i = 0; i <= nSessionConsoleHeight; i++) {
			// Repeat creation of sides with std::string buffer
			std::cout << std::string(nLeftBorderWidth - 1, ' ') << '\xb2';
			if (i < nSessionConsoleHeight) std::cout << '\n';
		}

		// 2. Draw right side border
		for (short int i = 0; i <= nSessionConsoleHeight; i++) {
			// Repeat creation of sides with std::string buffer
			SetCursorPosition(nScreenWidth - nRightBorderWidth, i); // 25 is width of information pane
			std::cout << '\xb2' << std::string(nRightBorderWidth - 1, ' ');
			if (i < nSessionConsoleHeight) std::cout << '\n';

		}

		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// MoveUserCarLeft
	void MoveUserCarLeft() {
		// Check if user car is already at the left border
		if (UserCar.bottomLeft.X <= nLeftBorderWidth) {
			return;
		}

		EraseCar(UserCar);

		// Move car left by 2
		UserCar.bottomLeft.X -= 2;
		UserCar.bottomRight.X -= 2;

		RenderCar(UserCar);
		
		return;
	}

	// MoveUserCarRight
	void MoveUserCarRight() {
		// Check if user car is already at the right border
		if (UserCar.bottomRight.X >= nScreenWidth - nRightBorderWidth) {
			return;
		}

		EraseCar(UserCar);

		// Move car right by 2
		UserCar.bottomLeft.X += 2;
		UserCar.bottomRight.X += 2;

		RenderCar(UserCar);

		return;
	}

	// RenderNewEnemyCar
	void RenderNewEnemyCar() {
		static std::uniform_int_distribution<short int> Dist(nLeftBorderWidth, nScreenWidth - nRightBorderWidth - 4);

		// Too many rendered enemy cars at once
		if (nNumOfCurrentRenderedEnemyCars > 128) return;

		// Get next empty enemy car index now
		int nEnemyCarIndex = GetNextEmptyEnemyCarIndex();
		// Get random x co-ord for enemy car
		short int nRandomXCoord = Dist(RandEngine); // 4 because enemy cars are 4 chars in width

		// Set co-ords of this enemy car (the enemy car Y co-ordinate can be used as an identifier)
		EnemyCars[nEnemyCarIndex].bInUse = true;
		EnemyCars[nEnemyCarIndex].bottomLeft = { nRandomXCoord, 3 };
		nRandomXCoord += 4;
		EnemyCars[nEnemyCarIndex].bottomRight = { nRandomXCoord, 3 };

		// Render the new car now
		RenderCar(EnemyCars[nEnemyCarIndex]);
		
		// Finally, increment the number of currently rendered enemy cars
		nNumOfCurrentRenderedEnemyCars++;
	}

	// MoveAllEnemyCars
	void MoveAllEnemyCars() {
		for (int nEnemyCarIterator = 0; nEnemyCarIterator < nEnemyCarArraySize; nEnemyCarIterator++) {
			// Don't attempt to render if enemy car is not in use
			if (!EnemyCars[nEnemyCarIterator].bInUse) continue;

			EraseCar(EnemyCars[nEnemyCarIterator]);

			// Increment Y-values to make enemy cars appear 1 lower on screen
			EnemyCars[nEnemyCarIterator].bottomLeft.Y++;
			EnemyCars[nEnemyCarIterator].bottomRight.Y++;

			RenderCar(EnemyCars[nEnemyCarIterator]);
		}
	}

	// DeleteEnemyCarOnLowerBorderHit
	// Return Values: TRUE or 1 for enemy car deleted, FALSE or 0 for no enemy car deleted.
	bool DeleteEnemyCarOnLowerBorderHit() {
		for (int nEnemyCarIterator = 0; nEnemyCarIterator < nEnemyCarArraySize; nEnemyCarIterator++) {
			// Don't attempt to delete if enemy car is not in use
			if (!EnemyCars[nEnemyCarIterator].bInUse) continue;

			// Check if found enemy car is touching lower border
			if (EnemyCars[nEnemyCarIterator].bottomLeft.Y >= nSessionConsoleHeight) {
				// Erase car
				EraseCar(EnemyCars[nEnemyCarIterator]);

				// Reset car to defaults
				EnemyCars[nEnemyCarIterator].bInUse = false;
				EnemyCars[nEnemyCarIterator].bottomLeft = { 0,0 };
				EnemyCars[nEnemyCarIterator].bottomRight = { 0,0 };
				nNumOfCurrentRenderedEnemyCars--;

				// Because of how cars are rendered one-by-one, we shouldn't expect another car touching the border at this moment, so exit
				return true;
			}
		}

		return false;
	}

	// CheckForCarCollision - Checks if a collision occured between user car and enemy car.
	// Parameters: None
	// Return values: TRUE or 1 for collision occured, FALSE or 0 for no collision occured.
	//
	bool CheckForCarCollision() {
		// Reiterate through all enemy cars to check each one for crash
		for (int nEnemyCarIterator = 0; nEnemyCarIterator < nEnemyCarArraySize; nEnemyCarIterator++) {
			// Don't attempt to check if enemy car is not in use
			if (!EnemyCars[nEnemyCarIterator].bInUse) continue;

			// Check if car is in the necessary Y-coordinates to be in a crash
			if (EnemyCars[nEnemyCarIterator].bottomLeft.Y >= nSessionConsoleHeight - 3) {
				// Check if car is in the necessary X-coordinates to be in a crash
				if (EnemyCars[nEnemyCarIterator].bottomLeft.X < UserCar.bottomRight.X && EnemyCars[nEnemyCarIterator].bottomRight.X > UserCar.bottomLeft.X) {
					return true;
				}
			}
		}

		return false;
	}

	// CentreTextCarDodge - The CentreText() function, but tuned to centre text between the left and right game borders.
	//                    - The text is centred using spaces, and then returned as an updated string.
	// Parameters: sText - The text to centre.
	// Return Values: Centred text string.
	//
	std::string CentreTextCarDodge(std::string sText, size_t nCustomStringLength = std::numeric_limits<size_t>::max())
	{
		// Set string length for this function call
		size_t nStringLength;
		if (nCustomStringLength < std::numeric_limits<size_t>::max()) {
			nStringLength = nCustomStringLength;
		}
		else {
			nStringLength = sText.length();
		}

		// This will centre text between nLeftBorderWidth and (nScreenWidth - nRightBorderWidth)
		const short int nAvailableScreenSpace = (nScreenWidth - nRightBorderWidth) - nLeftBorderWidth;

		// Check to prevent memory overspill
		if (nStringLength >= nAvailableScreenSpace) return sText;

		// Return centred text
		return std::string((nAvailableScreenSpace - nStringLength) / 2, ' ') + sText;
	}
	
	// UpdateHighScoreFromFile - Gets the current points high score from the High Score file, and store it in nCurrentPointsHighScore.
	//                         - It first must decrypt the high score, and then it can retrieve it.
	// Parameters: None
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	// NOTE: If there is no file to read, the current memory high score will not be updated. A file can be created and updated manually with the UpdateHighScoreInFile() function.
	// NOTE: The current high score will not be updated if the high score that is stored in the high score file is smaller than or equal to the current high score in memory.
	//
	bool UpdateHighScoreFromFile() {
		// Open file
		std::ifstream HighScoreFileIn(sHighScoreFileName, std::ios::binary);

		// Check if failed
		if (HighScoreFileIn.fail()) {
			return false;
		}

		// Get length of file
		// Use seek to find file length in bytes to initialise buffer of that size later
		HighScoreFileIn.seekg(0, HighScoreFileIn.end);
		uint64_t nFileByteLength = HighScoreFileIn.tellg();
		HighScoreFileIn.seekg(0, HighScoreFileIn.beg); // move back to beginning

		// Copy all file data to buffer
		std::string sBuffer = std::string(nFileByteLength, '\0');

		// Retrieve data
		HighScoreFileIn.read(sBuffer.data(), nFileByteLength);
		HighScoreFileIn.close();

		// Decrypt data
		RyRyCryptor HighScoreDecryptor;
		std::string sDecryptedData = HighScoreDecryptor.DecryptString(sBuffer, nHighScoreKey1, nHighScoreKey2);

		// Check for errors in decryption
		if (HighScoreDecryptor.GetErrorLevel() > HighScoreDecryptor.N_SUCCESSFUL) {
			return false;
		}

		// Check decrypted data
		if (!isNumberull(sDecryptedData)) {
			return false;
		}

		// Set high score to decrypted number IF the retrieved score is more than the currently-set high score
		SetHighScore(std::stoull(sDecryptedData));

		// Exit
		return true;
	}

	// UpdateHighScoreInFile - Updates the high score value in the high score file, from what is stored in the global variable.
	// Parameters: None
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool UpdateHighScoreInFile() {
		// Encrypt high score and put into string
		RyRyCryptor HighScoreEncryptor;
		std::string sEncryptedHighScore = HighScoreEncryptor.EncryptString(std::to_string(static_cast<long double>(nCurrentPointsHighScore)), nHighScoreKey1, nHighScoreKey2);

		// Open file from fresh in binary mode
		std::ofstream HighScoreFileOut(sHighScoreFileName, std::ios::binary);

		// Check if failed
		if (HighScoreFileOut.fail()) {
			return false;
		}

		// Write to new high score file
		HighScoreFileOut.write(sEncryptedHighScore.data(), sEncryptedHighScore.size());

		// Check if failed again
		if (HighScoreFileOut.fail()) {
			return false;
		}

		// Exit
		return true;
	}
};