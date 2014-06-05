#include <iostream>
#include "FractArray.h"
#include "Fraction1.h"
using namespace std;

// PRE:
// POST: Create a local FractArray object with default size.
void makeFractArray () {
  FractArray oneList;
}

// PRE:
// POST: Create a local FractArray object with pNumFractions 
//        Fraction objects.
void makeFractArray (int pNumFractions) {
  FractArray oneList(pNumFractions);
}

int main () {
  int temp; // to read in just for a pause.

  cout << "Check memory usage before arrays are built." << endl;
  cin >> temp; // program pauses here, so that you can check memory size.

  makeFractArray (); // create one FractArray of the default size
  cout << "Check memory usage after one array has been built." << endl;
  cin >> temp; // program pauses here, so that you can check memory size.

  makeFractArray (5000); // make 5000 Fraction objects.
  cout << "Check memory usage after array size 5000 was made." << endl;
  cin >> temp; // program pauses here, so that you can check memory size.

  // Create 100 instances of local FractArray objects, each with 10000
  // Fraction objects.
  for (int i = 0; i < 100; i++) {
    makeFractArray (10000); 
  }
  cout 
    << "Check memory after 100 arrays of size 10000 have been made." 
    << endl;
  cin >> temp; // program pauses here, so that you can check memory size.

}
