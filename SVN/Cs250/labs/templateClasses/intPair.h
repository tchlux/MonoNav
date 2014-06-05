#ifndef included_intPair
#define included_intPair

class intPair
{
private:
  int First;
  int Second;

public:
  // Constructors

  //PRE:
  //POST: This object is defined to be (0, 0).
  intPair(){First = Second = 0;};

  // PRE: pFirst is defined = p1, pSecond is defined = p2.
  // POST: This object is (p1, p2)
  intPair(int pFirst, int pSecond)
    {
      First = pFirst;
      Second = pSecond;
    };

  // PRE: This object is defined = (p1, p2)
  // POST: RV = p1
  int getFirst () const {return (First);};
  
  // PRE: This object is defined = (p1, p2)
  // POST: RV = p2
  int getSecond () const {return (Second);};

  // PRE: This object is defined = (p1, p2), pFirst = p3
  // POST: This object is (p3, p2)
  void putFirst (int pFirst) {First = pFirst;};

  // PRE: This object is defined = (p1, p2), pSecond = p3
  // POST: This object is (p1, p3)
  void putSecond (int pSecond) {Second = pSecond;};

  // PRE: This object is defined = (p1, p2), pFirst = p3, pSecond = p4
  // POST: This object is (p3, p4)
  void putPair (int pFirst, int pSecond) 
    {
      First = pFirst;
      Second = pSecond;
    };

  // PRE: This object (implicit parameter) is defined to be (p1, p2).
  //      Pair2 is defined to be (q1, q2).
  // POST: RV is true iff (p1 == q1) and (p2 == q2)
  bool operator == (const intPair Pair2) const
  {
    return ((First == Pair2.First) && (Second == Pair2.Second));
  }

};

#endif
