// 
// ColConv.cpp - Contains all the colour conversion function definitions in the colconv namespace.
//
#include "ZeeTerminalCore.h"
#include "../Core/ZTFormattingDefinitions.h"
#include <string>

namespace zt {
	namespace colconv {

		// A switch-case function that returns a colour associated with its number.
		std::string NumberToColour(int nNumberChoice) {

			// Switch case based on number choice
			switch (nNumberChoice) {
			case 1:
				return BLK;
				break;
			case 2:
				return BLU;
				break;
			case 3:
				return GRN;
				break;
			case 4:
				return CYN;
				break;
			case 5:
				return RED;
				break;
			case 6:
				return MAG;
				break;
			case 7:
				return YLW;
				break;
			case 8:
				return WHT;
				break;
			case 9:
				return GRAY;
				break;
			case 10:
				return LBLU;
				break;
			case 11:
				return LGRN;
				break;
			case 12:
				return LCYN;
				break;
			case 13:
				return LRED;
				break;
			case 14:
				return LMAG;
				break;
			case 15:
				return LYLW;
				break;
			case 16:
				return LWHT;
				break;
			default:
				VerbosityDisplay("ERROR - An error occured when returning the colour string associated with its number. This is probably a bug.\n");
				break;
			}

			return "";
		}

		// A switch-case function that returns a number associated with one of the default colour strings.
		// 0 is returned on error.
		int ColourToNumber(std::string sColourChoice)
		{
			if (sColourChoice == BLK) {
				return 1;
			}
			else if (sColourChoice == BLU) {
				return 2;
			}
			else if (sColourChoice == GRN) {
				return 3;
			}
			else if (sColourChoice == CYN) {
				return 4;
			}
			else if (sColourChoice == RED) {
				return 5;
			}
			else if (sColourChoice == MAG) {
				return 6;
			}
			else if (sColourChoice == YLW) {
				return 7;
			}
			else if (sColourChoice == WHT) {
				return 8;
			}
			else if (sColourChoice == GRAY) {
				return 9;
			}
			else if (sColourChoice == LBLU) {
				return 10;
			}
			else if (sColourChoice == LGRN) {
				return 11;
			}
			else if (sColourChoice == LCYN) {
				return 12;
			}
			else if (sColourChoice == LRED) {
				return 13;
			}
			else if (sColourChoice == LMAG) {
				return 14;
			}
			else if (sColourChoice == LYLW) {
				return 15;
			}
			else if (sColourChoice == LWHT) {
				return 16;
			}
			else {
				VerbosityDisplay("ERROR - An error occured when returning the number associated with its colour string. This is probably a bug.\n");
				return 0;
			}

			return 0;
		}

		// ColourToDisplayColour - Converts an RGB colour string into a string appropriate for the average user.
		std::string ColourToLogicalDisplayName(std::string sRGBColourString) {
			if (sRGBColourString == BLK) {
				return "Black";
			}
			else if (sRGBColourString == BLU) {
				return "Blue";
			}
			else if (sRGBColourString == GRN) {
				return "Green";
			}
			else if (sRGBColourString == CYN) {
				return "Aqua";
			}
			else if (sRGBColourString == RED) {
				return "Red";
			}
			else if (sRGBColourString == MAG) {
				return "Purple";
			}
			else if (sRGBColourString == YLW) {
				return "Yellow";
			}
			else if (sRGBColourString == WHT) {
				return "White";
			}
			else if (sRGBColourString == GRAY) {
				return "Gray";
			}
			else if (sRGBColourString == LBLU) {
				return "Light Blue";
			}
			else if (sRGBColourString == LGRN) {
				return "Light Green";
			}
			else if (sRGBColourString == LCYN) {
				return "Light Aqua";
			}
			else if (sRGBColourString == LRED) {
				return "Light Red";
			}
			else if (sRGBColourString == LMAG) {
				return "Light Purple";
			}
			else if (sRGBColourString == LYLW) {
				return "Light Yellow";
			}
			else if (sRGBColourString == LWHT) {
				return "Bright White";
			}
			else {
				return "";
			}

			return "";
		}

