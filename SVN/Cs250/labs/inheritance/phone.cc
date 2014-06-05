#include <iostream>
#include "phone.h"

using namespace std;

// default constructor
phone::phone() {
  cout << "Using phone default constructor" << endl;
  mynum = -1;
  volume = -1;
}

// PRE: number = n is defined.
// POST: This phone object is initialised so that 
//       mynum = n and volume = 0
phone::phone(int number) {
  cout << "Using the second constructor for the phone object" << endl;
  mynum = number;
  volume = 0;
}

// constructor with two parameters
// PRE: number = n and vol = v are defined
// POST: This phone object is initialised so that 
//       mynum = n and volume = v
phone::phone(int number, int vol) {
  cout << "Using phone third constructor" << endl;
  mynum = number; 
  volume = vol;
}

// setters
// PRE: number = n
// POST: This phone object is initialised so that myum = n
void phone::setNumber(int number) {
  mynum = number;
}

// PRE: newvol = v is defined
// POST: The volume for this object is set to v
void phone::setVolume (int newvol) {
  volume = newvol;
}

// PRE: newnum = n is defined.
// POST: OS contains "<mynum> dialing <n>
void phone::dial (int newnum){
  cout << mynum << " dialing " << newnum << endl;
}

// PRE:
// POST: OS contains "<mynum> receiving at volume <volume>"
void phone::receive () {
  cout << mynum << " receiving at volume " << volume << endl;
}
  
// PRE: 
// POST: RV is the volume of this object
int phone::getVolume () {
  return (volume);
}

/*
// destructor
// PRE:
// POST: This phone object is destroyed.
//       OS contains "Phone number <mynum> being destroyed."
phone::~phone() {
  cout << "Phone number " << mynum << " being destroyed." << endl;
}
*/
