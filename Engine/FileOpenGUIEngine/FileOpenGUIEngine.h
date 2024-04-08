#pragma once
#include <Windows.h>
#include <string>

// FileOpenGUIEngine - Engine for the File Open Dialogue Box GUI.
//
class FileOpenGUIEngine {
private:
	// Object ID
	int nObjectID;
protected:

	std::string sFinalFilePath = "";

	// ThoroughRelease - Releases an object and clears all its memory allocation automatically.
	// Please note that using this method should only be used on exit, as using this function 
	// will not allow using the same variable again.
	// 
	// Arguments - *iObject - the object to release/clear.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool ThoroughRelease(IUnknown* iObject);

public:

	// Constructor
	FileOpenGUIEngine();

	// Destructor
	~FileOpenGUIEngine();

	// FileOpenDialogue - Opens a Windows file dialogue, with a custom title.
	// Arguments - sTitle: The title of the dialogue window, as a string.
	//           - bSelectFolder: Boolean to toggle selecting folder or file. TRUE for folder, FALSE for file. Defaulted to FALSE due to the name of this function.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool FileOpenDialogue(std::string sTitle, bool bSelectFolder = false);

	// GetRetrievedPathName - Gets the file name of the open dialogue that was returned to the associated object.
	// Arguments - NONE
	// Return Values - The string of the final filepath.
	//
	std::string GetRetrievedPathName() {
		return sFinalFilePath;
	}
};