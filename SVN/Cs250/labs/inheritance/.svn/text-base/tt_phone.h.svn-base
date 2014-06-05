#ifndef included_tt_phone
#define included_tt_phone

#include "phone.h"

// This object is derived from a phone object.
// In addition to the phone object member data, this object may also
// have a FAX number.
class tt_phone : public phone {

private:
  // Additional data objects beyond the ones in a phone object.
  bool hasFAX;   // true iff this is a FAX phone
  int FAXnumber; // the FAX number for this FAX phone.

public:

  tt_phone();

  // constructor is an extension of the phone constructor that 
  // takes two integer parameters.
  // PRE: number = n and vol = v are defined.
  // POST: This object is initialised so that mynum = n, volume = v 
  //         and hasFAX is false.
  tt_phone(int number, int vol);

  // constructor is an extension of the phone constructor that 
  // takes one integer parameter
  // PRE: number = n
  // POST: This object is initialised so that mynum = n, volume = 0
  //         and hasFAX is false.
  tt_phone(int number);

  // PRE: newnum = n is defined.
  // POST: OS contains "Beep Beep Beep ..." followed by the output of 
  //         the dial function of phone. If this is a FAX phone, the
  //         next line of OS contains "Using FAX number: <FAXnumber>"
  void dial (int newnum);

  // PRE: num = n is defined
  // POST: This object is updated so that hasFAX is true and FAXnumber = n
  void assignFAX (int num);

};

#endif
