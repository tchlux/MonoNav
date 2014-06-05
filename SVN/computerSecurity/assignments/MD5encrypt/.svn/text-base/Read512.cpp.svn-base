//***************************************************************************
// Author:  Scotty Smith & Thomas Lux
//
// Purpose: Implement a class that reads and stores 512 bits worth of a
//          file at a time. and extra provided functionality.
//***************************************************************************

#include <iostream>
using namespace std;

#include <cstdio> //For the EOF check
#include <iostream>
#include "Read512.h"
#include "constants.h"

using namespace std;

//Pre:  None
//Post: Creates the msg array, and initializes all blocks in msg to
//      be 0's. 
Read512::Read512(){
  needsPadding = false; //no padding needed yet
  needsSize = false; //no size needed yet
  bitsReadIn = 0; //set bitsReadIn to 0
  msg = new unsigned int[BLOCKS_IN_512]; //init 512 bit storage (16*32)
  
  for(int index = 0; index < BLOCKS_IN_512; index++){ //for i < 16
    msg[index] = 0; //init to 0
  }
}

//Pre:  
//Post: return value for needsSize
bool Read512::doesNeedSize(){
  return(needsSize);
}

//Pre:  
//Post: Return the 512 bits stored in an array of 16 unsigned
//      integers
unsigned int * Read512::returnBits(){
  return (msg); //return the 16 unsigned integers in the array
}

//Pre:  
//Post: Size is written to the last 8 bytes if there is room
void Read512::writeSize(){
  int lastBlock = BLOCKS_IN_512 - 1;
  if ((msg[lastBlock] == 0)&&(msg[lastBlock-1] == 0)){ //if the last
    //two integers are free (64 bits)
    msg[lastBlock] = ((bitsReadIn & LEFT_HALF_AND) >> SIZE_SHIFT);
    //get the left half of the size
    msg[lastBlock-1] = (bitsReadIn & (LEFT_HALF_AND >> SIZE_SHIFT));
    //get the right half of the size
    needsSize = false; //size has been added
  }
}

//Pre:  
//Post: class is reset as normally would be done, padding is added to
//      the first open location if needed, and size is added if it is
//      needed
void Read512::resetAndPad(){
  for(int index = 0; index < BLOCKS_IN_512; index++){ //for i < 16
    msg[index] = 0; //init to 0
  }
  if (needsSize){ //size needs to be added
    if (needsPadding){ //if padding is still needed
      msg[0] = (int) PAD_VALUE; //set the
      //last byte of the first int = to the pre-pad value
      needsPadding = false; //no longer needs padding
    }
    writeSize(); //now write the size of the message
  }
}

// Pre:  i            == index of next byte to fill
//       curr_integer == index in msg of current integer
//       final_char   == char storage (can be junk)
// Post: If the end of file has been reached, padding and size are
//       either added or marked to be added later
void Read512::endOfFile(int i, int curr_integer, char final_char){
  if (i < CHARS_PER_BLOCK){ //if there's room in the current integer
    final_char = (PAD_VALUE) << (BYTE_SHIFT * i); //shift the value of pad
    //    to the appropriate byte location
    msg[curr_integer] |= final_char; //or it into the value
  }
  else{//needs a new byte in a the next integer
    if (curr_integer+1 < BLOCKS_IN_512){ //if there is another
      //integer available
      msg[curr_integer+1] = (int) PAD_VALUE; //set the
      //next byte = to the pad value
    }
    else{ //there is no room in this 512
      needsPadding = true; //then there was no room
      //for padding so another 512 needs to be used
    }
  }
  needsSize = true; //flag that size needs to be added
  //since the EOF was found
}


//Pre:  in is a well defined input stream reference, which may or
//      may not be at EOF.
//      data_holder is a well defined Read512 reference.
//Post: Returns a reference to the istream object, with 512 bits
//      read out of the stream.
//      Modifies the data_holder reference, so that data_holder.msg
//      holds the correct bits from the input file.
istream& operator>>(istream& in, Read512& data_holder){
  char input_char; //storage for the input character
  //We want Read512 to store the characters "left-to-right", so start
  //high and go low.
  int final_char; //storage for temporary bytes and masking
  for(int curr_integer = 0; //start
      (curr_integer < BLOCKS_IN_512) && (!data_holder.needsSize);  //condition
      curr_integer--){ //step
    input_char = in.get(); //get first char
    //Reset to zero, to remove anything that was there previously
    data_holder.msg[curr_integer] = 0;
    int i; //init storage for counter with larger scope (for case EOF)
    for(i = 0; ((i < CHARS_PER_BLOCK) && (input_char != EOF)); i++){
      final_char = ((int) input_char) << (BYTE_SHIFT * i); //put input into a
      //32 bit integer (padded with 0's) and shifted by corresponding
      //factor of 8
      data_holder.msg[curr_integer] |= final_char; //bitwise or with
      //final character
      cerr << "Char read in: " << input_char << endl;
      data_holder.bitsReadIn += 8; //increment the number of bits read in
      if (i < CHARS_PER_BLOCK-1){ //if not the last loop
	input_char = in.get(); //get next input character
      }
    }
    //SPECIAL CASE CHECK, END OF FILE
    if (input_char == EOF){ //if end of file
      data_holder.endOfFile(i, curr_integer,
			    final_char);
    }
  }
  //ASSERT: data_holder.msg[curr_integer] now holds 32 bits of the
  //message, or we hit the end of the input stream and it holds less
  //than that.
  if (data_holder.doesNeedSize()){ //if size needs to be added to the 512
    data_holder.writeSize(); //pad the current and write the size
  }
}
