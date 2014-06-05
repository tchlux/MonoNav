#include <iostream>
#include <fstream>
#include "TokenArray.h"

using namespace std;

//PRE: argv[1] is the name of an input file that contains a well
//      formed prefix expression. The only operators allowed are +, -
//      and *. The only operands allowed are natural numbers. The
//      input file does not contain errors. The operands and the
//      operators are separated by one space. The last operand or
//      operator in the expression is terminated by the end of line
//      character. 
//POST: OS contains the evaluation of the
//      prefix expression in the input file.
int main (int argc, char * argv[]) {
  ifstream inFile((char *) argv[1]); // Open the input file.
  if (inFile != NULL) {
    // ASSERT: The input file could be opened correctly.
    TokenArray expression(inFile); // construct the array of tokens
				   // from the expression in the input
				   // file. 
    cout << "The token array " << expression << endl;
    int answer = expression.evaluatePre();
    cout << "The expression " << expression << " evaluates to: "
	 << answer << endl;
  }
}
