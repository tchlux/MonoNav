#ifndef INCLUDED_MYSTRING
#define INCLUDED_MYSTRING

class MyString {
  
 private:
  
  char * theString; // pointer to the space allocated for the array of
		    // characters.
  int currentMax;   // the maximum number of characters that can be
		    // currently accommodated in this MyString object.
  int currentSize;  // the number of characters currently in this
		    // MyString object.

  // CI: theString points to space allocated for at least one
  //       character.
  //     currentMax >= 0. theString points to space allocated for
  //       currentMax + 1 characters (one character space is reserved for
  //       the end of string character)
  //     currentSize = 0. currentSize <= currentMax.
  //       theString[0]..theString[currentSize-1] is
  //       defined. theString[currentSize] is the end of string
  //       character.

 public:

  // Default constructor
  // PRE:
  // POST: currentMax = 0. currentSize = 0. There is one space
  //         allocated for the object. theString[0] = '\0'. 
  //         CI is satisfied.
  MyString ();
  

};
#endif
