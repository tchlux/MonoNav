#include "MyString1.h"

// Default constructor
// PRE:
// POST: currentMax = 0. currentSize = 0. There is one space
//         allocated for the object. theString[0] = '\0'. 
//         CI is satisfied.
MyString::MyString () {
  currentMax = 0;
  theString = new char[currentMax + 1];
  theString[0] = '\0';
  currentSize = 0;
}




