#include <iostream>
#include <fstream>
#define FILENAME "text1.txt"
#define BYTES_TO_READ 64	// bytes in file
#define HEX_DIGITS 128		// hex digits in final string
#define HEX_PER_BYTE 2		// hex digits per byte read
#define HEX_BASE 16		// numerical base of hex

using namespace std;

// Pre:  hex is of length HEX_PER_BYTE, c is the byte to change to hex
// Post: hex[0] and hex[1] are the hex character form of c
void getHex(char * hex, char c){
  hex[0] = ((int) c) / HEX_BASE; // get the left hex bit
  hex[1] = ((int) c) % HEX_BASE; // get the right hex bit
}

// Hashes text1.txt file
int main(int argc, char * argv[]){
  int status = 0;		// normal exit status
  char finalHash[HEX_DIGITS];	// Total number of hex chars
  char hex[HEX_PER_BYTE];	// holder for two hex characters
  ifstream inFile(FILENAME);	// open the inFile
  char c;			// holder for current byte
  for (int i=0; i<BYTES_TO_READ; i++){
    c = inFile.get();		// get the next character from inFile
    getHex(hex, c);		// fill hex with the two hex digits
    // Put the hex digits into the final string
    finalHash[HEX_PER_BYTE*i] = hex[0];
    finalHash[HEX_PER_BYTE*i+1] = hex[1];
  }
  cout << finalHash; 		// Deliver the final hash
  return(status);
}
