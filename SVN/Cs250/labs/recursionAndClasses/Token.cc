#include <iostream>
#include "String.h"
#include "Token.h"

using namespace std;

// Constructors
// Default constructor
Token::Token (){}

// PRE: aString is defined and is a valid string value for a token
// POST: This object is defined so that the string value for this
//        object is aString
Token::Token (const String & aString){
  int length = aString.length(); //get the length of the string
  for (int i=0; i<length; i++){
    tokenStr.add(aString.index(i)); //add all the characters
  }
}

//Pre:  A character array that has been defined
//Post: This object is defined so that tokenStr's value is str
Token::Token (char * str){
  int i = 0; //index counter
  while (str[i] != '\0'){
    tokenStr.add(str[i]);
    i++;
  }
}

// PRE: This object is defined and satisfies the CI.
// POST: RV is true iff the token object is an operator.
bool Token::isOperator(){
  char firstToken = tokenStr.index(0); //get the first element of the
                                       // token
  bool answer = false; //storage for bool -- isOperator
  switch(firstToken){
  case '*': //for any of these operators, answer would be set to true
  case '+':
  case '-':answer=true;
  }
  return (answer); //return boolean
}


// PRE: This object is defined, satisfies the CI and is an operator
// POST: RV is the type of operator for this object, i.e., MULT,
//        ADD, or SUB.
int Token::getOperator(){
  char firstToken = tokenStr.index(0); //get the first element of the
                                       // token
  int returnValue; //space for returnValue
  switch(firstToken){
  case '*':returnValue=MULT; //if mult op
    break;
  case '+':returnValue=ADD; //if add op
    break;
  case '-':returnValue=SUB; //if sub op
    break;
  }
  return (returnValue); //return appropriate global integer
}

// PRE: This object is defined, satisfies the CI and is a numeric operand.
// POST: RV is the natural number value for this token.
int Token::getValue(){
  int num = 0; //the final number
  int ind = 0; //index place holder
  char chr = tokenStr.index(ind); //current character
  while (chr != '\0'){
    num = num*10 + ((int) chr - (int) '0'); //shift num and add new least
    // significant num
    ind ++; //increment index
    chr = tokenStr.index(ind); //reestablish current character
  }
  return (num); //return the numerical representation of tokenStr
}

// PRE: str is a defined output stream. aToken is a defined Token
//       object satisfying the CI.
// POST: str contains the string value for this token followed by a
//         space.
//       RV is the resulting output stream.
ostream & operator<<(ostream & str, const Token & aToken){
  str << aToken.tokenStr << " "; //add the current token char array to
  //the ostream with a space, then return
  return str;
}

//Pre:  Destructor
//Post: Destruct
Token::~Token(){
}


// Pre:  
// Post: Print string information
void Token::debugPrint() {
  tokenStr.debugPrint();
}
