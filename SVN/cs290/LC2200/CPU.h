#ifndef INCLUDED_CPU
#define INCLUDED_CPU

#include <stdio.h>
#include <string>
#include "constants.h"

using namespace std;

class CPU {

 private:
  ulli PC; // program counter
  ulli registers[NUMREGISTERS];

 public:

  // Constructors
  
  // PRE: 
  // POST: This CPU object is defined. PC and all registers are set to 0.
  CPU();

  // Accessors

  // PRE: This object is defined. 
  // POST: RV = the value of PC (as an ulli)
  ulli getPC () { return (PC); };

  // PRE: This object is defined. regNo is defined
  // POST: RV = the contents of registers[regNo]. (as an ulli)
  ulli getReg (ulli regNo){ return (registers[regNo]); };

  // Modifiers

  // PRE: value is defined.
  // POST: The value of PC is set to value.
  void setPC (ulli value) { PC = value; };

  // PRE: value is defined.
  // POST: The value of FP (reg. 14) is set to value.
  void setFP (ulli value) { setReg (FP, value); };

  // PRE: value is defined.
  // POST: The value of SP (reg. 13) is set to value.
  void setSP (ulli value) { setReg (SP, value); };

  // PRE: regNo is defined. value is defined. 
  // POST: registers[regNo] = value.
  void setReg (ulli regNo, ulli value) { registers[regNo] = value; };

  // I/O

  // PRE: output is defined, and will be sent to the shell
  // POST: char * containing the value of PC and registers, all in hex in the format:
  //         PC = 0xhhhhhhhh
  //         00: 0xhhhhhhhh 01: 0xhhhhhhhh 02: 0xhhhhhhhh 03: 0xhhhhhhhh
  //         04: ....
  //         08: ....
  //         12: ....
  void printCPU (string & output);

  // Pre:  regNo is in range 0<NUMREGISTERS, len(code) > 
  // Post: Gets the register code from a specified register and places
  //       its contents in code
  void getRegCode(int regNo, char code[]);

};
#endif
