#ifndef INCLUDED_ASSEMBLE
#define INCLUDED_ASSEMBLE

#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "strops.h"

#define DEFAULT_TYPE '~' // A non-type default value for opCodes

class label{
  // CI holds three data values, name, line, defined
public:
  char * name;  // The actual name of the label
  int line;     // The line it is found on
  bool defined; // Whether or not the label has been found

  //Post: all data initialized
  label(){
    name = NULL;
    line = 0;
    defined = false;
  };

  // Pre:  other is defined
  // Post: all of other's qualities are shallow copied over to this
  label(const label & other){
    name = other.name;
    line = other.line;
    defined = other.defined;
  }

  //Post: if defined, name is deleted
  void del(){
    if (defined){
      delete(name);
    }
  };
};

class opCode{
  // CI Holds three data values, name, type, and binary
public:
  char * name;   // Holder for the opCode name
  char type;     // The type of the opCode
  char * binary; // The binary form of the opCode as a char*
  //Post: all data initialized
  opCode(){
    type = DEFAULT_TYPE;
    name = NULL;
    binary = NULL;
  };

  // Pre:  other is defined
  // Post: all of other's qualities are shallow copied over to this
  opCode(const opCode & other){
    name = other.name;
    type = other.type;
    binary = other.binary;
  }

  // Pre:  n is defined and initialized
  // Post: true if n.name is equal to name (streq == strings equal)
  bool operator==(const opCode & n){return (streq(n.name, name));};

  //Post: if defined, name and binary are deleted
  void del(){
    if (type != DEFAULT_TYPE){
      delete(name);
      delete(binary);
    }
  };
};

// Pre:  opCodes is a list of all opCodes and their types as to check
//       for syntax.  labels is an empty list ready to store labels,
//       their line numbers, and whether or not they have a line
//       number. asmName is the name of the assembly file to be read
// Post: The dotASM file is checked for syntactical errors, a return
//       status as an integer for main if errors are found in argument
//       structure.
int firstPass(ifstream dotASM, LinkedList<opCode> & opCodes,
	      LinkedList<label> & labels);

// Pre:  opCodes is a list of all opCodes and their types as to
//       translate to machine code.  labels is populated with all
//       labels and their associated line numbers.  dotASM is the
//       assembly file that is being translated
// Post: a .obj file is made 
int secondPass(ifstream & dotASM, LinkedList<opCode> & opCodes,
	       LinkedList<label> & labels); 

// Pre:  opCodes is initialized, opCodes file is valid
// Post: The opCodes list is initialized 
void getOpCodes(LinkedList<opCode> & opCodes);

// Pre:  argc == 2, argv[1] == filename of .asm assembly file
// Post: A number corresponding to the appropriate run status, the
//       filename given as an .obj will contain the hexadecimal output
//       of the assembly code translation
int main(int argc, char * argv[]);
// ERROR if argc != 2
// ifstream(argv[1]);
// ERROR if file not open (doesn't exist)

// Initialize op codes list (argv[1])
// Initialize labels list

// Call first pass function (op codes list, labels list)
// ASSERT labels list populated

// Check for labels without definitions

// 2nd pass function (op codes list, labels list)

// return(status);

#endif
