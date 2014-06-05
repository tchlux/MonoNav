#ifndef DEFINED_FREEMEMORY
#define DEFINED_FREEMEMORY

#include "constants.h"
#include "Loop.h"
#include "string"

class FreeMemory{
private:
  // This class will manage the free memory for the machine
  ulli maxMem; // The maximum amount of memory
  Loop<ulli> Mem; // The blocks of memory available
  Loop<ulli> Start; // The start addresses of the associated blocks of
		    // mem at the same index

public:
  // This is the standard constructor for this class
  FreeMemory();

  // memoryAvailable > 0 and the size of available memory
  void memSize(ulli memoryAvailable);

  // Pre:  progSize > 0, startAddress is initialized
  // Post: false if no room, true if room for program and start
  //       address is set to the start address associated with the
  //       program 
  bool assignMemory(ulli progSize, ulli & startAddress);

  // Pre:  sA and eA are valid memory addresses
  // Post: This block of memory is marked as free
  void freeMemory(ulli sA, ulli eA);

  // Pre:  There is some set of free memory
  // Post: The adjacent free memory cells are collapsed into singles
  void condenseMem();

  // Pre:  out is defined
  // Post: out is filled with information about the free memory
  void printMem(string & out);

};


#endif
