#include <iostream>
#include "String.h"

using namespace std;

// Default constructor
// PRE:
// POST: currentMax = 0. currentSize = 0. There is one space
//         allocated for the object. theString[0] = '\0'. 
//         CI is satisfied.
String::String () {
  currentMax = 0;
  theString = new char[currentMax + 1];
  theString[0] = '\0';
  currentSize = 0;
}

// Constructor given a string
//Pre:  Pointer to string is given
//Post: The given string is stored
String::String(char * str) {
  currentMax = 0;
  theString = new char[currentMax+1];
  theString[0] = '\0';
  currentSize = 0;
  while (str[currentSize] != '\0'){
    add(str[currentSize]);
  }
}

//Pre:  Another instance of Mystring is given along with a starting
//      index in the current string for comparison
//Post: true if substrings match for each character preceeding a
//      terminator node, false if there is a non-matching
//      character before either terminator node
bool String::subString(String aString, int index) const{
  int aIndex = 0; //index access for aString.theString
  while ((aString.theString[aIndex] != '\0') //While neither
	 &&(theString[index] != '\0')){ //string has terminated
    if (aString.theString[aIndex] != theString[index]){ //If the
      //      characters do not match each other
      return (false); //not a substring
    }
    index ++;
    aIndex ++;
  }
  return true; //Every character in the substring matched
}

//Pre:  
//Post: The current length of the string is returned as an integer
int String::length() const{
  return (currentSize);
}

// Output member functions
// PRE: This String object is defined and satisfies the CI.
// POST: OS contains a newline followed by the values of currentMax,
//       currentSize and the characters in theString followed by a
//       newline. 
void String::debugPrint () const  {
  cout << endl;
  cout << "currentMax = " << currentMax << "; "
       << "currentSize = " << currentSize << "; "
       << "current string = ";
  for (int i = 0; i < currentSize; i++) {
    cout << "(" << i << ", *" << theString[i] << "*) ";
  }
  cout << "(" << currentSize;
  if (theString[currentSize] == '\0') {
    cout << ", *EOS*)";
  }
  else {
    cout << ", *NOT EOS*)";
  }
  cout << endl;
}

// PRE: This String object is defined and satisfies the CI.
// POST: OS contains the characters in this string.
void String::print () const {
  cout << theString;
}

// PRE: This String object is defined with values 
//       currentMax = M, currentSize = S, and satisfies the CI.
// POST: ch is defined. 
//       theString[0]..theString[S-1] are the same as before.
//       theString[S] = ch
//       theString[S+1] = '\0'
//       The result object satisfies the CI.
void String::add (char ch) {
  if ((currentMax - currentSize) <= 0){ //if the current array is full
    //       ( '<= 0' is used simply for safety but unnecessary)
    char * tempString = theString; //create a temp pointer to the old
    //       string
    theString = new char[(currentMax+1)*2]; //create a new arry twice as
    //       large for theString
    for (int i=0; i<currentSize; i++){ //Cycle through old string
      theString[i] = tempString[i]; //transfer values to new array
    }
    currentMax = (currentMax*2)+1; //Double the size of current max
    delete tempString; //Delete old useless array
  }
  theString[currentSize] = ch; //Add new character
  currentSize ++; //increment currenSize
  theString[currentSize] = '\0'; //Add terminator




  // Check if there is space for another character.
  // If not, then 
  //   create a temporary char pointer, say tempString, and assign it
  //     the value of theString. 
  //   get twice as much as the current space allocated 
  //     (2 * (currentMax + 1)) and store the returned address/pointer
  //     in theString.
  //   Copy the first currentSize characters from tempString to
  //     theString. 
  //   Update currentMax
  //   delete tempString
  // Now, either there was already space for the new character, or
  //   space was created.
  // Assign the character to theString[currentSize]
  // Update currentSize
  // Assign '\0' to theString[currentSize].
  // Verify that all the conditions of the CI must be satisfied at
  //   this point.
}
  





