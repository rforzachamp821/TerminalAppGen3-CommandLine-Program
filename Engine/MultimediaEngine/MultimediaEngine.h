#pragma once

//
// MultimediaEngine.h - Houses the interface for the MultimediaEngine class.
//

#include <dshow.h>
#include <string>

class MultimediaEngine {
private:
	// Object ID
	int nObjectID;
protected:

	// RemoveFilters - Removes all filters from IGraphBuilder variable.
	// Arguments: pGraph for the graph to remove filters from.
	// Returns true for success, false for fail.
	//
	bool RemoveFilters(IGraphBuilder* pGraph);

public:

	// Constructor
	MultimediaEngine();

	// Destructor
	~MultimediaEngine();

	// DShowMultimediaPlayer - Plays a multimedia file using the DirectShow API.
	// Allowed filetypes are: WMA, WMV, AIFF, AU, AVI, MIDI, SND, WAV, JPG, JPEG, BMP
	// Arguments: wsInputFilePath - The file path for the multimedia file.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool DShowMultimediaPlayer(std::wstring wsInputFilePath);

	// BASSAudioPlayer - Plays an audio file using the BASS Audio API.
	// Allowed filetypes are: MP3, MP2, MP1, OGG, WAV, AIFF, FLAC, XM, IT, S3M, MOD, MTM, UMX, WMA, M4A, OPUS, AAC
	// Arguments: sInputFilePath - The file path for the audio file.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool BASSAudioPlayer(std::string sInputFilePath);

	// MMAPIAudioPlayer - Plays a WAV file using the Windows MultiMedia API.
	// Arguments: wsInputFilePath - The file path for the WAV file.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool MMAPIAudioPlayer(std::string sInputFilePath);

	// TTSOutput - Takes in an std::wstring (wide 'unicode' string) and outputs
	//             it through device speakers with a human-like voice.
	// Arguments: wsText - Text to be outputted as Text-To-Speech.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool TTSOutput(std::wstring wsText);

	// BeepSound - Produces access to produce a low-latency, audible and constant beep sound.
	// Arguments: dFrequency - Set the frequency of the beep sound. This is measured in Hertz.
	//            dDuration - Set the duration of the sound. This is measured in MILLISECONDS.
	//            bExitOnKeyPress - Exit on keypress while sound is being outputted.
	// Return values: TRUE or 1 for uninterrupted output, and FALSE or 0 for key pressed.
	// Notes: Providing no arguments will give a 500hz beep sound for 1 second.
	//
	bool BeepSound(long double dFrequency = 500, long double dDuration = 1, bool bExitOnKeyPress = false);
};