#include <iostream>
#include "Fraction1.h"

using namespace std;

// PRE: msg is defined. pFract is defined.
// POST: OS contains msg followed by the value of pFract.
void printFraction (char msg[], Fraction pFract) {
  cout << msg;
  pFract.print();
  cout << endl;
}

// PRE:
// POST: Demonstrates use of the Fraction class.
int main () {
  Fraction f1;  // create a new default fraction. The default
		// constructor for the Fraction object is used to
		// construct this object.
  // ASSERT: f1 = 0/1

  Fraction f2 (3); // create a fraction from an integer. The second
		   // constructor for Fraction objects, i.e., the one
		   // that takes one integer as a formal parameter, is
		   // used to construct this object.
  // ASSERT: f2 = 3/1

  Fraction f3 (3, 5); // create a fraction giving it a numerator and a
		      // denominator, where the denominator is not
		      // zero. The third
       		      // constructor for Fraction objects, i.e., the one
		      // that takes two integers as formal parameters, is
		      // used to construct this object.
  // ASSERT: f3 = 3/5
  
  Fraction f4 (-4, -5); // create another fraction object.
  // ASSERT: f4 = -4/-5 = 4/5.

  // NOTE: We cast the explicit string being passed as an actual
  // parameter to the printFraction function since the formal
  // parameter is of the type char * (or a character array as
  // declared). Try removing the cast to (char *) inone of the
  // printFraction calls below and see the messages you get from the
  // compiler. 
  printFraction((char *)"Fraction 1: ", f1);
  printFraction((char *)"Fraction 2: ", f2);
  printFraction((char *)"Fraction 3: ", f3);
  printFraction((char *)"Fraction 4: ", f4);


  Fraction result1 = f1.add(f2);  // Add fraction f2 to fraction f1 by
				  // calling the member function for
				  // the object f1. f1 is called the
				  // implicit parameter to add and f2
				  // is the explicit parameter.

  // ************************************************************
  // NOTE: Member functions of classes are _always_ called for
  // some objects of that class, i.e., they must have an implicit
  // parameter. 
  // ************************************************************

  Fraction result2 = f2.add(f1);

  Fraction result3 = f3.add(f4);

  // USING THE SECOND ADD member function.
  f3.add2(f4);                     // This modifies the object f3.
  

  printFraction ((char *)"Result 1: ", result1);
  printFraction ((char *)"Result 2: ", result2);
  printFraction ((char *)"Result 3: ", result3);

  // USING THE SECOND ADD member function.
  printFraction ((char *)"Modified fraction 3: ", f3);
  

  return (0);
}
