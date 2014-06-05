#ifndef INCLUDED_Pair
#define INCLUDED_Pair

#include <iostream>

using namespace std;

template <class Type1, class Type2>

class Pair
{
 private:
  Type1 First;
  Type2 Second;

 public:

  // PRE: pFirst is defined = p1, pSecond is defined = p2.
  // POST: This object is (p1, p2)
  Pair(Type1 pFirst, Type2 pSecond)
    {
      First = pFirst;
      Second = pSecond;
    };

  // PRE: This object is defined = (p1, p2)
  // POST: RV = p1
  Type1 getFirst () const {return (First);};
  
  // PRE: This object is defined = (p1, p2)
  // POST: RV = p2
  Type2 getSecond () const {return (Second);};

  // PRE: This object is defined = (p1, p2), pFirst = p3
  // POST: This object is (p3, p2)
  void putFirst (Type1 pFirst) {First = pFirst;};

  // PRE: This object is defined = (p1, p2), pSecond = p3
  // POST: This object is (p1, p3)
  void putSecond (Type2 pSecond) {Second = pSecond;};

  // PRE: This object is defined = (p1, p2), pFirst = p3, pSecond = p4
  // POST: This object is (p3, p4)
  void putPair (Type1 pFirst, Type2 pSecond) 
  {
    First = pFirst;
    Second = pSecond;
  };

  // PRE: This object (implicit parameter) is defined to be (p1, p2).
  //      Pair2 is defined to be (q1, q2).
  // POST: RV is true iff (p1 == q1) and (p2 == q2)
  bool operator == (const Pair<Type1, Type2> Pair2) const
  {
    return ((First == Pair2.First) && (Second == Pair2.Second));
  };

  friend ostream & operator << (ostream & str, const
				Pair<Type1, Type2> pair)
  {
    str << "(" << pair.First << ", " << pair.Second << ")";
    return(str);
  };

};
#endif
