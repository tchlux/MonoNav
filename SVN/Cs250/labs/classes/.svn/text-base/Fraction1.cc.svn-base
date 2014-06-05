// This is the implementation of the Fraction class.

#include "Fraction.h"       // need to include the class declaration

#include <iostream>          // we need to include this for the print
			     // member function.
using namespace std;
			     // in the class implementation file.
// PRE: This object = p/q, q != 0.
// POST: This object = n/d such that d > 0 and n/d = p/q.
void Fraction::fixSign () {  // The Fraction:: indicates that this is
                             // a member function of the Fraction
                             // class.
                             // Note that this prefix is required only
                             // in the implementation (.cc file) of
                             // the class, not the class declaration
                             // (.h file)

  if (denominator < 0) {
    // ASSERT: q < 0.
    numerator = -1 * numerator;
    denominator = -1 * denominator;
    // ASSERT: This object = n/d such that n = -p and d = -q.
    //         Therefore, n/d = p/q, and d > 0.
  }
  // ASSERT: This object = n/d = p/q, such that d > 0.
}
  
// constructors       // Note that the constructors have the same name
                      // as the class and so do not need the
                      // Fraction:: prefix.

// default constructor
// PRE: 
// POST: This object = 0/1 (CI is satisfied)
Fraction::Fraction() {
  numerator = 0;
  denominator = 1;
  // ASSERT: This object = 0/1. Thus, CI is satisfied.
}

// PRE: pNum (is defined) = n
// POST: This object = n/1 (CI is satisfied)
Fraction::Fraction(int pNum) {
  numerator = pNum;
  denominator = 1;
  // ASSERT: This object = n/1. Thus, CI is satisfied.    
}

// PRE: pNum = p, pDenom = q != 0.
// POST: This object = n/d such that d > 0 and n/d = p/q. 
//       (CI is satisfied)
Fraction::Fraction(int pNum, int pDenom) {
  numerator = pNum;
  denominator = pDenom;
  // ASSERT: This object = p/q, q != 0
  fixSign ();
  // ASSERT: This object = n/d such that d > 0 and n/d = p/q.
  //         Thus, CI is satisfied.
      
}

// ======================================== 
//       accessor functions
// ======================================== 

// PRE: This object = n/d.
// POST: RV = n
int Fraction::getNumerator () const {
  return (numerator);
}

// PRE: This object = n/d
// POST: RV = d.
int Fraction::getDenominator () const {
  return (denominator);
}

// ======================================== 
// modifier functions
// ======================================== 

// PRE: This object = n/d and CI is satisfied. pNum = p
// POST: This object = p/d. CI is satisfied.
void Fraction::setNumerator (int pNum) {
  // d > 0.
  numerator = pNum;
  // This object = p/d, and d > 0. Thus, CI is satisfied.
}

// PRE: This object = n/d and CI is satisfied. pDenom = q != 0
// POST: This object = a/b = n/q such that b > 0.
void Fraction::setDenominator (int pDenom) {
  denominator = pDenom;
  // This object = n/q, q != 0.
  fixSign ();
  // ASSERT: This object = a/b such that b > 0 and a/b = n/q.
  //         Thus, CI is satisfied.
}


// FIRST ADD MEMBER FUNCTION

// PRE: This object = n/d, d > 0. pFract = p/q, q > 0.
// POST: RV = a/b such that a/b = n/d + p/q and the b > 0.
Fraction Fraction::add (const Fraction pFract) const {
  // cout << "Using the first add" << endl;
  Fraction answer;   // create a new default fraction object.
  answer.numerator = numerator * pFract.denominator +
    denominator * pFract.numerator;
  // ASSERT: answer.numerator = n*q + d*p.
  answer.denominator = denominator * pFract.denominator;
  // ASSERT: answer.denominator = d*q > 0 (since d > 0 and q > 0.
  // ASSERT: Therefore, answer = n/d + p/q and answer satisfies the
  //         CI.
  return (answer);
}

// END OF FIRST ADD MEMBER FUNCTION


 
//   SECOND ADD MEMBER FUNCTION

// PRE: This object = n/d, d > 0. pFract = p/q, q > 0.
// POST: This object = a/b such that a/b = n/d + p/q and the b > 0.
void Fraction::add2 (const Fraction pFract) {
  // cout << "Using the second add" << endl;
  int tempNum = numerator * pFract.denominator +
    denominator * pFract.numerator;
  // ASSERT: tempNum = n*q + d*p.
  int tempDenom = denominator * pFract.denominator;
  // ASSERT: tempDenom = d*q > 0 (since d > 0 and q > 0.
  
  numerator = tempNum;
  denominator = tempDenom;
  // ASSERT: Therefore, this object = n/d + p/q and satisfies the
  //         CI.
}

//  END OF SECOND ADD MEMBER FUNCTION


// PRE: This object = n/d, d > 0.
// POST: OS contains n/d
void Fraction::print () const {
  cout << numerator << "/" << denominator;
}
