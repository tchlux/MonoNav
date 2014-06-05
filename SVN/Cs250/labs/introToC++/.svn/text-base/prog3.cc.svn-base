#include <string.h>            // include the header file called
			       // string.h (Note this is different
			       // from the previous version of this
			       // program where we included string,
			       // not string.h. C++ is an extension of
			       // the language C, and string.h is the
			       // library provided by C. C is not an
			       // object oriented language, and thus
			       // does not provide objects to use. It
			       // simply provides libraries of
			       // functions -- string.h is a library
			       // of functions that can be used for
			       // manipulating arrays of characters.

#include <iostream>

using namespace std;

#define PROMPTSIZE 5          // This preprocessor directive define
			       // will cause the pre-processor to
			       // replace every occurrence of the
			       // string PROMPTSIZE (case sensitive)
			       // with the string 20. Thus, this is
			       // like defining constant values, and
			       // is used to do so.

// PRE: 
// POST: Output stream (OS) contains the string "Hello world".
int main (int argc, char * argv[]) {

  char prompt[PROMPTSIZE];     // declare an array of PROMPTSIZE
			       // number of characters.
  
  strcpy(prompt, "Hello world"); // Use the system function strcpy
				 // (from the system library string.h)
				 // to copy the value "Hello world" to
				 // the array of characters
				 // prompt. The characters in the
				 // value will be copied one by one to
				 // the array, and at the end of the
				 // characters in the value, the end
				 // of string character, denoted by
				 // \0, will also be 
				 // written to the array. Since the
				 // length of the value itself is 11
				 // characters, the array prompt will
				 // now contain 12 characters -- the
				 // 11 characters of the value
				 // followed by the end of string
				 // character. 

  cout << prompt << endl;
  // ASSERT: OS contains the value of prompt.

  return (0);
}
