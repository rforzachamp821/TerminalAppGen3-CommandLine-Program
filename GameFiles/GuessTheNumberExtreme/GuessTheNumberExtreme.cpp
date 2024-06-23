//
// GuessTheNumberExtreme.cpp - Contains the definitions for GuessTheNumberExtreme class.
//
#include "GuessTheNumberExtreme.h"
#include "../../Core/ZeeTerminalCore.h"
#include "../../Engine/OptionSelectEngine/OptionSelectEngine.h"
#include "../../GameFiles/GameHighScoresSystem/GameHighScoresSystem.h"
#include <conio.h>

// DisplayHighScore
void GuessTheNumberExtreme::DisplayHighScore() {
	// Make sure the high score is updated before outputting
	GameHighScoresSystem::UpdateHighScoreVariables();

	// Output title
	std::cout << "\n";
	colour(WHT, RED);
	slowcharfn(false, "  YOUR HIGH SCORE...         ");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	std::cout << "\n\n\n";
	OutputBoxWithText('\n' + std::string(34 + std::to_string(GameHighScoresSystem::GetGuessTheNumberExtremeHighScore()).length(), ' ') + '\n', RED, YLW, BLK, ConfigObjMain.sColourGlobalBack, true);

	// Set to same height as area of output in rendered box
	CONSOLE_SCREEN_BUFFER_INFO csbiHighScore;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiHighScore);
	SetCursorPosition(0, csbiHighScore.dwCursorPosition.Y - 3);

	// Output high score
	slowcharCentredFn(false, " Your current high score is... " + std::string(std::to_string(GameHighScoresSystem::GetGuessTheNumberExtremeHighScore()).length() + 2, ' '));

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiHighScore);
	SetCursorPosition(csbiHighScore.dwCursorPosition.X - std::to_string(GameHighScoresSystem::GetGuessTheNumberExtremeHighScore()).length() - 2, csbiHighScore.dwCursorPosition.Y);
	colour(BLU, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, std::to_string(GameHighScoresSystem::GetGuessTheNumberExtremeHighScore()) + "!");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	std::cout << "\n\n\n\n";
	std::cout << CentreText("Press any key to continue...") << '\n';
	_getch();

	return;
}

// CorrectGuessScreen
void GuessTheNumberExtreme::CorrectGuessScreen(int nNumOfTriesUsed, uint64_t nCurrentSessionScore) {
	// clear screen for next round
	cls();

	// Display win screen, display prompt to restart
	colour(LWHT, GRN);
	std::cout << wordWrap("  YOU GUESSED THE NUMBER!       ");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	sleep(500);

	// Display that the number was correct with score and number of tries used.
	slowcharfn(false, "\n\nYou got the number right in ");
	colour(BLK, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, std::to_string(nNumOfTriesUsed));
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, +" tries!\nYour new score is: ");
	colour(BLK, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, std::to_string(nCurrentSessionScore));
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	slowcharfn(true, ".\n");

	std::cout << wordWrap("Press any key to move onto the next round...\n");
	_getch();
	cls();
}

// LossScreen
bool GuessTheNumberExtreme::LossScreen(int nCorrectGuessNum, uint64_t nSessionScore) 
{
	// Clear screen to give space for loss screen
	cls();

	// Display loss screen, display prompt to restart
	colour(LWHT, RED);
	std::cout << wordWrap("  YOU RAN OUT OF TRIES...       ");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	sleep(500);

	// Display user loss screen
	slowcharfn(false, "\n\nOh no! You have used up all of your " + std::to_string(PERMISSIBLE_TRIES) + " tries.\n\nThe last correct number was: ");
	colour(BLK, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, std::to_string(nCorrectGuessNum));
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, ".\nYour final score was: ");
	colour(BLK, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, std::to_string(nSessionScore));
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Display 'new high score' if session score was the new high score
	if (GameHighScoresSystem::GetGuessTheNumberExtremeHighScore() < nSessionScore) {
		// Set high score in system as well
		GameHighScoresSystem::SetGuessTheNumberExtremeHighScore(nSessionScore);
		slowcharfn(false, " (NEW HIGH SCORE).");

		// Update game high scores file
		if (!GameHighScoresSystem::UpdateHighScoreFile()) {
			UserErrorDisplay("Failed to update High Scores file.\n");
		}
	}
	else std::cout << ".";

	std::cout << "\n\n";
	sleep(500);

	bool bPlayAgain = YesNoInput("You lost! Would you like to play again? [y/n]: > ");

	cls();
	return bPlayAgain;
}

