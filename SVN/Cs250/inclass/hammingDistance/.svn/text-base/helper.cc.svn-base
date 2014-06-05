#include <iostream>
#include "helper.h"

#define ordZero 48
#define ordNine 57


using namespace std;

// PRE: argc = n is defined; argv[0]..argv[n-1] is
// defined. 
// POST: RV = true iff n = 3 and argv[1] and arg[2]
// (as integers) are natural numbers
bool validArguments(int argc, char * argv[]) {
  bool answer = true;
  if (argc != 3) {
    answer = false;
  }
  else {
    if (!isNaturalNumber (argv[1])) {
      answer = false;
    }
    else {
      if (!isNaturalNumber (argv[2])) {
	answer = false;
      }
    }
  }
  return (answer);
}

// PRE: charNum1 and charNum2 are character
// representations of natural numbers m and n.
// POST: OS contains the binary representations for
// m and n and the hamming distance between m and n.
void computeHammingDistance (char * charNum1,
			     char * charNum2) {
  int num1 = charToNum (charNum1);
  int num2 = charToNum (charNum2);
  // ASSERT: num1 and num2 are the integer
  // representations of charNum1 and charNum2
  // respectively.
 
  int larger = num1;
  if (num2 > num1) {
    larger = num2;
  }
  // ASSERT: larger = max{num1, num2}.
  //         Thus, the number of bits needed for
  //         larger are adequate for num1 and
  //         num2.

  int bitSize = 1;
  if (larger > 0) {
    bitSize = floorLog(larger, 2) + 1;
  }
  int * bitArray1 = getBits (num1, bitSize);
  int * bitArray2 = getBits (num2, bitSize);

  int ham = hammingDistance (bitArray1, bitArray2, 
			     bitSize);

  // ASSERT: ham is the hamming distance between
  // num1 and num2. 

  print (num1, bitArray1, bitSize);
  print (num2, bitArray2, bitSize);
  printHamming (num1, num2, ham);
}

// PRE: num = n > 0 is defined; 
//      base = b > 0 is defined 
// POST: RV = floor (log_b (n)).
int floorLog (int num, int base) {
  int power = 0;
  int raisedPower = 1;
  // ASSERT: raisedPower = base^power
  while (raisedPower <= num) {
    // ASSERT: raisedPower <= num
    raisedPower *= base;
    power++;
    // ASSERT: raisedPower = base^power    
  }
  // ASSERT: raisedPower > num and 
  //         base^(power-1) <= num.
  //         Thus, floor of log_b(n) = power-1.
  return (power-1);
}


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
int * getBits (int num, int bits) {
  // Allocate space for the bit array.
  int * bitArray = new int[bits];
  // initialise the array to all 0.
  int count = 0; //indicates the bit position being computed.
  while (num != 0){
    bitArray[count] = num % 2; //The current index of bitArray is
                               //equal to the remainder of the number
                               //divided by 2
    count++;     //Increment count
    num = num/2; //Divide the number by 2
    //ASSERT: num is still an integer
    //        count < length of bitArray
  }
  return (bitArray);
}

// PRE: bits1 and bits2 are defined and are arrays
// containing the binary representation of numbers where the
// 0-th element of bits1 (and bits2) are the least
// significant bits of those numbers.
// bits = b is defined, and both bits1 and bits2
// have b elements each.
// POST: RV = the hamming distance between the two
// bit arrays bits1 and bits2.
int hammingDistance (int * bits1, int * bits2, 
		     int bits) {
  int index = 0; // the current bit position being 
                 // compared in the two arrays.
  int distance = 0; // current value of the hamming 
                    // distance.
  // ASSERT: distance is the number of bit positions
  //         in which the two arrays differ.
  while (index < bits) {
  // ASSERT: distance is the number of bit positions
  //         up through position index-1
  //         in which the two arrays differ.
    if (bits1[index] != bits2[index]) {
      // The bit arrays differ at position index.
      distance++;
    }
  // ASSERT: distance is the number of bit positions
  //         up through position index
  //         in which the two arrays differ.
    index++;
  }
  // ASSERT: distance is the number of bit positions
  //         in which the two arrays differ.
  return (distance);
}


// PRE: num1, num2 ham are defined.
// POST: OS contains "The Hamming Distance
// between " num1 " and " num2 " is " ham.
void printHamming (int num1, int num2, int ham) {
  cout << "The Hamming Distance between " << num1 
       << " and " << num2 << " is " << ham << endl;
}

// PRE: num = n is defined. bitSize = b > 0 is
// defined. bitNum[0]..bitNum[b-1] is the
// binary representation of n with the 0-th bit
// in the array being the least significant bit
// of the binary representation of n.
// POST: OS contains n and the contents of
// bitNum with the most significant bit to the
// left. 
void print (int num, int * bitNum, int bitSize) {
  cout << num << ": ";
  int index; //initialize the index of the list
  for (index=bitSize-1; index >= 0; index--){ //cycle backwards through
                                             // the array starting at
                                             // the length of the array-1
    cout << bitNum[index]; //print the number at index
  }
  cout << endl;
  // Loop through the bitNum array with the index 
  // variable, say index, starting at bitSize-1 and 
  // counting down to 0, and output bitNum[index].
}


// PRE: charNum is a string.
// POST: RV = true iff charNum is the character
// representation of a natural number.
bool isNaturalNumber(char * charNum){
  //Since response is of arbitrary length, cycle until a terminator
  //node is found
  int index = 0; //Start at the beginning of the array
  bool isNatural = true; //Initialize the pass/fail bool
  int value; //initialize storage for the ord value
  //ASSERT: response has a terminator node since it's a string
  while ((charNum[index] != '\0') && (isNatural)) {
    //ASSERT: response[index] is a valid part of the response
    value = (int) charNum[index];
    if (! (ordZero <= value)&&(value <= ordNine)){
      isNatural = false;
      //If the ord value isn't in the range of ord(0) --> ord(9),
      //then the number is not natural
    }
    index++; //incrementing index, as not to loop indefinitely
  }
  return (isNatural);
}

// PRE: charNum is the character representation of
// a natural number, say n
// POST: RV = n.
int charToNum (char * charNum){
  int index = 0; //Index used to cycle charNum
  int value; //the integer value of the current character
  int result = 0; //the resultant number to be returned
  while (charNum[index] != '\0'){
    value = ((int) charNum[index]) - ordZero; //subtract the ordZero
                                              //in order to shift the
                                              //value into the range
                                              //of 0-9  
    result = result*10 + value;//slowly transition the result as
                               //places are added (adding new least
                               //significant numbers)
    index++; //increment index
  }
  return (result);
}