		// A switch-case function that returns the win32 equivalent of ANSI colours
		std::string Win32ToAnsiColours(std::string sWin32Colour)
		{
			if (sWin32Colour == BLK_WIN32) {
				return BLK_ANSI;
			}
			else if (sWin32Colour == RED_WIN32) {
				return RED_ANSI;
			}
			else if (sWin32Colour == GRN_WIN32) {
				return GRN_ANSI;
			}
			else if (sWin32Colour == YLW_WIN32) {
				return YLW_ANSI;
			}
			else if (sWin32Colour == BLU_WIN32) {
				return BLU_ANSI;
			}
			else if (sWin32Colour == MAG_WIN32) {
				return MAG_ANSI;
			}
			else if (sWin32Colour == CYN_WIN32) {
				return CYN_ANSI;
			}
			else if (sWin32Colour == WHT_WIN32) {
				return WHT_ANSI;
			}
			else if (sWin32Colour == GRAY_WIN32) {
				return GRAY_ANSI;
			}
			else if (sWin32Colour == LRED_WIN32) {
				return LRED_ANSI;
			}
			else if (sWin32Colour == LGRN_WIN32) {
				return LGRN_ANSI;
			}
			else if (sWin32Colour == LYLW_WIN32) {
				return LYLW_ANSI;
			}
			else if (sWin32Colour == LBLU_WIN32) {
				return LBLU_ANSI;
			}
			else if (sWin32Colour == LMAG_WIN32) {
				return LMAG_ANSI;
			}
			else if (sWin32Colour == LCYN_WIN32) {
				return LCYN_ANSI;
			}
			else if (sWin32Colour == LWHT_WIN32) {
				return LWHT_ANSI;
			}
			else {
				return "";
			}
		}

		// A switch-case function that returns the ANSI RGB equivalent of Win32 colours
		std::string AnsiToWin32Colours(std::string sAnsiColour)
		{
			if (sAnsiColour == BLK_ANSI) {
				return BLK_WIN32;
			}
			else if (sAnsiColour == RED_ANSI) {
				return RED_WIN32;
			}
			else if (sAnsiColour == GRN_ANSI) {
				return GRN_WIN32;
			}
			else if (sAnsiColour == YLW_ANSI) {
				return YLW_WIN32;
			}
			else if (sAnsiColour == BLU_ANSI) {
				return BLU_WIN32;
			}
			else if (sAnsiColour == MAG_ANSI) {
				return MAG_WIN32;
			}
			else if (sAnsiColour == CYN_ANSI) {
				return CYN_WIN32;
			}
			else if (sAnsiColour == WHT_ANSI) {
				return WHT_WIN32;
			}
			else if (sAnsiColour == GRAY_ANSI) {
				return GRAY_WIN32;
			}
			else if (sAnsiColour == LRED_ANSI) {
				return LRED_WIN32;
			}
			else if (sAnsiColour == LGRN_ANSI) {
				return LGRN_WIN32;
			}
			else if (sAnsiColour == LYLW_ANSI) {
				return LYLW_WIN32;
			}
			else if (sAnsiColour == LBLU_ANSI) {
				return LBLU_WIN32;
			}
			else if (sAnsiColour == LMAG_ANSI) {
				return LMAG_WIN32;
			}
			else if (sAnsiColour == LCYN_ANSI) {
				return LCYN_WIN32;
			}
			else if (sAnsiColour == LWHT_ANSI) {
				return LWHT_WIN32;
			}
			else {
				return "";
			}
		}

		// Checks all ConfigObjMain.sColour colours to see if they don't exceed the WIN32 colour limit (8192)
		// Returns TRUE for all correct, FALSE for 1 or more variables incorrect.
		bool ValidateColourStringsWin32() {
			bool bSuccess = true;

			// Check validity of WIN32 values - They may not exceed 8192 (base 10).
			if (not (isNumberi(ConfigObjMain.sColourGlobal) && std::stoi(ConfigObjMain.sColourGlobal) < 8192)) {
				ConfigObjMain.sColourGlobal = LWHT_WIN32;
				bSuccess = false;
			}
			if (not (isNumberi(ConfigObjMain.sColourGlobalBack) && std::stoi(ConfigObjMain.sColourGlobalBack) < 8192)) {
				ConfigObjMain.sColourGlobalBack = BLK_WIN32;
				bSuccess = false;
			}
			if (not (isNumberi(ConfigObjMain.sColourHighlight) && std::stoi(ConfigObjMain.sColourHighlight) < 8192)) {
				ConfigObjMain.sColourHighlight = LWHT_WIN32;
				bSuccess = false;
			}
			if (not (isNumberi(ConfigObjMain.sColourHighlightBack) && std::stoi(ConfigObjMain.sColourHighlightBack) < 8192)) {
				ConfigObjMain.sColourHighlightBack = BLU_WIN32;
				bSuccess = false;
			}
			if (not (isNumberi(ConfigObjMain.sColourTitle) && std::stoi(ConfigObjMain.sColourTitle) < 8192)) {
				ConfigObjMain.sColourTitle = BLK_WIN32;
				bSuccess = false;
			}
			if (not (isNumberi(ConfigObjMain.sColourTitleBack) && std::stoi(ConfigObjMain.sColourTitleBack) < 8192)) {
				ConfigObjMain.sColourTitleBack = LCYN_WIN32;
				bSuccess = false;
			}
			if (not (isNumberi(ConfigObjMain.sColourSubheading) && std::stoi(ConfigObjMain.sColourSubheading) < 8192)) {
				ConfigObjMain.sColourSubheading = LWHT_WIN32;
				bSuccess = false;
			}
			if (not (isNumberi(ConfigObjMain.sColourSubheadingBack) && std::stoi(ConfigObjMain.sColourSubheadingBack) < 8192)) {
				ConfigObjMain.sColourSubheadingBack = MAG_WIN32;
				bSuccess = false;
			}

			return bSuccess;
		}

