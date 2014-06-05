//***************************************************************************
// Author:  Scotty Smith
//
// Purpose: Implement a class that reads and stores 512 bits worth of a
//          file at a time.
//***************************************************************************

#include <iostream>
using namespace std;

#include <cstdio> //For the EOF check
#include <stdbool.h>
#include "Read512.h"
#include "constants.h"

//Pre:  None
//Post: Creates the msg array, and initializes all blocks in msg to
//      be 0's. 
Read512::Read512(){
  msg = new unsigned int[BLOCKS_IN_512];
  added_one = false;
  md5_eof = false;
  msg_len = 0LL;
  holding_char = '\b';
  clear();
}


//Pre:  message_string is a valid, NULL terminated char*.
//      starting_location is an integer,
//      0 <= starting_location < length of message_string
//Post: Processes as much of message_string as possible, storing up to
//      512 bits from message_string into the msg array as possible.
//      Returns an integer, the location of the next character that
//      should be read.
int Read512::process_string(char* message_string,
			    int starting_location){ 
  char current_char = message_string[starting_location];
  int curr_integer  = 0;
  int curr_char_loc = starting_location;
  int i             = 0;
  clear();

  for(curr_integer = 0;
      curr_integer < BLOCKS_IN_512 && current_char != EOS; 
      curr_integer++){
    //Reset to zero, to remove anything that was there previously
    msg[curr_integer] = 0;
    
    for(i = 0; i < CHARS_PER_BLOCK && current_char != EOS; i++){
      msg_len++;
      msg[curr_integer] |= ((int) current_char) << (SHIFT_AMOUNT * i);

      current_char = message_string[++curr_char_loc];
    }
    if(current_char == EOS){
      break; //Ouch...but, I do need to make sure curr_integer
	     //doesn't increment
    }

    //ASSERT: msg[curr_integer] now holds 32 bits of the
    //message, or we hit the end of the input stream and it holds less
    //than that.
  }
  pad_as_necessary(current_char, i, curr_integer);

  return curr_char_loc;
}

//Pre:  in is a well defined input stream reference, which may or
//      may not be at EOF.
//      data_holder is a well defined Read512 reference.
//Post: Returns a reference to the istream object, with 512 bits
//      read out of the stream.
//      Modifies the data_holder reference, so that data_holder.msg
//      points to the correct bits from the input file.
istream& operator>>(istream& in, Read512& data_holder){
  char input_char = data_holder.holding_char;
  if(input_char == '\b')
    input_char = in.get();

  int curr_integer = 0;
  int i = 0;

  //We want Read512 to store the characters "left-to-right", so start
  //high and go low.
  data_holder.clear();

  for(curr_integer = 0;
      curr_integer < BLOCKS_IN_512 && input_char != EOF; 
      curr_integer++){
    //Reset to zero, to remove anything that was there previously
    data_holder.msg[curr_integer] = 0;
    
    for(i = 0; i < CHARS_PER_BLOCK && input_char != EOF; i++){
      data_holder.msg_len++;
      data_holder.msg[curr_integer] |= ((int) input_char) <<
      	(SHIFT_AMOUNT * i);

      input_char = in.get();
    }
    if(input_char == EOF){
      break; //Ouch...but, I do need to make sure curr_integer
	     //doesn't increment
    }

    //ASSERT: data_holder.msg[curr_integer] now holds 32 bits of the
    //message, or we hit the end of the input stream and it holds less
    //than that.
  }
  data_holder.holding_char = input_char;
  data_holder.pad_as_necessary(input_char, i, curr_integer);
  return in;
}

//Pre:  this is a well defined Read512 object
//      input_char is some character out of the input stream
//      i in an integer in the range [0, 32)
//      curr_integer is a reference to an int in the range [0,
//      BLOCKS_IN_512)
//Post: Pads the message, with a 1, 0's, and message size as
//      necessary.
void Read512::pad_as_necessary(char input_char, int i, int& curr_integer){
  add_one(input_char, i, curr_integer);
  put_size(curr_integer);
}

//Pre:  this is a well defined Read512 object
//      curr_integer is a reference to an int in the range[0,
//      BLOCKS_IN_512) 
//Post: Puts the size in the 64 LSB of the current msg.
void Read512::put_size(int& curr_integer){
  if(added_one){
    if(!md5_eof && curr_integer < BLOCKS_IN_512 - 2){
      //There's room in this 512 block to put the size!
      msg_len *= 8;
      md5_eof = true;
      for(int j = 0; j < CHARS_PER_BLOCK; j ++){
	msg[BLOCKS_IN_512 - 2] |= ((msg_len >> (j * BITS_IN_BYTE)) &
				   0xFF) << (j * BITS_IN_BYTE);
      }
      for(int j = 4; j < 2 * CHARS_PER_BLOCK; j ++){
	msg[BLOCKS_IN_512 - 2] |= ((msg_len >> (j * BITS_IN_BYTE)) &
				   0xFF) << (j * BITS_IN_BYTE);
      }
    }
  }
}

//Pre:  this is a well defined Read512 object
//      input_char is some character out of the input stream
//      i in an integer in the range [0, 32)
//      curr_integer is a reference to an int in the range [0,
//      BLOCKS_IN_512)
//Post: Adds a 1 character to the current msg, as necessary
void Read512::add_one(char input_char, int i, int& curr_integer){
  unsigned char one = 0x80;
  if(!added_one && (input_char == EOF || input_char == EOS)){
    //Need to add one, if possible
    if(i == CHARS_PER_BLOCK){
      curr_integer++;
      i = 0;
    }

    if(curr_integer < BLOCKS_IN_512){
      added_one = true;
      msg[curr_integer] |= ((unsigned int) one) << (SHIFT_AMOUNT * i);
    }
  }

}

ostream& operator<<(ostream& out, Read512& data_holder){
  char* buffer = new char[10];
  for(int i = 0; i < BLOCKS_IN_512; i++){
    for(int j = 0; j < 10; j++){
      buffer[j] = (char) 0;
    }
    sprintf(buffer, "%08X", data_holder.msg[i]); 
    out << buffer << endl;
  }

  return out;
}
