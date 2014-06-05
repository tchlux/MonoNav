#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
#include "stdlib.h"
#include "utilities.h"
#include "Memory.h"
#include "CPU.h"
#include "Machine.h"
#include "constants.h"

using namespace std;

// PRE: size is defined (> 0) as number of words of memory. stack is
//      the size of the stack space for each program.  timeSlice is
//      the length of the timeSlice for each program
//      pageSize is the number of words in one page
//      swapSpace is the size (in pages) of the swap space
//      toSfxn is a function to write to the shell
//      readSfxn is a function to read from the shell,
//      ch1 -> toMachine pipe ch2 -> toShell pipe
// POST: This object is constructed with size bytes of memory.
Machine::Machine (ulli size, int stack, int tS, int pS, int sS,
		  void(*toSfxn)(const char*,int*),
		  void(*readSfxn)(char*,int*,bool&),int *ch1,
		  int *ch2){
  pageSize = pS;
  RamPages = size/pS;
  SwapPages = sS;
  ulli swapSize = (sS * pageSize) * BYTESPERWORD;
  RAM = new PageTableEntry[RamPages]; // Array for RAM, the number of
  //      words divided by the page size
  Swap = new PageTableEntry[SwapPages]; // Swap space number of pages
  max_chars = size*HEXPERWORD; // Max shell output size (this
  //      computation results in 32 characters per mem address
  timeSliceLength = tS;
  MMemory.setSize (size, swapSize);       MMemory.setStackSize(stack);
  Error = false;     MachineHALT = false; sentEndLoop = false;
  Clock = 0;         timeSlice = 0;
  nextFreePID = 0;   nextFreeAddr = 0;
  toShell = toSfxn;  readShell = readSfxn;
  channel1 = ch1;    channel2 = ch2;
}

// PRE: A program has been loaded in memory. PC has an address.
// POST: The word of memory at the address given by PC is fetched
//        and decoded as opcode, X, Y, Z, value.
void Machine::decode () {
  string output; // Holder for decode output
  ulli opcode;
  ulli regX;
  ulli regY;
  ulli regZ;
  long long int value;
  bool abortedTimeSlice = false;
  ulli word; // Word content holder
  bool error;
  ulli currPC = MCPU.getPC(); // Address in memory to access
  MMemory.getWord(currPC, word, error);
  if ((!Error)&&(MMemory.addressOK(currPC + BYTESPERWORD))) {
    timeSlice++;    Clock++; // Increment the Machine clock 
    (ReadyQ[0]->getData())->RunTime++; // Increment the runtime

    MCPU.setPC(currPC + BYTESPERWORD); // Increment the PC
    (ReadyQ[0]->getData())->PC += BYTESPERWORD; // Increment program's pc

    opcode = (word & OPCODEMASK) >> OPCODEPOS;
    regX = (word & XMASK) >> XPOS;   regY = (word & YMASK) >> YPOS;
    regZ = (word & ZMASK);    value = (word & OFFSETMASK);
    long long int offsetValue = value;
    if ((value & OFFSETENDMASK) != 0)
      offsetValue = (value | (~ OFFSETMASK));
    switch (opcode){
    case ADDI:
      addi (regX, regY, offsetValue);
      break;
    case ADD:
      add (regX, regY, regZ);
      break;
    case NAND:
      nand (regX, regY, regZ);
      break;
    case LW:
      lw (regX, regY, offsetValue);
      break;
    case SW:
      sw (regX, regY, offsetValue);
      break;
    case BEQ:
      beq (regX, regY, offsetValue);
      break;
    case JALR:
      jalr (regX, regY);
      break;
    case LA:
      la (regX, offsetValue);
      break;
    case HALT:
      MachineHALT = true;
      programComplete();
      break;
    case IN:
      if ((ReadyQ[0]->getData())->OwnsIO)
	in (regX);	
      else{
	MCPU.setPC(currPC); // Reset the pc back
	(ReadyQ[0]->getData())->PC -= BYTESPERWORD;
	(ReadyQ[0]->getData())->RunTime--; // Reset runtime back
	abortedTimeSlice = true;
      }      
      break;
    case OUT:
      if ((ReadyQ[0]->getData())->OwnsIO)
	out (regX);
      else{
	MCPU.setPC(currPC); // Reset the pc back
	(ReadyQ[0]->getData())->PC -= BYTESPERWORD;
	(ReadyQ[0]->getData())->RunTime--; // Reset runtime back
	abortedTimeSlice = true;
      }
      break;
    default:
      programComplete(); // The program is done running
      output.append("Incorrect opcode.\n");
      Error = true;
      break;
    }
  }
  else {
    programComplete(); // The program is done running
    output.append("PC counter: Bad memory address\n");
    Error = true;
  }
  if ((abortedTimeSlice) || (timeSlice >= timeSliceLength))
    nextProgram();
  toShell(output.c_str(), channel2); // Write output to shell
}