// MainGame
void GuessTheNumberExtreme::MainGame() 
{
	while (true) 
	{
		// Set up environment to default
		// Calculate random ranges and right numbers for this round
		short int nRightNum = RandNumld(100, 1);
		short int nLowerNum = RandNumld(nRightNum, 1);
		short int nUpperNum = RandNumld(100, nRightNum);
		short int nNumOfTriesUsed = 0;
		uint64_t nCurrentSessionScore = 0;

		cls();
		std::cout << wordWrap("\nLet the games begin!\n");
		sleep(1000);
		cls();

		while (true) 
		{
			// End game if PERMISSIBLE_TRIES nNumOfTriesUsed have passed
			if (nNumOfTriesUsed == PERMISSIBLE_TRIES) 
			{
				if (LossScreen(nRightNum, nCurrentSessionScore) == true) {
					// Play again
					break;
				}
				else {
					// Exit to menu
					return;
				}
			}

			// Display and input
			std::cout << wordWrap("\nThis number is between " + std::to_string(nLowerNum) + " and " + std::to_string(nUpperNum) + ".\n\n");
			int nGuessNum = NumInputi("Input guess number (0 to exit game): > ");

			// Exit on 0
			if (nGuessNum == 0) {
				// Save score as high score if the score was a high score
				if (GameHighScoresSystem::GetGuessTheNumberExtremeHighScore() < nCurrentSessionScore) {
					// Set high score in system as well
					GameHighScoresSystem::SetGuessTheNumberExtremeHighScore(nCurrentSessionScore);

					// Update game high scores file
					if (!GameHighScoresSystem::UpdateHighScoreFile()) {
						UserErrorDisplay("Failed to update High Scores file.\n");
					}
				}
				
				return;
			}

			// Check if number is correct
			if (nGuessNum == nRightNum) {
				nCurrentSessionScore++;

				// Display correct guess number screen
				CorrectGuessScreen(nNumOfTriesUsed, nCurrentSessionScore);

				// Reset and re-calculate necessary variables for next round
				nRightNum = RandNumld(100, 1);
				nLowerNum = RandNumld(nRightNum, 1);
				nUpperNum = RandNumld(100, nRightNum);
				nNumOfTriesUsed = 0;

				// go to end of game round loop
				continue;
			}

			// If higher than upper number
			if (nGuessNum > nUpperNum) {
				std::cout << wordWrap("\nThat guess number was higher than the higher boundary (" + std::to_string(nUpperNum) + "). Please try again.\n");
				continue;
			}
			// If lower than lower number
			else if (nGuessNum < nLowerNum) {
				std::cout << wordWrap("\nThat guess number was less than the lower boundary (" + std::to_string(nLowerNum) + "). Please try again.\n");
				continue;
			}

			// If wrong but guess number was lower than the correct number
			if (nGuessNum < nRightNum) {
				nNumOfTriesUsed++;
				std::cout << wordWrap("\nWrong! Your guess was lower than the correct number.\nYou have " + std::to_string(PERMISSIBLE_TRIES - nNumOfTriesUsed) + " tries left (out of " + std::to_string(PERMISSIBLE_TRIES) + ").\n");
			}
			// If wrong but guess number was higher than the correct number
			else if (nGuessNum > nRightNum) {
				nNumOfTriesUsed++;
				std::cout << wordWrap("\nWrong! Your guess was higher than the correct number.\nYou have " + std::to_string(PERMISSIBLE_TRIES - nNumOfTriesUsed) + " tries left (out of " + std::to_string(PERMISSIBLE_TRIES) + ").\n");
			}

			// To give user time to absorb information recieved
			sleep(700);
		}
	}

	return;
}

// GuessTheNumberExtremeMainMenu
void GuessTheNumberExtreme::GuessTheNumberExtreme_MainMenu() 
{
	// Change the global colours temporarily - this will be changed back on exit
	std::string sColourGlobalUser = ConfigObjMain.sColourGlobal;
	std::string sColourGlobalUserBack = ConfigObjMain.sColourGlobalBack;
	ConfigObjMain.sColourGlobal = ConfigObjMain.sGTNEGameplayColourFore;
	ConfigObjMain.sColourGlobalBack = ConfigObjMain.sGTNEGameplayColourBack;

	// Set colour and refresh it to all parts of screen
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	while (true) {
		cls();

		// Display banner
		std::cout << "\n";
		OutputBoxWithText("Welcome to Guess The Number - Extreme!", LWHT, YLW, BLU, YLW, true);

		// Display options
		OptionSelectEngine oseGuessTheNumber;
		oseGuessTheNumber.nSizeOfOptions = 4;
		std::string sOptions[] = {
			"Play",
			"How To Play",
			"High Score",
			"Exit"
		};
		oseGuessTheNumber.sOptions = sOptions;

		int nChoice = oseGuessTheNumber.OptionSelect("Please select where you want to go in Guess The Number Extreme:", "", true, true, true);

		// Perform tasks corresponding to input number
		if (nChoice == 1) {
			// Start game
			MainGame();
		}

		// Display how to play
		else if (nChoice == 2) {
			cls();
			std::cout << "################################# GUESS THE NUMBER - EXTREME ####################################\n\n";

			slowcharfn(true, "You have " + std::to_string(PERMISSIBLE_TRIES) + " tries to guess a number between 2 randomly picked numbers. \n");
			slowcharfn(true, "These 2 numbers are between 1 and 100. The game will log your highest score.");
			slowcharfn(true, "If you get the answer wrong, the game will tell you if your answer was higher or lower than the correct number.\n");
			std::cout << "\n";
			slowcharfn(true, "Good luck!\n");
			std::cout << wordWrap("Press any key to go back to main menu...\n");
			std::cout << "#################################################################################################\n";
			_getch();
		}

		// Display high score
		else if (nChoice == 3) {
			cls();
			DisplayHighScore();
		}

		// Exit game
		else if (nChoice == -1 || nChoice == 4) {
			// Exit game
			break;
		}

		// Error
		else {
			VerbosityDisplay("In GuessTheNumberExtreme::GuessTheNumberExtreme_MainMenu() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
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