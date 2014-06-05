#ifndef included_Fraction
#define included_Fraction

// This is the class declaration.
class Fraction {           // Every class begins with the class
			   // statement. class <class name>
                           // Note that the file name need not be the
                           // same as the class name, although very
                           // often we do retain the same names for
                           // convenience. 

  // Class Invariant (CI): This object is a defined fraction n/d such
  //                       that d > 0. The fraction is reduced.

  // The class invariant is a condition that is true about any objects
  // of that class. Each public member function of the class must
  // ensure that the object satisfies the CI at the end of the function.

 private: 
  int numerator;   // holds the numerator for this Fraction object.
  int denominator; // holds the denominator for this Fraction object.

  // PRE: This object = p/q, q != 0.
  // POST: This object = n/d such that d > 0 and n/d = p/q.
  void fixSign (); // Note that each member function header ends with
                   // a semicolon

  // Note that the above function, fixSign, is a private
  // function. Thus, "clients" of this
  // class, i.e., C++ functions that use objects of this class cannot
  // use this member function. 
 public:
  
  // ======================================== 
  // constructors
  // ======================================== 

  // default constructor
  // PRE: 
  // POST: This object = 0/1 (CI is satisfied)
  Fraction();

  // PRE: pNum (is defined) = n
  // POST: This object = n/1 (CI is satisfied)
  Fraction(int pNum);

  // PRE: pNum = p, pDenom = q != 0.
  // POST: This object = n/d such that d > 0 and n/d = p/q. 
  //       (CI is satisfied)
  Fraction(int pNum, int pDenom);

  // ======================================== 
  //       accessor functions
  // ======================================== 

  // PRE: This object = n/d.
  // POST: RV = n
  int getNumerator () const;
  // NOTE: The reserved word const at the end of the function header
  // indicates to C++ that this member function does not change the
  // implicit parameter for which this member function is called.


  // PRE: This object = n/d
  // POST: RV = d.
  int getDenominator () const;

  // ======================================== 
  // modifier functions
  // ======================================== 

  // PRE: This object = n/d and CI is satisfied. pNum = p
  // POST: This object = p/d. CI is satisfied.
  void setNumerator (int pNum);

  // PRE: This object = n/d and CI is satisfied. pDenom = q != 0
  // POST: This object = a/b = n/q such that b > 0.
  void setDenominator (int pDenom);

  // ======================================== 
  //     operations.
  // ======================================== 


  // FIRST ADD MEMBER FUNCTION

  // PRE: This object = n/d, d > 0. pFract = p/q, q . 0.
  // POST: RV = a/b such that a/b = n/d + p/q and the b > 0.
  Fraction add (const Fraction pFract) const;

  // END OF FIRST ADD MEMBER FUNCTION

 
//   SECOND ADD MEMBER FUNCTION
  // PRE: This object = n/d, d > 0. pFract = p/q, q > 0.
  // POST: This object = a/b such that a/b = n/d + p/q and the b > 0.
  void add2 (const Fraction pFract);

  // Note the difference between the above two member functions. The
  // first one returns a Fraction object and does not modify this
  // fraction object. The second one modifies this Fraction object,
  // i.e., the implicit parameter Fraction object for which this
  // member function was called.

//  END OF SECOND ADD MEMBER FUNCTION


  // ======================================== 
  //     Input/Output
  // ======================================== 

  // PRE: This object = n/d, d > 0.
  // POST: OS contains n/d
  void print () const;

  // Note that although the implementation of this member function
  // will require cout, we do not need to include iostream in this
  // file since, in this case,  there is no reference to cout in the
  // class declaration. 


};  // Note that the class declaration ends with a semicolon.


#endif