// PRE: 0 <= regX, regY < 16. immediate is defined.
// POST: regX is set to the sum of the contents of regY and
// immediate. 
void Machine::addi (int regX, int regY, long long int immediate) {
  long long int answer = MCPU.getReg(regY) + immediate;
  MCPU.setReg (regX, answer);
}

// PRE: 0 <= regX, regY, regZ < 16.
// POST: regX is set to the sum of the contents of regY and regZ
void Machine::add (int regX, int regY, int regZ) {
  long long int answer = MCPU.getReg(regY) + MCPU.getReg(regZ);
  MCPU.setReg (regX, answer);
}

// PRE: 0 <= regX, regY, regZ < 16.
// POST: regX is set to the nand of the contents of regY and regZ
void Machine::nand (int regX, int regY, int regZ) {
  long long int answer = ~(MCPU.getReg(regY) & MCPU.getReg(regZ));
  MCPU.setReg (regX, answer);
}

// PRE: 0 <= regX, regY < 16. offset is defined.
// POST: regX is set to the contents of the effective address formed
// by adding offset to the contents of regY.
// The machine indicates an error if the effective address is not a
// word address, or is out of bounds.
void Machine::lw (int regX, int regY, long long int offset) {
  long long int effAddr = MCPU.getReg(regY) + offset;
  if (MMemory.addressOK(effAddr)) {
    bool error;
    ulli contents;
    MMemory.getWord (effAddr, contents, error);
    MCPU.setReg (regX, contents);
  }
  else{
    toShell("Load word: Bad address\n", channel2);
    Error = true;
  }
}

// PRE: 0 <= regX, regY < 16. offset is defined.
// POST: The contents of the effective address (formed
// by adding offset to the contents of regY) are set to the contents
// of regX.
// The machine indicates an error if the effective address is not a
// word address, or is out of bounds.
void Machine::sw (int regX, int regY, long long int offset) {
  long long int effAddr = MCPU.getReg(regY) + offset;
  if (MMemory.addressOK(effAddr)) {
    bool error;
    ulli contents = MCPU.getReg(regX);
    MMemory.putWord (effAddr, contents, error);
  }
  else{
    toShell("Store word: Bad address\n", channel2);
    Error = true;
  }
}

// PRE: 0 <= regX, regY < 16. offset is defined.
// POST: If the contents of regX and regY are equal, then PC is to the
// effective address formed by adding offset to the contents of PC.
// The machine indicates an error if the effective address is not a
// word address, or is out of bounds.
void Machine::beq (int regX, int regY, long long int offset) {
  long long int effAddr = MCPU.getPC() + offset;
  if (MMemory.addressOK(effAddr)) {
    bool error;
    ulli contents;
    if (MCPU.getReg(regX) == MCPU.getReg(regY))
      MCPU.setPC(effAddr);
  }
  else{
    toShell("Branch equals: Bad address\n", channel2);
    Error = true;
  }
}

// PRE: 0 <= regX, regY < 16.
// POST: Set the contents of regY to the current value of PC.
//       Set PC to the contents of regX.
void Machine::jalr (int regX, int regY) {
  MCPU.setReg(regY, MCPU.getPC());
  ulli effAddr = MCPU.getReg(regX);
  if (MMemory.addressOK(effAddr)){
    MCPU.setPC(effAddr);}
  else{
    toShell("Jalr: Bad address\n", channel2);
    Error = true;
  }

}

