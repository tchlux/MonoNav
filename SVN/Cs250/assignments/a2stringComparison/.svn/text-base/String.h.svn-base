#ifndef INCLUDED_String
#define INCLUDED_String

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
