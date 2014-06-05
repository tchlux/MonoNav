#include <iostream>

using namespace std;

unsigned int makeMask (int position) {
  // Start with a positive mask at bit position 0.
  unsigned int mask = 1;
  // Now shift the word left to move the 1 to the given position
  mask = mask << position;
  
  return (mask);
}

// Pre:  num is int or uInt, 0 <= pos < 32
// Post: True if the given position has a 1
bool testPosition(unsigned int num, int pos){
  unsigned int mask = makeMask(pos); //make the mask for the pos
  unsigned int final = (mask & num); //get the value of that pos
  return(final != 0); //return if that value was 1
}

// PRE: position1 = i and position2 = j are defined and within the
//        range of the bit positions for a word. i >= j.
// POST: RV is a positive mask for bit positions i through j, both
//         inclusive. 
unsigned int makePositiveMask (int position1, int position2){
  unsigned int mask = 1; //make a 1 bit mask
  int range = position1 - position2; //get the range
  cout << hex;
  for (int i=1; i<=range; i++){ //for every extra bit
    mask = (mask << 1) | 1; //shift the current bits and add one
  }
  mask <<= position2; //shift the mask to the appropriate range 
  return (mask);
}


// PRE: position1 = i and position2 = j are defined and within the
//        range of the bit positions for a word. i >= j.
// POST: RV is a negative mask for bit positions i through j, both
//         inclusive. 
unsigned int makeNegativeMask (int position1, int position2){
  unsigned int mask = makePositiveMask(position1, position2); //make
  //        the positive mask
  mask = ~mask; //negate the mask
  return (mask); //return the negated mask
}

// PRE: given is defined. toInsert is defined. position1 = i is
//      defined. position2 = j is defined. i and j are in the range of
//      bit positions for a word. i >= j.
// POST: RV is the word given with the bits from position i through j,
//        both inclusive, of toInsert inserted into bit positions i
//        through j.
int insertBits(int given, int toInsert, int position1, int position2){
  unsigned int givenMask = makeNegativeMask(position1, position2);
  //get the negative mask for the given number
  unsigned int insertValue = toInsert << position2; //shift insert
  //      value to the correct position
  unsigned int final = (given & givenMask) | insertValue; //get all
  //      values from given except the location for insertion, then
  //      add the insertion values into the gap
  return(final); //return the final pattern
}


// Pre:  optional command line args
// Post: masking tests
int main(int argc, char * argv[]){
  int returnStatus = 0; //normal execution
  unsigned int mask; //mask holder
  int a = 1;
  int b = 2;
  // number 15
  mask = makeMask(0); //make a mask for position 0
  cout << "a & mask:  " << (a & mask) << "\n should be 1\n";
  mask = makeMask(1); //make a mask for position 1
  cout << "a & mask:  " << (a & mask) << "\n should be 0\n";
  cout << "b & mask:  " << (b & mask) << "\n should be 2\n";
  // number 17
  mask = makePositiveMask(2,0);
  cout << "Test mask: " << mask << "\n Should be 7\n";
  mask = makePositiveMask(4,2);
  cout << "Test mask: " << mask << "\n Should be 1c\n";
  // number 18
  mask = makeNegativeMask(2,0);
  cout << "Test mask: " << mask << "\n Should be fffffff8\n";
  mask = makeNegativeMask(4,2);
  cout << "Test mask: " << mask << "\n Should be ffffffe3\n";
  // number 19
  int num;
  num = insertBits(0x1234, 7, 7, 4);
  cout << "Test insert: " << num << "\n   Should be 0x1274\n";

  return (returnStatus);
}