// PRE: 0 <= regX < 16.
// POST: A 32 bit integer is input from the user and the contents of
// register X are set to this value.
void Machine::in (int regX) {
  long long int num;  
  char pidDisp[LINESIZE];
  sprintf(pidDisp, PID_DISPLAY_STR,(ReadyQ[0]->getData())->ProcessID);
  toShell(pidDisp, channel2);
  toShell(PROGRAM_PROMPT, channel2);
  char userInput[LINESIZE];
  bool success = false;
  while (!success){
    readShell(userInput, channel1, success); // Get user input from
    // shell->machine pipe     
  }
  num = atoi(userInput);
  MCPU.setReg (regX, num);
}

// PRE: 0 <= regX < 16.
// POST: OS contains the contents of regX.
void Machine::out (int regX) {
  //  long long int contents = MCPU.getReg(regX);
  string contents;
  char pidDisp[LINESIZE]; // For displayin PID
  char machineOut[max_chars]; // This will hold all machine output

  sprintf(pidDisp, PID_DISPLAY_STR,(ReadyQ[0]->getData())->ProcessID);
  sprintf(machineOut, "%d\n", (int) MCPU.getReg(regX)); // Used to
  // take advantage of the string formatting

  contents.append(pidDisp); // Add the PID information
  contents.append(machineOut); // Add the information to output

  toShell(contents.c_str(), channel2);
}

// PRE: regX is defined, 0 <= regX < 16
//      offset is defined.
// POST: Set the contents of regX to be PC + offset.
void Machine::la (int regX, long long int offset) {
  long long int effAddr = MCPU.getPC() + offset;
  MCPU.setReg(regX, effAddr);
}

// PRE: fileName is defined.
// POST: If the file fileName exists, then read the machine language
// in the file, load it into memory and initialise the CPU for
// executing this program.
// The error flag is set to true if the file does not exist or if the
// program does not fit in memory.
void Machine::loadProgram (string fileName, bool oio) {
  string output; // used to build output string
  ifstream inFile (fileName.c_str());
  if (inFile != NULL) {
    inFile.seekg (NO_OFFSET, inFile.end); // Go to the end of the file
    ulli progSize = inFile.tellg() + MMemory.getStackSize(); // Get
    // line character after each 8 hex
    progSize = (progSize / (HEXPERWORD+1))*WORD_SIZE; // Each line corresponds to one word
    // num bytesand add stack space traversed in order to get to the
    // end of the file 
    PCB * currentPCB = new PCB(nextFreePID, Clock, progSize, oio,
			       fileName.c_str());
    nextFreePID ++;
    ReadyQ.add(currentPCB);
    if (ReadyQ.getSize() == 1){
      loadPCB();
    }
    MachineHALT = false;
    Error = false;
  }
  else {
    toShell("No file\n", channel2);
    Error = true;
  }
  // Optional line to print the information of the file that's loaded
  //  toShell(output.c_str(), channel2);
}

// Pre:  ReadyQ has a PCB in it
// Post: The next PCB is loaded into Memory
void Machine::loadPCB(){
  if (ReadyQ.getSize() > 0){
    PCB * curr = (ReadyQ[0])->getData(); // Get current PCB
    ulli currPC = curr->PC; page(currPC); // Turn that into a physical address
    MCPU.setPC(currPC);
    for (int r=0; r<NUMREGISTERS; r++){
      MCPU.setReg(r, curr->Registers[r]);
    }
  }
}

// Pre:  The current head of the ready queue has executed it's time
//       slices and should be switched out
// Post: The next PCB is loaded in
void Machine::nextProgram(){
  if (ReadyQ.getSize() > 0){
    saveRegisters(); // Save the registers for the current process
    PCB * curr = (ReadyQ[0])->getData(); // Get current pcb
    ReadyQ.remove(0); // Remove this from front of queue
    ReadyQ.add(curr); // Add it back to the end of the queue
    timeSlice = 0; // Reset the timeSlice counter
    loadPCB(); // Load the next progam in the queue
  }
}

// Pre:  The current PCB needs to be saved
// Post: Saves the register states to the first PCB in readyQ
void Machine::saveRegisters(){
  PCB * curr = (ReadyQ[0])->getData(); // Get the current PCB
  for (int r=0; r<NUMREGISTERS; r++){
    curr->Registers[r] = MCPU.getReg(r);
  }  
}

