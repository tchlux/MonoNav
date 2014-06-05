#include <iostream>
#include "String.h"
#include "Token.h"
#include "TokenArray.h"

// Default constructor
// PRE:
// POST: currentMax = 0. currentSize = 0. theTokens is NULL.
//         CI is satisfied.
TokenArray::TokenArray (){
  currentMax = 0; //set currentMax to 0
  currentSize = 0; //set currentSize to 0
}
  
// PRE: str is defined and contains a sequence of strings
//       corresponding to tokens, separated by spaces, and a new
//       line at the end.
// POST: This object contains the tokens in str in that order, and
//       this object satisfies the CI.
TokenArray::TokenArray (istream & str){
  currentMax = 0; //set currentMax to 0
  currentSize = 0; //set currentSize to 0
  String inFile; //storage for everything from inFile before but not
  //               including the new line character
  char chr = str.get();
  while (chr != '\n'){
    inFile.add(chr); //add character to string
    chr = str.get(); //get the line as a character array
  }	       
  int length; //storage for the length of tokens
  char ** tokens = inFile.splitBy(' ', length); //get each token as a character
  //       array
  for (int i=0; i<length; i++){
    Token temp(tokens[i]); //create new temp token
    add (temp); //add each new token to the array
  }  
  currentSize = length; //save the current size
}

// PRE: str is a defined output stream.
//      tokens is defined, and satisfies the CI for the TokenArray
//      objects.
// POST: str contains the string values of the Token objects in
//         tokens in order, separated by spaces.
//       RV is the resulting output stream.
ostream & operator<< (ostream & str, const TokenArray & tokens){
  for (int i=0; i<tokens.currentSize; i++){ //for token in theTokens
    str << tokens.theTokens[i]; //print the token
  }
  return (str);
}

// Modifiers

// PRE: This TokenArray object is defined with values 
//       currentMax = M, currentSize = S, and satisfies the CI.
//      aToken is defined.
// POST: currentMax >= S+1.
//       theTokens[0]..theTokens[S-1] are the same as before.
//       theTokens[S] = aToken
//       The result object satisfies the CI.
void TokenArray::add (const Token & aToken){
  if ((currentMax - currentSize) <= 0){ //if the current array is full
    //       ( '<= 0' is used simply for safety but unnecessary)
    Token * tempTokens = theTokens; //create a temp pointer to the old
    //       tokens
    theTokens = new Token[(currentMax*2)+1]; //create a new arry twice as
    //       large for theTokens
    for (int i=0; i<currentSize; i++){ //Cycle through old tokens
      theTokens[i] = tempTokens[i]; //transfer values to new array
    }
    currentMax = currentMax*2+1; //Double the size of current max
    //    delete [] tempTokens; //Delete old useless array
  }
  theTokens[currentSize] = aToken; //Add new token
  currentSize ++; //increment currenSize
}


// PRE: This object is defined, and contains a well-formed
//       expression in prefix notation.
// POST: RV is the evaluation of the expression in this object.
int TokenArray::evaluatePre () const{
  int next = -1; //next available index
  return (evaluateHelper(next)); //get int value
}

// Pre:  A Token class that exists
//       a pointer to an integer that is the next available index
// Post: The value of the final equation worked out
int TokenArray::evaluateHelper(int & next) const{
  next ++;
  int value; //final value storage
  if (! theTokens[next].isOperator()) { //if it is a number
    value = theTokens[next].getValue(); //get the value of the token
  }
  else{
    int op1, op2; //storage for next two tokens
    int oper; //storage for the operator
    oper = theTokens[next].getOperator(); //get the operator
    op1 = evaluateHelper(next);// get value of left
    op2 = evaluateHelper(next);// get value of right
    switch(oper){ //open switch
    case Token::MULT: //mult operator
      value = op1 * op2; //evaluate
      break;
    case Token::ADD: //add operator
      value = op1 + op2; //evaluate
      break; 
    case Token::SUB: //sub operator
      value = op1 - op2; //evaluate
      break;
    }
  }
  return(value); //return final integer value
}

// Output member functions
// PRE: This TokenArray object is defined and satisfies the CI.
// POST: OS contains a newline followed by the values of currentMax,
// currentSize and the string values of theTokens objects, separated
// by spaces, in theTokens followed by a newline. 
void TokenArray::debugPrint () const{
  cout << "\ncurrentMax: " << currentMax << "\ncurrentSize: "
       << currentSize << endl;
  for (int i=0; i<currentSize; i++){ //for token in theToken
    cout << theTokens[i]; //print the token
  }
}

// PRE: This TokenArray object is defined and satisfies the CI.
// POST: OS contains the string values of theTokens objects,
// separated by spaces.
void TokenArray::print() const{
  for (int i=0; i<currentSize; i++){ //for token in theTokens
    cout << theTokens[i]; //print the token
  }
}

