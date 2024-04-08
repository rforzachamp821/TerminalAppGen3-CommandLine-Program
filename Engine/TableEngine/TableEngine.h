#pragma once
//
// TableEngine.h - File containing the interface for the TableEngine class.
//
#include <vector>
#include <string>

// TableEngine - A class that allows for creating tables at any point in time in your code.
// 
class TableEngine {
private:
	// Object ID
	int nObjectID;
protected:

	std::vector<std::vector<std::string>> vsTable;

	// GetLargestTableMemberSize
	size_t GetColumnSize(std::vector<std::string> vsMembers);

public:

	// TableEngine constructor
	TableEngine();

	// TableEngine destructor
	~TableEngine();

	// Add a new row to vsTable
	inline void addRow(std::vector<std::string> row) {
		vsTable.push_back(row);
		return;
	}

	// Output the table based on all user arguments
	void OutputTable();
};