// Pre:  The PCB currently in memory is completed
// Post: The information for this process is stored and moved to the
//       completed process queue
void Machine::programComplete(){
  if (ReadyQ.getSize() > 0){
    PCB * curr = (ReadyQ[0])->getData(); // Get current pcb
    killPID(curr->ProcessID); // Kill this process
    timeSlice = 0; // Reset the timeSlice counter
    if (curr->OwnsIO){
      toShell(END_LOOP, channel2); // This run cycle is complete
      sentEndLoop = true; // There was an end sent
    }
  }
}

// Pre:  The simulator is exiting and the stats for completed
//       processes should be sent to the terminal
// Post: The statistics for the processes in the completed queue are
//       sent to the shell
void Machine::printCompletedStats(){
  int size = ReadyQ.getSize();
  for (int id=0; id<size; id++) // Kill all active processes
    killPID((ReadyQ[0]->getData())->ProcessID);

  toShell(COMPLETED_Q_HEADER,channel2);
  ulli PID, RespT, RunT, WaitT;
  char info[COMPLETED_Q_REPORT_LENGTH];
  while (CompletedQ.getSize() > 0){ // While the Q is not empty
    PCB * curr = (CompletedQ[0])->getData(); // Get current pcb
    sprintf(info, COMPLETED_Q_REPORT_STRING, curr->ProcessID,
	    (curr->EndTime-curr->StartTime), curr->RunTime,
	    ((curr->EndTime-curr->StartTime)-curr->RunTime));
    toShell(info, channel2);
    CompletedQ.remove(0); // Remove this element from the Q
  }
  toShell(COMPLETED_Q_FOOTER,channel2);
}

// Pre:  numSteps >= 0, pid is initialized
// Post: This pid is rigged to have the appropriate number of steps
void Machine::rigThePID(int numSteps, int pid, bool & grantedIO){
  // Try and find the pid
  bool found = false;
  for (int id=0; id<ReadyQ.getSize(); id++){
    if ((ReadyQ[id]->getData())->ProcessID == pid){
      PCB * toRun = ReadyQ[id]->getData();
      ReadyQ.remove(id);
      ReadyQ.addFront(toRun);
      timeSlice = timeSliceLength - numSteps; // Set the
      // appropriate number of timeSlices to run
      if (! toRun->OwnsIO){
	toRun->OwnsIO = true; // Make this process own I/O
	grantedIO = true; // This process was granted I/O
      }
      found = true;
    }
  }
  if (! found){
    Error = true;
    toShell(NO_PID_FOUND, channel2);
  }
}

// Pre:  pid is defined
// Post: The pid is searched for in the readyQ, if there it's I/O
//       privaliges are removed
void Machine::takeIO(int pid){
  for (int id=0; id<ReadyQ.getSize(); id++){
    PCB * pcb= (ReadyQ[id]->getData());
    if (pcb->ProcessID == pid){
      pcb->OwnsIO = false;
    }
  }
}

// PRE: numSteps > 0, PID >= 0
// POST: numSteps number of instructions are executed, or until halt
// is executed or an error is encountered.  
void Machine::step (int numSteps, int pid) {
  sentEndLoop = false; // There has not been an end loop sent
  bool notRigged = true; // This process is not rigged
  bool grantedIO = false; // This pid has been granted io
  for (int i = 0; ((i < numSteps) && !(MachineHALT) && !(Error)); i++) {      
    if (ReadyQ.getSize() > 0){ // If there is a program to run
      if ((pid != 0)&&(notRigged)){
	notRigged = false; // This process has been rigged to run
	rigThePID(numSteps, pid, grantedIO); // Set this PID to run
      }
      decode ();  // Decode
    }
  }
  if (Error)
    Error = false;
  if (MachineHALT)
    MachineHALT = false;
  if (grantedIO)
    takeIO(pid); // take away the I/O privalages of this PID
}

// Pre:  Called by the machine operator
// Post: The report on all of the PCB's is given
void Machine::queueReport(){
  stringstream output;
  for (int q=0; q<ReadyQ.getSize(); q++){
    PCB * pcb = ReadyQ[q]->getData();
    output << *pcb << std::endl;
  }
  for (int q=0; q<CompletedQ.getSize(); q++){
    PCB * pcb = CompletedQ[q]->getData();
    output << *pcb << std::endl;
  }
  output.seekg (0, output.end);  int length = output.tellg();
  if (length > 0){
    toShell(QUEUE_HEADER, channel2);
    output.seekg (0, output.beg);  char * buffer = new char [length+1];
    output.read(buffer,length);
    buffer[length] = '\0';
    toShell(buffer, channel2);  
    toShell(QUEUE_FOOTER, channel2); 
    delete(buffer);
  }
  toShell(END_LOOP, channel2);
}

