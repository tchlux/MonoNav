#ifndef INCLUDED_Machine
#define INCLUDED_Machine

#include "CPU.h"
#include "Memory.h"
#include <string.h>
#include "constants.h"
#include "PCB.h"
#include "Loop.h"
#include "PageTableEntry.h"

using namespace std;

class Machine {
 private:
  CPU MCPU;
  Memory MMemory;
  Loop<PCB*> ReadyQ; // Holder for queue of PCB's
  Loop<PCB*> CompletedQ; // Holds the completed programs
  Loop<PageTableEntry*> LRU; // The least recently used queue
  PageTableEntry * RAM; // Array of ram pages
  PageTableEntry * Swap; // Array of swap space pages
  void (*toShell)(const char*, int*); //Funtion for sending info to shell
  void (*readShell)(char*, int*, bool&); //'' for retrieving information  
  ulli Clock; // system clock
  ulli nextFreePID;
  ulli nextFreeAddr;
  ulli RamPages; // Number of pages in RAM
  ulli SwapPages; // Number of pages in swap
  bool Error;
  bool MachineHALT;
  bool sentEndLoop; // If the machine has returned I/O to shell
  int *channel1, *channel2; // Holders for the pipes
  int max_chars; // Maximum characters in mem output
  int timeSlice; // Current time Slice
  int timeSliceLength; // Number of time slices per program
  int pageSize;  // Number of words in a page
  
 public:

  // Constructors

  // PRE: size is defined (> 0) as number of bytes of memory. stack is
  //      the size of the stack space for each program.  timeSlice is
  //      the length of the timeSlice for each program
  //      pageSize is the number of words in one page
  //      swapSpace is the size (in pages) of the swap space
  //      toSfxn is a function to write to the shell
  //      readSfxn is a function to read from the shell,
  //      ch1 -> toMachine pipe ch2 -> toShell pipe
  // POST: This object is constructed with size bytes of memory.
  Machine (ulli size, int stack, int tS, int pS, int sS,
	   void(*toSfxn)(const char*,int*),
	   void(*readSfxn)(char*,int*,bool&), int *ch1, int *ch2);

  // Post: Returns whether or not the machine is given back I/O
  //       privaliges to the shell
  bool returnedIO() { return(sentEndLoop); };

  // PRE: A program has been loaded in memory. PC has an address.
  // POST: The word of memory at the address given by PC is fetched
  //        and decoded as opcode, X, Y, Z, value.
  void decode ();

  // PRE: address is defined. contents is defined.
  // POST: Set the value of memory at address "address" to be
  // contents. 
  //       The error flag is set to true if the address is not valid. 
  void putWord (unsigned long long int address, 
		unsigned long long int contents) {
    bool error = Error;
    MMemory.putWord (address, contents, error);
    Error = error;
  };

  // PRE: 0 <= regX, regY < 16. immediate is defined.
  // POST: regX is set to the sum of the contents of regY and
  // immediate. 
  void addi (int regX, int regY, long long int immediate);

  // PRE: 0 <= regX, regY, regZ < 16.
  // POST: regX is set to the sum of the contents of regY and regZ
  void add (int regX, int regY, int regZ);

  // PRE: 0 <= regX, regY, regZ < 16.
  // POST: regX is set to the nand of the contents of regY and regZ
  void nand (int regX, int regY, int regZ);

  // PRE: 0 <= regX, regY < 16. offset is defined.
  // POST: regX is set to the contents of the effective address formed
  // by adding offset to the contents of regY.
  // The machine indicates an error if the effective address is not a
  // word address, or is out of bounds.
  void lw (int regX, int regY, long long int offset);

  // PRE: 0 <= regX, regY < 16. offset is defined.
  // POST: The contents of the effective address (formed
  // by adding offset to the contents of regY) are set to the contents
  // of regX.
  // The machine indicates an error if the effective address is not a
  // word address, or is out of bounds.
  void sw (int regX, int regY, long long int offset);

  // PRE: 0 <= regX, regY < 16. offset is defined.
  // POST: If the contents of regX and regY are equal, then PC is to the
  // effective address formed by adding offset to the contents of PC.
  // The machine indicates an error if the effective address is not a
  // word address, or is out of bounds.
  void beq (int regX, int regY, long long int offset);

  // PRE: 0 <= regX, regY < 16.
  // POST: Set the contents of regY to the current value of PC.
  //       Set PC to the contents of regX.
  void jalr (int regX, int regY);

  // PRE: 0 <= regX < 16.
  // POST: A 32 bit integer is input from the user and the contents of
  // register X are set to this value.
  void in (int regX);

