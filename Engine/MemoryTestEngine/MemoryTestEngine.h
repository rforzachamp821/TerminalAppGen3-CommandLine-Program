#pragma once

//
// MemoryTestEngine.h - Interface for the Memory Test Engine and its class.
//
#include <atomic>
#include <vector>
#include <string>
#include <thread>


// MemoryTestEngine - Engine containing components for memory testing and stressing.
//                  - Contains multithreading support.
//                  - Contains binary search stress testing, linear search verification and testing algorithms, etc.
//                  - The test algorithms involved are intended to fill up the host system's memory to its maximum
//                    WITHOUT restarting it, which can run the risk of memory paging. It is highly recommended to
//                    run the tests with minimal background tasks and open programs to reduce the likelihood of this 
//                    happening, and instead rely on Windows memory compression.
//
class MemoryTestEngine {

private:

	// Keyboard termination global variable - For reporting keyboard press on process execution
	bool bKeyboardTermination = false;

	// KeyboardAbortHandler termination switch
	std::atomic<bool> bKillKeyboardAbortHandler = false;

	// Thread worker termination switch
	std::atomic<bool> bKillThreads = false;

	// Number of logical cores to use for multithreading
	const unsigned int nNumOfThreads = std::thread::hardware_concurrency();

	// Boolean thread completion vector - to indicate thread completion
	std::vector<bool> vThreadCompletionIndicator;


	///////////////////////////////////////
	/*  PROPRIETARY VARIABLES / MEMBERS  */
	///////////////////////////////////////

	// Container for index number result for binary search
	uint64_t nIndexNum = 0;

	// To communicate to main threadcall that one thread found the correct number (Binary Search proprietary)
	std::atomic<bool> bNumberFound = false;

	// Vector for all indexes that failed (Linear Searches proprietary)
	std::vector<uint64_t> vFailedIndexes;

	// Number of current errors found in memory on current pass (Linear Searches proprietary)
	uint64_t nNumOfCurrentCheckErrors = 0;

	// Object ID
	int nObjectID;


	// BinarySearch - A custom multithreaded binary search algorithm with little optimisation (focused on memory stress, not searching specifically)
	//              - Binary search requires a sorted list, which is how the memory container is initialised.
	//              - This custom algorithm looks only at the memory container, and does not accept a memory container pointer argument.
	// Arguments: nSearchNum - The value to search for.
	//            bMultiThreaded - Use multithreading or not.
	//            nInitialisationThreadNumber - Thread number out of total thread count, which indicates the part of the array to search through for the thread.
	//                                          If bMultiThreaded is TRUE, this must be passed with 0 or above, to nNumOfThreads - 1.
	// Return values: Index of the found number.
	// 
	// NOTE: 0 may be returned when an error occurs. This is normal, as it sets nErrorLevel instead. See nErrorLevel for more info about the error codes.
	//
	void BinarySearch(const uint64_t nSearchNum, bool bMultiThreaded, unsigned int nInitialisationThreadNumber);

	// KeyboardAbortHandler - Handler for keyboard abortion
	void KeyboardAbortHandler();

	// Reset the thread completion vector, thread kill switch
	void ResetThreads();

protected:


	// Memory container in the form of std::vector
	std::vector<uint64_t> nMemoryContainer;

	// nErrorLevel - Error level of error that occured. Error code definitions are below:
	//             - 0: No error has occured, and all operations should be normal. 
	//             - 1: An error occured when getting the size of the host system memory.
	//             - 2: An unknown binary search error has occured, where the random search value wasn't found.
	//             - 3: A bad initialisation thread number was passed into a thread worker.
	//             - 4: An memory error was detected.
	//
	int nErrorLevel = 0;


	// InitialiseMemoryContainer - Initialise the memory container and fill it linearly, depending on host system memory capacity.
	// Arguments: None
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool InitialiseMemoryContainer();

	// UninitialiseMemoryContainer - Unload and destroy the memory stored in the memory container and bring it back to 0.
	// Arguments: None
	// Return values: None
	//
	void UninitialiseMemoryContainer();

	//////////////////////////////
	/* THREADS FOR MEMORY TESTS */
	//////////////////////////////

