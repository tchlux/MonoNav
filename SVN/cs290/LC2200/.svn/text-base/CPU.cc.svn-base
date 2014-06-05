#include <iostream>
#include "utilities.h"
#include "CPU.h"
#include "constants.h"
#include "string.h"
#include "stdio.h"

using namespace std;

// PRE: 
// POST: This CPU object is defined. PC and all registers are set to 0.
CPU::CPU() {
  PC = 0;
  for (int i=0; i < NUMREGISTERS; i++) {
    registers[i] = 0;
  }
}


// PRE:  output is defined
// POST: char * containing the value of PC and registers, all in hex in the format:
//         PC = 0xhhhhhhhh
//         00: 0xhhhhhhhh 01: 0xhhhhhhhh 02: 0xhhhhhhhh 03: 0xhhhhhhhh
//         04: ....
//         08: ....
//         12: ....
void CPU::printCPU(string & output) {
  char * hexPC = uIntToHex (PC);
  output.append("PC = ");
  output.append(hexPC);
  for (int i = 0; i < NUMREGISTERS; i++) {
    if (i % NUMREGONONELINE == 0) {
      output.push_back('\n');
    }
    char * hexReg =    uIntToHex (registers[i]);
    char regCode [3];  getRegCode(i, regCode);
    char codes[CPU_CODES]; 
    sprintf(codes, "%s (%2d): %s  \n", regCode, i, hexReg);
    output.append(codes);
    delete[] hexReg;
  }

  delete[] hexPC;
}

// Pre:  regNo, code
// Post: 
void CPU::getRegCode(int regNo, char code[]) {
  char regCodes[NUMREGISTERS][3] = {"z0", "at", "v0", "a0", 
				    "a1", "a2", "t0", "t1",
				    "t2", "s0", "s1", "s2",
				    "k0", "sp", "fp", "ra"};
  strcpy(code, regCodes[regNo]);
}
