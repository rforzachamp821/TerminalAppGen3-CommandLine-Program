#pragma once
#include <string>

//
// Commands.h - Responsible for housing the commands namespace class interface.
//

// commands - contains all command functions, put into a namespace for code reliability and neatness.
namespace commands {
	bool Commands1To10(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer = "");
	bool Commands11To20(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer = "");
	bool Commands21To30(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer = "");
	bool Commands31To40(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer = "");
	bool Commands41To50(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer = "");
	bool Commands51To60(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer = "");
}
