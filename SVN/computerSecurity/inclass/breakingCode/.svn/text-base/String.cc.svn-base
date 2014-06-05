#include <iostream>
#include "String.h"

using namespace std;

// ========================================
//              Constructors
// ========================================

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
String::String(const String & aString){
  currentMax = aString.currentMax; //get value for current max
  theString = new char[currentMax+1]; //create new array for storage
  //with + 1 for the terminator node
  for (int i=0;i<aString.currentSize+1; i++){ //for value in aString
    theString[i] = aString.theString[i]; //copy the char
  }
  currentSize = aString.currentSize; //set current size
}

// ========================================
//              Destructor
// ========================================

//Pre:  theString exists as a pointer to an array in heap space
//Post: The heap space is freed
String::~String(){
  delete (theString);
}

// ========================================
//              Operators
// ========================================

//Pre:  str is a defined string object
//Post: This object is a deep copy of str
//      RV: a reference to this object
String & String::operator=(const String & str){
  currentMax = str.currentMax; //get max
  currentSize = str.currentSize; //get size
  if (theString != NULL){ //if there was something stored
    delete (theString); //delete old allocated memory
  }
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

// Pre:  index <= currentSize
// Post: A reference to that location is returned
char & String::operator[](int index){
  return(theString[index]);
}

//Pre:  otherString is defined
//Post: otherString is appended to the end of this string
String & String::operator+(String & otherString){
  String * result = new String(*this);
  for (int i=0; i<otherString.currentSize; i++){
    result->add(otherString[i]);
  }
  return(*result);
}

//Pre:  otherString is defined and terminated
//Post: otherString is appended to the end of this string
String & String::operator+(char * otherString){
  String * result = new String(*this);
  for (int i=0; otherString[i] != '\0'; i++){
    result->add(otherString[i]);
  }
  return(*result);
}

// Pre:  newChars is defined and properly terminated
// Post: The characters in newChars are added to this string
void String::operator+=(char * newChars){
  for (int i=0; newChars[i] != '\0'; i++){
    add(newChars[i]);
  }  
}

// ========================================
//               Accessors
// ========================================

//Pre:  
//Post: The current length of the string is returned as an integer
int String::length() const{
  return (currentSize);
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

// Pre:  chr is a character to find
// Post: -1 if the char doesn't exist, otherwise, the lowest index
//       at which the given character occurs
int String::index(char chr) const{
  int returnValue = -1;
  int index = 0;
  while ((theString[index] != chr)&&(theString[index] != '\0')){
    index ++;
  }
  if (theString[index] != '\0'){
    returnValue = index;
  }
  return(returnValue);
}

// ========================================
//              Modifiers
// ========================================

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
    theString = new char[(currentMax+1)*2]; //create a new arry twice
    //       as large for theString
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

//Pre:  Integer index for starting the search,
//      and the character to search for in theString
//Post: The number of characters from [start, char)
int String::countToNextChar(int start, char ch) const{
  int curr = start; //temp place holder
  int finalCount = 0; //final count holder
  if (start <= currentSize){
    char chr = theString[curr]; //current character
    while ((chr != ch)&&(chr != '\0')){ //current != search
      curr ++; //increment place holder
      chr = theString[curr]; //get new character
    }
    finalCount = curr - start;
  }
  return (finalCount); //+1 to be inclusive on start
}

// ========================================
//             Operations
// ========================================

//Pre:  A character to divide the string by is given, and a reference
//      to an integer that will hold the size of the return array
//Post: An array of character arrays
char ** String::splitBy(char ch, int & length) const{
  length = count(ch)+1; //save length to the given reference,
  //      length is the number of array references that will be
  //      present
  int curr = 0; //place holder in stringArray
  char ** stringArray = new char*[length]; //get heap space mem for
  //      array 
  int size; //variable for holding the size of the current string
  //  for (int i=0; i < currentSize; i++){
  int start = 0;
  while (start <= currentSize){
    size = countToNextChar(start, ch); //count of current array
    stringArray[curr] = new char[size+start]; //create pointer to new
                                          //      array 
    fillArray(stringArray[curr], start, size+start); //fill the array
    start = start+size+1; //increment i
    curr ++; //increment current index
  }
  //Assert:   The whole file has been added
  //          The characters that were split by are removed
  //          The character arrays each hold a sub string
  //          Length has been set to the number of strings
  return (stringArray);
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

// ========================================
//       Output member functions                
// ========================================


// Pre:  str is a defined output stream. aString is a defined String
//       object satisfying the CI.
// Post: str contains the character array stored in a String
//       RV is resulting output stream
ostream & operator<<(ostream & str, const String & aString){
  str << aString.theString; //add current string to stream
  return (str); //return stream
}

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
