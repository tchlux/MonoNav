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

//Pre:  aString is defined and follows CI
//Post: Deep copy of aString created
String::String(String & aString){
  currentMax = aString.currentMax; //get value for current max
  delete (theString); //delete old saved array
  theString = new char[currentMax+1]; //create new array for storage
  //with + 1 for the terminator node
  for (int i=0;i<aString.currentSize; i++){ //for value in aString
    theString[i] = aString.theString[i]; //copy the char
  }
  currentSize = aString.currentSize; //set current size
  theString[currentSize] = '\0'; //set the last char to the terminator
  //node 
}

//Pre:  str is a defined string object
//Post: This object is a deep copy of str
//      RV: a reference to this object
String & String::operator=(const String & str){
  currentMax = str.currentMax; //get max
  currentSize = str.currentSize; //get size
  delete (theString); //delete old allocated memory
  theString = new char[currentMax+1]; //get new memory
  for (int i=0; i<currentSize; i++){ //for char in str
    theString[i] = str.theString[i]; //copy
  }
  theString[currentSize] = '\0';
  return(*this); //return lvalue
}
//lvalue --> value to the left of an operation
//rvalue --> value to the right of an operation

//Pre:  This string is compared to another
//Post: Whether or not the given string is equal to the current
bool String::operator==(const String & str) const{
  bool isEqual = true;
  if (str.currentSize != currentSize){ //if the sizes are not the same
    isEqual = false; //they are not equal
  }
  else{ //ASSERT: sizes are equal
    for (int i=0; i<currentSize && isEqual; i++){ //while the strings
      //are not done and they are still equal
      if (str.theString[i] != theString[i]){ //if the chars don't match
	isEqual = false; //they are not equal
      }
    }
  }
  return (isEqual); //return the final value
}


// Pre:  str is a defined output stream. aString is a defined String
//       object satisfying the CI.
// Post: str contains the character array stored in a String
//       RV is resulting output stream
ostream & operator<<(ostream & str, const String & aString){
  str << aString.theString; //add current string to stream
  return (str); //return stream
}


//Pre:  The array of characters to be filled of length stop-start + 1
//      start & stop are indices in theString
//Post: The given array is filled with values from start to stop
void String::fillArray(char * array, int start, int stop) const{
  for (int i=start ; i < stop; i++){
    array[i-start] = theString[i]; //shift all values over to
                                         //appropriate indices and
				         //transfer them to the given
				         //array of characters
  }
  array[stop-start] = '\0'; //add terminator
}

//Pre:  Integer index for starting the search,
//      and the character to search for in theString
//Post: The number of characters from [start, char)
int String::countToNextChar(int start, char ch) const{
  int curr = start; //temp place holder
  char chr = theString[curr]; //current character
  while ((chr != ch)&(chr != '\0')){ //current != search
    curr ++; //increment place holder
    chr = theString[curr]; //get new character
  }
  return (curr - start); //+1 to be inclusive on start
}

//Pre:  A character to divide the string by is given, and a reference
//      to an integer that will hold the size of the return array
//Post: An array of character arrays
char ** String::splitBy(char ch, int & length) const{
  length = count(ch); //save length to the given reference,
  //      length is the number of array references that will be
  //      present
  int curr = 0; //place holder in stringArray
  char ** stringArray = new char*[length]; //get heap space mem for
  //      array 
  int size; //variable for holding the size of the current string
  for (int i=0; i < currentSize; i++){
    size = countToNextChar(i, ch); //count of current array
    stringArray[curr] = new char[size+1]; //create pointer to new
                                          //      array 
    fillArray(stringArray[curr], i, size+i); //fill the array
    i = i+size; //increment i
    curr ++; //increment current index
  }
  //Assert:   The whole file has been added
  //          The characters that were split by are removed
  //          The character arrays each hold a sub string
  //          Length has been set to the number of strings
  return (stringArray);
}

//Pre:  array of size >= (currentSize+1)
//Post: The given array is filled with the values from theString
void String::retExactArray(char array[]) const{
  for (int i=0; i<currentSize; i++){
    array[i] = theString[i];
  }
  array[currentSize] = '\0';
}

//Pre:  
//Post: A new array of exact size is built in heap space and returned
char * String::retExactArray() const{
  char * returnArray = new char[currentSize+1];
  for (int i=0; i<currentSize; i++){
    returnArray[i] = theString[i];
  }
  returnArray[currentSize] = '\0';
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
