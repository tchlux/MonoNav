/****************************************************************************
 * Author:  Scotty Smith
 *
 *
 * Purpose: Implement a very insecure hashing algorithm.
  ****************************************************************************/
#include <iostream>
#include <fstream>
using namespace std;

//File input validation
#define FILE_LOC  1
#define ARG_ERROR 1
#define USAGE_STRING "USAGE: ./hash <filename>\n"

//Hash info
#define HEX_DIGITS 2  //How many hex digits represent our hash
#define KEY_VAL   'S' //The inital value

//Masking information
#define FOUR_MASK   0xF //0xF is 1111 in binary
#define RIGHT_SHIFT 4   //Shift amount to get left half

//HEX conversion
#define MAX_NUMERAL  10
#define MIN_DIGIT   '0'
#define MIN_LETTER  'A'

//Pre:  input c is a character whose most significant bits are 0000.
//Post: Returns a char, which is the hexadecimal representation of
//      the 4 LSB of c.
char char_to_hex_str(char c){
  char hex_rep;
  int char_val = (int) c;

  if(char_val < MAX_NUMERAL){
    hex_rep = (char)(MIN_DIGIT + char_val);
  }else{
    hex_rep = (char)(MIN_LETTER + (char_val - MAX_NUMERAL));
  }

  return hex_rep;
}

//Pre:  hash_code is a valid, 8 bit character
//Post: Writes the specified character as a hex value to the cout
//      output stream.
void write_char_as_hex(char hash_code){
  char right_half = hash_code & FOUR_MASK;
  char left_half  = (hash_code >> RIGHT_SHIFT) & FOUR_MASK;

  char left_half_chr = char_to_hex_str(left_half);
  char right_half_chr = char_to_hex_str(right_half);

  cout << left_half_chr << right_half_chr << endl;
}

//Pre:  argc == 2, where argv[1] == a file to hash
//Post: writes the hashed value to standard output.
int main(int argc, char* argv[]){
  if(argc <= FILE_LOC){
    cout << USAGE_STRING << endl;
    return ARG_ERROR;
  }
  
  /* TEST CASES
  for(int i = 0; i < 256; i++){
    write_char_as_hex((char)i);
  }
  */

  //ASSERT: argv[FILE_LOC] exists
  //ASSUME: argv[FILE_LOC] is a string, the path to a file we have
  //access to read from.
  ifstream input(argv[FILE_LOC]);
  
  //This will ultimately hold the resultant hash.
  char hash = KEY_VAL;
  
  //Perform a block-wise xor of all characters in the file
  while(!input.eof()){
    char file_chr = input.get();
    hash ^= file_chr;
  }
  //ASSERT: hash holds 8 bits, the hash code for the input file

  //write_char_as_hex(hash);
  printf("%2X\n", hash & 0xFF);

  input.close();
}
