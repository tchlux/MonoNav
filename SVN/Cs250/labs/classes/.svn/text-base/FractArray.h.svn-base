#ifndef INCLUDED_FractArray
#define INCLUDED_FractArray

#include "Fraction1.h"
#define DEFAULT_ARRAY_SIZE 10

class FractArray {

 private:
  Fraction * FractList; // Reference to a Fraction object. In this 
                        // object, this reference will point to
                        // an array of Fraction objects.
  int numFractions;     // number of Fraction objects in this object.

 public:
  /*
    Constructors
  */

  // PRE:
  // POST: An array with DEFAULT_ARRAY_SIZE number of 
  //        Fraction objects is constructed. 
  //        Each Fraction object in the array is constructed as the 
  //        default Fraction object 0/1.
  FractArray();

  // PRE:  pNumFractions = n > 0 is defined.
  // POST: An array with n Fraction objects is constructed. 
  //        Each Fraction object in the array is constructed as the 
  //        default Fraction object 0/1.
  FractArray(int pNumFractions);



  //
  //  Destructor
  //
  
  // PRE: This FractArray object is defined.
  // POST: Free the memory allocated for the FractList.
  ~FractArray();



};

#endif
