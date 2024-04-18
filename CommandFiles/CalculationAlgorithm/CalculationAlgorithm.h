//
// CalculationAlgorithm.h - Contains the interface for the CalculationAlgorithm class.
//
#include <string>
#include <tgmath.h>


// CalculationAlgorithm - A numerical-only calculator class with support for up to a theoretical 18 trillion characters per calculation line.
//
// It supports the modern implementation of the BIDMAS order of operations, negative numbers, spaces and is crash-safe.
// It also supports multipliers after brackets (without the multiplication symbol also works), powers, and support for multiple
// addition-subtraction operators beside each other. It also supports multiple brackets inside of each other.
// Basic trigonometric and arc-trigonometric functions are available and supported. 2 constants, PI and E (Euler's Number), are supported
// and calculated at runtime as well.
// The CalculationAlgorithm also supports square and cube root functions. The algorithm is NOT case-sensitive.
// 
// The allowed operators are: (), *, /, +, -, and ^ (power of). You must have a number on each side of the operators.
// 
// Example allowed expressions are:
// -> 5+5(5)
// -> 7*4+(6/2)
// -> 5+++-+---+-6*7/5(3)4
// -> 5^2+9/3
// -> (10+5^2)((5*-2)+9-3^3)/2
// -> 3(sin(5)acos(-1))
//
// - This calculation algorithm's display output is currently limited by the maximum precision of long double (16 digits of precision). 
// 
// - Please beware that the number outputted may not actually be 16 digits and possibly less, due to natural IEE754 limits.
// 
// - Please note that there is no support for logarithmic functions yet.
//
class CalculationAlgorithm 
{
protected:

	// Constants - Pi and Degrees -> Radians Calculation Constant (and opposite)
	const long double dPiConstant = std::acosl(-1);
	const long double dEulerConstant = std::expl(1.0);
	const long double dDegToRad = dPiConstant / 180;
	const long double dRadToDeg = 180 / dPiConstant;

	const char        cDefaultDecimalPoint = '.';
	const char        cDefaultThousandsSeparator = ',';
	const char        cEuropeanDecimalPoint = ',';
	const char        cEuropeanThousandsSeparator = '.';

	char              cDecimalPoint = '.';
	char              cThousandsSeparator = ',';


	// VerifyIfStringIsNumerical - Checks whether std::string argument is a true number or not
	// Arguments: sNumberTest - The number string to check.
	// Return Values: TRUE or 1 for number, FALSE or 0 for not a number.
	//
	bool VerifyIfStringIsNumerical(const std::string sNumberTest);

	// FormatValueForDisplay - Formats a specific value for display output.
	//                       - Has a max of 15-16dp.
	// Arguments: dValue - The number to format.
	// Return Value: Formatted number as a string.
	//
	std::string FormatValueForDisplay(long double dValue);

	// FormatValueForAlgorithm - Formats a specific value for internal algorithm calculations.
	//                         - Has a max of 18-19dp.
	// Arguments: dValue - The number to format.
	// Return Value: Formatted number as a string.
	//
	std::string FormatValueForAlgorithm(long double dValue);

	// FormatStringForDisplay - Formats a calculation string for display output, by rounding the numbers inside and removing the zeroes from them.
	// Arguments: sCalculationString - The string to format.
	// Return value: Formatted string.
	//
	std::string FormatStringForDisplay(std::string sCalculationString);
	
	// FormatStringForAlgorithm - Formats a calculation string for algorithm use, including changing number formatting to the American notation.
	// Arguments: sCalculationString - The string to format.
	// Return value: Formatted string.
	//
	std::string FormatStringForAlgorithm(std::string sCalculationString);

	// nErrorLevel - The type of error that occured when calculating. The following values are what they are:
	//              0) No error has occured.
	//              1) A math error has occured (e.g division by 0).
	//              2) A syntax error has occured.
	//              3) An unknown number parsing error has occured.
	//              4) The calculated number is either infinity or too large to calculate.
	// This can be recieved as a string using the CalculationAlgorithm::GetLastCalculationErrorInfo() function.
	//
	short int nErrorLevel = 0;

	// dLastAns - The last calculated value known on the object.
	//          - Used for the (Ans) user-space variable.
	//
	long double dLastAns = 0;

	// Object ID
	int nObjectID;


	// Calculate - Main calculation algorithm that calculates using each of the 4 basic mathematical operators,
	//             with negative number support along with that. The nErrorLevel variable is modified when 
	//             anything goes wrong.
	// Arguments: sCalculationString - The calculation string to work out the product of/find the answer of.
	// Return values: The calculated answer in long double-grade precision.
	//
	long double Calculate(std::string sCalculationString);

	// EradicateBrackets - Removes brackets from calculation string and converts them to constant numbers.
	//                     It has support for numbers before and after the brackets that are attached to the brackets.
	// Arguments: sCalculationString - The calculation string to remove and simplify the brackets from.
	// Return values: Modified string
	//
	std::string EradicateBrackets(std::string sCalculationString);

	// RemoveUnnecessaryArithmeticSymbols - Simplifies/removes arithmetic operators that are placed next to each other,
	//                                 e.g) 5+-++--+-5 simplifies to 5+5
	// Arguments: sCalculationString - The calculation string to remove the arithmetic symbols from.
	// Return values: Modified string
	//
	std::string RemoveUnnecessaryArithmeticSymbols(std::string sCalculationString);

	// RemoveAllFormatting - Remove spaces/thousands separators from mathematical expression.
	//                     - Required in case user uses spaces/thousands separators, as spaces/thousands separators will cause unintended syntax errors.
	// Arguments: sCalculationString - The calculation string to remove space/thousands separator characters from.
	// Return values: Modified string
	//
	std::string RemoveAllFormatting(std::string sCalculationString);

public:

	// A switch for displaying calculator working out process.
	bool bDisplayWorkingOutProcess = false;

	// CalculationAlgorithm Constructor
	CalculationAlgorithm();

	// CalculationAlgorithm Destructor
	~CalculationAlgorithm();

	// GetLastCalculationErrorInfo - Gets the last calculation error and outputs details as a string.
	// Arguments: None
	// Return values: Error information string.
	//
	std::string GetLastCalculationErrorInfo();

	// GetLastCalculationErrorValue - Gets the last calculation error value. The value return meanings are as follows:
	//              0) No error has occured.
	//              1) A math error has occured (e.g division by 0).
	//              2) A syntax error has occured.
	//              3) An unknown number parsing error has occured.
	// Arguments: None
	// Return values: Last calculation error value.
	//
	inline short int GetLastCalculationErrorValue() 
	{
		return nErrorLevel;
	}

	// SafeCalculate - Calculates and finds the product of a calculation string provided by the user,
	//                 which utilises all features contained in the calculation algorithm to prepare
	//                 the calculation string for the calculation.
	// Arguments: sCalculationString - The string to find the product of/calculate.
	// Return values: The calculated answer in long double-grade precision.
	// 
	// NOTE: This function returns 0.0 if any errors occur, and sets the error level accordingly.
	//
	long double SafeCalculate(std::string sCalculationString);

	// UseEuropeanNotation - When the toggle value is TRUE, allow the use of European Number Notation, with '.' being set as the thousands separator, and ',' being the decimal point.
	//                     - When set to FALSE though, the notation resets to default, with ',' being set as the thousands separator, and '.' being the decimal point.
	// Arguments - bToggleValue: The value for setting the notaton. Values are explained in the description above.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail. If FALSE/0 is returned, a bad value has been passed.
	//
	bool UseEuropeanNotation(bool bToggleValue);
};