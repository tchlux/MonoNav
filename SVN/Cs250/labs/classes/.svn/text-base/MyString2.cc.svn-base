#include <iostream>
#include "MyString2.h"

using namespace std;

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

// Output member functions
// PRE: This MyString object is defined and satisfies the CI.
// POST: OS contains a newline followed by the values of currentMax,
//       currentSize and the characters in theString followed by a
//       newline. 
void MyString::debugPrint () const  {
  cout << endl;
  cout << "currentMax = " << currentMax << "; " << endl
       << "currentSize = " << currentSize << "; " << endl
       << "current string = ";
  for (int i = 0; i < currentSize; i++) {
    cout << "(" << i << ", *" << theString[i] << "*) ";
  }
  cout << "(" << currentSize;
  if (theString[currentSize] == '\0') {
    cout << ", *EOS*) (End of String)";
  }
  else {
    cout << ", *NOT EOS*) (Missing terminator)";
  }
  cout << endl;
}

// PRE: This MyString object is defined and satisfies the CI.
// POST: OS contains the characters in this string.
void MyString::print () const {
  cout << theString;
}






