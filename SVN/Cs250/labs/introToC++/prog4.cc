#include <iostream>

using namespace std;

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
  cout << "Enter a number: ";
  cin >> num1;
  // ASSERT: OS contains prompt for one number.
  //         num1 = x
  //         IS contains y

  cout << "Enter a second number: ";
  cin >> num2;
  // ASSERT: OS contains prompt for a second number.
  //         num2 = y

  // declare a variable to hold the value of the minimum.
  int minNum; 
  // ASSERT: minNum is declared, but undefined.

  if (num1 < num2) {
    minNum = num1;
  }
  else {
    minNum = num2;
  }
  // ASSERT: minNum = the smaller of x and y.
  
  cout << "Minimum = " << minNum << endl;
  // ASSERT: OS contains "Minimum =" followed by the smaller of x and y.

  
  return (0);

}
