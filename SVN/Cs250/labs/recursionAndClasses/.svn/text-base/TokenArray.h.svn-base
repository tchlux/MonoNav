#ifndef INCLUDED_TokenArray
#define INCLUDED_TokenArray

#include <iostream>
#include "Token.h"

using namespace std;

class TokenArray {
 private:
  
  Token * theTokens; // pointer to the space allocated for the array of
                      // Token objects.
  int currentMax;   // the maximum number of Token objects that can be
		    // currently accommodated in this TokenArray object.
  int currentSize;  // the number of Token objects currently in this
		    // TokenArray object.

  // CI: 
  //     currentMax >= 0. theTokens points to space allocated for
  //       currentMax Token objects.
  //     0 <= currentSize <= currentMax.
  //       theTokens[0]..theTokens[currentSize-1] is
  //       defined.

  // Pre:  A Token class that exists
  //       a pointer to an integer that is the next available index
  // Post: The value of the final equation worked out
  int evaluateHelper(int & next) const;
  
 public:

  // Default constructor
  // PRE:
  // POST: currentMax = 0. currentSize = 0. theTokens is NULL.
  //         CI is satisfied.
  TokenArray ();
  
  // PRE: str is defined and contains a sequence of strings
  //       corresponding to tokens, separated by spaces, and a new
  //       line at the end.
  // POST: This object contains the tokens in str in that order, and
  //       this object satisfies the CI.
  TokenArray (istream & str);

  bool readToken(istream & str);

  // Output member functions
  // PRE: This TokenArray object is defined and satisfies the CI.
  // POST: OS contains a newline followed by the values of currentMax,
  // currentSize and the string values of theTokens objects, separated
  // by spaces, in theTokens followed by a newline. 
  void debugPrint () const;

  // PRE: This TokenArray object is defined and satisfies the CI.
  // POST: OS contains the string values of theTokens objects,
  // separated by spaces.
  void print () const;

  // PRE: str is a defined output stream.
  //      tokens is defined, and satisfies the CI for the TokenArray
  //      objects.
  // POST: str contains the string values of the Token objects in
  //         tokens in order, separated by spaces.
  //       RV is the resulting output stream.
  friend ostream & operator<< (ostream & str, const TokenArray & tokens);

  // Modifiers

  // PRE: This TokenArray object is defined with values 
  //       currentMax = M, currentSize = S, and satisfies the CI.
  //      aToken is defined.
  // POST: currentMax >= S+1.
  //       theTokens[0]..theTokens[S-1] are the same as before.
  //       theTokens[S] = aToken
  //       The result object satisfies the CI.
  void add (const Token & aToken);

  // PRE: This object is defined, and contains a well-formed
  //       expression in prefix notation.
  // POST: RV is the evaluation of the expression in this object.
  int evaluatePre () const;

};

#endif
