#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Choice.h"
#include "constants.h"
#include "stdlib.h"

using namespace std;

// PRE: This object is defined. IS contains the user's choice.
// POST: This object is populated with the user's choice.
void Choice::getUserChoice (const char * userChoice) {

  stringstream buffer;  // Buffer to hold the tokens of the input
			// string from user.

  string str;
  for (int chr=0; userChoice[chr]!='\0'; chr++)
    str.push_back(userChoice[chr]);
  // str is the entire command line.

  buffer << str;
  // buffer has the tokens from the command line.

  parseBuffer (buffer);

}

// PRE: buffer has all the tokens from the command line input by the
//       user. 
// POST: This Choice object is populated by the tokens of the command
//       line
void Choice::parseBuffer (stringstream & buffer){

  string command; // holds the command.
  buffer >> command;

  if (command == "step") {
    choiceNum = C_STEP;
    buffer >> stepNo;
    toStep = 0; // Default the PID to 0
    command.clear();
    buffer >> command;
    if (command.length() > 0)
      toStep = atoi(command.c_str());
  }
  else if (command == CPU_STATE) 
    choiceNum = C_CPU;
  else if (command == MEM_RANGE) {
    choiceNum = C_MEM;
    buffer >> fromAddr;
    buffer >> toAddr;
  }
  else if (command == END_PROGRAM)
    choiceNum = C_QUIT;
  else if (command == SHOW_QUEUE)
    choiceNum = C_QUEUE;
  else if (command == SUSPEND)
    choiceNum = C_SUSPEND;
  else if (command == RESTART)
    choiceNum = C_RESTART;
  else if (command == PAGE_TABLE)
    choiceNum = C_PAGETABLE;
  else if (command == KILL_PID){
    choiceNum = C_KILL;
    command.clear(); // Clear out the kill statment
    buffer >> command;
    toKill = atoi(command.c_str());
  }

  else if (command == "fg"){
    command.clear();
    buffer >> command;
    choiceNum = C_FG;
    if (command.length() == 0)
      toFG = 0;
    else
      toFG = atoi(command.c_str());
  }
  else if (command == "jobs")
    choiceNum = C_JOBS;
  else {
    ifstream theFile(command.c_str());
    if (theFile){
      fileName.clear();
      fileName.append(command); // Save the filename 
      command.clear(); // Clear the old command
      buffer >> command; // Get the next argument
      if (command.length() == 0){ // If nothing else was specified
	choiceNum = C_LOAD_RUN; // Let the machine know it is ready	
      }
      else if (!command.compare(BACKGROUND_COMMAND)){
	command.clear(); // Clear out that command
	buffer >> command; // Get the next argument if there are any
	if (command.size() == 0)
	  choiceNum = C_RUN_BG;
	else
	  choiceNum = C_BAD_COM;
      }
      else
	choiceNum = C_BAD_COM;
    }
    else
      choiceNum = C_INVALID;      
  }
}  

// // PRE: stream is a defined output stream; C is a defined CHoice object.
// // POST: stream contains the member data objects of C.
// ostream & operator << (ostream & stream, Choice & C) {
//   stream << "Choice Num = " << C.choiceNum << endl;
//   stream << " fileName = " << C.fileName << endl;
//   stream << " step count = " << C.stepNo << endl;
//   stream << " from and to addresses: "  
// 	 << C.fromAddr << ", " << C.toAddr << endl; 
//   return (stream);
// }
