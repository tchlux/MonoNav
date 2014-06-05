#include <iostream>

using namespace std;

typedef float f;
typedef int i;

//Pre:  num is a floating point number, either negative or positive
//Post: The positive version of num
f abs(f num){
  if (num < 0){//if num is negative
    num *= -1; //make it positive
  }
  return (num);//return num  
};

// Pre:  num is defined
// Post: positive version of num
i abs(i num){
  if (num < 0){
    num *= -1;
  }
  return(num);
}

// PRE: num = n > 0 is defined; 
//      base = b > 0 is defined 
// POST: RV = floor (log_b (n)).
i floorLog (i num, i base){
  i power = 0;
  i raisedPower = 1;
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
};

// Pre:  0 < num, 0 < precision
// Post: The approximate square root of num to a set digit accuracy
float sqrt(float num, float precision);

// Pre:  num > 1, inc > 0
// Post: the square root, accurate to given increment
i sqrt(i num){
  i test = 1;
  while (square(test) < num){
    test ++;
  }
  return(test-1);
};

// Pre:  A defined floating point number
// Post: The number squared
f square(f num){
  
};

// Pre:  A defined integer
// Post: The number squared
i square(i num){
  
};

// Pre:  number and the power to raise it to
// Post: the number to that power
i power(i num, i power){
  
};
