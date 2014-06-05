#include "iostream"
#include "FreeMemory.h"
#include "constants.h"
#include "Loop.h"
#include "string"
#include "stdio.h"

// Default constructor
FreeMemory::FreeMemory(){
  maxMem = 0;
};

// Pre:  memoryAvailable > 0 and the size of available memory
// Post: The single block of full free memory is added to records
void FreeMemory::memSize(ulli memoryAvailable){
  if (memoryAvailable > 0){
    maxMem = memoryAvailable;
    Mem.add(maxMem); // Add a sinle open node with the maxMemory space
    // available 
    ulli firstAddress = 0;
    Start.add(firstAddress); // Add the start address of this free block of memory
  }
}

// Pre:  progSize > 0, startAddress is initialized
// Post: false if no room, true if room for program and start
//       address is set to the start address associated with the
//       program 
bool FreeMemory::assignMemory(ulli progSize, ulli & startAddress){
  bool space = false;
  for (int block=0; ((!space)&&(block<Mem.getSize())); block++){
    ulli freeMem = Mem[block]->getData();
    if (freeMem > progSize){ // If there is room
      space = true;
      Mem[block]->setData(freeMem-progSize); // Modify free space
      startAddress = Start[block]->getData();
      Start[block]->setData(startAddress+progSize); // Modify start
      // into the new leading program

    }
  }
  return(space);
}

// Pre:  sA and eA are valid memory addresses
// Post: This block of memory is marked as free
void FreeMemory::freeMemory(ulli sA, ulli eA){
  bool freed = false;
  for (int block=0; block<Mem.getSize(); block++){
    ulli start = Start[block]->getData();    
    ulli size = Mem[block]->getData();
    if ((eA == start)||(sA == (start+size))){
      freed = true;
      Start[block]->setData( eA == start ? sA : start );
      Mem[block]->setData(size+(eA-sA));      
    }
  }
  if (! freed){
    bool inserted = false;
    for (int block=0; ((!inserted)&&(block<Mem.getSize())); block++){
	if ( sA < Start[block]->getData() ){
	Start.insert(sA, block);
	ulli size = eA-sA;
	Mem.insert(size, block);
	inserted = true;
      }
    }
  }
  condenseMem(); // Make sure all adjacent cells are collapsed
}

// Pre:  There is some set of free memory
// Post: The adjacent free memory cells are collapsed into singles
void FreeMemory::condenseMem(){
  if (Mem.getSize() > 1 ){
    for (int block = 0; block<Mem.getSize()-1; block++){
      ulli start = Start[block]->getData();
      ulli size = Mem[block]->getData();
      ulli nextStart = Start[block+1]->getData();
      ulli nextSize = Mem[block+1]->getData();
      if ((start + size) == nextStart){
	Start.remove(block+1);	Mem.remove(block+1);
	Mem[block]->setData(size+nextSize);
	block--; // Decrement block and check this expanded cell again
      }
    }    
  }
}

// Pre:  out is defined
// Post: out is filled with information about the free memory
void FreeMemory::printMem(string & out){
  char line[LINESIZE];
  for (int block=0; block<Mem.getSize(); block++){
    ulli start = Start[block]->getData();
    ulli size = Mem[block]->getData();
    sprintf(line, FREEMEM_STRING, block, start, size);
    out.append(line); // Add the line to the output
  }
}

