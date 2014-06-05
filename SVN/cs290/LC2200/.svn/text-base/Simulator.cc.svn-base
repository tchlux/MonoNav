#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <wait.h>
#include "assert.h"
#include <fcntl.h>     // To use the defined constant O_NONBLOCK

#include "Machine.h"
#include "Choice.h"
#include "constants.h"

using namespace std;

// Pre:  str is properly terminated
// Post: true iff chars 0-9 are used in this string or len
bool isAllDigits (const char str[]) {
  bool answer = true;
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    answer = answer && ((str[0] >= '0') && (str[0] <= '9'));
  }
  return (answer);
}

// Pre:  Info is terminated properly
// Post: Information is sent to the pipe for machine to output
void toPipe(const char * info, int * channel){
  write(channel[1], info, strlen(info)+1);
}

// Pre:  user is defined and of length MAX_STRING, channel is the pipe
//       for communication from machine to machine
// Post: 
void readPipe(char * holder, int * channel){
  char ch = ' '; // Default to empty
  int i; // Index in machineResponse
  for (i=0; ch!='\0'; i++){
    if (i < SHELL_PROMPT_MAX){
      read (channel[0], &ch, 1);  // try to read one character
      // from the pipe.
      holder[i] = ch; // Store character
    }
  }
  holder[i] = '\0'; // Terminate char array
}

// Pre:  holder is defined and of suitable length, channel is pipe id,
//       success will state whether or not information was read
// Post: This pipe is actively read
void readPipeNB( char * holder, int * channel, bool & success){
  int i = 0;  char ch;
  int numRead;    // to hold the return value from reading pipe
  success = true; // Default the success of reading
  do {
    numRead = read (channel[0], &ch, 1);  // try to read one character
                                          // from the pipe.
    if (numRead == -1) {
      success = false; // Nothing was read from pipe
    }
    else { // something was read on the pipe.
      holder[i] = ch;
      i++;
    }
  }
  while ((ch != '\0') && (success));
  // End of message.
  holder[i] = '\0';  // Terminate the string in line.
}

// Pre:  The channels have been initialized, numWords > 0,
//       shellToMachinePipe, machineToShellPipe, open and ready
// Post: The shell communicates with the user for the machine
void runShell(int numWords, int * shellToMachinePipe, 
	      int * machineToShellPipe){
  bool done = false;      // Programe operations complete
  char userInput[LINESIZE]; // Holds user input
  char shellPrompt[SHELL_PROMPT_MAX]; // Holds machine output                                         
  shellPrompt[0] = '\0';
  while (!done) {
    shellPrompt[0] = '\0'; // Reset machine output buffer
    cout << USER_PROMPT_SYMBOL;
    cin.getline(userInput, LINESIZE); // Get user input      
    toPipe(userInput, shellToMachinePipe); //Send the user input to machine
    if (!strcmp(userInput, END_PROGRAM)){ // Check if user ends
      done = true;
      while(strcmp(shellPrompt, COMPLETED_Q_FOOTER)){
	readPipe(shellPrompt, machineToShellPipe);
	cout << shellPrompt;
      }
    }
    else{ // Non-end command
      while (strcmp(shellPrompt, END_LOOP)){ // while ! end loop
	if (!strcmp(shellPrompt, PROGRAM_PROMPT)){ // if machine in
	  shellPrompt[0] = '\0'; // Reset machine output buffer
	  cin.getline(userInput, LINESIZE); // Get user input
	  toPipe(userInput, shellToMachinePipe); //Send the user input to machine
	}      
	else{
	  readPipe(shellPrompt, machineToShellPipe); // Wait for machine response
	  if (strcmp(shellPrompt, END_LOOP)){ // If ! end loop
	    cout << shellPrompt; // Print it to user
	  }
	}
      }
    }
  }
}


