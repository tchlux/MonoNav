#include <iostream>
#include "phone.h"
#include "tt_phone.h"

using namespace std;

tt_phone::tt_phone() {
  cout << "Using tt_phone default constructor" << endl;
  mynum = -2;
  hasFAX = false;
}

// constructor is an extension of the phone constructor that 
// takes two integer parameters.
// PRE: number = n and vol = v are defined.
// POST: This object is initialised so that mynum = n, volume = v 
//         and hasFAX is false.
tt_phone::tt_phone(int number, int vol) : phone(number, vol) {
  cout << "Using tt_phone third constructor" << endl;
  hasFAX = false;
}

// constructor is an extension of the phone constructor that 
// takes one integer parameter
// PRE: number = n
// POST: This object is initialised so that mynum = n, volume = 0
//         and hasFAX is false.
tt_phone::tt_phone(int number) : phone(number) {
  cout << "Using tt_phone second constructor" << endl;
  hasFAX = false;
}

// PRE: newnum = n is defined.
// POST: OS contains "Beep Beep Beep ..." followed by the output of 
//         the dial function of phone. If this is a FAX phone, the
//         next line of OS contains "Using FAX number: <FAXnumber>"
void tt_phone::dial (int newnum) {
  cout << "Beep Beep Beep ... "; 
  phone::dial(newnum);
  if (hasFAX) {
    cout << "Using FAX number: " << FAXnumber << endl;
  }
}

// PRE: num = n is defined
// POST: This object is updated so that hasFAX is true and FAXnumber = n
void tt_phone::assignFAX (int num) {
  hasFAX = true;
  FAXnumber = num;
}
