#include <iostream>
#include "FractArray.h"
#include "Fraction1.h"
using namespace std;

// PRE:
// POST: An array with DEFAULT_ARRAY_SIZE number of 
//        Fraction objects is constructed. 
//        Each Fraction object in the array is constructed as the 
//        default Fraction object 0/1.
FractArray::FractArray() {
  cout << " Default FractArray constructor " << endl;
  FractList = new Fraction[DEFAULT_ARRAY_SIZE];
  numFractions = DEFAULT_ARRAY_SIZE;
}

// PRE:  pNumFractions = n > 0 is defined.
// POST: An array with n Fraction objects is constructed. 
//        Each Fraction object in the array is constructed as the 
//        default Fraction object 0/1.
FractArray::FractArray(int pNumFractions) {
  cout << " Parametrised FractArray constructor for " 
       << pNumFractions << " Fraction objects." << endl;
  FractList = new Fraction[pNumFractions];
  numFractions = pNumFractions;
}


// PRE: This FractArray object is defined.
// POST: Free the memory allocated for the FractList.
FractArray::~FractArray() {
  cout << "FractArray destructor called " << endl;
  delete (FractList);
  // You could also use
  //  free (FractList); //for memory allocation involving c function malloc
}

