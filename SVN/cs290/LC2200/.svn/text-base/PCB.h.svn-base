#ifndef INCLUDED_PCB
#define INCLUDED_PCB

#include "constants.h"
#include <string>

class PCB{
  // CI: This class will hold all necessary information for one
  //     program, and the information that is important.
public:
  ulli ProcessID;  // Current PID
  ulli PC; // Current PC
  ulli Registers[NUMREGISTERS]; // All register states
  bool OwnsIO; // Whether or not this program can print
  ulli StartTime; // The start clock time
  ulli EndTime; // The end clock time
  ulli RunTime; // The run time of the process
  ulli sA; // Start address for program
  ulli eA; // End address for program
  ulli pageFaults; // Number of pagefaults caused by program
  char Name[LINESIZE]; // Filename holder

  // Default constructor
  // Pre:  Process ID, Start Time, Stack Pointer, Owns I/O
  // Post: All member data is set accordinly, EndTime and RunTime set
  //       to 0 as default
  PCB(ulli pid, ulli st, ulli sp, ulli oio, const char *name){
    ProcessID = pid; 
    StartTime = st; 
    EndTime = 0;
    eA = sp;
    Registers[SP] = sp;
    PC = Registers[FP] = sA = 0;
    OwnsIO = oio;
    RunTime = 0;
    pageFaults = 0;
    strcpy(Name, name); // Save the name to this PCB
  }

  // Pre:  sp is the last valid memory byte location for this
  //       program's stack
  // Post: sp is set in the register to the appropriate value
  void setSP(ulli sp){ Registers[SP] = sp; }

  // Pre:  fp is the last valid memory byte location for this
  //       program's stack
  // Post: fp is set in the register to the appropriate value
  void setFP(ulli fp){ Registers[FP] = fp; }

  // Pre:  out and pcb are well defined and initialized
  // Post: The data from pcb is posed to output
  friend ostream & operator<<(ostream & out, PCB & pcb){
    out << "---PID: " << pcb.ProcessID << "---" << std::endl;
    out << "PC: " << pcb.PC << std::endl;    
    out << "Frame Pointer: " << pcb.sA << std::endl;
    out << "OwnsIO: " << pcb.OwnsIO << std::endl;
    out << "End Address: " << pcb.eA << std::endl;
    out << "Start Time: " << pcb.StartTime << std::endl;
    out << "End Time: " << pcb.EndTime << std::endl;
    out << "Run Time: " << pcb.RunTime << std::endl;
    out << "Page Faults: " << pcb.pageFaults << std::endl;
    out << "::Registers::" << std::endl;
    for (int r=0; r<NUMREGISTERS; r++){
      out << "r" << r << " " << std::hex << pcb.Registers[r] 
	  << std::dec << std::endl;
    }
    out << "------------" << std::endl;
    return(out);
  }

};

#endif