	// PerformLinearSearchOnMemoryThread - Thread worker for PerformLinearSearchOnMemory.
	// Arguments: bMultiThreaded - Use multithreading or not.
	//            nInitialisationThreadNumber - Thread number out of total thread count, which indicates the part of the array to search through for the thread.
	//                                          If bMultiThreaded is TRUE, this must be passed with 0 or above, to nNumOfThreads - 1.
	// Does not return any values.
	//
	void PerformLinearSearchOnMemoryThread(bool bMultiThreaded, unsigned int nInitialisationThreadNumber, std::atomic_ullong& nProgressCounter);

	// PerformExtendedLinearSearchOnMemoryThread - Thread worker for PerformExtendedLinearSearchOnMemory.
	// Arguments: bMultiThreaded - Use multithreading or not.
	//            nInitialisationThreadNumber - Thread number out of total thread count, which indicates the part of the array to search through for the thread.
	//                                          If bMultiThreaded is TRUE, this must be passed with 0 or above, to nNumOfThreads - 1.
	// Does not return any values.
	//
	void PerformExtendedLinearSearchOnMemoryThread(bool bMultiThreaded, unsigned int nInitialisationThreadNumber, std::atomic_ullong& nProgressCounter);

public:

	/* bUseTotalPhysicalCapacity - Adjusts how much memory will be reserved and checked on the host system.

	If this is set to true, the memory container will reserve all the memory available on the host system.
			 - It may cause slowdowns if there are too many programs running.
	If this is set to false, the memory container will reserve all the currently unused available memory on the host system.
			 - This may lead to a less accurate test when too much memory is being used by other programs at test starting time.
	*/
	bool bUseTotalPhysicalCapacity = false;

	MemoryTestEngine();

	~MemoryTestEngine();

	// FillMemoryMaximum - Fills up memory to the maximum that the host's memory can hold, and then unloads memory. Nothing more, nothing less.
	// Arugments: bKeypressBeforeUnload - Require user keypress before unloading memory. True or 1 for requiring keypress, false or 0 for not requiring it.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool FillMemoryToMaximum(bool bKeypressBeforeUnload = false);

	// PerformBinarySearchOnMemory - Fills up memory to the maximum that the host's memory can hold, performs random number binary searches depending on the number
	//                               of passes desired, and unloads the memory.
	//                             - This function very lightly checks for memory integrity both during the binary search and after it, and is more of a memory stress test.
	// Arguments: nNumOfPasses - Number of binary search passes to perform.
	//            bMultiThreaded - Use more than 1 thread for the test when this is TRUE.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool PerformBinarySearchOnMemory(uint64_t nNumOfPasses, bool bMultiThreaded);

	// PerformLinearSearchOnMemory - Fills up memory to the maximum that the host's memory can hold, performs linear check searches depending on the number of passes
	//                               desired, and unloads the memory.
	//                             - This function heavily checks for memory integrity by checking for the right values for each byte on memory. This is more of a memory integrity test.
	// Arguments: nNumOfPasses - Number of binary search passes to perform.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool PerformLinearSearchOnMemory(uint64_t nNumOfPasses, bool bMultiThreaded);

	// PerformExtendedLinearSearchOnMemory - Fills up memory to the maximum that the host's memory can hold, checks each 8 bytes of memory for correct values linearly,
	//                                     - changes the cell of memory to a randomly calculated integer (and checks for validity again), and switches back to the same old
	//                                     - integer with the same validity check at the beginning.
	// Arguments: nNumOfPasses - Number of extended linear check search passes to perform.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool PerformExtendedLinearSearchOnMemory(uint64_t nNumOfPasses, bool bMultiThreaded);

	/* Error functions */

	// GetLastErrorValue - Gets the error code of last error that occured.
	// Arguments: None
	// Return values: Error code of last error that occured.
	//
	inline int GetLastErrorValue() {
		return nErrorLevel;
	}

	// GetLastErrorInfo - Gets the error info of the last error that occured.
	// Arguments: None
	// Return values: Error info of last error that occured, as a string.
	//
	std::string GetLastErrorInfo();
};