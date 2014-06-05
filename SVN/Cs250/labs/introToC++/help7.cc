#include <iostream>

using namespace std;

#include "help7.h"    // include the correcponding function declarations.

// PRE: IS contains an integer x
//      prompt is defined.
// POST: OS contains prompt.
//       Return value (RV) is x
int getNum (char * prompt) {
  // Declare an integer variable to hold the user number
  int tempNum;
  // ASSERT: tempNum is declared, but undefined.
  
  cout << prompt;
  // OS contains the value of prompt
  // IS contains x
  cin >> tempNum;
  // ASSERT: tempNum = x

  return (tempNum);
}

// PRE: x and y are defined
// POST: RV is the smaller of the two values x and y.
int getMin (int x, int y) {
  // Declare an integer variable to hold the minimum value.
  int answer;
  // ASSERT: answer is declared, but undefined.

  if (x < y) {
    answer = x;
  }
  else {
    answer = y;
  }
  // ASSERT: answer is defined to be the smaller of the two numbers x and y. 
  
  return (answer);
}
