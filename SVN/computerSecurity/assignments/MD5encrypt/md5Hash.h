#ifndef INCLUDED_md5Hash
#define INCLUDED_md5Hash

#include <iostream>
#include "constants.h"
#include "Read512.h"
#include "String.h"

using namespace std;

class md5Hash{

 private:

  unsigned int * finalHash; //get space for ABCD

  int * SET_0_SHIFTS; //space for four integer arrays,
  int * SET_1_SHIFTS; //one for each set, 4 values in
  int * SET_2_SHIFTS; //each for the 4 possible mod values
  int * SET_3_SHIFTS;


  //Pre:  input c is a character whose most significant bits are 0000.
  //Post: Returns a char, which is the hexadecimal representation of
  //      the 4 LSB of c.
  char char_to_hex_str(char c);

  // Pre:  final is defined, bits is an integer representing 32 bits
  // Post: The string given is modified
  String & intToHexStr(String & final, int bits);

  // Pre:  0 <= round < 64, 0 <= set < 4
  // Post: the corresponding function is run on the finalHash
  void function(int round, int set);

  // Pre:  r >= 0, times defined, plus defined, mod > 0
  // Post: The formula below  .. :P
  int timesPlusMod(int r, int times, int plus, int mod);

  // Pre:  0 <= round < 64, 0 <= set < 4
  // Post: the corresponding g is run on the finalHash
  int g(int round, int set);

  // Pre:  0 <= round < 64, 0 <= set < 4
  // Post: the corresponding k is run on the finalHash
  void k(int round, int set);

  // Pre:  value >= 0, shift > 0 for left < 0 for right
  // Post: value is shifted by the corresponding amount
  void cyclicShift(unsigned int & value, int shift);

  // Pre:  0 <= round < 64, 0 <= set < 4
  // Post: the corresponding shift is performed on the finalHash
  void shift(int round, int set);

  // Pre:  
  // Post: All values in final hash are rotated left (i0 = i1)
  void moveValuesRight();

 public:
  // Pre:  
  // Post: Initializes values in the finalHash
  md5Hash();

  // Pre:  allBits is all 512 bits read into 16 blocks of unsigned
  //       integers
  // Post: The md5 algorithm is run all 64 times, changing final hash
  //       each time
  void runMD5(unsigned int * allBits);

  //Pre:  input is a defined istream object
  //Post: The istream is read through EOF and hashed with MD5
  void makeHash(istream & inputStream);

  //Pre:  
  //Post: The full ABCD hex values are sent to cout
  void printHash();

  // Pre:  
  // Post: Delete all heap allocation
  ~md5Hash();


};

#endif
