#include <iostream>
#include <fstream>

#define FILENAME "text0.txt"
#define LOWER (int) 'a'
#define UPPER (int) 'z'

#define A_VALUE 7
#define B_VALUE 2
#define M_VALUE 26

using namespace std;

// c is character, bool for if c is lower case alphabetic character
bool isAlpha(char c){
  return( ((((int) c) >= LOWER)&&
	   (((int) c) <= UPPER)) );
}

// shifts c cyclically be predefined amount
char shift(char c){
  int final = ((int) c) - LOWER; // shift to 0-26 range
  final = ((final*A_VALUE) + B_VALUE) % M_VALUE; // perform cipher
  return((char) final+LOWER);    // return final in character form
}


// Encrypts text0.txt with affine cipher A=7 B=2 M=26
int main(int argc, char * argv[]){
  int status = 0;		// return status
  ifstream text0(FILENAME);	// inFile with message to encrypt
  char curr; 			// holder for curr character
  curr = text0.get();		// get first character of file
  while (! text0.eof()){
    if (isAlpha(curr)){		// if the character is alphabetic
      cout << shift(curr);	// cout the shifted character
    }
    curr = text0.get();		// get the next character from file
  }
  return(status);		// Normal exit status
}
