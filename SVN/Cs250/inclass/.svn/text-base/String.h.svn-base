#ifndef INCLUDED_String
#define INCLUDED_String

#include <iostream>

using namespace std;

class String {
  
 private:
  
  char * theString; // pointer to the space allocated for the array of
		    // characters.
  int currentMax;   // the maximum number of characters that can be
		    // currently accommodated in this String object.
  int currentSize;  // the number of characters currently in this
		    // String object.

  // CI: theString points to space allocated for at least one
  //       character.
  //     currentMax >= 0. theString points to space allocated for
  //       currentMax + 1 characters (one character for EOS)
  //     currentSize = 0. currentSize <= currentMax.
  //       theString[0]..theString[currentSize-1] is
  //       defined. theString[currentSize] is EOS


 public:

  // Default constructor
  // PRE:
  // POST: currentMax = 0. currentSize = 0. There is one space
  //         allocated for the object. theString[0] = '\0'. 
  //         CI is satisfied.
  String();

  // Constructor given a string
  //Pre:  Pointer to string is given
  //Post: The given string is stored
  String(char* str);

  //Pre:  aString is defined and follows CI
  //Post: Deep copy of aString created
  String(String & aString);

  //Pre:  str is a defined string object
  //Post: This object is a deep copy of str
  //      RV: a reference to this object
  String & operator=(const String & str);

  //Pre:  This string is compared to another
  //Post: Whether or not the given string is equal to the current
  bool operator==(const String $ str);

  // Pre:  str is a defined output stream. aString is a defined String
  //       object satisfying the CI.
  // Post: str contains the character array stored in a String
  //       RV is resulting output stream
  friend ostream & operator<<(ostream & str, const String & aString);

  //Pre:  The array of characters to be filled of length stop-start +
  //      1 
  //      start & stop are indices in theString
  //Post: The given array is filled with values from start to stop
  void fillArray(char * array, int start, int stop) const;

  //Pre:  Integer index for starting the search,
  //      and the character to search for in theString
  //Post: The number of characters from [start, char)
  int countToNextChar(int start, char ch) const;

  //Pre:  A character to divide the string by is given, and a
  //      reference 
  //      to an integer that will hold the size of the return array
  //Post: An array of character arrays
  char ** splitBy(char ch, int & length) const;

  //Pre:  array of size >= (currentSize+1)
  //Post: The given array is filled with the values from theString
  void retExactArray(char array[]) const;

  //Pre:  
  //Post: A new array of exact size is built in heap space and returned
  char * retExactArray() const;

  //Pre:  A character is given
  //Post: The number of occurances of that character is counted in
  //      theString
  int count(char ch) const;

  //Pre:  
  //Post: The current length of the string is returned as an integer
  int length() const;

  // Pre:  integer of index in array is given, the index must be les
  // than current size or else an empty character is returned
  // Post: The character at that index is returned
  char index(int index) const;

  // Output member functions
  // PRE: This String object is defined and satisfies the CI.
  // POST: OS contains a newline followed by the values of currentMax,
  // currentSize and the characters in theString followed by a
  // newline. 
  void debugPrint () const;

  // PRE: This String object is defined and satisfies the CI.
  // POST: OS contains the characters in this string.
  void print () const;

  // Modifiers

  // PRE: This String object is defined with values 
  //       currentMax = M, currentSize = S, and satisfies the CI.
  // POST: ch is defined. 
  //       theString[0]..theString[S-1] are the same as before.
  //       theString[S] = ch
  //       theString[S+1] = '\0'
  //       The result object satisfies the CI.
  void add (char ch);

  // Pre:  
  // Post: All values are reset back to initial settings
  void reset();

  //Pre:  theString exists as a pointer to an array in heap space
  //Post: The heap space is freed
  ~String();
  
};
#endif
