#ifndef INCLUDED_icTuple
#define INCLUDED_icTuple

#include <iostream>
#include "Tuple.h"

using namespace std;

class icTuple:  public Tuple<int,char*> {
  //CI:  Each data type is well defined, including comparison
  //     operator.  Comparisons will resort to the first element,
  //     possibly will be upgraded to specify element, addition must
  //     be custom written for purpose

  //========================================
  //           Private methods
  //========================================

  //Pre:  string is defined
  //Post: The length of the character array not including the
  //      terminator node is returned
  int getLength(const char * string) const;

  //Pre:  s1 and s2 are character arrays
  //Post: the combined character array is returned
  char * combine(const char * s1,const char * s2) const;

 public:

  //========================================
  //             Constructors
  //========================================

  //Pre:  
  //Post: Default constructor
  icTuple();

  //Pre:  lData is defined
  //Post: lData is saved to left
  icTuple(int lData);

  //Pre:  rData is defined
  //Post: rData is saved to left
  icTuple(char * rData);

  //Pre:  lData and rData are defined appropriately
  //Post: saved data
  icTuple(int lData, char * rData);

  //Pre:  other is defined and satisfies CI
  //Post: Copy constructor executed
  icTuple(const icTuple & other);

  //========================================
  //             Operators
  //========================================

  //Pre:  other is defined
  //Post: copy of other saved here
  icTuple & operator= (const icTuple & other);

  //Pre:  other is defined
  //Post: bool comparison result
  bool operator> (const icTuple & other) const;

  //Pre:  other is defined
  //Post: bool comparison result
  bool operator< (const icTuple & other) const;

  //Pre:  other is defined
  //Post: bool comparison result
  bool operator<= (const icTuple & other) const;

  //Pre:  other is defined
  //Post: bool comparison result
  bool operator>= (const icTuple & other) const;

  // Pre:  other is defined
  // Post: bool result, c is the only character in right
  bool operator== (const icTuple & other) const;

  // Pre:  c is an ASCII character
  // Post: bool result, c is the only character in right
  bool operator== (char c) const;

  // Pre:  c is an ASCII character
  // Post: bool result, not equals
  bool operator!= (char c) const {return(!((*this)==c));};

  //Pre:  other is defined
  //Post: The addition of other with this is returned
  icTuple & operator+(const icTuple & other) const;

  //Pre:  other is defined
  //Post: The other tuple is added to this
  icTuple & operator+=(const icTuple & other);

  //Pre:  
  //Post: int value is incremented
  icTuple & operator++(int null);

  //========================================
  //               Destructor
  //========================================

  //Pre:  
  //Post: deleted
  ~icTuple();

  // ========================================
  //             Accessors
  // ========================================

  // Pre:  c is defined
  // Post: if c exists in right
  bool in(char c);
};

#endif
