//
// FileOpenGUIEngine.cpp - Responsible for managaing the FileOpenGUI Engine and its class, used for showing file dialogue boxes.
//
#include "FileOpenGUIEngine.h"
#include <string>
#include "../../Core/ZTConstDefinitions.h"
#include "../../Core/ZeeTerminalCore.h"
#include <ShObjIdl.h>

// FileOpenGUIEngine - Engine for the File Open Dialogue Box GUI.
//

// ThoroughRelease
bool FileOpenGUIEngine::ThoroughRelease(IUnknown* iObject)
{
	HRESULT hr = S_OK;

	// Attempt to release object.
	if (iObject) {
		hr = iObject->Release();
		if (FAILED(hr)) goto done;
	}

done:

	// Output message if failed
	if (FAILED(hr)) {
		VerbosityDisplay("Failed to thoroughly release object.", nObjectID);
		return false;
	}
	else return true;

	return true;
}

// Constructor
FileOpenGUIEngine::FileOpenGUIEngine() {
	static int nStaticID = 10000;
	// Wrap-around to prevent overflow
	if (nStaticID >= (std::numeric_limits<int>::max)() - 1) nStaticID = 10000;
	nObjectID = ++nStaticID;

	VerbosityDisplay("FileOpenGUIEngine Object Created.\n", nObjectID);
	sFinalFilePath = "";
}

// Destructor
FileOpenGUIEngine::~FileOpenGUIEngine() {
	VerbosityDisplay("FileOpenGUIEngine Object Destroyed.\n", nObjectID);
	// Nothing to clear/destroy
}

// FileOpenDialogue
bool FileOpenGUIEngine::FileOpenDialogue(std::string sTitle, bool bSelectFolder) {
	HRESULT hr = S_OK;

	IFileOpenDialog* pFileOpen = NULL;
	IShellItem* pItem = NULL;

	LPWSTR pwszFilePath = 0;

	// Initialise COM libraries
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr)) {
		VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Could not initialise the COM library.\n", nObjectID);
		UserErrorDisplay("ERROR: Failed to load libraries that are required for operation. Please try again later.\n", nObjectID);

		goto done;
	}

	// Create the FileOpenDialog object.
	hr = CoCreateInstance(
		CLSID_FileOpenDialog,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pFileOpen)
	);

	if (FAILED(hr)) {
		VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Could not initialise the FileOpenDialog object.\n", nObjectID);
		UserErrorDisplay("ERROR: Failed to create platform for the dialogue box. Please try again later.\n", nObjectID);

		goto done;
	}

	// Set the title
	hr = pFileOpen->SetTitle(s2ws(sTitle).c_str());

	if (bSelectFolder) {
		// Set to pick folders
		hr = pFileOpen->SetOptions(FOS_PICKFOLDERS);
		if (FAILED(hr)) {
			VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Could not set dialogue box options to pick folders.\n", nObjectID);
			UserErrorDisplay("ERROR: Failed to set dialogue box options to pick folders. Please try again later.\n", nObjectID);

			goto done;
		}
	}


	if (FAILED(hr)) {
		VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Failed to set window title of dialogue box.\n", nObjectID);
		UserErrorDisplay("ERROR: Failed to set the title for the dialogue box. Please try again later.\n", nObjectID);

		goto done;
	}

	// Show the file-open dialog.
	hr = pFileOpen->Show(NULL);

	if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED))
	{
		// User cancelled.
		hr = S_OK;
		goto done;
	}
	else if (FAILED(hr)) {
		VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Failed to display the file dialogue box using current setup.\n", nObjectID);
		UserErrorDisplay("ERROR: Failed to display the file dialogue box. Please try again later.\n", nObjectID);

		goto done;
	}


	// Get the file name from the dialog.
	hr = pFileOpen->GetResult(&pItem);

	if (FAILED(hr)) {
		VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Failed to get the full results from the File Dialogue Box.\n", nObjectID);
		UserErrorDisplay("ERROR: Failed to get results, such as filepath, from the dialogue box platform. Please try again later.\n", nObjectID);

		goto done;
	}

	hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);
	sFinalFilePath = ws2s(pwszFilePath);

	if (FAILED(hr)) {
		VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Failed to get the filepath from the results from the File Dialogue Box.\n", nObjectID);
		UserErrorDisplay("ERROR: Failed to get filepath from gathered results from the dialogue box platform. Please try again later.\n", nObjectID);

		goto done;
	}

done:

	if (pwszFilePath) {
		CoTaskMemFree(pwszFilePath);
	}

	if (pItem)
	{
		ThoroughRelease(pItem);
	}
	if (pFileOpen)
	{
		ThoroughRelease(pFileOpen);
	}

	CoUninitialize();

	if (FAILED(hr)) return false; else return true;
}