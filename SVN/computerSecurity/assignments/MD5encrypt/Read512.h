//***************************************************************************
// Author:  Scotty Smith
//
// Purpose: Write a class that reads and stores 512 bits worth of a
//          file at a time.
//***************************************************************************
#ifndef INCLUDED_READ512_H
#define INCLUDED_READ512_H

#include <iostream>
#include "constants.h"

using namespace std;

class Read512{
  //CLASS INVARIANT:  msg is a pointer to an array of BLOCKS_PER_512
  //integers, which represent 512 blocks of the input stream

 private:
  unsigned int * msg;
  bool needsPadding; //needs a new 512 to pad (with extra 1)
  bool needsSize; //needs a new 512 to hold size
  unsigned long bitsReadIn; //init storage for the number of bits read in

  // Pre:  i            == index of next byte to fill
  //       curr_integer == index in msg of current integer
  //       final_char   == char storage (can be junk)
  // Post: If the end of file has been reached, padding and size are
  //       either added or marked to be added later
  void endOfFile(int i, int curr_integer, char final_char);

 public:
  //Pre:  None
  //Post: Creates the msg array, and initializes all blocks in msg to
  //      be 0's. 
  Read512();

  //Pre:  
  //Post: return value for needsSize
  bool doesNeedSize();

  //Pre:  
  //Post: Return the 512 bits stored in an array of 16 unsigned
  //      integers
  unsigned int * returnBits();

  //Pre:  
  //Post: Size is written to the last 8 bytes if there is room
  void writeSize();

  //Pre:  
  //Post: class is reset as normally would be done, padding is added to
  //      the first open location if needed, and size is added if it is
  //      needed
  void resetAndPad();

  //Pre:  in is a well defined input stream reference, which may or
  //      may not be at EOF.
  //      data_holder is a well defined Read512 reference.
  //Post: Returns a reference to the istream object, with 512 bits
  //      read out of the stream.
  //      Modifies the data_holder reference, so that data_holder.msg
  //      holds the correct bits from the input file.
  friend istream& operator>>(istream& in, Read512& data_holder);

};

#endif
