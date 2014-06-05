

//  get_512_bits, possibly padded
//    8 bits at a time (16 integer values total (each is 32 bits)) -->
//    reads right to left per 32

//  already broken into 16 32 bit chunks
//  pull out one integer (32 bits) and run the round on it (based on g)


//FOR 64 ITERATIONS ___________

//  D+B+C -> function + A;
//  M(round specific, one of the 16 integers) + A;
//  K(some integer between 0 and 64, current round number) + A;
//  Cyclic left (round specific);
//  A+B
//  Swap variables (A>B B>C C>D D>A)

// END FOR ______________

// take values of A,B,C,D and add to globals for next 512 bits

//AFTER ALL 512 BLOCKS PROCESSED (including padded)

// the values of A, B, C, and D are the hash code
// translate this value into hex
//    each hex value is litle endian
//    whole 


#include <iostream>
#include "md5Hash.h"

using namespace std;


// Pre:  Can use input file, or prompted input
// Post: hash value for input (whatever user decided)
int main(int argc, char * argv[]){
  int returnCondition = 0; //normal run
  md5Hash final;
  final.makeHash(cin); //pass finalHash.makeHash cin as the form of input
  final.printHash(); //print the final hashed value
  return(returnCondition); //return program state
}
