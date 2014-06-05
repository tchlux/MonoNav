#ifndef INCLUDED_Choice
#define INCLUDED_Choice

#include <string>
#include <sstream>

using namespace std;

// Class Invariant: An object of this type holds the choice made by
// the user. It contains the choice number corresponding to the table
// below. For certain choices, it may contain other parameters too
// explained below.
// 
//   1) load one machine language program
//   2) run the program
//   3) step through the program
//   4) print the contents of the cpu
//   5) print the contents of memory.
//   6) quit the program.
// For 1, the second parameter is a string corresponding to the file
//   name.
// For 3, the second parameter is the number of steps to run. Default
//   value = 1.
// For 5, the second and third parameters are the "from" and "to"
//   addresses of memory locations. Each address is between 0 and
//   1022, both inclusive, and the "from" address <= "to" address.
// 


class Choice {

 private:
  int choiceNum;    // choice made by user as above.
  string fileName;  // name of machine code file for M
  int stepNo;       // number of steps to run
  int fromAddr;     // "from" address to dump memory
  int toAddr;       // "to" address to dump memory
  int toFG;         // The PID that should be given ownership of i/o
  int toKill;       // The PID that should be viciously murdered
  int toStep;       // The PID  that will be given n steps

  // PRE: buffer has all the tokens from the command line input by the
  //       user. 
  // POST: This Choice object is populated by the tokens of the command
  //       line
  void parseBuffer (stringstream & buffer);

 public:
  // Default constructor.
  // This object is an intial choice object with stepNo = 1, the only
  // default value.
  Choice() {
    stepNo = 1;
  };

  // Returns the current pid for stepping
  int getToStep() const { return(toStep); };

  // Returns the current target for death
  int getHit() const { return (toKill); };

  // PRE: This object is defined. userChoice contains user input
  // POST: This object is populated with the user's choice.
  void getUserChoice (const char * userChoice);

  // PRE: This object is defined with the user's choice.
  // POST: RV = the choice number for this choice object.
  int getChoiceNum () { return choiceNum; };

  // PRE: This object is defined with the user's choice.
  // POST: RV = the name of the file containing the M machine language
  //       program. 
  string getFileName () { return fileName; };

  // PRE: This object is defined with the user's choice.
  // POST: RV = the number of steps to run for this choice object.
  int getStepNo () { return stepNo; };

  // PRE: This object is defined with the user's choice.
  // POST: RV = the "from" address to dump memory
  int getFromAddr () { return fromAddr; };

  // PRE: This object is defined with the user's choice.
  // POST: RV = the "to" address to dump memory
  int getToAddr () { return toAddr; };

  // Pre:  The FG command has been used
  // Post: The number provided by the user is returned
  int getToFG(){ return (toFG); };

  // PRE: stream is a defined output stream; C is a defined CHoice object.
  // POST: stream contains the member data objects of C.
  friend ostream & operator << (ostream & stream, Choice & C);
};

#endif