// Pre:  n/a
// Post: A listing of the page table state for RAM and swap
void Machine::pageTable(){
  stringstream output;
  for (int p=0; p<RamPages; p++){
    output << "Physical Page " << p << ": " << std::endl;
    output << RAM[p] << std::endl;
  }
  for (int p=0; p<SwapPages; p++){
    output << "Swap Page " << p << ": " << std::endl;
    output << Swap[p] << std::endl;
  }

  output.seekg (0, output.end);  int length = output.tellg();
  output.seekg (0, output.beg);  char * buffer = new char [length+1];
  output.read(buffer,length);
  buffer[length] = '\0';
  toShell(buffer, channel2);  toShell(END_LOOP, channel2);
  delete(buffer);
}

// Pre:  0 <= startAddr < endAddr < mem size
// Post: The words in that range are sent to user in hex
void Machine::printMemRange (unsigned long long int startAddr, 
			     unsigned long long int endAddr) {
  string output;
  MMemory.printRange (startAddr, endAddr, output);
  toShell(output.c_str(), channel2);
  toShell(END_LOOP, channel2);
}

// PRE: This Machine object is defined.
// POST: Print the contents of the CPU to shell
void Machine::printCPU () { 
  string output;
  MCPU.printCPU(output);
  toShell(output.c_str(), channel2);
  toShell(END_LOOP, channel2);
}

// Pre:  n/a
// Post: A listing of each process and it's current location
void Machine::jobsReport(){
  string report;
  char onePCB[JOBS_REPORT_LENGTH];   onePCB[0] = '\0';
  toShell(JOBS_HEADER, channel2);
  for (int q=0; q<ReadyQ.getSize(); q++){
    PCB * pcb = ReadyQ[q]->getData();
    sprintf(onePCB, JOBS_REPORT_STRING, pcb->ProcessID,
	    pcb->pageFaults, pcb->Name,
	    pcb->OwnsIO ? PROCESS_RUNNING : PROCESS_WAITING);
    report.append(onePCB);
  }
  if (ReadyQ.getSize() > 0){
    sprintf(onePCB, CURRENT_PROCESS_INFO, 
	    (ReadyQ[0]->getData())->ProcessID );
    report.append(onePCB);    
  }
  toShell(report.c_str(), channel2);
  toShell(JOBS_FOOTER, channel2);
  toShell(END_LOOP, channel2);
}

// Pre:  processID is defined and a current ID in the readyQ
// Post: That PID is given ownership of input/output
void Machine::giveIO(int processID){
  bool found = false;
  if (processID == 0){
    for (int id=0; id<ReadyQ.getSize(); id++){
      if ((ReadyQ[id]->getData())->ProcessID > processID){
	processID = (int) (ReadyQ[id]->getData())->ProcessID;
      }
    }
  }
  for (int id=0; id<ReadyQ.getSize(); id++){
    PCB * pcb= (ReadyQ[id]->getData());
    if (pcb->ProcessID == processID){
      found = true;
      pcb->OwnsIO = true;
    }
  }
  if (!found){
    toShell(NO_PID_FOUND, channel2);
    toShell(END_LOOP, channel2);
  }
}

// Pre:  deadMan is a PID in the readyQ on call
// Post: This PID is maimed and dismembered, leaving a sparky mess
void Machine::killPID(int deadMan){
  bool found = false;
  for (int id=0; id<ReadyQ.getSize(); id++){
    PCB * pcb= (ReadyQ[id]->getData());
    if (pcb->ProcessID == deadMan){
      pcb->EndTime = Clock;
      found = true;
      ReadyQ.remove(id); // Remove the killed element
      CompletedQ.add(pcb); // Add the PCB to the completed queue
      loadPCB(); // Load in the new next element
      //      toShell(KILLED_PID, channel2); 
      // Killed that poor PID, no trace was left behind
    }
  }
  for (int page=0; page<RamPages; page++) // Remove all from RAM
    if (RAM[page].pid() == deadMan)
      RAM[page].free();
  for (int page=0; page<SwapPages; page++) // Remove all from swap
    if (Swap[page].pid() == deadMan)
      Swap[page].free();
  for (int page=0; page<LRU.getSize(); page++){
    if (LRU[page]->getData()->pid() == deadMan)
      LRU.remove(page); // Remove this page from LRU stack
  }
  if (!found)
    toShell(NO_PID_FOUND, channel2);
  //  toShell(END_LOOP, channel2);
}

