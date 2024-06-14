#pragma once

//
// RyRyCryptor.h - Contains the interface for the RyRyCryptor class.
//

// As this may change, typedef the key format
typedef uint64_t RYRYKEY;

// Undefine EncryptFile macro defined in Windows.h for FileCryptor command
#ifdef EncryptFile
#undef EncryptFile
#endif // ENCRYPTFILE

// Undefine DecryptFile macro defined in Windows.h for FileCryptor command
#ifdef DecryptFile
#undef DecryptFile
#endif // DECRYPTFILE

// RyRyCryptor - Class that manages and contains an implementation of the RyRy encryption algorithm.
//
class RyRyCryptor {
private:

	// Error level - defines the type of error that occured in a function/operation
	int nErrorLevel = N_SUCCESSFUL;

	// DecryptionVerifierString - String that indicates if the data was decrypted correctly or not
	static constexpr char czDecryptionVerifierString[] = "$RYRY";
	static constexpr size_t nDecryptionVerifierStringSize = sizeof(czDecryptionVerifierString) - 1;

	// EncodingVerifierString - String that verifies the encoding of the encrypted data - verifies that it's encoded by the RyRy Encryptor.
	static constexpr char czEncodingVerifierString[] = "$iN59";
	static constexpr size_t nEncodingVerifierStringSize = sizeof(czEncodingVerifierString) - 1;
	                     

	// EncryptStringUsingRyRyCryptor - Encrypts a string using the custom RyRy algorithm.
	//                                 - This does NOT return a modified string, nor does it copy one into itself. 
	//                                   This function modifies and encrypts a string reference directly, to save memory.
	// Parameters: sStringToDecrypt - A pointer to an std::string variable containing the string data to encrypt. Please pass a reference here, not a value.
	//             nKey1 - The first key to use for encryption (PIN).
	//             nKey2 - The second key to use for encryption (PIN 2).
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail (To get error details, call GetErrorLevelInfo()).
	//
	bool EncryptStringUsingRyRyCryptor(std::string* sStringToEncrypt, RYRYKEY nKey1, RYRYKEY nKey2);

	// DecryptStringUsingRyRyCryptor - Decrypts a string that was encrypted using the custom RyRy algorithm.
	//                                 - This does NOT return a modified string, nor does it copy one into itself. 
	//                                   This function modifies and decrypts a string reference directly, to save memory.
	// Parameters: sStringToDecrypt - A pointer to an std::string variable containing the string data to decrypt. Please pass a reference here, not a value.
	//             nKey1 - The first key to use for decryption (PIN).
	//             nKey2 - The second key to use for decryption (PIN 2).
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail (To get error details, call GetErrorLevelInfo()).
	//
	bool DecryptStringUsingRyRyCryptor(std::string* sStringToDecrypt, RYRYKEY nKey1, RYRYKEY nKey2);

public:

	// Class Constructor
	RyRyCryptor();

	// Constants for defining what error codes are what
	static constexpr int N_SUCCESSFUL = 0;
	static constexpr int N_FAILED_OPENFILE_READING = 1;
	static constexpr int N_FAILED_OPENFILE_WRITING = 2;
	static constexpr int N_DATA_INCORRECT_ENCODING = 3;
	static constexpr int N_FAILED_READING = 4;
	static constexpr int N_FAILED_WRITING = 5;
	static constexpr int N_INCORRECT_KEYS = 6;
	static constexpr int N_UNKNOWN_ERROR = std::numeric_limits<int>::max();


	// GetErrorLevel - Gets the value of the Error Level, which indicates the error code of the last function that was executed.
	// Parameters: None
	// Return Value: (int) Error level value.
	//
	inline int GetErrorLevel() {
		return nErrorLevel;
	}

	// GetErrorLevelInfo - Gets the error information of the current error level and returns it as a string.
	// Parameters: None
	// Return Value: (std::string) Information on the current error level.
	//
	std::string GetErrorLevelInfo();

	// EncryptString - Encrypts a string specified by sStringToEncrypt, and then returns the encrypted string.
	// Parameters: sStringToEncrypt - An std::string variable containing the string data to encrypt.
	//             nKey1 - The first key to use for encryption (PIN).
	//             nKey2 - The second key to use for encryption (PIN 2).
	// Return Value: (std::string) Encrypted string.
	//
	std::string EncryptString(std::string sStringToEncrypt, const RYRYKEY nKey1, const RYRYKEY nKey2);

	// EncryptString - Decrypts a string containing encrypted data specified by sStringToDecrypt, and then returns the decrypted string.
	// Parameters: sStringToDecrypt - An std::string variable containing the encrypted string data to decrypt.
	//             nKey1 - The first key to use for decryption (PIN).
	//             nKey2 - The second key to use for decryption (PIN 2).
	// Return Value: (std::string) Decrypted string.
	//
	std::string DecryptString(std::string sStringToDecrypt, const RYRYKEY nKey1, const RYRYKEY nKey2);

	// EncryptFile - Encrypts a file's contents in bulk (path specified by sFilePath), and then immediately writes the encrypted data back to the file.
	// Parameters: sFilePath - An std::string variable containing the file path of the file to encrypt.
	//             nKey1 - The first key to use for encryption (PIN).
	//             nKey2 - The second key to use for encryption (PIN 2).
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail (Get error information with GetErrorLevelInfo()).
	//
	bool EncryptFile(const std::string sFilePath, const RYRYKEY nKey1, const RYRYKEY nKey2);

	// DecryptFile - Decrypts an encrypted file's contents in bulk (path specified by sFilePath), and then immediately writes the decrypted data back to the file.
	// Parameters: sFilePath - An std::string variable containing the file path of the file to decrypt.
	//             nKey1 - The first key to use for decryption (PIN).
	//             nKey2 - The second key to use for decryption (PIN 2).
	// Return Values: TRUE or 1 for success, FALSE or 0 for fail (Get error information with GetErrorLevelInfo()).
	//
	bool DecryptFile(const std::string sFilePath, const RYRYKEY nKey1, const RYRYKEY nKey2);

};