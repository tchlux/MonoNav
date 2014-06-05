#ifndef INCLUDED_intList
#define INCLUDED_intList

#include <iostream>      // Since we are using the type ostream.
#include "intNode.h"     // Since we are using the intNode class here.

using namespace std;

class intList {

  // Class Invariant (CI): This object contains a defined pointer f
  // that points to the first intNode, if any, in this linked list
  // object. n is defined and contains the number of intNode objects
  // in this linked list object. 

 private:
  intNode * front;             // stores the pointer to the first
			       // intNode in the linked list. This
			       // intNode will also be called the
			       // front of the linked list.
                               // denoted by f.
  int numItems;                // stores the number of items in the
			       // linked list.
                               // denoted by n.

  // NOTE: We will sometimes also refer to the elements of the list as
  // f(0), f(1),..., f(n-1), where f(0) is the intNode at the front of
  // the list.

 public:
  
  // ======================================== 
  // constructors
  // ======================================== 

  // default constructor
  // PRE: 
  // POST: This object is defined with f = NULL and n = 0.
  intList();


  /* COMMENTED OUT COPY CONSTRUCTOR
  // copy constructor
  // PRE: L is defined.
  // POST: This object is defined and is a deep copy of L.
  //       Thus, f = L.f, with all the intNodes in f being physically
  //         distinct from the intNodes of L.
  //       n = L.n
  //       Note here that L is being passed by reference to avoid the
  //        shallow copy of the actual parameter being passed as L. We
  //        indicate that L does not change with the keyword const.
  intList(const intList & L);
  END OF COPY CONSTRUCTOR COMMENT */

  /* COMMENTED OUT ASSIGNMENT OPERATOR
  // PRE: L is defined.
  // POST: This object is defined and is a deep copy of L.
  //       Thus, f = L.f, with all the intNodes in f being physically
  //         distinct from the intNodes of L.
  //       n = L.n
  //       Note here that L is being passed by reference to avoid the
  //        shallow copy of the actual parameter being passed as L. We
  //        indicate that L does not change with the keyword const.
  intList & operator= (const intList & L);
  END OF ASSIGNMENT COMMENT */


  // ======================================== 
  // destructor
  // ======================================== 
  
  // PRE: This object is defined.
  // POST: This object has no elements. f = NULL and n = 0.
  //       All space allocated for this object is deallocated.
  ~intList();


  // ======================================== 
  //       accessor functions
  // ======================================== 

  // PRE: This object is defined.
  // POST: RV = n.
  int getSize () const;

  // PRE: This object is defined and n > 0.
  // POST: RV = the integer stored in f(0).
  int getFront () const;

  // PRE: N is defined. This object is defined and n > N.
  // POST: RV = the integer stored in the f(N).
  int getNth (int N) const;

  // ======================================== 
  // modifier functions
  // ======================================== 

  // PRE: num = v is defined. This object is defined.
  // POST: This object is defined with n = (pre)n + 1. An intNode
  //       object t contains the integer data v.
  //       f = t, (pre)f(0),(pre)f(1),...,(pre)f((pre)n).
  //       NOTE: (pre) is an informal mechanism of referring to the
  //             state of the variable in the PRE state of the function.
  void addFront (int num);

  // PRE: This object is defined. n > 0.
  // POST: This object is defined and n = (pre)n - 1. 
  //       f = (pre)f(1), (pre)f(2),..., (pre)f((pre)n-2).
  void deleteFront ();

  // PRE: N is defined. This object is defined. n > N.
  // POST: This object is defined and n = (pre)n - 1.
  //       f = (pre)f(0),...,(pre)f(N-1),(pre)f(N+1),...,(pre)f((pre)n - 2).
  void deleteNth (int N);

  // ======================================== 
  //     Input/Output
  // ======================================== 

  // PRE: L is defined.
  // POST: str contains L.f(0),...,L.f(L.n-1).
  //       NOTE: Here L.f refers to the elements of the intList object L.
  friend ostream & operator<< (ostream & str, const intList L);

};
#endif
