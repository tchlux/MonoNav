#ifndef INCLUDED_Token
#define INCLUDED_Token

#include <iostream>
#include "String.h"

using namespace std;

class Token {
 private:
  String tokenStr; // the string value of this token

  // CI:
  //  tokenStr is defined and is a valid operator or numeric operand.
 public:
  static const int MULT = 0; // the constant denoting the multiplication operator. 
  static const int ADD = 1; // the constant denoting the addition operator. 
  static const int SUB = 2; // the constant denoting the subtraction operator. 
  // In clients of this class, these constants can be accessed as
  // Token::MULT, Token::ADD and Token::SUB. 
  // The static prefix in the above declarations indicates to C++ that
  // these are not member data objects of each Token object, but there
  // is only one instance of each of these objects that is shared by
  // all Token objects.

  // Constructors
  // Default constructor
  Token ();
  
  // PRE: aString is defined and is a valid string value for a token
  // POST: This object is defined so that the string value for this
  //        object is aString
  Token (const String & aString);

  //Pre:  A character array that has been defined
  //Post: This object is defined so that tokenStr's value is str
  Token (char * str);

  // Predicates
  
  // PRE: This object is defined and satisfies the CI.
  // POST: RV is true iff the token object is an operator.
  bool isOperator();

  // Properties

  // PRE: This object is defined, satisfies the CI and is an operator
  // POST: RV is the type of operator for this object, i.e., MULT,
  //        ADD, or SUB.
  int getOperator();

  // PRE: This object is defined, satisfies the CI and is a numeric operand.
  // POST: RV is the natural number value for this token.
  int getValue();

  // Input/Output

  // PRE: str is a defined output stream. aToken is a defined Token
  //       object satisfying the CI.
  // POST: str contains the string value for this token followed by a
  //         space.
  //       RV is the resulting output stream.
  friend ostream & operator<<(ostream & str, const Token & aToken);

  //Pre:  Destructor
  //Post: Destruct
  ~Token();

  // Pre:  
  // Post: Print string information
  void debugPrint();

};

#endif