  // PRE: 0 <= regX < 16.
  // POST: OS contains the contents of regX.
  void out (int regX);

  // PRE: regX is defined, 0 <= regX < 16
  //      offset is defined.
  // POST: If PC + offset is a word boundary address, then
  //       set the contents of regX to be PC + offset.
  void la (int regX, long long int offset);

  // PRE: This Machine object is defined.
  // POST: Print the contents of the CPU to shell
  void printCPU ();

  // Pre:  0 <= startAddr < endAddr < mem size
  // Post: The words in that range are sent to user in hex
  void printMemRange (unsigned long long int startAddr, 
		      unsigned long long int endAddr);
  
  // Pre:  n/a
  // Post: A listing of each process and it's current location
  void jobsReport();

  // Pre:  n/a
  // Post: A listing of the page table state for RAM and swap
  void pageTable();

  // PRE: fileName is defined, channel 2 is defined, oio defined
  // POST: If the file fileName exists, then read the machine language
  // in the file, load it into memory and initialise the CPU for
  // executing this program.
  // The error flag is set to true if the file does not exist or if the
  // program does not fit in memory.
  void loadProgram (string fileName, bool oio);

  // Pre:  ReadyQ has a PCB in it
  // Post: The next PCB is loaded into Memory
  void loadPCB();

  // Pre:  The current head of the ready queue has executed it's time
  //       slices and should be switched out
  // Post: The next PCB is loaded in
  void nextProgram();

  // Pre:  The current PCB needs to be saved
  // Post: Saves the register states to the first PCB in readyQ
  void saveRegisters();

  // Pre:  The PCB currently in memory is completed
  // Post: The information for this process is stored and moved to the
  //       completed process queue
  void programComplete();

  // Pre:  The simulator is exiting and the stats for completed
  //       processes should be sent to the terminal
  // Post: The statistics for the processes in the completed queue are
  //       sent to the shell
  void printCompletedStats();

  // PRE: numSteps > 0, pid initialized >= 0
  // POST: numSteps number of instructions are executed, or until halt
  // is executed or an error is encountered.  
  void step (int numSteps, int pid);

  // PRE: 
  // POST: run the program until halt is executed, or until an
  // error is encountered.  
  void run ();

  // Pre:  Called by the machine operator
  // Post: The report on all of the PCB's is given
  void queueReport();

  // PRE: This machine object is defined.
  // POST: RV is the current value of the Error flag
  bool error () { return (Error); };

  // Pre:  processID is defined and a current ID in the readyQ
  // Post: That PID is given ownership of input/output
  void giveIO(int processID);

  // Pre:  deadMan is a PID in the readyQ on call
  // Post: This PID is maimed and dismembered, leaving a sparky mess
  void killPID(int deadMan);

  // Pre:  numSteps >= 0, pid is initialized
  // Post: This pid is rigged to have the appropriate number of steps
  void rigThePID(int numSteps, int pid, bool & grantedIO);

  // Pre:  pid is defined
  // Post: The pid is searched for in the readyQ, if there it's I/O
  //       privaliges are removed
  void takeIO(int pid);

  // Handles getting the memory address given a virtual address
  void page(ulli & address);

  // Pre:  Index initialized
  // Post: index is set if a free page is found, otherwise no change
  void findFreePage(int & index);

  // Pre:  0 <= pid, 0 <= virtualPage
  // Post: PAGE_NOT_FOUND if the page wasn't found, otherwise the
  //       index of the page in the RAM array
  void findPage(ulli pid, int virtualPage, int & index);

  // Will return an index of a free page, if none will return PAGE_NOT_FOUND
  void findFreeSwapPage(int & index);

  // Pre:  0 <= pid, 0 <= virtualPage, index initialized
  // Post: if found, index is changed to an index in Swap
  void findSwapPage(ulli pid, int virtualPage, int & index);

  //Pre:  fileName null-terminated, 0 < pageNumber < maxPages, 0 < pageSize,
  //      numWordsRead is initialized, page is of length pageSize
  //Post: This will read through (pageNumber of pageSize words) and extract
  //      the appropriate page
  void getPage(PCB * curr, int pageNumber, int loadLoc);

  //Pre:  There is a page fault, index is defined, LRU loop is not empty
  //Post: Sets index to the victim page
  void selectVictimPageLRU(int & index);

  // Pre:  index is defined, it represents the index of a victim page
  //       in RAM that needs to be moved to swap space
  // Post: true if the page is successfully moved, otherwise false
  bool moveToSwap(int index);

  // Pre:  index is a page in Swap that should be put in RAM
  // Post: The least recently used RAM program is pushed to swap, true
  //       if this is successful
  bool switchForSwap(int index);
};

#endif
