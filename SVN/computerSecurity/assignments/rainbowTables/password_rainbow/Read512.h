//***************************************************************************
// Author:  Scotty Smith
//
// Purpose: Write a class that reads and stores 512 bits worth of a
//          file at a time.
//***************************************************************************
#ifndef INCLUDED_READ512_H
#define INCLUDED_READ512_H

#include "constants.h"

class Read512{
  //CLASS INVARIANT:  msg is a pointer to an array of BLOCKS_PER_512
  //integers, which represent 512 blocks of the input stream

 private:
  unsigned int * msg;
  unsigned long long msg_len;
  bool added_one;
  bool md5_eof;
  char holding_char;

  void clear(){
    for(int index = 0; index < BLOCKS_IN_512; index++){
      msg[index] = 0;
    }
  }
 public:
  //Pre:  None
  //Post: Creates the msg array, and initializes all blocks in msg to
  //      be 0's. 
  Read512();


  //Pre:  msg is a well defined unsigned int array of size
  //      BLOCKS_IN_512. 
  //      index is an integer, 0 <= index < BLOCKS_IN_512
  //Post: Returns the value of the unsigned integer at the specified
  //      index in msg.
  unsigned int get_block(int index){
    return msg[index];
  }

  //Pre:  in is a well defined input stream reference, which may or
  //      may not be at EOF.
  //      data_holder is a well defined Read512 reference.
  //Post: Returns a reference to the istream object, with 512 bits
  //      read out of the stream.
  //      Modifies the data_holder reference, so that data_holder.msg
  //      points to the correct
  friend istream& operator>>(istream& in, Read512& data_holder);
  friend ostream& operator<<(ostream& out, Read512& data_holder);

  //Pre:  this is a well defined Read512 object
  //      input_char is some character out of the input stream
  //      i in an integer in the range [0, 32)
  //      curr_integer is a reference to an int in the range [0,
  //      BLOCKS_IN_512)
  //Post: Adds a 1 character to the current msg, as necessary
  void add_one(char input_char, int i, int& curr_integer);

  //Pre:  this is a well defined Read512 object
  //      input_char is some character out of the input stream
  //      i in an integer in the range [0, 32)
  //      curr_integer is a reference to an int in the range [0,
  //      BLOCKS_IN_512)
  //Post: Pads the message, with a 1, 0's, and message size as
  //      necessary.
  void pad_as_necessary(char input_char, int i, int& curr_integer);

  //Pre:  this is a well defined Read512 object
  //      curr_integer is a reference to an int in the range[0,
  //      BLOCKS_IN_512) 
  //Post: Puts the size in the 64 LSB of the current msg.
  void put_size(int& curr_integer);

  //Pre:  None
  //Post: Returns the current value of the md5_eof instance variable.
  bool eof(){
    return md5_eof;
  }

  //Pre:  message_string is a valid, NULL terminated char*.
  //      starting_location is an integer,
  //      0 <= starting_location < length of message_string
  //Post: Processes as much of message_string as possible, storing up to
  //      512 bits from message_string into the msg array as possible.
  //      Returns an integer, the location of the next character that
  //      should be read.
  int process_string(char* message_string, int starting_location);
};

#endif
