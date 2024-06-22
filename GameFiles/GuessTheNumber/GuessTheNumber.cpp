//
// GuessTheNumber.cpp - Contains the definitions of the GuessTheNumber class members.
//

#include "GuessTheNumber.h"
#include "../../Core/ZeeTerminalCore.h"
#include "../../Engine/OptionSelectEngine/OptionSelectEngine.h"
#include <conio.h>

// MainGameFn
void GuessTheNumber::MainGameFn() {
	while (true) 
	{
		// Set up environment
		int nCorrectRandNum = RandNumld(100, 0);
		int nNumberOfTriesUsed = 0;
		cls();
		std::cout << wordWrap("\nLet the games begin!\n");
		sleep(1000);
		cls();

		while (true) {
			// Lose if 10 tries passed
			if (nNumberOfTriesUsed >= nNumOfTriesAllowed) 
			{
				// Display win screen
				if (LossScreen(nCorrectRandNum) == true) {
					// Play again
					break;
				}
				else {
					// Exit to menu
					return;
				}
			}

			// Input guess number prompt
			int nUserGuessNumber = 0;
			nUserGuessNumber = NumInputi("\nInput a guess number between 1 and 100 (0 to exit game): > ");

			// Exit to menu on 0
			if (nUserGuessNumber == 0) {
				return;
			}

			// Check if won
			if (nUserGuessNumber == nCorrectRandNum) 
			{
				// Display win screen
				if (WinScreen(nCorrectRandNum, nNumberOfTriesUsed) == true) {
					// Play again
					break;
				}
				else {
					// Exit to menu
					return;
				}
			}

			// if guess number is more than 100
			if (nUserGuessNumber > 100) {
				std::cout << wordWrap("That guess number was higher than 100. Please try again.\n");
				continue;
			}
			// if guess number is less than 0
			else if (nUserGuessNumber < 0) {
				std::cout << wordWrap("That guess number was less than 0. Please try again.\n");
				continue;
			}

			// If wrong but guess number was lower than the correct number
			if (nUserGuessNumber < nCorrectRandNum) {
				nNumberOfTriesUsed++;
				std::cout << wordWrap("\nWrong! Your guess was lower than the correct number.\nYou have " + std::to_string(nNumOfTriesAllowed - nNumberOfTriesUsed) + " tries left (out of " + std::to_string(nNumOfTriesAllowed) + ").\n");
			}
			// If wrong but guess number was higher than the correct number
			else if (nUserGuessNumber > nCorrectRandNum) {
				nNumberOfTriesUsed++;
				std::cout << wordWrap("\nWrong! Your guess was higher than the correct number.\nYou have " + std::to_string(nNumOfTriesAllowed - nNumberOfTriesUsed) + " tries left (out of " + std::to_string(nNumOfTriesAllowed) + ").\n");
			}

			sleep(700);
		}
	}
}

// LossScreen
bool GuessTheNumber::LossScreen(int nCorrectNumber) {
	cls();

	// Display loss screen, display prompt to restart
	colour(LWHT, RED);
	std::cout << wordWrap("  YOU RAN OUT OF TRIES...       ");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	sleep(500);

	slowcharfn(false, "\n\nOh no! You have used up all of your " + std::to_string(nNumOfTriesAllowed) + " tries.\n\nThe correct number was: ");
	colour(BLK, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, std::to_string(nCorrectNumber));
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	slowcharfn(true, ".\n");
	sleep(500);

	bool bPlayAgain = YesNoInput("You lost! Would you like to play again? [y/n]: > ");

	cls();
	return bPlayAgain;
}

// WinScreen
bool GuessTheNumber::WinScreen(int nCorrectNumber, int nNumOfTriesUsed) {
	cls();

	// Display win screen, display prompt to restart
	colour(LWHT, GRN);
	std::cout << wordWrap("  YOU GUESSED THE NUMBER!       ");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	sleep(500);

	slowcharfn(false, "\n\nCongratulations, you won!\nYou guessed the correct number ");
	colour(BLK, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, std::to_string(nCorrectNumber));
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, " within a span of ");
	colour(BLK, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, std::to_string(nNumOfTriesUsed));
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	slowcharfn(true, " tries.\n");
	sleep(500);

	bool bPlayAgain = YesNoInput("Would you like to play again? [y/n]: > ");

	cls();
	return bPlayAgain;
}

// GuessTheNumber_MainMenu
void GuessTheNumber::GuessTheNumber_MainMenu() 
{
	// Change the global colours temporarily - this will be changed back on exit
	std::string sColourGlobalUser = ConfigObjMain.sColourGlobal;
	std::string sColourGlobalUserBack = ConfigObjMain.sColourGlobalBack;
	ConfigObjMain.sColourGlobal = ConfigObjMain.sGTNGameplayColourFore;
	ConfigObjMain.sColourGlobalBack = ConfigObjMain.sGTNGameplayColourBack;

	// Set colour and refresh it to all parts of screen
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	while (true) {
		cls();

		// Display banner
		std::cout << "\n";
		OutputBoxWithText("Welcome to Guess The Number!", LWHT, YLW, BLU, YLW, true);

		// Display options
		OptionSelectEngine oseGuessTheNumber;
		oseGuessTheNumber.nSizeOfOptions = 3;
		std::string sOptions[] = {
			"Play",
			"How To Play",
			"Exit"
		};
		oseGuessTheNumber.sOptions = sOptions;

		int nChoice = oseGuessTheNumber.OptionSelect("Please select where you want to go in Guess The Number:", "", true, true, true);

		// Perform tasks corresponding to input number
		if (nChoice == 1) {
			// Start game
			MainGameFn();
		}
		else if (nChoice == 2) {
			// Display how to play
			cls();
			std::cout << "################################# GUESS THE NUMBER ##############################################\n\n";

			slowcharfn(true, "You have " + std::to_string(nNumOfTriesAllowed) + " tries to guess a number between 0 and 100 inclusive. \n");
			slowcharfn(true, "If you get the answer wrong, the game will tell you if your answer was higher or lower than the correct number.");
			std::cout << "\n";
			slowcharfn(true, "Good luck!\n");
			std::cout << wordWrap("Press any key to go back to main menu...\n");
			std::cout << "#################################################################################################\n";
			_getch();
		}
		else if (nChoice == -1 || nChoice == 3) {
			// Exit game
			break;
		}
		else {
			VerbosityDisplay("In GuessTheNumber::GuessTheNumber_MainMenu() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
			std::cout << wordWrap("Press any key to exit game...");
			_getch();
			break;
		}
	}

	// Change global colours back to user settings and set to whole screen
	ConfigObjMain.sColourGlobal = sColourGlobalUser;
	ConfigObjMain.sColourGlobalBack = sColourGlobalUserBack;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	cls();

	return;
}