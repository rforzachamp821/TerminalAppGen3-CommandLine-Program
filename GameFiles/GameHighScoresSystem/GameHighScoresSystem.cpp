//
// GameHighScoresSystem.cpp - Contains the definitions for the GameHighScoresSystem namespace.
//
#include "GameHighScoresSystem.h"
#include <fstream>
#include "../../RyRyCryptor/RyRyCryptor.h"
#include "../../Core/ZeeTerminalCore.h"

// UpdateHighScoreVariables
bool GameHighScoresSystem::UpdateHighScoreVariables() {
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

	// Parse the values from the retrieved string
	// The values are separates like this: XXX;YYY
	// XXX is CarDodge value, while YYY is Guess The Number Extreme value
	//
	uint64_t nSemicolonPos = 0;
	for (uint64_t i = 0; i < sDecryptedData.length(); i++) {
		// Found semicolon - break out
		if (sDecryptedData[i] == ';') {
			nSemicolonPos = i;
			break;
		}
	}

	// Assign parsed strings to buffers
	std::string sCarDodgeStrBuf = sDecryptedData.substr(0, nSemicolonPos);
	std::string sGTMEStrBuf = sDecryptedData.substr(nSemicolonPos + 1, std::string::npos);

	// Pop the last semicolon in guess the number extreme string
	sGTMEStrBuf.pop_back();

	// Check parsed decrypted data for validity (number check)
	if (!isNumberUINT64(sCarDodgeStrBuf) || !isNumberUINT64(sGTMEStrBuf)) {
		return false;
	}

	// Set high score to decrypted number IF the retrieved score is more than the currently-set high score
	uint64_t nCarDodgeParsedHighScore = std::stoull(sCarDodgeStrBuf);
	uint64_t nGuessTheNumberExtremeParsedHighScore = std::stoull(sGTMEStrBuf);
	// Set now
	if (nCarDodgeParsedHighScore > nCarDodgeHighScore) {
		nCarDodgeHighScore = nCarDodgeParsedHighScore;
	}
	if (nGuessTheNumberExtremeParsedHighScore > nGuessTheNumberExtremeHighScore) {
		nGuessTheNumberExtremeHighScore = nGuessTheNumberExtremeParsedHighScore;
	}

	// Exit
	return true;
}

// UpdateHighScoreFile
bool GameHighScoresSystem::UpdateHighScoreFile() {
	// Encrypt high scores and put into string in the format of XXX;YYY where X is Car Dodge and Y is Guess The Number Extreme
	RyRyCryptor HighScoreEncryptor;
	std::string sEncryptedHighScore = HighScoreEncryptor.EncryptString(
		std::to_string(nCarDodgeHighScore) + "."  + std::to_string(static_cast<uint64_t>(RandNumld(90000000, 10000000))) + ";"
		+ std::to_string(nGuessTheNumberExtremeHighScore) + "." + std::to_string(static_cast<uint64_t>(RandNumld(90000000, 10000000))) + ";",
		nHighScoreKey1, nHighScoreKey2);

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

// GetHighScoreFileName
char* GameHighScoresSystem::GetHighScoreFileName() {
	return sHighScoreFileName;
}

// GetCarDodgeHighScore
uint64_t GameHighScoresSystem::GetCarDodgeHighScore() {
	return nCarDodgeHighScore;
}

// GetGuessTheNumberExtremeHighScore
uint64_t GameHighScoresSystem::GetGuessTheNumberExtremeHighScore() {
	return nGuessTheNumberExtremeHighScore;
}

// SetCarDodgeHighScore
void GameHighScoresSystem::SetCarDodgeHighScore(uint64_t nValueParam) {
	// Only set if param is larger than current high score
	if (nValueParam > nCarDodgeHighScore) {
		nCarDodgeHighScore = nValueParam;
	}
}

// SetGuessTheNumberExtremeHighScore
void GameHighScoresSystem::SetGuessTheNumberExtremeHighScore(uint64_t nValueParam) {
	// Only set if param is larger than current high score
	if (nValueParam > nGuessTheNumberExtremeHighScore) {
		nGuessTheNumberExtremeHighScore = nValueParam;
	}
}
