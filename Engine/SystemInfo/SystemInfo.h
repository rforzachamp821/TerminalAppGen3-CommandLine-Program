#pragma once

//
// SystemInfo.h - Interface for the SystemInfo class.
//

#include <intrin.h>
#include <Windows.h>
#include <string>

// SystemInfo class - Manages getting system information for the LogFileSystem class.
class SystemInfo
{
private:

	// MaxValue - Returns the largest value out of 2 variables.
	// Arguments: nValueA - First value.
	//            nValueB - Second value.
	// Return Value: unsigned long long int containing the max value.
	//
	inline unsigned long long int MaxValue(unsigned long long int nValueA, unsigned long long int nValueB) {
		if (nValueA > nValueB) {
			return nValueA;
		}
		else return nValueB;
	}

	// GetRegistryDword - Gets a specified DWORD value from the Windows Registry and returns it.
	// Arguments: hKey - A handle to an open registry key.
	//            subKey - The path to the key, without the actual key name.
	//            value - The registry value name.
	// Return Value: DWORD value containing the value within the value argument.
	//
	DWORD GetRegistryDword(HKEY hKey, const std::string& subKey, const std::string& value);

	// GetRegistryDword - Gets a specified string value from the Windows Registry and returns it.
	// Arguments: hKey - A handle to an open registry key.
	//            subKey - The path to the key, without the actual key name.
	//            value - The registry value name.
	// Return Value: std::string containing the value within the value argument.
	//
	std::string GetRegistryString(HKEY hKey, const std::string& subKey, const std::string& value);

public:

	// GetCPUModelName - Gets the full CPU name as a string, using __cpuid intristics.
	// Arguments: None
	// Return Value: CPU name string as std::string.
	//
	std::string GetCPUModelName();

	// GetSysMemorySizeInGiB - Gets the system memory size in gibibytes.
	// Arguments: None
	// Return Value: System memory size, in gibibytes, as long double.
	//
	long double GetSysMemorySizeInGiB();

	// GetSysPageSizeInGiB - Gets the memory page file size in gibibytes.
	// Arguments: None
	// Return Value: System page file size, in gibibytes, as long double.
	//
	long double GetSysPageSizeInGiB();

	// GetSysVirtualMemorySizeInGiB - Gets the system virtual memory size in gibibytes.
	// Arguments: None
	// Return Value: System virtual memory size, in gibibytes, as long double.
	//
	long double GetSysVirtualMemorySizeInGiB();

	// GetLowestAccessibleMemoryAddress - Gets the lowest accessible memory address to any application in the system, as a string.
	// Arguments: None
	// Return Value: std::string, containing the memory address.
	//
	std::string GetLowestAccessibleMemoryAddress();

	// GetHighestAccessibleMemoryAddress - Gets the highest accessible memory address to any application in the system, as a string.
	// Arguments: None
	// Return Value: std::string, containing the memory address.
	//
	std::string GetHighestAccessibleMemoryAddress();

	// GetOSName - Gets the full OS name as stored in the Windows Registry.
	// Arguments: None
	// Return Value: Full OS name with build number, as a string.
	//
	std::string GetOSName();

	// GetOSBuildInfo - Gets extra build info as a string, as stored in the Windows Registry.
	// Arguments: None
	// Return Value: OS Build Info as a string.
	//
	inline std::string GetOSBuildInfo() {
		// Get build info
		return GetRegistryString(((HKEY)(ULONG_PTR)((LONG)0x80000002)), "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "BuildLabEx");
	}

	// GetCPUCoreCount - Gets the number of processors on the CPU as an integer.
	// Arguments: None
	// Return Value: Integer containing the number of CPU cores in the system.
	//
	inline int GetCPUCoreCount() {
		SYSTEM_INFO SysInfoCPUCoreCount{};
		GetSystemInfo(&SysInfoCPUCoreCount);
		return (int)SysInfoCPUCoreCount.dwNumberOfProcessors;
	}

	// GetCPUArchitectureAsName - Gets the CPU architecture (x64, ARM, etc) as a custom string.
	// Arguments: None
	// Return Value: CPU architecture as a string.
	//
	std::string GetCPUArchitectureAsName();
};
