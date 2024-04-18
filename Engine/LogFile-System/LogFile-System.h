#pragma once

//
// LogFile-System.h - Interface for the LogFile system and its class.
//
#include "../../Core/ZTConstDefinitions.h"
#include "../SystemInfo/SystemInfo.h"
#include <Windows.h>
#include <string>

//std::string BoolToString(bool);
//bool EnableVTMode();

// LogFileSystem - Manages ZeeTerminal logging.
class LogFileSystem {

private:
	// ONLY CALL THIS ON CONSTRUCTOR CALL
	// This function initialises all time structures to object initialisation time.
	//
	bool InitialiseTimeStructs();

	// GetCurrentMillisecondTime - Gets and returns the millisecond part of the current system time.
	//                           - This does NOT return the total system time since epoch in milliseconds.
	// Arguments: None
	// Return Value: time_t value, containing the millisecond value.
	//
	time_t GetCurrentMillisecondTime();

	// ConvertValueToTimeFormat - Converts a time_t value to a format widely accepted to be the best fit for time (strictly HH:MM:SS, no less digits)
	// Arguments: nValue - The value to convert. 
	//            nValueWidth - If custom width is wanted for value, this can be specified. Defaults to 2.
	// Return value: std::string, containing the converted time value.
	//
	std::string ConvertValueToTimeFormat(time_t nValue, int nValueWidth = 2);

	// ConvertTimeStructToString - Converts a 'tm' struct into a string format representing time.
	// Arguments: tmStructArg - The standard time structure to convert.
	//            bIncludeTime - Include the time part of date in string, not just date.
	//            cDateSeparator - The separator for the date. Default is '/'.
	// Return Value: std::string, containing the formatted time string.
	//
	std::string ConvertTimeStructToString(struct tm tmStructArg, time_t nMillisecondValue, bool bIncludeTime, char cDateSeparator = '/');

	// GetEntryTypesOfLogFileString - Gets the types of entries that are in the current log file, and puts them in a list in a string.
	// Arguments: None
	// Return Value: std::string, containing the types of entries that are in the current log file.
	//
	std::string GetEntryTypesOfLogFileString();

	// UpdateEntryTypesLine - Updates the log file line for entry types.
	// Arguments: None
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool UpdateEntryTypesLine();

	// InitialiseLogFileObject - Initialises the current logfile-system object with the correct parameters and values.
	// Arguments: None
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool InitialiseLogFileObject();

	// Initialisation indicators
	bool bObjectInitialised = false;
	bool bTimeStructsInitialised = false;
	bool bVTConsoleBugForProgramInfo = false;

	// Variable to indicate that the line for presenting the different types of log entries in the log file has to be updated
	bool bEntryTypesLineNeedsUpdate = false;

	// csLogFileTitle - Constant part of log file title.
	const std::string csLogFileTitle = "ZeeTerminal Log File";

	// Object ID
	int nObjectID;

protected:

	// SysInfoLogFileSystem - Contains all necessary functions to access system info.
	SystemInfo SysInfoLogFileSystem;

	// sSystemInfoString - String containing all formatted system information.
	std::string sSystemInfoString = "";

	// sProgramInfoString - String containing all formatted program information.
	std::string sProgramInfoString = "";

	// Time structures for program start date and time
	struct tm tmLocalTimeStart {};
	time_t nStartMillisecondValue = 0;

	// sLogFileName - Log file name that the object is looking at.
	std::string sLogFileName = "";

	// GetStartTimeAsString - Gets the start time for this object, and returns it as a string.
	// Arguments: bIncludeTime - Include the time part of date in string, not just date.
	//            cDateSeparator - The separator for the date. Default is '/'.
	// Return Value: std::string containing the start time.
	//
	inline std::string GetStartTimeAsString(bool bIncludeTime, char cDateSeparator = '/')
	{
		// Use the correct function for the job
		return ConvertTimeStructToString(tmLocalTimeStart, nStartMillisecondValue, bIncludeTime, cDateSeparator);
	}


	// UpdateSystemInfo - Update the system info string.
	// Arguments: None
	// Return Value: TRUE or 1 for success, FALSE or 0 for fail.
	//
	inline void UpdateSystemInfo()
	{
		// Initialise System Info string with necessary functions
		sSystemInfoString = "# __System Information__\n# - OS Name: " + SysInfoLogFileSystem.GetOSName()
			+ "\n# - OS Build Info: " + SysInfoLogFileSystem.GetOSBuildInfo()
			+ "\n# - Total System Memory: " + std::to_string(SysInfoLogFileSystem.GetSysMemorySizeInGiB()) + " GiB"
			+ "\n# - CPU Model Name: " + SysInfoLogFileSystem.GetCPUModelName()
			+ "\n# - CPU Logical Core Count: " + std::to_string(SysInfoLogFileSystem.GetCPUCoreCount()) + " cores"
			+ "\n# - CPU Architecture: " + SysInfoLogFileSystem.GetCPUArchitectureAsName() + "\n";

		return;
	}

	// UpdateSystemInfo - Update the system info string.
	// Arguments: None
	// Return Value: TRUE or 1 for success, FALSE or 0 for fail.
	//
	void UpdateProgramInfo();

	// CreateLogFile - Creates the log file and sets it up.
	//               - Also manages the initialisation of the sLogFileName string.
	// Arguments: None
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool CreateLogFile();

public:

	// Constructor
	LogFileSystem();

	// Destructor
	~LogFileSystem();

	// AddLogLine - Adds a logging line to a log file.
	//            - AddLogLine() will automatically format the line based on the line type (verbose, etc)
	// Arguments: sLogLine - Logging info/message.
	//            nTypeOfLine - The type of line to be outputted. Select: 1 for verbose message, 2 for user-space error, 3 for command input info, and 4 for user input info.
	//            nObjectID - If coming from an object, optionally specify a custom Object ID. Defaults to 10000 if no argument is given.
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool AddLogLine(std::string sLogLine, short int nTypeOfLine, int nObjectID = 10000);

	// UpdateEntryLineOnNextWrite - Force-update the entry line in the current log file on the next log-line write.
	// Arguments: None
	// Return Value: None
	//
	inline void UpdateEntryLineOnNextWrite() {
		bEntryTypesLineNeedsUpdate = true;
		return;
	}

};