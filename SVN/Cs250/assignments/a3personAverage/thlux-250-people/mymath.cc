#include <iostream>
#include "mymath.h"
#define START_INCREMENT 10
#define INCREMENT_DIVISOR 5.0

using namespace std;


//Pre:  num is a floating point number, either negative or positive
//Post: The positive version of num
float abs(float num){
  if (num < 0){//if num is negative
    num *= -1; //make it positive
  }
  return (num);//return num
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

// Pre:  num > 1, inc > 0
// Post: the square root, accurate to thousandths place
float sqrt(float num, float inc){
  float sqrt = 1; //init sqrt value
  float increment = START_INCREMENT; //initial increment
  while (increment >= inc){
    while (square(sqrt) <= num){ //while 1's place squared is less than
      // number
      sqrt += increment; //increment number
    }
    //ASSERT: sqrt**2 > num
    sqrt -= increment; //go to the number smaller than the square root
    increment /= INCREMENT_DIVISOR; //decrement the increment (hahah)
  }
  return(sqrt-increment); //return final square root (immediately less than
  // the real square root of the value
}

// Pre:  num > 1, inc > 0
// Post: the square root, accurate to given increment
int sqrt(int num, int inc){
  int sqrt = 1; //init sqrt value
  while (square(sqrt) <= num){ //while sqrt squared <= num
    sqrt = sqrt+inc; //increment number
  }
  return(sqrt-inc); //return final square root (immediately less than
  // the real square root of the value
}

// Pre:  A defined floating point number
// Post: The number squared
float square(float num){
  return (num * num); //return number squared
}

// Pre:  A defined integer
// Post: The number squared
int square(int num){
  return (num * num); //return number squared
}