// PRE: Machine M is initialized, numWords > 0
//      shellToMachinePipe -> toMachine ::: machineToShellPipe -> toPipe
// POST: Run user commands on the machine M.
void runMachine (int numWords, int stackSize, int timeSlice,
		 int pageSize, int swapSpace, 
		 int *shellToMachinePipe, int *machineToShellPipe){
  bool done = false;      // Program operations complete bool
  Machine M(numWords, stackSize, timeSlice, pageSize, swapSpace, 
	    toPipe, readPipeNB, shellToMachinePipe, 
	    machineToShellPipe); // Machine:
  // understands instructions load, step, run, mem, cpu, quit
  Choice userChoice; // This will interpret user responses
  char userInput[LINESIZE]; // Holder for user input from shell
  bool successfulRead = false;
  bool suspend = false; // If the machine is in suspend mode
  while (!done) { 
    readPipeNB(userInput, shellToMachinePipe, successfulRead); // Get  user
    //      input from shell->machine pipe 
    if (successfulRead){      
      bool sendEndFlag = false;
      userChoice.getUserChoice(userInput); // Parse user input
      // ASSERT: userChoice contains the choice object entered by the
      // user.
      int choiceNum = userChoice.getChoiceNum();
      switch (choiceNum) {
      case C_QUIT:   // User entered the quit command
	done = true;
	M.printCompletedStats();
	break;
      case C_LOAD_RUN: // User attempting to run a program in foreground
	toPipe(C_LOAD_RUN_STRING, machineToShellPipe);
	M.loadProgram (userChoice.getFileName(), !suspend);
	// This will force programs to the bg if in suspend mode ^^
	if (M.error())
	  toPipe(ERROR_IN_PROGRAM, machineToShellPipe);
	if (suspend)
	  sendEndFlag = true; // The machine no longer needs i/o
	break;
      case C_RUN_BG: // User ran program with "&" in background
	toPipe(C_RUN_BG_STRING, machineToShellPipe);
	M.loadProgram (userChoice.getFileName(), false);
	if (M.error())
	  toPipe(ERROR_IN_PROGRAM, machineToShellPipe);
	sendEndFlag = true; // The machine is done with I/o
	break;
      case C_FG:
	M.giveIO(userChoice.getToFG());
	break;
      case C_STEP: // Step 'n' lines through specified process
	M.step (userChoice.getStepNo (), userChoice.getToStep()); 
	if (M.error ())
	  toPipe(ERROR_IN_PROGRAM, machineToShellPipe);
	if (! M.returnedIO() )
	  sendEndFlag = true;
	break;
      case C_SUSPEND:
	suspend = true; // The machine is put in suspend mode
	sendEndFlag = true;
	break;
      case C_RESTART:
	suspend = false; // The machine is taken out of suspend mode
	sendEndFlag = true;
	break;
      case C_KILL: // User request to kill a PID
	M.killPID(userChoice.getHit());
	sendEndFlag = true; // Tell the shell machine is done
	break;
      case C_JOBS: // User request jobs listing
	M.jobsReport();
	break;
      case C_QUEUE: // User request queue listing
	M.queueReport();
	break;
      case C_CPU: // User typed cpu command
	M.printCPU (); // Print cpu information
	break;
      case C_MEM: // User typed mem command
	M.printMemRange (userChoice.getFromAddr(), // Get start point
			 userChoice.getToAddr()); // Get end point
	break;
      case C_INVALID: // If it was an invalid file
	toPipe(INVALID_FILE, machineToShellPipe);
	sendEndFlag = true; // The machine is done with I/O for now
	break;
      case C_BAD_COM: // If the command was invalid
	toPipe(INVALID_COMMAND, machineToShellPipe);
	sendEndFlag = true; // The machine is done with I/O for now
	break;
      case C_PAGETABLE:
	M.pageTable();
	break;
     }
      if (sendEndFlag) toPipe(END_LOOP, machineToShellPipe);
    }
    else{
      if (! suspend)
	M.step(1, 0); // If there was nothing to be read, resume machine FDE
    }
  }
}

// Pre:  numWords, stack, timeSlice, memError are all initialized
// Post: if CONFIG_FILE exists then the information on number of
//       bytes, stack size, and time slice length are loaded from it
void configure(int & numWords, int & stack, int & timeSlice,
	       int & pageSize, int & swapSpace, bool & memError){
  ifstream configureFile(CONFIG_FILE);
  if (configureFile.is_open()){    
    string variable;    int value;
    for (int arg=0; arg<ARGS_IN_CONFIG; arg++){
      variable.clear();
      configureFile >> variable;
      configureFile >> value;
      if (!variable.compare(NUM_WORDS_STRING))
	numWords = value;	
      else if (!variable.compare(STACK_SPACE_STRING))
	stack = value;	
      else if (!variable.compare(TIMESLICE_STRING))
	timeSlice = value;	
      else if (!variable.compare(PAGESIZE_STRING))
	pageSize = value;
      else if (!variable.compare(SWAPSPACE_STRING))
	swapSpace = value;
    }
    if (numWords > MAX_MEM_SIZE) {
      cout << "Memory size too big." << endl;
      memError = true;
    }
    else if (numWords % 4 != 0) {
      cout << "Memory size must be a multiple of 4. " << endl;
      memError = true;
    }
    else if (numWords % pageSize != 0){
      cout << "Memory must be divisible by page size." << endl;
      memError = true;
    }
  }
  else
    std::cerr << "Error opening configure file: <" 
	      << CONFIG_FILE << ">" << std::endl;
}

// Pre:  argc == 1
// Post: A pretty sweet simulator is run
int main(int argc, char * argv[]) {
  int shellToMachinePipe[PIPE_COMS]; // Channel for toMachine
  int machineToShellPipe[PIPE_COMS]; // Channel for to Shell
  int numWords, stackSize, timeSlice, pageSize, swapSpace;
  bool memError = false;
  if (argc > 1) {cerr<<"Command line args not expected."<<endl;};
  configure(numWords, stackSize, timeSlice, pageSize, swapSpace, memError);
  if (!memError) {
    int perror1;     // Pipe for shell to machine
    int perror2;     // Pipe for machine to shell
    perror1 = pipe2(shellToMachinePipe, O_NONBLOCK); // Init pipes
    perror2 = pipe(machineToShellPipe);
    cout << "memory      " << numWords << " words" << endl;
    cout << "stack       " << stackSize << " words" << endl;
    cout << "time slice  " << timeSlice << " instructions" << endl;
    cout << "page size   " << pageSize << " words" << endl;
    cout << "swap size   " << swapSpace << " pages" << endl;
    if ((perror1 == ERROR_IN_PIPE)||(perror2 == ERROR_IN_PIPE)){
      std::cout << "Error creating comm pipes" << std::endl;
    }
    else{ // Pipes successfully opened
      int retPID = fork(); // get fork process ID
      if (retPID == CHILD_PROCESS){ // This is the child process
	runMachine(numWords, stackSize, timeSlice, pageSize,
		   swapSpace, shellToMachinePipe, machineToShellPipe);
	close (shellToMachinePipe[0]); // Close the read end of shell->machine
	close (machineToShellPipe[1]); // Close write end of machine->shell
      }
      else{
    	runShell(numWords, shellToMachinePipe, machineToShellPipe);
	wait(NULL);          // wait for the machine process to end.
	close (shellToMachinePipe[1]); // Close write end of shell->machine
	close (machineToShellPipe[0]); // Close read end of machine->shell
      }
    }
  }
  return (0);
}

// struct TAG{
//   int variable;
// };
// typedef struct TAG;
