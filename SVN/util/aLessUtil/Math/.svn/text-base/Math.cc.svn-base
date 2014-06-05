#include <iostream>
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

// Pre:  0 < num, 0 < precision
// Post: The approximate square root of num to a set digit accuracy
float sqrt(float num, float precision){
  bool flipped = num < 1.0; // if less than one, needs to be flipped
  if (flipped) num = 1 / num; // Make the number > 1
  float last = 1.0;  float guess = 2.0;
  float diff = (num-guess*guess);
  while ( diff*diff > precision){
    if (guess*guess < num){
      last = guess;
      guess = (guess+num)/2;
    }
    else
      guess = (guess+last)/2;
    diff = (num-guess*guess);
  }
  if (flipped) guess = 1 / guess; // flip back if necessary
  return(guess);
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

// Pre:  number and the power to raise it to
// Post: the number to that power
int power(int num, int power){
  if (power == 0){
    num = 1;
  }
  for (int i=0; i<power; i++){
    num *= num;
  }
  return (num);
}