// Handles getting the memory address given a virtual address
// Pre: address is the virtual address in the currently executing
//       program that needs to be translated to a physical address
void Machine::page(ulli & address){
  PCB * curr = ReadyQ[0]->getData();
  int vPage = (curr->PC) / (BYTESPERWORD * pageSize); // Virtual page number
  int index = PAGE_NOT_FOUND;     // Initialize memory page index
  findPage(curr->ProcessID, vPage, index); // Find the page address
  if (index == PAGE_NOT_FOUND){   // If the page wasn't in memory    
    curr->pageFaults++; // Incremement the number of pfs w/ this
    findSwapPage(curr->ProcessID, vPage, index);
    if (index == PAGE_NOT_FOUND){ // If the page wasn't in swap
      findFreePage(index); // Look for free space in RAM
      if (index == PAGE_NOT_FOUND){ // If there were no free pages
	selectVictimPageLRU(index); // Get the victim
	if ((RAM[index].dirty()) || (LRU.getSize() >= RamPages)){ 
	  // If the victim page is dirty or ram is full
	  bool moved = moveToSwap(index); // Try to move it to swap
	  if (!moved){ // If there was no swap space available
	    killPID(curr->ProcessID); // Kill this PID 
	    Error = true; // There was an error in memory
	  }
	  else
	    RAM[index].free(); // Free this page from ram
	}
	else // Else this page was not dirty
	  RAM[index].free(); // Free this page from ram
	LRU.remove(0); // Remove the least recently used element
      }
      if (!Error){ // If there was no swap space error
	getPage(curr, vPage, index); // Load page into memory, handle if
	// it is stack, how many words are read, occupied and dirty
	// bits, and if it is already in swap space
	RAM[index].set(curr->ProcessID, vPage); // Set associated data
	// that was not available during the get process and mark as
	// occupied 
	PageTableEntry * toAdd = &RAM[index];
	LRU.add(toAdd); // Add this program to the LRU stack
      }
    }
    else{
      switchForSwap(index); // Switch this page into swap
    }
  }
  if (!Error){
    address = index * (pageSize*BYTESPERWORD) + (curr->PC % (pageSize*BYTESPERWORD)); // Translate
    // the virtual page address to a physical page address
    // Find this page in the LRU stack and move it to the back
    for (int page=0; page<LRU.getSize(); page++){
      if (RAM[index] == *(LRU[page]->getData())){
	PageTableEntry * toAdd = LRU[page]->getData();
	LRU.add(toAdd); // Add this to the back
	LRU.remove(page); // Remove it from it's old location
      }
    }
  }
}

// Will return an index of a free page, if none will return PAGE_NOT_FOUND
void Machine::findFreePage(int & index){
  for (int page=0;((index==PAGE_NOT_FOUND)&&(page<RamPages));page++){
    if (!RAM[page].occupied())  // If not occupied
      index = page; // This page is free
  }
}

// Pre:  0 <= pid, 0 <= virtualPage, index initialized
// Post: if found, index is changed to an index in RAM
void Machine::findPage(ulli pid, int virtualPage, int & index){
  for (int page=0;((index==PAGE_NOT_FOUND)&&(page<RamPages));page++)
    if (RAM[page].occupied()     &&    // If occupied
	(RAM[page].pid() == pid) &&    // and same pid
	(RAM[page].vp() == virtualPage)) // and same vp number
      index = page;
}

// Will return an index of a free page, if none will return PAGE_NOT_FOUND
void Machine::findFreeSwapPage(int & index){
  for (int page=0;((index==PAGE_NOT_FOUND)&&(page<RamPages));page++)
    if (!Swap[page].occupied())  // If not occupied
      index = page; // This page is free
}

