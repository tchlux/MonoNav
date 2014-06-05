#ifndef INCLUDED_StringArray
#define INCLUDED_StringArray

#include "String.h"
#define DEFAULT_ARRAY_SIZE 10

class StringArray {

 private:
  String * StringList; // Reference to a String object. In this 
                        // object, this reference will point to
                        // an array of String objects.
  int numString;     // number of String objects in this object.

 public:
  /*
    Constructors
  */

  // PRE:
  // POST: An array with DEFAULT_ARRAY_SIZE number of 
  //        Stringion objects is constructed. 
  //        Each Stringion object in the array is constructed as the 
  //        default Stringion object 0/1.
  StringArray();

  // PRE:  numStrings = n > 0 is defined.
  // POST: An array with n String objects is constructed. 
  //        Each String object in the array is constructed as the 
  //        default String object.
  StringArray(int numStrings);


  int size() const

  //
  //  Destructor
  //
  
  // PRE: This StringArray object is defined.
  // POST: Free the memory allocated for the StringList.
  ~StringArray();



};

#endif
