#include <iostream>
#include "md5Hash.h"
#include "constants.h"
#include "Read512.h"
#include "String.h"
#include <cmath>
#include <stdio.h>

using namespace std;



//constants only needed in this file, to prevent multiple
//initializations


// Pre:  
// Post: Initializes values in the finalHash
md5Hash::md5Hash(){
  finalHash = new unsigned int[INTS_IN_FINAL_HASH]; //init storage for
						    //final hash
  finalHash[0] = INIT_A; //set initial A value
  finalHash[1] = INIT_B; //set initial B value
  finalHash[2] = INIT_C; //set initial C value
  finalHash[3] = INIT_D; //set initial D value

  SET_0_SHIFTS = new int[7, 12, 17, 22];
  SET_1_SHIFTS = new int[5, 9, 14, 20];
  SET_2_SHIFTS = new int[4, 11, 16, 23];
  SET_3_SHIFTS = new int[6, 10, 15, 21];
}

//Pre:  input c is a character whose most significant bits are 0000.
//Post: Returns a char, which is the hexadecimal representation of
//      the 4 LSB of c.
char md5Hash::char_to_hex_str(char c){
  char hex_rep;
  int char_val = (int) c;
  if(char_val < MAX_NUMERAL){
    hex_rep = (char)(MIN_DIGIT + char_val);
  }else{
    hex_rep = (char)(MIN_LETTER + (char_val - MAX_NUMERAL));
  }
  return (hex_rep);
}

// Pre:  final is defined, bits is an integer representing 32 bits
// Post: The string given is modified
String & md5Hash::intToHexStr(String & final, int bits){
  char c1; //temp 8 bits for finding hex values
  char c2; //temp 8 bits for finding hex values
  for (int i=(HEX_IN_INT-1); i >= 1; i-=2){ //for 4bit set in the int
    c1 = RIGHT_MASK & (bits >> SINGLE_HEX*i); //move the current 4 bits to the far
    //right 
    c2 = RIGHT_MASK & (bits >> SINGLE_HEX*i+1); //move the current 4 bits to the far
    //right
    final.add(char_to_hex_str(c2)); //get only the right
    final.add(char_to_hex_str(c1)); //get only the right

    //four bits of the character to hex
  }
}


// Pre:  0 <= round < 64, 0 <= set < 4
// Post: the corresponding function is run on the finalHash
void md5Hash::function(int round, int set){
  unsigned int value;
  unsigned int A = finalHash[0];
  unsigned int B = finalHash[1];
  unsigned int C = finalHash[2];
  unsigned int D = finalHash[3];
  switch(set){
  case 0: //set == 0
    value = ((B & C) | (!B & D));
    break;
  case 1: //set == 1
    value = ((B & D) | (C & !D));
    break;
  case 2: //set == 2
    value = ((B ^ C) ^ D);
    break;
  case 3: //set == 3
    value = (C ^ (B | !D));
  }
  finalHash[0] += value; //change the value of A accordingly
}

// Pre:  r >= 0, times defined, plus defined, mod > 0
// Post: The formula below  .. :P
int md5Hash::timesPlusMod(int r, int times, int plus, int mod){
  return((r*times + plus)%mod);
}

// Pre:  0 <= round < 64, 0 <= set < 4
// Post: the corresponding g is run on the finalHash
int md5Hash::g(int round, int set){
  int index; //storage for the final index
  switch(set){
  case 0: //set == 0
    index = timesPlusMod(round, SET_0_TIMES, SET_0_PLUS, SET_0_MOD);
    break;
  case 1: //set == 1
    index = timesPlusMod(round, SET_1_TIMES, SET_1_PLUS, SET_1_MOD);
    break;
  case 2: //set == 2
    index = timesPlusMod(round, SET_2_TIMES, SET_2_PLUS, SET_2_MOD);
    break;
  case 3: //set == 3
    index = timesPlusMod(round, SET_3_TIMES, SET_3_PLUS, SET_3_MOD);
  }
  return(index); //return the i value for the current round/set
}

// Pre:  0 <= round < 64, 0 <= set < 4
// Post: the corresponding k is run on the finalHash
void md5Hash::k(int round, int set){
  int final = floor(abs(sin(round+1))) * pow(ONE_BIT, BITS_IN_INT);
  finalHash[0] += final; //change the value of A accordingly
}

