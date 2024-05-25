#pragma once
//
// GuessTheNumberExtreme.h - Contains the interface [class] for GuessTheNumberExtreme.
//
#include <stdint.h>

// GuessTheNumberExtreme - A game where you guess a number between 2 randomly-generated numbers in 5 tries,
//                         and fight for the highest score.
//
class GuessTheNumberExtreme 
{
private:
	// PERMISSIBLE_TRIES - Number of tries allowed
	static constexpr int PERMISSIBLE_TRIES = 6;

	// DisplayHighScore - Displays the high score in a neat format. Intended to be accessed from the game menu.
	// There are no return values or parameters.
	//
	void DisplayHighScore();

	// CorrectGuessScreen - Displays the screen for when the user gets a correct guess.
	// Parameters: nNumOfTriesUsed - The number of tries used to get the correct guess.
	//             nCurrentSessionScore - The current session score.
	// Return Values: None
	//
	void CorrectGuessScreen(int nNumOfTriesUsed, uint64_t nCurrentSessionScore);

	// LossScreen - Displays the game loss screen.
	// Parameters: nCorrectGuessNum - The correct guess number for the last round.
	//             nSessionScore - The final score of the whole game.
	// Return values: TRUE or 1 for restart game, FALSE or 0 for do not restart game.
	//
	bool LossScreen(int nCorrectGuessNum, uint64_t nSessionScore);

	// MainGame - The main game interface.
	void MainGame();

public:

	// GuessTheNumberExtreme_MainMenu - The main menu UI for the Guess The Number Extreme game.
	// There are no return values or parameters.
	//
	void GuessTheNumberExtreme_MainMenu();
};
