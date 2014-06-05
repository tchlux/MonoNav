#include <iostream>
#include "StringArray.h"
#include "String.h"
using namespace std;

// PRE:
// POST: An array with DEFAULT_ARRAY_SIZE number of 
//        String objects is constructed. 
//        Each String object in the array is constructed as the 
//        default String object.
StringArray::StringArray() {
  cout << " Default StringArray constructor " << endl;
  StringList = new String[DEFAULT_ARRAY_SIZE];
  numStrings = DEFAULT_ARRAY_SIZE;
}

// PRE:  numStrings = n > 0 is defined.
// POST: An array with n String objects is constructed. 
//        Each String object in the array is constructed as the 
//        default String object.
StringArray::StringArray(int numStrings) {
  cout << " Parametrised StringArray constructor for " 
       << pNumStrings << " String objects." << endl;
  StringList = new String[pNumStrings];
  numStrings = numStrings;
}


// PRE: This StringArray object is defined.
// POST: Free the memory allocated for the StringList.
StringArray::~StringArray() {
  cout << "StringArray destructor called " << endl;
  delete (StringList);
  // You could also use
  //  free (StringList); //for memory allocation involving c function malloc
}

