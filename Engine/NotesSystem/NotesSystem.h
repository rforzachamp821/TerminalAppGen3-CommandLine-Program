#pragma once
//
// NotesSystem.h - Contains interfaces for the NotesSystem and NotesSystemUI classes.
//
#include <string>


// NotesSystem - System for managing the creation and saving of user-defined notes.
//             - NotesSystem has the capabilities to save both in memory and as a file.
//             - NotesSystem will wipe out all notes from memory on object destruction for security measures.
//             - NotesSystem will update memory contents with ones in file on object creation.
// 
class NotesSystem
{
private:

	// Some constants declared so whenever there's a bug/change that's needed to be done, less steps are needed.
	const int nArraySize = 1024;
	const char* sDefaultFileName = "NotesFile.txt";

	std::string* sNotes = new std::string[1024];

	// Object ID
	int nObjectID;

public:

	// Constructor
	NotesSystem();

	// Destructor
	~NotesSystem();

	// AddNoteToArray - Adds a note to a passed note index, on the notes array.
	// Parameters: nArrayIndex - Note index to save the note to, based on 0. This cannot be higher than the returned value of GetCurrentNotesCount().
	//            sNoteText - The text to be used in the note.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool AddNoteToArray(size_t nArrayIndex, std::string sNoteText);

	// WriteToNotesFile - Write to notes file in the same directory as program folder, from contents saved in memory.
	//                  - This function will create a new file if an existing one isn't found, by default due to C++.
	// Parameters: None
	// Return values: TRUE for success, FALSE for fail.
	//
	bool WriteToNotesFile();

	// ReadFromNotesFile - Read from notes file and put contents into memory.
	//                   - This function will stop copying when the number of lines read reach nArraySize.
	// Parameters: None
	// Return values: TRUE for success, FALSE for fail.
	//
	bool ReadFromNotesFile();

	// ClearAllNotes - Clears all notes from notes file and notes array.
	//               - This is equivalent to performing a full reset of the entire Notes system.
	// Parameters: None
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	// NOTE: Any FALSE return comes from the NotesSystem::WriteToNotesFile() function, and is related to clearing the notes file.
	//
	bool ClearAllNotes();

	// GetMemoryNotes - Gets all contents of the notes saved in memory and returns them as a singular string.
	// Parameters: None
	// Return value(s): The singular string containing the contents of the notes saved in memory.
	//
	std::string GetMemoryNotes();


	// GetFileNotes - Gets all contents of the notes file and returns them as a singular string.
	// Parameters: None
	// Return value(s): The singular string containing the contents of the notes file.
	//
	std::string GetFileNotes();

	// GetCurrentNotesCount - Gets the current number of notes in memory.
	// Parameters: None
	// Return value(s): The number of notes in memory, base 1.
	//
	size_t GetCurrentNotesCount();

	// GetMaxNotesArraySize - Gets the size of the notes array.
	// Parameters: None
	// Return value(s): The size of the notes array, in the number of elements.
	//
	inline int GetMaxNotesArraySize() {
		return nArraySize;
	}
};

// NotesSystemUI - Class containing UI functions for the Notes System.
class NotesSystemUI
{
private:
	// Object ID
	int nObjectID;
public:

	NotesSystemUI();

	~NotesSystemUI();

	// NotesEditor - Provides an interface to edit notes.
	// Parameters: None
	// Return Value: None
	//
	void NotesEditor();

	// NotesViewer - Provides an interface to view notes.
	// Parameters: None
	// Return Value: None
	//
	void NotesViewer();
};