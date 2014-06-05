#include <iostream>

using namespace std;

//Pre:  num is a floating point number, either negative or positive
//Post: The positive version of num
float abs(float num);

// PRE: num = n > 0 is defined; 
//      base = b > 0 is defined 
// POST: RV = floor (log_b (n)).
int floorLog (int num, int base);

// Pre:  num > 1, inc > 0
// Post: the square root, accurate to thousandths place
float sqrt(float num, float inc);

// Pre:  num > 1, inc > 0
// Post: the square root, accurate to given increment
int sqrt(int num, int inc);

// Pre:  A defined floating point number
// Post: The number squared
float square(float num);

// Pre:  A defined integer
// Post: The number squared
int square(int num);
