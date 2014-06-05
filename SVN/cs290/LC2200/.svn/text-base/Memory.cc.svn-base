#include <iostream>
#include "constants.h"
#include "utilities.h"
#include "Memory.h"

using namespace std;

// PRE: size is defined (> 0) as number of bytes of memory and is a
// multiple of 4
// POST: The memory store is defined with size bytes. Each word is
//       initialised to 0. memorySize = (size + (4 - (size % 4)))). 
Memory::Memory (ulli size) {
  //  memorySize = (size + (BYTESPERWORD - (size % BYTESPERWORD)));
  memorySize = size; // since simulator makes sure this is a multiple of 4. 
  int numWords = memorySize / BYTESPERWORD;
  store = new ulli[numWords];
  for (int i = 0; i < numWords; i++)  store[i] = 0;
}

// PRE: size is defined (> 0) as number of words of memory. swapSize
//      is defined as the number of bytes of memory
// POST: The memory store is defined with size bytes. Each word is
//       initialised to 0. memorySize = (size - (size % 4)). 
void Memory::setSize (ulli size, ulli swapSize) {
  //  memorySize = (size + (BYTESPERWORD - (size % BYTESPERWORD)));
  memorySize = size * WORD_SIZE;
  store = new ulli[size];
  for (int i = 0; i < size; i++)  store[i] = 0;
  swap = new ulli[swapSize];
  for (int i = 0; i < swapSize; i++)  swap[i] = 0;
}

// PRE: size is defined (> 0) as number of words of memory. swapSize
//      is defined as the number of pages of memory
// POST: The memory store is defined with size bytes. Each word is
//       initialised to 0. memorySize = (size - (size % 4)). 
void Memory::setStackSize (int size){ stackSize = size; } ;


// Accessor
// PRE: address is defined and less than memory size.
// POST: If the address is within memory bounds and is a multiple of
//          4, contents is set to
//          the ulli at memory address "address" and error is
//          set to false;
//       Else error is set to true.
void Memory::getWord (ulli address, ulli & contents, 
		      bool & error) {
  error = false;
  if (((address % BYTESPERWORD) == 0) && (address < memorySize))
    contents = store[address / BYTESPERWORD];
  else
    error = true;
}

// Modifiers

// PRE: address is defined and less than memory size.
//      contents is defined.
// POST: If the address is within memory bounds and is a multiple of
//          4, the word at address is set to the value of contents
//          and error is set to false;
//       Else error is set to true.
void Memory::putWord (ulli address, ulli contents, bool & error) {
  error = false;
  if ((address % BYTESPERWORD == 0) && (address < memorySize))
    store[address / BYTESPERWORD] = contents;
  else
    error = true;
}

// Accessor
// PRE: address is defined and less than memory size.
// POST: If the address is within memory bounds and is a multiple of
//          4, contents is set to
//          the ulli at memory address "address" and error is
//          set to false;
//       Else error is set to true.
void Memory::getSwapWord (ulli address, ulli & contents, 
		      bool & error) {
  error = false;
  if (((address % BYTESPERWORD) == 0) && (address < memorySize))
    contents = swap[address / BYTESPERWORD];
  else
    error = true;
}

// Modifiers

// PRE: address is defined and less than memory size.
//      contents is defined.
// POST: If the address is within memory bounds and is a multiple of
//          4, the word at address is set to the value of contents
//          and error is set to false;
//       Else error is set to true.
void Memory::putSwapWord (ulli address, ulli contents, bool & error) {
  error = false;
  if ((address % BYTESPERWORD == 0) && (address < memorySize))
    swap[address / BYTESPERWORD] = contents;
  else
    error = true;
}

// I/O
// PRE: This object is defined. address is a defined
//       address, and is less than memorySize.
// POST: Output stream contains the (word) contents of address "address" in
//        hexadecimal and decimal in the format 
//        0xaaaaaaaa: 0xhhhhhhhh (ddd)
//       If address is not a multiple of 4, the content of the word
//        containing that byte is printed.
void Memory::printWord (ulli address, 
			string & output) {
  if (address < memorySize) {
    char * hexAddr = uIntToHex(address);
    char * hexContent = uIntToHex (store[address / BYTESPERWORD]);

    output.append(hexAddr);    output.append(": "); 
    output.append(hexContent); output.append("\n");

    delete[] (hexAddr);
    delete[] (hexContent);
  }
  else 
    output.append("Word address out of range.\n");
}

// PRE: This object is defined. startAddr and endAddr are
//       addresses. endAddr >= startAddr.
// POST: output contains the contents of memory locations starting
//       with the word at address "startAddr" and ending with the word
//       at address "endAddr". Each word is printed on one line in the
//       format
//       0xaaaaaaaa: 0xhhhhhhhh (ddd)
//       If startAddress is not a multiple of 4, the startAddr is
//       startAddr - (startAddr % 4)
//       If endAddress is not a multiple of 4, the endAddr is
//       endAddr - (endAddr % 4)
void Memory::printRange (ulli startAddr, 
			 ulli endAddr,
			 string & output) {
  if (endAddr > startAddr) {
    if (startAddr >= 0) {
      startAddr = (startAddr / 4) * 4;
      endAddr = (endAddr / 4) * 4;
      if (addressOK(startAddr) && addressOK(endAddr)) {
	for (ulli i = startAddr; 
	     i <= endAddr; i+=BYTESPERWORD) { 
	  printWord (i, output);
	}
      }
      else 
	output.append("Address out of range.\n");
    }
    else 
      output.append("Addresses must be positive.\n");
  }
  else
    output.append("Empty address range to print.\n");
}
