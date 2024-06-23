//
// ConverterAssets.cpp - Contains all the function definitions of the converter namespace.
//
#include "ConverterAssets.h"
#include "../../Core/ZeeTerminalCore.h"
#include <sstream>
#include <bitset>

namespace converter 
{
	// Celsius to fahrenheit
	void celsiusToFahrenheit(long double dCelsius, bool bFromArgument) {
		// Prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Celsius to Fahrenheit converter!");
			std::cout << "\n\n";
			dCelsius = NumInputld("Please input your celsius value: > ");
		}

		// Calculate
		long double		dFahrenheit;
		dFahrenheit = dCelsius * (9.0 / 5.0) + 32;

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nCelsius value: " << dCelsius << "C\nConverted fahrenheit value: " << dFahrenheit << "F.\n\n";

		return;
	}

	// Fahrenheit to celsius
	void fahrenheitToCelsius(long double dFahrenheit, bool bFromArgument) {
		// Prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Fahrenheit to Celsius converter!");
			std::cout << "\n\n";
			dFahrenheit = NumInputld("Please input your fahrenheit value: > ");
		}

		// Calculate
		long double	dCelsius;
		dCelsius = (dFahrenheit - 32) * 5.0 / 9.0;

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nFahrenheit value: " << dFahrenheit << "F\nConverted Celsius value: " << dCelsius << "C.\n\n";

		return;
	}

	// Kilometres to Miles Converter
	void kilometresToMiles(long double kilometres, bool bFromArgument) {
		// prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Kilometres to Miles converter!");
			std::cout << "\n\n";

			while (true) {
				kilometres = NumInputld("Please input the number of kilometres: > ");

				// Negative numbers are not allowed
				if (kilometres < 0) {
					UserErrorDisplay("Negative numbers aren't allowed. Please try again with a different number.\n");
				}
				else break;
			}
		}

		// Negative numbers aren't allowed
		if (kilometres < 0) {
			UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again later.\n");
			return;
		}

		// Work out value
		long double	miles;
		miles = kilometres / 1.609344;

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted kilometres value: " << kilometres << "km\nConverted miles value: " << miles << " miles\n";

		return;
	}

	// Miles to Kilometres Converter
	void milesToKilometres(long double miles, bool bFromArgument) {
		// prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Miles to Kilometres converter!");
			std::cout << "\n\n";

			while (true) {
				miles = NumInputld("Please input the number of miles: > ");

				// Negative numbers are not allowed
				if (miles < 0) {
					UserErrorDisplay("Negative numbers aren't allowed. Please try again with a different number.\n");
				}
				else break;
			}
		}
		
		// Negative numbers aren't allowed
		if (miles < 0) {
			UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again later.\n");
			return;
		}

		// Work out value
		long double kilometres;
		kilometres = miles * 1.609344;

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted miles value: " << miles << " miles\nConverted kilometres value: " << kilometres << "km\n";

		return;
	}

	// Binary to Denary converter
	void binaryToDenary(std::string	binary, bool bFromArgument) {
		long long int	denary = 0;

		// Prompt if no user argument specified
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Binary to Denary converter!");
			std::cout << "\n\n";
			do {
				bool didItWork = true;
				binary = StrInput("Please input your string of binary numbers ('exit' without quotes to exit): > ");

				// Exit on exit
				if (binary == "exit") {
					Exiting();
					return;
				}

				// Check in case if the user inputted too many binary numbers
				if (binary.length() > 62) {
					UserErrorDisplay("The max number of binary numbers is 62. You put " + std::to_string(binary.length()) + " characters. Please try again.\n");
					didItWork = false;
					continue;
				}

				// Check characters in string; Make sure that they are only 1 and 0
				for (int i = 0; i < binary.length(); i++) {
					if (binary[i] != '1' && binary[i] != '0') {
						UserErrorDisplay("Sorry, you have inputted a character other than 1 or 0. Please try again.\n");
						didItWork = false;
						break;
					}
				}

				// Only if everything worked will execution be allowed to advance from this do loop
				if (didItWork != false) break;

			} while (true);
		}
		else {
			// Check in case if the user inputted too many binary numbers
			if (binary.length() > 62) {
				UserErrorDisplay("The max number of binary numbers is 62. You put " + std::to_string(binary.length()) + " characters. Please try again later.\n");
				return;
			}

			// Check characters in string; Make sure that they are only 1 and 0
			for (int i = 0; i < binary.length(); i++) {
				if (binary[i] != '1' && binary[i] != '0') {
					UserErrorDisplay("Sorry, you have inputted a character other than 1 or 0. Please try again later.\n");
					return;
				}
			}
		}

		// Calculate denary value
		for (int64_t i = binary.length() - 1, ind = 1; i >= 0; i--) {
			if (binary[i] == '1') {
				denary += ind;
			}
			ind *= 2;
		}

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted binary string: " << binary << "\nDenary value: " << denary << "\n\n";

		// End
		return;
	}

	// Denary to Binary Converter
	void denaryToBinary(int64_t denary, bool bFromArgument) {
		short int		binary[64];
		int				i = 0;

		// Prompt for denary number
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Denary to Binary converter!");
			std::cout << "\n\n";
			while (true) {
				denary = NumInputll("Please enter your denary number: > ");

				// Negative numbers aren't allowed
				if (denary < 0) {
					UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again.\n");
					continue;
				} 
				else break;
			}
		}

		// Negative numbers aren't allowed
		if (denary < 0) {
			UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again later.\n");
			return;
		}

		// Output 0 off the spot if denary equals 0
		if (denary == 0) { binary[0] = 0; } // output only 0

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted denary value: " << denary << "\nConverted binary string value: ";

		// Calculate and output binary number
		for (; (denary > 0); i++) {
			binary[i] = denary % 2;
			denary /= 2;
		}

		// Output binary result
		for (int j = i - 1; j >= 0; j--) {
			std::cout << binary[j];
		}
		std::cout << ".\n\n";

		// End
		return;
	}

	// Denary to Hexadecimal Converter
	void DenaryToHexadecimal(int64_t nDenaryVal, bool bFromArgument) {
		
		// Prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Denary to Hexadecimal Converter!");
			std::cout << "\n\n";
			while (true) {
				nDenaryVal = NumInputll("Please input the denary value that you want to convert: > ");

				// Negative numbers are not allowed
				if (nDenaryVal < 0) {
					UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again.\n");
					continue;
				}
				else break;
			}
		}
		else {
			// Negative numbers are not allowed
			if (nDenaryVal < 0) {
				UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again later.\n");
				return;
			}
		}

		// Convert to hex
		std::stringstream ss;
		ss << std::hex << nDenaryVal; // std::hex flag for hex conversion
		std::string sResult = ss.str();

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted denary value: " << std::dec << nDenaryVal << "\nConverted hexadecimal string value: " << sResult << "\n\n";

		return;
	}

	// Binary to Denary converter
	void BinaryToHexadecimal(std::string binary, bool bFromArgument) 
	{
		// Prompt if no user argument specified
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Binary to Hexadecimal converter!");
			std::cout << "\n\n";
			do {
				bool didItWork = true;
				binary = StrInput("Please input your string of binary numbers ('exit' without quotes to exit): > ");

				// Exit on exit
				if (binary == "exit") {
					Exiting();
					return;
				}

				// Check in case if the user inputted too many binary numbers
				if (binary.length() > 64) {
					UserErrorDisplay("The max number of binary numbers is 64. You put " + std::to_string(binary.length()) + " characters. Please try again.\n");
					didItWork = false;
					continue;
				}

				// Check characters in string; Make sure that they are only 1 and 0
				for (int i = 0; i < binary.length(); i++) {
					if (binary[i] != '1' && binary[i] != '0') {
						UserErrorDisplay("Sorry, you have inputted a character other than 1 or 0. Please try again.\n");
						didItWork = false;
						break;
					}
				}

				// Only if everything worked will execution be allowed to advance from this do loop
				if (didItWork != false) break;

			} while (true);
		}
		else {
			// Check in case if the user inputted too many binary numbers
			if (binary.length() > 64) {
				UserErrorDisplay("The max number of binary numbers is 64. You put " + std::to_string(binary.length()) + " characters. Please try again later.\n");
				return;
			}

			// Check characters in string; Make sure that they are only 1 and 0
			for (int i = 0; i < binary.length(); i++) {
				if (binary[i] != '1' && binary[i] != '0') {
					UserErrorDisplay("Sorry, you have inputted a character other than 1 or 0. Please try again later.\n");
					return;
				}
			}
		}

		// Calculate hexadecimal value
		std::bitset<64> set(binary);

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted binary string: " << binary << "\nConverted hexadecimal string value: " << std::hex << set.to_ullong() << "\n\n";

		// End
		return;
	}

	// Seconds to Other Time Types
	void SecondsToOtherTime(long double dSeconds, bool bFromArgument) {
		// Prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Seconds to Other Time Types Converter!");
			std::cout << "\n\n";
			while (true) {
				dSeconds = NumInputld("Please input the seconds value that you want to convert: > ");

				// Negative numbers are not allowed
				if (dSeconds < 0) {
					UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again.\n");
					continue;
				}
				else break;
			}
		}
		else {
			// Negative numbers are not allowed
			if (dSeconds < 0) {
				UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again later.\n");
				return;
			}
		}

		// Convert seconds to other time types
		long double dMilliseconds = dSeconds * 1000;
		long double dMinutes = dSeconds / 60;
		long double dHours = dMinutes / 60;
		long double dDays = dHours / 24;
		long double dWeeks = dDays / 7;
		long double dYears = dWeeks / 52.1428571; // this long decimal is the number of weeks in one year

		// Output results
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted seconds value: " << dSeconds 
			<< "\nConverted milliseconds value: " << dMilliseconds
			<< "\nConverted minutes value: " << dMinutes
			<< "\nConverted hours value: " << dHours
			<< "\nConverted days value: " << dDays
			<< "\nConverted weeks value: " << dWeeks
			<< "\nConverted normal years value: " << dYears << "\n\n";

		return;
	}

	// Kilowatts to Horsepower
	void KilowattsToHorsepower(long double dKilowatts, bool bFromArgument) {
		// Prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Kilowatts to Horsepower Converter!");
			std::cout << "\n\n";
			while (true) {
				dKilowatts = NumInputld("Please input the kilowatts value that you want to convert: > ");

				// Negative numbers are not allowed
				if (dKilowatts < 0) {
					UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again.\n");
					continue;
				}
				else break;
			}
		}
		else {
			// Negative numbers are not allowed
			if (dKilowatts < 0) {
				UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again later.\n");
				return;
			}
		}

		// Calculate result
		long double dHorsepower = dKilowatts / 0.745699872; // the decimal is the constant to get horsepower

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted kilowatt value: " << dKilowatts << "kw\nConverted horsepower value: " << dHorsepower << "hp\n\n";

		return;
	}

	// Horsepower to Kilowatts
	void HorsepowerToKilowatts(long double dHorsepower, bool bFromArgument) {
		// Prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Horsepower to Kilowatts Converter!");
			std::cout << "\n\n";
			while (true) {
				dHorsepower = NumInputld("Please input the horsepower value that you want to convert: > ");

				// Negative numbers are not allowed
				if (dHorsepower < 0) {
					UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again.\n");
					continue;
				}
				else break;
			}
		}
		else {
			// Negative numbers are not allowed
			if (dHorsepower < 0) {
				UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again later.\n");
				return;
			}
		}

		// Calculate result
		long double dKilowatts = dHorsepower * 0.745699872; // the decimal is the constant for multiplying to get kilowatts and horsepower

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted horsepower value: " << dHorsepower << "hp\nConverted kilowatt value: " << dKilowatts << "kw\n\n";

		return;
	}

	// Light-Years to Kilometres
	void LightYearsToKilometres(long double dLightYears, bool bFromArgument) {
		// Prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Light-Years to Kilometres Converter!");
			std::cout << "\n\n";
			while (true) {
				dLightYears = NumInputld("Please input the light-years value that you want to convert: > ");

				// Negative numbers are not allowed
				if (dLightYears < 0) {
					UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again.\n");
					continue;
				}
				else break;
			}
		}
		else {
			// Negative numbers are not allowed
			if (dLightYears < 0) {
				UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again later.\n");
				return;
			}
		}

		// Calculate result
		long double dKilometres = dLightYears * 9460730472580.8; // This constant is required to calculate kilometres because 1 light year is that many kilometres.

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted light-years value: " << dLightYears << " light-years\nConverted kilometres value: " << dKilometres << "km\n\n";

		return;
	}

	// Kilometres to Light-Years
	void KilometresToLightYears(long double dKilometres, bool bFromArgument) {
		// Prompt
		if (!bFromArgument) {
			slowcolourfn(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack, "Welcome to the Kilometres to Light-Years Converter!");
			std::cout << "\n\n";
			while (true) {
				dKilometres = NumInputld("Please input the kilometres value that you want to convert: > ");

				// Negative numbers are not allowed
				if (dKilometres < 0) {
					UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again.\n");
					continue;
				}
				else break;
			}
		}
		else {
			// Negative numbers are not allowed
			if (dKilometres < 0) {
				UserErrorDisplay("Sorry, negative numbers aren't allowed. Please try again later.\n");
				return;
			}
		}

		// Calculate result
		long double dLightYears = dKilometres / 9460730472580.8; // This constant is required to calculate light years because 1 light year is that many kilometres.

		// Output result
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nInputted kilometres value: " << dKilometres << "km\nConverted light-years value: " << dLightYears << " light-years\n\n";

		return;
	}
}