// Pre:  value >= 0, shift > 0 for left < 0 for right
// Post: value is shifted by the corresponding amount
void md5Hash::cyclicShift(unsigned int & value, int shift){
  int mask = 0; //storage for masking the edge values
  for (int i=0; i<shift; i++){
    mask *= 2; //shift all current bits in mask
    mask += 1; //add next new bit
  }
  if (shift > 0){
    mask << BITS_IN_INT - shift; //get *shift of left bits
    mask &= value; //grab the bits from the value
    value << shift; //shift the value
    mask >> BITS_IN_INT - shift; //move mask back
  }
  else{
    mask &= value; //grab the about-to-be-lost bits from value
    value >> shift; //shift value
    mask << BITS_IN_INT - shift; //move mask to appropriate loc
  }
  value |= mask; //fill in empty side of value
}

// Pre:  0 <= round < 64, 0 <= set < 4
// Post: the corresponding shift is performed on the finalHash
void md5Hash::shift(int round, int set){
  int mod = round % SHIFT_GROUP_MOD; //the mod value of the round
  int shift; //storage for shift of round
  switch(set){
  case 0:  //set == 0
    shift = SET_0_SHIFTS[mod];
    //get appropriate shift value from array
    break;
  case 1: //set == 1
    shift = SET_1_SHIFTS[mod];
    //get appropriate shift value from array
    break;
  case 2: //set == 2
    shift = SET_2_SHIFTS[mod];
    //get appropriate shift value from array
    break;
  case 3: //set == 3
    shift = SET_3_SHIFTS[mod];
    //get appropriate shift value from array
  }
  cyclicShift(finalHash[0], shift);
}

// Pre:  
// Post: All values in final hash are rotated left (i0 = i1)
void md5Hash::moveValuesRight(){
  int temp = finalHash[0]; //kill first value
  for (int i=1; i<INTS_IN_FINAL_HASH; i++){
    finalHash[i-1] = finalHash[i]; //shift all value's positions left
  }
  finalHash[3] = temp; //yank first value back to last value
}

// Pre:  allBits is all 512 bits read into 16 blocks of unsigned
//       integers
// Post: The md5 algorithm is run all 64 times, changing final hash
//       each time
void md5Hash::runMD5(unsigned int * allBits){
  int set; //storage for current set
  int index; //storage for index to access in allBits
  for (int i=0; i<MD5_ROUNDS; i++) {
    set = i / RANGE_PER_ROUND; //get set

    function(i, set); //perform set function add to A
    //Begin M function

    index = g(i, set); //get index

    finalHash[0] += allBits[index]; //add allBits[index] to A
    //End M function

    k(i, set); //perform k addition to A

    shift(i, set); //perform appropriate shift on A

    finalHash[0] += finalHash[1]; //add B to final hash

    moveValuesRight(); //cycle all values in finalhash
    cerr << i;
    printHash();
  }
}

//Pre:  input is a defined istream object
//Post: The istream is read through EOF and hashed with MD5
void md5Hash::makeHash(istream & inputStream){
  Read512 inputReader; //init a reader class
  while (!inputStream.eof()){ //while not at the end of the file
    inputStream >> inputReader; //get the next 512 bits


    String output;
    unsigned int * allBits = inputReader.returnBits();
    for (int i=0; i<16; i++){
      intToHexStr(output, allBits[i]);      
      cout << output << endl;
      output.reset();
    }


    runMD5(inputReader.returnBits()); //run md5 on the current 512bits
  }
  if (inputReader.doesNeedSize()){ //if there was no room for size
    inputReader.resetAndPad(); //make sure there is padding and add
      //size to a new 512
    runMD5(inputReader.returnBits()); //run md5 on the current 512bits
  }
}

//Pre:  
//Post: The full ABCD hex values are sent to cout
void md5Hash::printHash(){
  String output;
  intToHexStr(output, finalHash[0]);
  cout << "==> A: " << output;
  output.reset();
  intToHexStr(output, finalHash[1]);
  cout << " B: " << output;
  output.reset();

  intToHexStr(output, finalHash[2]);
  cout << " C: " << output;
  output.reset();

  intToHexStr(output, finalHash[3]);
  cout << " D: " << output << endl;
  output.reset();
}

// Pre:  
// Post: Delete all heap allocation
md5Hash::~md5Hash(){
  delete SET_0_SHIFTS;
  delete SET_1_SHIFTS;
  delete SET_2_SHIFTS;
  delete SET_3_SHIFTS;
}
