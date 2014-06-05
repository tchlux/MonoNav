#include <iostream>

using namespace std;

int main () {
  char ch;   // To hold the character read in.
  while (!cin.eof()) { // RV of this library function is true iff the
		       // end of file character has been read.
    cin.get(ch); // Read the next character from standard input.
    // Need to chack again for the end of file character since
    // something new was just read in.
    if (!cin.eof()) {
      cout << "Character: ASCII value = " << (int)ch 
	   << " char is *" << ch << "*" << endl;
      // When printing variables that are characters or arrays of
      // characters, it is useful to surround them with some known
      // character (as the * above) so that you can see in the
      // printout exactly the contents of the character or string
      // variable. 
    }
  }
  return (0);
}