// Pre:  0 <= pid, 0 <= virtualPage, index initialized
// Post: if found, index is changed to an index in Swap
void Machine::findSwapPage(ulli pid, int virtualPage, int & index){
  for (int page=0;((index==PAGE_NOT_FOUND)&&(page<SwapPages));page++)
    if (Swap[page].occupied()     &&    // If occupied
	(Swap[page].pid() == pid) &&    // and same pid
	(Swap[page].vp() == virtualPage)) // and same vp number
      index = page;
}

//Pre:  curr defined, 0 < pageNumber/loadLoc < maxPages
//Post: This will read through (pageNumber of pageSize words) and extract
//      the appropriate page
void Machine::getPage(PCB * curr, int pageNumber, int loadLoc){
// If the page is outside of the program space, as in it is not in the
//      file then it is a stack space location, that means that the
//      dirty bit needs to be set immediately for this page.  
  if (pageNumber*pageSize*BYTESPERWORD < curr->eA){ // if this page is
    //actually in the file and needs to be read
    ifstream inFile(curr->Name);
    inFile.seekg (pageNumber*pageSize*(HEXPERWORD+1));
    // ^^ Go to the beginning of the first line that needs to be read
    int wordsRead = 0; bool error = false;
    while (!inFile.eof()) {
      char wordStr[9];
      inFile >> wordStr;
      if (!inFile.eof()) {
	int word = hex8StrToInt(wordStr);
	char intStr[20];
	sprintf(intStr, "%d", word);
	MMemory.putWord (loadLoc*pageSize*BYTESPERWORD+wordsRead*BYTESPERWORD,
			 word, error);
	wordsRead ++;
	Error = Error || error; // Set Machine Error
      }
    }
    inFile.close();
    RAM[loadLoc].words(wordsRead); // Set the number of words read
    RAM[loadLoc].dirty(false); // This is not a dirty page (swap)
  }
  else{ // else this is a stack space page requested
    RAM[loadLoc].words(0); // Set the number of words read
    RAM[loadLoc].dirty(true); // This is a dirty page (swap)
  }
}

//Pre:  There is a page fault, index is defined, LRU loop is not empty
//Post: Returns the frame number of the victim page
void Machine::selectVictimPageLRU(int & index){
  index = 0; // Get the element that is the data in the first node
  PageTableEntry * pte = LRU[0]->getData();
  while (!(RAM[index] == *(pte)))  index ++; // Search for the LRU page
};

//if default catch, switch this while for virtual-case, or else delete new-const.

// Pre:  index is defined, it represents the index of a victim page
//       in RAM that needs to be moved to swap space
// Post: true if the page is successfully moved, otherwise false
bool Machine::moveToSwap(int index){
  bool error = false;  // error recorder
  int moveTo = PAGE_NOT_FOUND; // Initialize receiving page index
  findFreeSwapPage(moveTo);
  if (moveTo != PAGE_NOT_FOUND){
    Swap[moveTo] = RAM[index]; // Move the pageTable entry to swap
    ulli word;
    for (int w=0; w<pageSize; w++){ // Copy all words over
      MMemory.getWord(index*pageSize*BYTESPERWORD+w*BYTESPERWORD, 
		      word, error);
      MMemory.putSwapWord(moveTo*pageSize*BYTESPERWORD+w*BYTESPERWORD,
			  word, error);
    }
  }
  return ((moveTo!=PAGE_NOT_FOUND)&&(!error));
}

// Pre:  index is a page in Swap that should be put in RAM
// Post: The least recently used RAM program is pushed to swap
bool Machine::switchForSwap(int index){
  bool error = false;
  PageTableEntry temp = Swap[index];  int swapLocation = index;
  selectVictimPageLRU(index);
  Swap[swapLocation] = RAM[index];
  RAM[index] = temp; // Now all of the surface data has been moved
  ulli word;
  for (int w=0; w<pageSize; w++){ // Copy all words over
    MMemory.getSwapWord(swapLocation*pageSize*BYTESPERWORD+w*BYTESPERWORD, 
			word, error);
    MMemory.putWord(index*pageSize*BYTESPERWORD+w*BYTESPERWORD,
		    word, error);
  }
  return(!error);
}
