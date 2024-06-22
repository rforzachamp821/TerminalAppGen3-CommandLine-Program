//
// ConverterAssets.h - Contains all the function declarations and the declaration of the converter namespace.
//
#pragma once
#include <string>

namespace converter {
	// Celsius to fahrenheit
	void celsiusToFahrenheit(long double dCelsius = 0.0, bool bFromArgument = false);

	// Fahrenheit to celsius
	void fahrenheitToCelsius(long double dFahrenheit = 0.0, bool bFromArgument = false);

	// Kilometres to Miles Converter
	void kilometresToMiles(long double kilometres = 0.0, bool bFromArgument = false);

	// Miles to Kilometres Converter
	void milesToKilometres(long double miles = 0.0, bool bFromArgument = false);

	// Binary to Denary converter
	void binaryToDenary(std::string	binary = "", bool bFromArgument = false);

	// Denary to Binary Converter
	void denaryToBinary(int64_t denary = 0, bool bFromArgument = false);

	// Denary to Hexadecimal Converter
	void DenaryToHexadecimal(int64_t nDenaryVal = 0, bool bFromArgument = false);

	// Binary to Hexadecimal Converter
	void BinaryToHexadecimal(std::string nBinaryVal = "", bool bFromArgument = false);

	// Seconds to Other Time Types
	void SecondsToOtherTime(long double dSeconds = 0.0, bool bFromArgument = false);

	// Kilowatts to Horsepower
	void KilowattsToHorsepower(long double dKilowatts = 0.0, bool bFromArgument = false);

	// Horsepower to Kilowatts
	void HorsepowerToKilowatts(long double dHorsepower = 0.0, bool bFromArgument = false);

	// Light-Years to Kilometres
	void LightYearsToKilometres(long double dLightYears = 0.0, bool bFromArgument = false);

	// Kilometres to Light-Years
	void KilometresToLightYears(long double dKilometres = 0.0, bool bFromArgument = false);
}
