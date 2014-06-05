#ifndef INCLUDED_helper
#define INCLUDED_helper

// PRE: argc = n is defined; argv[0]..argv[n-1] is
// defined. 
// POST: RV = true iff n = 3 and argv[1] and arg[2]
// (as integers) are natural numbers
bool validArguments(int argc, char * argv[]);

// PRE: charNum1 and charNum2 are character
// representations of natural numbers m and n.
// POST: OS contains the binary representations for
// m and n and the hamming distance between m and n.
void computeHammingDistance (char * charNum1,
			     char * charNum2);

// PRE: charNum is a string.
// POST: RV = true iff charNum is the character
// representation of a natural number.
bool isNaturalNumber (char * charNum);

// PRE: charNum is the character representation of
// a natural number, say n
// POST: RV = n.
int charToNum (char * charNum);

// PRE: num = n > 0 is defined; 
//      base = b > 0 is defined 
// POST: RV = floor (log_b (n)).
int floorLog (int num, int base);

// PRE: num = n is defined. bits = b is defined.
//      Binary representation of n fits in b bits.
// POST: RV is the address of an array containing
//      the bits in the binary representation of n,
//      with the 0-th bit in the array
//      corresponding to the least significant bit
//      of n.
//      The space for the array is dynamically
//      allocated in the function. Thus, the
//      calling function should not assign this
//      to a variable that already has space
//      allocated. 
int * getBits (int num, int bits);

// PRE: bits1 and bits2 are defined and are arrays
// containing 
// the binary representation of numbers where the
// 0-th element of bits1 (and bits2) are the least
// significant bits of those numbers.
// bits = b is defined, and both bits1 and bits2
// have b elements each.
// POST: RV = the hamming distance between the two
// bit arrays bits1 and bits2.
int hammingDistance (int * bits1, int * bits2, 
		     int bits);

// PRE: num = n is defined. bitSize = b > 0 is
// defined. bitNum[0]..bitNum[b-1] is the
// binary representation of n with the 0-th bit
// in the array being the least significant bit
// of the binary representation of n.
// POST: OS contains n and the contents of
// bitNum with the most significant bit to the
// left. 
void print (int num, int * bitNum, int bitSize);

// PRE: num1, num2 ham are defined.
// POST: OS contains "The Hamming Distance
// between " num1 " and " num2 " is " ham.
void printHamming (int num1, int num2, int ham);

#endif
