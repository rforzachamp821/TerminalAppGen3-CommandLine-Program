#pragma once
//
// CarDodgeCore.h - Houses the interface for the CarDodgeCore class.
//
#include <iostream>
#include <limits>
#include <random>
#include "../../../../Core/ZTFormattingDefinitions.h"
#include "../CarInfo/CarInfo.h"

extern CarInfo EnemyCars[128];
extern CarInfo UserCar;
extern const int nEnemyCarArraySize;

class CarDodgeCore 
{
private:
	// InitialiseCarDodgeCore - Initialises the whole core of the CarDodge game.
	//                        - This can include setting variables, attributes of terminal, etc.
	// Parameters - None
	// Return value: None
	//
	void InitialiseCarDodgeCore();

	// GetNextEmptyEnemyCarIndex - This is for the EnemyCars array
	// Returns nEnemyCarArraySize + 1 when there are no more enemy car spaces left.
	int GetNextEmptyEnemyCarIndex();

	short int nNumOfCurrentRenderedEnemyCars = 0; // Symbolises the number of rendered enemy cars currently being rendered on screen
	std::mt19937_64 RandEngine; // Random number generation engine
	bool bCarDodgeCoreInitialised = false; // Indicator to show if game is initialised or not
	bool bSyncWithStdioPrevious = true; // Previous stdio sync value

	// Keys for encryption and decryption for High Scores (This is just a small game - there is no need to go balls-to-the-wall with encrypting hardcoded keys)
	uint64_t nHighScoreKey1 = 19375937;
	uint64_t nHighScoreKey2 = 8452904164671;

	// High score file name
	static constexpr char sHighScoreFileName[] = "GameHighScores.dat";

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

	short int nChanceForPowerUpCarMultiplier = 1; // 1 for 1x chance, 2 for 2x chance, 3 for 3x chance, etc.

	// UninitialiseCarDodgeCore - Uninitialise the CarDodge Core.
	// No parameters or return values.
	//
	inline void UninitialiseCarDodgeCore() {
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
	inline void SetHighScore(uint64_t nNewHighScore) {
		if (nNewHighScore > nCurrentPointsHighScore) {
			nCurrentPointsHighScore = nNewHighScore;
		}
	}

	// RenderCar - Renders a car specified by CarInfo argument.
	//
	void RenderCar(CarInfo ciCarToRender);

	// EraseCar - Erases a car specified by CarInfo argument.
	//
	void EraseCar(CarInfo ciCarToErase);

	// RenderBorders
	void RenderBorders(std::string sSetBorderColourFore = LWHT, std::string sSetBorderColourBack = BLU);

	// MoveUserCarLeft
	void MoveUserCarLeft();

	// MoveUserCarRight
	void MoveUserCarRight();

	// RenderNewEnemyCar
	void RenderNewEnemyCar();

	// MoveAllEnemyCars
	void MoveAllEnemyCars();

	// DeleteEnemyCarAndResetSafely
	void DeleteEnemyCarAndResetSafely(int nEnemyCarArrayIndex);

	// DeleteEnemyCarOnLowerBorderHit
	// Return Values: TRUE or 1 for enemy car deleted, FALSE or 0 for no enemy car deleted.
	bool DeleteEnemyCarOnLowerBorderHit();

	// CheckForCarCollision - Checks if a collision occured between user car and enemy car.
	// Parameters: None
	// Return values: TRUE or 1 for collision occured, FALSE or 0 for no collision occured.
	//
	bool CheckForCarCollision(int* nEnemyCarIteratorValOut = nullptr);

	// CentreTextCarDodge - The CentreText() function, but tuned to centre text between the left and right game borders.
	//                    - The text is centred using spaces, and then returned as an updated string.
	// Parameters: sText - The text to centre.
	// Return Values: Centred text string.
	//
	std::string CentreTextCarDodge(std::string sText, size_t nCustomStringLength = (std::numeric_limits<size_t>::max)());
	
	// UpdateHighScoreFromFile - Gets the current points high score from the High Score file, and store it in nCurrentPointsHighScore.
	//                         - It first must decrypt the high score, and then it can retrieve it.
	// Parameters: None
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	// NOTE: If there is no file to read, the current memory high score will not be updated. A file can be created and updated manually with the UpdateHighScoreInFile() function.
	// NOTE: The current high score will not be updated if the high score that is stored in the high score file is smaller than or equal to the current high score in memory.
	//
	bool UpdateHighScoreFromFile();

	// UpdateHighScoreInFile - Updates the high score value in the high score file, from what is stored in the global variable.
	// Parameters: None
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool UpdateHighScoreInFile();
};