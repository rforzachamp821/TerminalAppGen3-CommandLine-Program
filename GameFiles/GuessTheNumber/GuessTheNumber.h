//
// GuessTheNumber.h - Contains the interface of the GuessTheNumber class.
//

// GuessTheNumber - A class containing the Guess The Number game.
//                - In the Guess The Number game, the computer generates a random number between 1 and 100, and you have 10 tries to guess it.
//
class GuessTheNumber {
private:

	// MainGameFn - Main game function.
	void MainGameFn();

	// LossScreen - Function to display screen when user loses.
	// nCorrectNumber - The correct number in the current round.
	// Returns TRUE when user wants to play again, and FALSE when the user wants to go back to main menu.
	bool LossScreen(int nCorrectNumber);

	// WinScreen - Function to display screen when user wins.
	// nCorrectNumber - The correct number in the current round.
	// nNumOfTriesUsed - The number of tries that the user used to get the correct number.
	// Returns TRUE when user wants to play again, and FALSE when the user wants to go back to main menu.
	bool WinScreen(int nCorrectNumber, int nNumOfTriesUsed);

	// nNumOfTriesAllowed - The maximum number of tries allowed in a single round.
	static constexpr int nNumOfTriesAllowed = 10;

public:
	
	// Constructor
	GuessTheNumber() {
		// Nothing to do
	}

	// GuessTheNumber_GameMenu - Game menu for the GuessTheNumber game.
	// No parameters or return values are accepted/available.
	//
	void GuessTheNumber_GameMenu();
};