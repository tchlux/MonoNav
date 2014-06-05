#ifndef INCLUDED_MEMORY
#define INCLUDED_MEMORY

#include <stdio.h>
#include <string>
#include "constants.h"

using namespace std;

class Memory {

 private:
  ulli * store; // an array of ullis for RAM storage
  ulli * swap;  // An array of ullis for Swap storage
  ulli memorySize; // the number of bytes of memory.
  int stackSize;

 public:

  // Constructors

  // Default constructor.
  Memory() { 
    memorySize = 0;
  };
  
  // Pre:  store has some data in it
  // Post: frees memory from store
  ~Memory() {  delete[] (store);  };

  // PRE: size is defined (> 0) as number of bytes of memory. 
  // POST: The memory store is defined with size bytes. Each word is
  //       initialised to 0. memorySize = (size - (size % 4)). 
  Memory (ulli size);

  // Returns memory size
  ulli getSize () { return (memorySize); };

  // Returns memory size
  int getStackSize () { return (stackSize); };

  // PRE: size is defined (> 0) as number of words of memory. swapSize
  //      is defined as the number of pages of memory
  // POST: The memory store is defined with size bytes. Each word is
  //       initialised to 0. memorySize = (size - (size % 4)). 
  void setSize (ulli size, ulli swapSize);

  // PRE: size is defined (> 0) as number of words of memory. swapSize
  //      is defined as the number of pages of memory
  // POST: The memory store is defined with size bytes. Each word is
  //       initialised to 0. memorySize = (size - (size % 4)). 
  void setStackSize (int size) ;

  // Accessor
  // PRE: address is defined and less than memory size.
  // POST: If the address is within memory bounds and is a multiple of
  //          4, contents is set to
  //          the ulli at memory address "address" and error is
  //          set to false;
  //       Else error is set to true.
  void getWord (ulli address, ulli & contents, 
		bool & error);

  // Modifiers

  // PRE: address is defined and less than memory size.
  //      contents is defined.
  // POST: If the address is within memory bounds and is a multiple of
  //          4, the word at address is set to the value of contents
  //          and error is set to false;
  //       Else error is set to true.
  void putWord (ulli address, ulli contents, bool & error);


  // Accessor
  // PRE: address is defined and less than memory size.
  // POST: If the address is within memory bounds and is a multiple of
  //          4, contents is set to
  //          the ulli at memory address "address" and error is
  //          set to false;
  //       Else error is set to true.
  void getSwapWord (ulli address, ulli & contents, bool & error);

  // PRE: address is defined and less than memory size.
  //      contents is defined.
  // POST: If the address is within memory bounds and is a multiple of
  //          4, the word at address is set to the value of contents
  //          and error is set to false;
  //       Else error is set to true.
  void putSwapWord (ulli address, ulli contents, bool & error);

  // I/O
  // PRE: This object is defined. address is a defined
  //       address. 
  // POST: Output stream contains the (word) contents of address "address" in
  //        hexadecimal and decimal in the format 
  //        0xaaaaaaaa: 0xhhhhhhhh (ddd)
  //       If address is not a multiple of 4, the content of the word
  //        containing that byte is printed.
  void printWord (ulli address, string & output);

  // PRE: This object is defined. startAddr and endAddr are
  //       addresses. endAddr >= startAddr.
  // POST: OS contains the contents of memory locations starting with
  //       the word at address "startAddr" and ending with the word at
  //       address "endAddr". Each word is printed on one line in the
  //       format
  //       0xaaaaaaaa: 0xhhhhhhhh (ddd)
  //       If startAddress is not a multiple of 4, the startAddr is
  //       startAddr - (startAddr % 4)
  //       If endAddress is not a multiple of 4, the endAddr is
  //       endAddr - (endAddr % 4)
  void printRange (ulli startAddr,  ulli endAddr,  string & output);

  bool addressOK (ulli addr) {
    return ( !((addr < 0)
	       || (addr > (memorySize - 4))
	       || (addr % 4 != 0)) );
  };
  
};

#endif
