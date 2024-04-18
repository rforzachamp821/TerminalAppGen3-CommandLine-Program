#pragma once
//
// CarDodgeMain.h - Houses the interface for the CarDodgeMain class.
//
#include <chrono>
#include "../CarInfo/CarInfo.h"
#include "../CarDodgeCore/CarDodgeCore.h"

class CarDodgeMain : CarDodgeCore 
{
private:
	uint64_t nSessionPoints = 0;
	std::chrono::duration<long double> nSessionTime;
	uint64_t nSessionLevel = 1;
	std::chrono::milliseconds nSessionEnemyCarInterval = GetSessionLevelEnemyCarInterval();
	bool bPanelAlreadyUpdated = false;

	// UpdatePanelInfo - Updates panel info (points, time, etc)
	void UpdatePanelInfo();

	// DisplayUserLossScreen - Displays the loss screen after crashing into an enemy car.
	// Returns TRUE if user wants to play again, else returns FALSE if user wants to exit to main menu.
	//
	bool DisplayUserLossScreen();

	// ResetGame
	void ResetGame();

	// GetSessionLevel - Gets the current session level according to the number of points collected by the user.
	// Parameters: None
	// Return Value: Numerical session level (uint64_t).
	//
	uint64_t GetSessionLevel();

	// GetSessionEnemyCarInterval - Gets the enemy car production interval time for the current session level, as set by nSessionLevel.
	// Parameters: None
	// Return Value: Enemy car interval in milliseconds (std::chrono::milliseconds).
	//
	std::chrono::milliseconds GetSessionLevelEnemyCarInterval();

	// GetLevelBorderColourFore - Gets the foreground border colour for the current level.
	// Parameters: None
	// Return Value: Foreground border colour (std::string).
	//
	std::string GetLevelBorderColourFore();

	// GetLevelBorderColourBack - Gets the background border colour for the current level.
	// Parameters: None
	// Return Value: Background border colour (std::string).
	//
	std::string GetLevelBorderColourBack();


public:

	// CarDodgeMainGame
	void CarDodgeMainGame();

	// CarDodgeChangeUserCar
	void CarDodgeChangeUserCar();

	// CarDodgeInstructions
	void CarDodgeInstructions();

	// CarDodgeHighScore
	void CarDodgeHighScore();
};