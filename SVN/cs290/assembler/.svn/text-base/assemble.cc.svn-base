#include <iostream>
#include <fstream>
#include "assemble.h"
#include "strops.h"
#include "syntaxCheck.h"
#include "LinkedList.h"

#define OPCODES_FILE "opcodes.txt" //The file with the opCodes in it
#define REGISTERS_FILE "registers.txt" // File with registers listed
#define MAX_LINE 70 //Length of longest line allowed in files
#define OPCODE_LINE_ARGS 3 // Number of space separated arguments on a
                           // line of the opCode file
#define OPCODE_NAME 0 // Index location of name argument
#define OP_TYPE 1 // Index location of type argument
#define OP_TYPE_IND 0 // Index location of type character in arg
#define OPCODE_BINARY 2 // Index location of the binary representation
#define SPLIT_CHARACTER ' ' // Split character used for files
#define LABEL_COLON ':' // Character signifying label

#define NORMAL_EXECUTION 0 // current runtime status is good
#define USAGE_ERROR 1 // incrorect number of arguments
#define FILE_ERROR 2  // .asm file did not open properly
#define INVALID_OPCODE 3 // invalid opcode found
#define WRONG_NUM_ARGS 4 // wrong number args for op code
#define INVALID_REGISTER 5 // invalid register name

using namespace std;

// Pre:  all elements of asmData must be terminated
//       lineSize >= 0, cLine >= 0
//       labels and opCodes are defined
//       status >= 0
// Post: The status of the line is returned (valid or invalid syntax)
int checkLine(char ** asmData, int lineSize, int cLine, 
	      LinkedList<label> & labels, 
	      LinkedList<opCode> & opCodes, int & status){
  label newLabel;  // Holder for any labels that are found
  int arg = 0; // Reset current argument to first element
  if (asmData[arg][alen(asmData[arg])-1] == LABEL_COLON){
    // If the last character of the first element is a colon
    newLabel.name = asmData[arg]; // Get the label name
    newLabel.line = cLine; // Get the line of the label
    newLabel.defined = true; // since line is known, defined=true
    labels.addBack(newLabel); // add label to list
    arg ++; // Increment arg since there was a label
  }
  opCode temp; //Temporary opCode checker
  temp.name = asmData[arg]; // Set the name of the opCode
  if (opCodes.has(temp)){ //If opCode is valid
    arg ++; // Move to next argument    
    temp.type = (opCodes.find(temp))->getData().type;
  }
  else{
    status = INVALID_OPCODE; //Invalid opCode found
  }
  return (status);
}

// Pre:  opCodes is a list of all opCodes and their types as to check
//       for syntax.  labels is an empty list ready to store labels,
//       their line numbers, and whether or not they have a line
//       number.  asmName is the name of the assembly file to be read
// Post: The dotASM file is checked for syntactical errors, a return
//       status as an integer for main if errors are found in argument
//       structure.
int firstPass(char * asmName, LinkedList<opCode> & opCodes,
	      LinkedList<label> & labels){
  ifstream dotASM(asmName); //Open the assembly file
  int status = NORMAL_EXECUTION; // Normal execution
  int currLine = 0; // Current line in file
  char line[MAX_LINE];  // Holder for the current line from file
  int lineSize; // Holder for length of split array (char**)
  char ** asmData; // Holder for the return of strops.split()    
  while (! dotASM.eof()){
    dotASM.getline(line, MAX_LINE); // Get the next line from file
    asmData = split(line, SPLIT_CHARACTER, lineSize); //Split line
    checkLine(asmData, lineSize, currLine, labels, opCodes, status);
    if (status == INVALID_OPCODE){
      std::cout << "ERROR opCode: line " << currLine << std::endl;
    }
    else if (status == WRONG_NUM_ARGS){
      std::cout << "ERROR opCode args: line " << currLine
		<< std::endl;
    }
    else if (status == INVALID_REGISTER){
      std::cout << "ERROR invalid register: line " << currLine 
		<< std::endl;
    }
    currLine ++; // Add one to line
  } // end while
  return(status);
} //end function

// Pre:  opCodes is a list of all opCodes and their types as to
//       translate to machine code.  labels is populated with all
//       labels and their associated line numbers.  dotASM is the
//       assembly file that is being translated
// Post: a .obj file is made 
int secondPass(ifstream & dotASM, LinkedList<opCode> & opCodes,
	       LinkedList<label> & labels){
  
}

// Pre:  opCodes is initialized, opCodes file is valid
// Post: The opCodes list is initialized 
void getOpCodes(LinkedList<opCode> & opCodes){
  ifstream inFile(OPCODES_FILE); // Open the opCodes file
  if (! inFile.is_open()){
    std::cout << "ERROR INTERNAL: opcode file does not exist" 
	      << std::endl;
  }
  else{
    char line[MAX_LINE];  // Holder for the current line from file
    int lineSize; // Holder for length of split array (char**)
    char ** opData; // Holder for the return of strops.split()
    opCode newCode; // new opCode to be added (will be reused)
    while (! inFile.eof()){ // While the file isn't finished
      inFile.getline(line, MAX_LINE); // Get the next line from file
      opData = split(line, SPLIT_CHARACTER, lineSize); //Split line
      if (lineSize == OPCODE_LINE_ARGS){ // if proper # of arguments
	newCode.name = opData[OPCODE_NAME]; // Get name
	newCode.type = opData[OP_TYPE][OP_TYPE_IND]; // Get type
	newCode.binary = opData[OPCODE_BINARY]; // Get the binary
                                                // representation 
	opCodes.addBack(newCode); // Add new code to opCodes
      }
      else{ // Improper number of arguments
	std::cout << "Found an incorrect opCode, suggest checking opCodes file"
		  << std::endl;
      }
    }
  }
}

// Pre:  argc == 2, argv[1] == filename of .asm assembly file
// Post: A number corresponding to the appropriate run status, the
//       filename given as an .obj will contain the hexadecimal output
//       of the assembly code translation
int main(int argc, char * argv[]){
  int status = 0; // Normal execution, no error
  if (argc != 2){
    std::cout << "ERROR USAGE: ./assemble file.asm" << std::endl;
    status = USAGE_ERROR; // Usage error, no filename or too many args
  }
  ifstream dotASM(argv[1]);
  if (! dotASM.is_open()){
    std::cout << "ERROR FIE: could not open file " << argv[1] 
	      << std::endl;
    status = FILE_ERROR; // File error, could not open given filename
  }
  LinkedList<opCode> opCodes; // Initialize opCodes list
  LinkedList<label> labels;   // Initialize labels list
  getOpCodes(opCodes);	      // Fill opCodes list

  if (status == NORMAL_EXECUTION){
    status = firstPass(argv[1], opCodes, labels);
    if (status == NORMAL_EXECUTION){
      status = secondPass(dotASM, opCodes, labels);    
    }
  }

  dotASM.close(); // Close the asm file
  return (status);
}
