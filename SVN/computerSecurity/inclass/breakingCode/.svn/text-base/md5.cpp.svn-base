#include "md5.h"
#include <cmath>
#include <cstdio>

//Pre:  None
//Post: Initializes the a, b, c, and d attributes, as well as K via
//      function call
md5::md5(){
  reset();
  setup_K();
}

//Pre:  round_num is an integer in the range [0, 64)
//      local_b, local_c, and local_d are unsigned integers as defined
//      by the MD5 protocol.
//Post: Returns the output of the given round groups F function.
uint4 md5::execute_group_f(int round_num, uint4 local_b,
				  uint4 local_c, uint4 local_d){
  uint4 f_val = 0;
  switch(round_num){
  case GROUP_1:
    f_val = F_RG1(local_b, local_c, local_d);
    break;
  case GROUP_2:
    f_val = F_RG2(local_b, local_c, local_d);
    break;
  case GROUP_3:
    f_val = F_RG3(local_b, local_c, local_d);
    break;
  default:
    f_val = F_RG4(local_b, local_c, local_d);
  }
  return f_val;
}

//Pre:  group_num is an integer in the range [0, 3)
//      round_num is an integer in the range [0, 64)
//Post: returns an integer, the index of the message block for the
//      current group and round numbers.
int md5::get_msg_index(int group_num, int round_num){
  int msg_index = round_num;
  switch(group_num){
  case GROUP_2:
    msg_index = (G2_MULT * round_num + G2_ADD) % GROUP_SIZE;
    break;
  case GROUP_3:
    msg_index = (G3_MULT * round_num + G3_ADD) % GROUP_SIZE;
    break;
  case GROUP_4:
    msg_index = (G4_MULT * round_num) % GROUP_SIZE;
    break;
  }
  return msg_index;
}
//Pre:  group_num is an integer in the range [0, 3)
//      round_num is an integer in the range [0, 64)
//Post: returns an integer, the predefined shift amounts as seen in
//      the prompt. 
int md5::get_shift_amount(int group_num, int round_num){
  int s = 0;
  int g1[SHIFT_SIZE] = GROUP_1_S;
  int g2[SHIFT_SIZE] = GROUP_2_S;
  int g3[SHIFT_SIZE] = GROUP_3_S;
  int g4[SHIFT_SIZE] = GROUP_4_S;

  int selector = round_num % SHIFT_SIZE;
  switch(group_num){
  case GROUP_1:
    s = g1[selector];
    break;
  case GROUP_2:
    s = g2[selector];
    break;
  case GROUP_3:
    s = g3[selector];
    break;
  default:
    s = g4[selector];
  }

  return s;
}

//Pre:  this has been setup
//Post: alters the K attribute as specified in the prompt.
void md5::setup_K(){
  K = new uint4[K_SIZE];

  for(int i = 0; i < K_SIZE; i++){
    K[i] = floor(abs(sin(i + 1)) * pow(2, UINT_SIZE));
  }
}
//Pre:  Input local_a is a reference to an unsigned integer
//      amount is an integer in the range [0, 32]
//Post: alters local_a, by performing a cyclic left_shift.
void md5::cyclic_shift(uint4 & local_a, int amount){
  uint4 most_significant_bits = local_a >> (UINT_SIZE - amount); 
  local_a <<= amount;
  local_a |= most_significant_bits;
}

//Pre:  msg_block is a well defined reference to a Read512 object
//Post: Performs all 64 rounds necessary on msg_block, for md5.
//      Accumulates the local a, b, c, and d's into the class
//      attributes a, b, c, and d.
void md5::execute_rounds(Read512& msg_block){
  uint4 local_a = a;
  uint4 local_b = b;
  uint4 local_c = c;
  uint4 local_d = d;

  for(int i = 0; i < NUM_ROUNDS; i++){
    uint4 f_val = 0;
    int group_num = i / GROUP_SIZE;
    int msg_index = get_msg_index(group_num, i);
    int s = get_shift_amount(group_num, i);

    f_val = execute_group_f(group_num, local_b, local_c, local_d);
    
    local_a += f_val;

    local_a += msg_block.get_block(msg_index);

    local_a += K[i];

    cyclic_shift(local_a, s);

    local_a += local_b;

    uint4 tmp = local_d;
    local_d = local_c;
    local_c = local_b;
    local_b = local_a;
    local_a = tmp;

  }
  a += local_a;
  b += local_b;
  c += local_c;
  d += local_d;
}

//Pre:  Instance variables a, b, c, and d are defined and accessible.
//Post: Returns the MD5 fingerprint of the defined state of the
//      system. 
char* md5::produce_fingerprint(){
  char* hash_string = new char[HASHCODE_SIZE];

  convert_to_chars(a, hash_string, A_LOC * HEX_CHARS_PER_INT);
  convert_to_chars(b, hash_string, B_LOC * HEX_CHARS_PER_INT);
  convert_to_chars(c, hash_string, C_LOC * HEX_CHARS_PER_INT);
  convert_to_chars(d, hash_string, D_LOC * HEX_CHARS_PER_INT);

  return hash_string;
}

//Pre:  cin is a well defined, open input stream
//Post: Returns a 32 character char*, formatted in the correct order
//      for an MD5 hash fingerprint.  Recipient is responsible for
//      freeing the return. 
char* md5::process_stdin(){
  Read512 data = Read512();
 
  
  while(!data.eof()){
    cin >> data;
    execute_rounds(data);
  }

  return produce_fingerprint();
}

//Pre:  value is a valid 32 bit integer.
//      buffer is a valid char* array of size at least
//      starting_location + 8 characters long.
//      starting_location is an integer in the range [0, length of
//      buffer - 8]
//Post: Converts value into 8 hex characters, and stores them in
//      little-endian order into buffer starting at the specified
//      starting location.
void md5::convert_to_chars(uint4 value, char* buffer, int
			   starting_location){

  for(int i = 0; i < HEX_CHARS_PER_INT; i += 2){
    char most_sig_block = (char)((value >> (HEX_CHAR_SHIFT * (i + 1)))
				 & CHAR_LSB_MASK); 
    buffer[starting_location + i] = char_to_hex_str(most_sig_block);

    char least_sig_block = (char)((value >> (HEX_CHAR_SHIFT * i))
				  & CHAR_LSB_MASK); 
    buffer[starting_location + i + 1] =
      char_to_hex_str(least_sig_block); 
  }
}


//Pre:  input c is a character whose most significant bits are 0000.
//Post: Returns a char, which is the hexadecimal representation of
//      the 4 LSB of c.
char md5::char_to_hex_str(char c){
  char hex_rep;
  int char_val = (int) c;

  if(char_val < MAX_NUMERAL){
    hex_rep = (char)(MIN_DIGIT + char_val);
  }else{
    hex_rep = (char)(MIN_LETTER + (char_val - MAX_NUMERAL));
  }

  return hex_rep;
}

//Pre:  md5_string is a valid char*, terminated by a \0 character.
//Post: Returns a 32 character char* md5 fingerprint for md5_string,
//      formatted in the correct order for an MD5 hash fingerprint
char* md5::process_string(char* md5_string){
  reset(); //Make sure the initial state is O.K.
  Read512 data = Read512();

  int curr_loc = 0;
  while(!data.eof()){
    curr_loc = data.process_string(md5_string, curr_loc); 
    execute_rounds(data);
  }

  return produce_fingerprint();
}

//Pre:  None
//Post: Resets the values of a, b, c, and d to be their original
//      values. 
void md5::reset(){
  a = INITIAL_A;
  b = INITIAL_B;
  c = INITIAL_C;
  d = INITIAL_D;
}
