//
// CommandsFile_61To70.cpp - File containing the commands::Commands61To70 function.
//
#include "Commands.h"
#include "../ConverterAssets/ConverterAssets.h"

// Commands61To70
bool commands::Commands61To70(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer) 
{
	// Converter
	if (sCommand == "converter" || sCommand == "61") {
		long double dConverterArgument = 0.0;
		std::string sConverterArgument = "";
		int nOption = 0;
		bool bFromArgument = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::ConverterHelp();
				return true;
			}

			if (sStringOptionCommandArgs[i] == "ctof") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 1;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");
					
					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "ftoc") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 2;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "kmtomi") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 3;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "mitokm") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 4;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "bintoden") {
				sConverterArgument = sStringDataCommandArgs[i];
				nOption = 5;
			}
			else if (sStringOptionCommandArgs[i] == "dentobin") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 6;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "dentohex") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 7;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "bintohex") {
				sConverterArgument = sStringDataCommandArgs[i];
				nOption = 8;
			}
			else if (sStringOptionCommandArgs[i] == "sectoall") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 9;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "kwtohp") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 10;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "hptokw") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 11;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "lytokm") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 12;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
			else if (sStringOptionCommandArgs[i] == "kmtoly") {
				// Check for argument validity and then execute
				if (isNumberld(sStringDataCommandArgs[i])) {
					dConverterArgument = std::stold(sStringDataCommandArgs[i]);
					nOption = 13;
				}
				else {
					// Bad argument
					VerbosityDisplay("In commands::Commands61To70(): ERROR - Number argument is not numerical or is in an invalid format, making it incorrect. Failed execution.\n");
					UserErrorDisplay("ERROR - Number argument is not numerical or is invalid and is incorrect. Please try again later with a correct argument.\nSee \"converter -h\" for more info.\n");

					return true;
				}
			}
		}

		// User UI
		if (nOption == 0) {
			OptionSelectEngine oseConverter;
			oseConverter.nSizeOfOptions = 13;
			std::string sOptions[] = {
				"Celsius to Fahrenheit",
				"Fahrenheit to Celsius",
				"Kilometres to Miles",
				"Miles to Kilometres",
				"Binary to Denary",
				"Denary to Binary",
				"Denary to Hexadecimal",
				"Binary to Hexadecimal",
				"Seconds to Other Time Formats",
				"Kilowatts to Horsepower",
				"Horsepower to Kilowatts",
				"Light-Years to Kilometres",
				"Kilometres to Light-Years"
			};
			oseConverter.sOptions = sOptions;

			nOption = oseConverter.OptionSelect("Please select what converter you would like to use:", " ___CONVERTER___ ");
		}
		else {
			// Record that this execution is from argument
			bFromArgument = true;
		}
		
		// Exit
		if (nOption == -1) {

			Exiting();
			return true;
		}
		else std::cout << '\n'; // skip a line for more neat output

		switch (nOption) {
		case 1:
			converter::celsiusToFahrenheit(dConverterArgument, bFromArgument);
			break;
		case 2:
			converter::fahrenheitToCelsius(dConverterArgument, bFromArgument);
			break;
		case 3:
			converter::kilometresToMiles(dConverterArgument, bFromArgument);
			break;
		case 4:
			converter::milesToKilometres(dConverterArgument, bFromArgument);
			break;
		case 5:
			converter::binaryToDenary(sConverterArgument, bFromArgument);
			break;
		case 6:
			converter::denaryToBinary(static_cast<int64_t>(dConverterArgument), bFromArgument);
			break;
		case 7:
			converter::DenaryToHexadecimal(static_cast<int64_t>(dConverterArgument), bFromArgument);
			break;
		case 8:
			converter::BinaryToHexadecimal(sConverterArgument, bFromArgument);
			break;
		case 9:
			converter::SecondsToOtherTime(dConverterArgument, bFromArgument);
			break;
		case 10:
			converter::KilowattsToHorsepower(dConverterArgument, bFromArgument);
			break;
		case 11:
			converter::HorsepowerToKilowatts(dConverterArgument, bFromArgument);
			break;
		case 12:
			converter::LightYearsToKilometres(dConverterArgument, bFromArgument);
			break;
		case 13:
			converter::KilometresToLightYears(dConverterArgument, bFromArgument);
			break;
		default:
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		}

		return true;
	}

	// RandNum
	else if (sCommand == "randnum" || sCommand == "62") {
		bool bCalculateFloatingPoint = false;
		long double nMaxNumber = 0;
		long double nMinNumber = 0;
		bool bFromArgument = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				helpmsgs::RandNumHelp();
				return true;
			}
			else if (cCommandArgs[i] == 'f') {
				bCalculateFloatingPoint = true;
			}

			// Max-min arguments
			if (sStringDataCommandArgs[0] != "") {
				if (sStringDataCommandArgs[1] != "") {
					// Convert min argument to 64-bit integer and check
					if (isNumberld(sStringDataCommandArgs[1])) {
						nMinNumber = std::stold(sStringDataCommandArgs[1]);
					}
					else {
						VerbosityDisplay("In Commands61To70() - ERROR: Could not detect numerical value in string-based number argument, due to isNumberld fail.\n");
						UserErrorDisplay("ERROR - Your minimum number generation boundary argument is invalid. Please try again.\nSee \"randnum -h\" for more info.\n");

						return true;
					}
				}
				else {
					VerbosityDisplay("In Commands61To70(): ERROR - Failed to detect second mandatory minimum boundary argument for random number generation. Arguments should be re-checked.\n");
					UserErrorDisplay("ERROR - There was no minimum boundary argument found to generate the random number. This must be included with a maximum boundary. Please add one and try again.\nSee \"randnum -h\" for more info.\n");

					return true;
				}

				// Convert max argument to 64-bit integer and check
				if (isNumberld(sStringDataCommandArgs[0])) {
					nMaxNumber = std::stold(sStringDataCommandArgs[0]);
				}
				else {
					VerbosityDisplay("In Commands61To70() - ERROR: Could not detect numerical value in string-based number argument, due to isNumberld fail.\n");
					UserErrorDisplay("ERROR - Your maximum number generation boundary argument is invalid. Please try again.\nSee \"randnum -h\" for more info.\n");

					return true;
				}

				bFromArgument = true; // from argument interface
			}
		}

		// User prompt
		if (bFromArgument == false) {
			CentreColouredText(" ___RANDNUM___ ", 1);
			std::cout << "\n\n";
			colour(CYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("This command is for generating random numbers.\nThe maximum boundary for the random number generation must be larger than the minimum boundary.\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			while (true) {
				nMaxNumber = NumInputld("Please input the maximum boundary for the generator: > ");
				nMinNumber = NumInputld("Please input the minimum boundary for the generator: > ");

				// Check if max boundary is less than minimum boundary
				if (nMaxNumber < nMinNumber) {
					UserErrorDisplay("ERROR - Maximum (upper) boundary is less than minimum (lower) boundary.\nPlease try again, ensuring that the maximum boundary is larger than the minimum.\n");
					continue;
				}
				else break;
			}

			std::cout << "\n";
		}

		// Check if max boundary is more than minimum boundary - arguments interface
		else if (nMaxNumber < nMinNumber) {
			UserErrorDisplay("ERROR - Maximum (upper) boundary is less than minimum (lower) boundary.\nPlease try again later. See \"randnum -h\" for more info.\n");
			return true;
		}

		long double dCalculatedNumber = 0.0;
		if (bCalculateFloatingPoint == true) {
			dCalculatedNumber = RandNumld(nMaxNumber, nMinNumber);
		}
		else {
			dCalculatedNumber = RandNumll(nMaxNumber, nMinNumber);
		}

		// Display result for calculated number
		std::cout << "Final Calculated Number: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << dCalculatedNumber << "\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return true;
	}

	else return false;

	return true;
}