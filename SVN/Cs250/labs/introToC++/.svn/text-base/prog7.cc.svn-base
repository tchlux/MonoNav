#include <iostream>

using namespace std;

#include "help7.h"   // include the function declarations necessary
		     // for this program.  

// PRE: input stream (IS) contains two integers, x and y.
// POST: (OS) contains prompts for the user to enter two numbers, and
//       then the string "Minimum = " followed by the smaller
//       of the two numbers x and y, that the user enters.
int main (int argc, char * argv[]) {

  // declare variables to hold the two numbers.
  int num1; 
  int num2;

  // ASSERT: num1 is declared, but undefined.
  //         num2 is declared, but undefined.

  // ASSERT: IS contains x and y
  num1 = getNum ("Enter a number: ");
  // ASSERT: OS contains prompt for one number.
  //         num1 = x

  //         IS contains y
  num2 = getNum ("Enter a second number: ");
  // ASSERT: OS contains prompt for a second number.
  //         num2 = y

  // declare a variable to hold the value of the minimum.
  int minNum; 
  // ASSERT: minNum is declared, but undefined.

  minNum = getMin (num1, num2);
  // ASSERT: minNum = the smaller of x and y.
  
  cout << "Minimum = " << minNum << endl;
  // ASSERT: OS contains "Minimum =" followed by the smaller of x and y.

  
  return (0);

}


