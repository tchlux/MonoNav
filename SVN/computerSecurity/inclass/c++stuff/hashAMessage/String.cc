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

//Pre:  array of size >= (currentSize+1)
//Post: The given array is filled with the values from theString
void String::retExactArray(char array[]) const{
  for (int i=0; i<currentSize; i++){
    array[i] = theString[i];
  }
}

//Pre:  
//Post: A new array of exact size is built in heap space and returned
char * String::retExactArray() const{
  char * returnArray = new char[currentSize+1];
  for (int i=0; i<currentSize; i++){
    returnArray[i] = theString[i];
  }
  return (returnArray);
}

//Pre:  A character is given
//Post: The number of occurances of that character is counted in
//      theString
int String::count(char ch) const{
  int count = 0; //init count
  for (int i=0; i < currentSize; i++){ //cycle string
    if (theString[i] == ch){ //if ch found
      count ++; //add to count
    }
  }
  return (count); //the # occurances
}

//Pre:  
//Post: The current length of the string is returned as an integer
int String::length() const{
  return (currentSize);
}

// Pre:  Integer of index in array is given, the index must be les
//       than current size or else an empty character is returned
// Post: The character at that index is returned
char String::index(int index) const{
  char returnCharacter;
  if (index > currentSize){
    returnCharacter = '\0';
  }
  else{
    returnCharacter = theString[index];
  }
  return(returnCharacter);
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
  cout << theString << endl;
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
    //       and add one ( - terminator node)
    delete tempString; //Delete old useless array
  }
  theString[currentSize] = ch; //Add new character
  currentSize ++; //increment currenSize
  theString[currentSize] = '\0'; //Add terminator
}

// Pre:  
// Post: All values are reset back to initial settings
void String::reset(){
  delete (theString);
  currentMax = 0;
  theString = new char[currentMax + 1];
  theString[0] = '\0';
  currentSize = 0;
}

//Pre:  theString exists as a pointer to an array in heap space
//Post: The heap space is freed
String::~String(){
  delete (theString);
}