		// VerifyANSIColourString - Verifies an ANSI colour string with the following rules:
		//                        - 1. It must only contain numbers and semicolons
		//                        - 2. The numbers in the colour string must be less than 256.
		// Parameters: sColourString - The colour string to check.
		// Return Values: TRUE or 1 for a valid colour string, FALSE or 0 for a bad colour string.
		//
		bool VerifyANSIColourString(std::string sColourString)
		{
			std::size_t nLastSemicolonPlus1 = 0;

			// Check if sColourString contains nothing - if so, it's not valid
			if (sColourString.empty()) return false;

			for (uint8_t i = 0; i < 3; i++)
			{
				// Parse up to first non-number
				std::string sBuffer = "";
				for (size_t j = nLastSemicolonPlus1; j < sColourString.length(); j++, nLastSemicolonPlus1 = j + 1) {
					if (sColourString[j] == ';') {
						break;
					}
					else sBuffer.push_back(sColourString[j]);
				}

				// Check if buffer is empty - if so, it means that the colour string doesn't have enough colour values to make a colour
				if (sBuffer == "") {
					return false;
				}
				// Check if buffer is a number
				if (!isNumberi(sBuffer)) {
					return false;
				}
				// Check if number is below 256 (convert as well)
				if (std::stoi(sBuffer) > 255) {
					return false;
				}
			}

			// Check if whole string checked - if not, it means that there's unwanted characters that are out of the scope of this algorithm, 
			// and therefore the colour string is invalid
			if (nLastSemicolonPlus1 - 1 < sColourString.length()) return false;

			return true;
		}

		// Checks all ConfigObjMain.sColour colours to see if they are valid, in the 255;255;255 format.
		// Returns TRUE for all correct, FALSE for 1 or more variables incorrect.
		bool ValidateColourStringsANSI() {
			bool bSuccess = true;

			// Check validity of ANSI string values
			if (!VerifyANSIColourString(ConfigObjMain.sColourGlobal)) {
				ConfigObjMain.sColourGlobal = LWHT_ANSI;
				bSuccess = false;
			}
			if (!VerifyANSIColourString(ConfigObjMain.sColourGlobalBack)) {
				ConfigObjMain.sColourGlobalBack = BLK_ANSI;
				bSuccess = false;
			}
			if (!VerifyANSIColourString(ConfigObjMain.sColourHighlight)) {
				ConfigObjMain.sColourHighlight = LWHT_ANSI;
				bSuccess = false;
			}
			if (!VerifyANSIColourString(ConfigObjMain.sColourHighlightBack)) {
				ConfigObjMain.sColourHighlightBack = BLU_ANSI;
				bSuccess = false;
			}
			if (!VerifyANSIColourString(ConfigObjMain.sColourTitle)) {
				ConfigObjMain.sColourTitle = BLK_ANSI;
				bSuccess = false;
			}
			if (!VerifyANSIColourString(ConfigObjMain.sColourTitleBack)) {
				ConfigObjMain.sColourTitleBack = LCYN_ANSI;
				bSuccess = false;
			}
			if (!VerifyANSIColourString(ConfigObjMain.sColourSubheading)) {
				ConfigObjMain.sColourSubheading = LWHT_ANSI;
				bSuccess = false;
			}
			if (!VerifyANSIColourString(ConfigObjMain.sColourSubheadingBack)) {
				ConfigObjMain.sColourSubheadingBack = MAG_ANSI;
				bSuccess = false;
			}

			return bSuccess;
		}
	}
}