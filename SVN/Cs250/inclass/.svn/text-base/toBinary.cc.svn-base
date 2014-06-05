#include <iostream>
#include "String.h"

using namespace std;

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

// Pre:  
// Post: The binary representation of the given sequences are returned
int main(){
  cout << "Welcome to the binary converter\n Type \"exit\" to quit\n";
  String exit("exit"); //string used for exiting comparison
  String response; //init storage for response
  cin >> response; //get user input
  int bitSize = 1;
  if (larger > 0) {
    bitSize = floorLog(larger, 2) + 1;
  }
  int * bitArray1 = getBits (num1, bitSize);
  int * bitArray2 = getBits (num2, bitSize);
  while (!(response==exit)) {
    
  }
