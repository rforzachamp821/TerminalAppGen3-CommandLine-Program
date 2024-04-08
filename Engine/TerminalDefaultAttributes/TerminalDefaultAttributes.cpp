//
// TerminalDefaultAttributes.cpp - File containing the TerminalDefaultAttributes class definitions.
//
#include "TerminalDefaultAttributes.h"

// Constructor
TerminalDefaultAttributes::TerminalDefaultAttributes() {
	// Initialise all structures and variables, as a 'default' scheme.
	InitialiseStructures();
}

// Destructor
TerminalDefaultAttributes::~TerminalDefaultAttributes() {
	// As the name of this class suggests, reset terminal attributes to defaults.
	ResetTerminalAttributesToDefault();
}
