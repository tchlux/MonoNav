#ifndef INCLUDED_MD5_H
#define INCLUDED_MD5_H
#include <iostream>
using namespace std;
#include "Read512.h"
#include "constants.h"

//I got tired of writing unsigned int, so I made my own type!
typedef unsigned int uint4;

class md5{
 private:
  uint4 a, b, c, d;
  uint4 * K;

  //Pre:  local_b, local_c, and local_d are valid unsigned integers
  //Post: Returns the result of MD5's Round 1 F function, a valid
  //      unsigned integer.
  uint4 F_RG1(uint4 local_b, uint4 local_c, uint4 local_d){
    return (local_b & local_c) | ((~local_b) & local_d);
  }

  //Pre:  local_b, local_c, and local_d are valid unsigned integers
  //Post: Returns the result of MD5's Round 2 F function, a valid
  //      unsigned integer.
  uint4 F_RG2(uint4 local_b, uint4 local_c, uint4 local_d){
    return (local_b & local_d) | (local_c & (~local_d));
  }

  //Pre:  local_b, local_c, and local_d are valid unsigned integers
  //Post: Returns the result of MD5's Round 3 F function, a valid
  //      unsigned integer.
  uint4 F_RG3(uint4 local_b, uint4 local_c, uint4 local_d){
    return local_b ^ local_c ^ local_d;
  }

  //Pre:  local_b, local_c, and local_d are valid unsigned integers
  //Post: Returns the result of MD5's Round 4 F function, a valid
  //      unsigned integer.
  uint4 F_RG4(uint4 local_b, uint4 local_c,
		     uint4 local_d){ 
    return local_c ^ (local_b | (~local_d));
  }

  //Pre:  value is a valid 32 bit integer.
  //      buffer is a valid char* array of size at least
  //      starting_location + 8 characters long.
  //      starting_location is an integer in the range [0, length of
  //      buffer - 8]
  //Post: Converts value into 8 hex characters, and stores them in
  //      little-endian order into buffer starting at the specified
  //      starting location.
  void convert_to_chars(uint4 value, char* buffer, int
			starting_location);


  //Pre:  round_num is an integer in the range [0, 64)
  //      local_b, local_c, and local_d are uint4egers as defined
  //      by the MD5 protocol.
  //Post: Returns the output of the given round groups F function.
  uint4 execute_group_f(int round_num, uint4 local_b, uint4 local_c,
			uint4 local_d);

  //Pre:  group_num is an integer in the range [0, 3)
  //      round_num is an integer in the range [0, 64)
  //Post: returns an integer, the index of the message block for the
  //      current group and round numbers.
  int get_msg_index(int group_num, int round_num);

  //Pre:  group_num is an integer in the range [0, 3)
  //      round_num is an integer in the range [0, 64)
  //Post: returns an integer, the predefined shift amounts as seen in
  //      the prompt. 
  int get_shift_amount(int group_num, int round_num);

  //Pre:  Input local_a is a reference to an uint4eger
  //      amount is an integer in the range [0, 32]
  //Post: alters local_a, by performing a cyclic left_shift.
  void cyclic_shift(uint4 & local_a, int amount);


  //Pre:  input c is a character whose most significant bits are 0000.
  //Post: Returns a char, which is the hexadecimal representation of
  //      the 4 LSB of c.
  char char_to_hex_str(char c);

 public:
  //Pre:  None
  //Post: Initializes the a, b, c, and d attributes, as well as K via
  //      function call
  md5();

  //Pre:  this has been setup
  //Post: alters the K attribute as specified in the prompt.
  void setup_K();

  /*
    Getters.  No pre/post conditions for you!
   */
  uint4 get_a(){ return a;}
  uint4 get_b(){ return b;}
  uint4 get_c(){ return c;}
  uint4 get_d(){ return d;}

  //Pre:  msg_block is a well defined reference to a Read512 object
  //Post: Performs all 64 rounds necessary on msg_block, for md5.
  //      Accumulates the local a, b, c, and d's into the class
  //      attributes a, b, c, and d.
  void execute_rounds(Read512& msg_block);

  //Pre:  Instance variables a, b, c, and d are defined and accessible.
  //Post: Returns the MD5 fingerprint of the defined state of the
  //      system. 
  char* produce_fingerprint();

  //Pre:  cin is a well defined, open input stream
  //Post: Returns a 32 character char*, formatted in the correct order
  //      for an MD5 hash fingerprint.
  char* process_stdin();

  //Pre:  md5_string is a valid char*, terminated by a \0 character.
  //Post: Returns a 32 character char* md5 fingerprint for md5_string,
  //      formatted in the correct order for an MD5 hash fingerprint
  char* process_string(char* md5_string);

  //Pre:  None
  //Post: Resets the values of a, b, c, and d to be their original
  //      values. 
  void reset();
};

#endif
