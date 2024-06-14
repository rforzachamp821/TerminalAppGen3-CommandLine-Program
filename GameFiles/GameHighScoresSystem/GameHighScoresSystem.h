#pragma once
//
// GameHighScoresSystem.h - Contains the interface [namespace] for the GameHighScores System.
//
#include <stdint.h>
#include <string>
#include "../../Core/ZeeTerminalCore.h"

// GameHighScoresSystem - A system dedicated to managing the high scores for different games in ZeeTerminal.
//
namespace GameHighScoresSystem {

	// Anonymous namespace - used to hide inner workings of namespace from user of API
	namespace 
	{
		// High Score variables
		uint64_t nCarDodgeHighScore = 0;
		uint64_t nGuessTheNumberExtremeHighScore = 0;

		// Keys for encryption and decryption for High Scores (These are just small games - there is no need to go balls-to-the-wall with encrypting hardcoded keys)
		constexpr uint64_t nHighScoreKey1 = 19375937;
		constexpr uint64_t nHighScoreKey2 = 8452904164671;

		// High score file name
		char sHighScoreFileName[] = "GameHighScores.dat";

		// isNumberUINT64 - A custom implementation of the isNumberull() ZeeTerminal function that skips any character-based checks and goes straight
		//                  to exception handling of std::stoull.
		//
		bool isNumberUINT64(std::string sCandidate) {
			// Check string validity as number
			// Test if above stoll() range
			try {
				uint64_t nRangeTest = std::stoull(sCandidate);
			}
			catch (const std::out_of_range&) {
				VerbosityDisplay("In isNumberull(): Exception caught - Number is too high/low (out of range).");
				return false;
			}
			catch (const std::invalid_argument&) {
				VerbosityDisplay("In isNumberull(): Exception caught - Argument cannot be converted whatsoever (invalid argument).");
				return false;
			}

			return true;
		}
	}

	// UpdateHighScoreVariables - Updates all high score variables in memory with those saved in the High Score file.
	//                          - The variables will only be updated if the values in the High Score file are larger than the ones in memory.
	//                          - If memory variable X is larger than its associated file high score X, it will NOT be changed.
	// Parameters: None
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool UpdateHighScoreVariables();

	// UpdateHighScoreFile - Updates values saved in High Score File with those saved in the high score variables in memory.
	//                     - The high score file values will be updated with the values in memory, regardless of which is bigger or not.
	// Parameters: None
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool UpdateHighScoreFile();

	// GetHighScoreFileName - Returns the file name of the High Scores file.
	//
	char* GetHighScoreFileName();

	// GetCarDodgeHighScore - Returns the current high score saved in memory of the CarDodge game.
	//
	uint64_t GetCarDodgeHighScore();

	// GetGuessTheNumberExtremeHighScore - Returns the current high score saved in memory of the Guess The Number Extreme game.
	//
	uint64_t GetGuessTheNumberExtremeHighScore();

	// SetCarDodgeHighScore - Set the Car Dodge high score variable.
	//                      - Will only set if argument is larger than current high score saved in the high score variable.
	// Parameters: nValueParam - Value to set Car Dodge high score variable to.
	// Return Values: None
	//
	void SetCarDodgeHighScore(uint64_t nValueParam);

	// SetGuessTheNumberExtremeHighScore - Set the Guess The Number Extreme high score variable.
	//                      - Will only set if argument is larger than current high score saved in the high score variable.
	// Parameters: nValueParam - Value to set Guess The Number Extreme high score variable to.
	// Return Values: None
	//
	void SetGuessTheNumberExtremeHighScore(uint64_t nValueParam);
}