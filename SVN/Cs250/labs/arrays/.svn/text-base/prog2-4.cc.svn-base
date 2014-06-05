#include <iostream>

using namespace std;

#define MAXCHARS 10

// PRE:
// POST: Print the ordinal values of characters in a string.
int main (int argc, char * argv[]) {

  char name[MAXCHARS];   // Declare an array that can hold
                         // MAXCHARS number of char objects.
                         // name will now be a string that can have up
                         // to 9 characters, since one character space
                         // is to be reserved for the end of string
                         // character. 

  // Assign the string "abcd" to name. Note the assignment of '\0' as
  // the last character.
  //name = "abcd";
  name[0] = 'a';
  name[1] = 'b';
  name[2] = 'c';
  name[3] = 'd';
  //  name[4] = '\0';


  for (int i = 0; i < MAXCHARS; i++) {
    cout << "Character at index " << i 
	 << " has ordinal value " << (int) name[i] << endl;
    /* Characters are represented using the ASCII encoding
       system. Each character takes up 8 bits, or 1 byte. The char data
       type can be used as it's character value, or as the integer when one
       evaluates the character's ASCII encoding. One can explicitly
       state the integer use of a character by casting it as an int as
       above. 
    */
  }

  // Print the name as a string ending with the end of string character.
  cout << "Name is " << name << endl;

  return (0);

}
