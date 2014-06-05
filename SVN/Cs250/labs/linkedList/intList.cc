#include <iostream>
#include "intNode.h"
#include "intList.h"

using namespace std;

// ======================================== 
// constructors
// ======================================== 

// default constructor
// PRE: 
// POST: This object is defined with f = NULL and n = 0.
intList::intList() {
  front = NULL;
  numItems = 0;
};



// copy constructor
// PRE: L is defined.
// POST: This object is defined and is a deep copy of L.
//       Thus, f = L.f, with all the intNodes in f being physically
//         distinct from the intNodes of L.
//       n = L.n
//       Note here that L is being passed by reference to avoid the
//        shallow copy of the actual parameter being passed as L. We
//        indicate that L does not change with the keyword const.
intList::intList(const intList & L) {
  cout << "Entering the copy constructor" << endl;
  front = NULL;
  numItems = 0;
  for (int index = L.numItems-1; index >= 0; index--) {
    addFront (L.getNth(index));
    // ASSERT: f = L.f(index),L.f(index+1),...,L.f(L.n-1)
    //         n = (L.n-1) - index + 1.
  }
  // ASSERT: f = L.f(0),...,L.f(L.n-1).
  //         n = L.n.
}




// PRE: L is defined.
// POST: This object is defined and is a deep copy of L.
//       Thus, f = L.f, with all the intNodes in f being physically
//         distinct from the intNodes of L.
//       n = L.n
//       Note here that L is being passed by reference to avoid the
//        shallow copy of the actual parameter being passed as L. We
//        indicate that L does not change with the keyword const.
intList & intList::operator= (const intList & L) {
  for (int index = L.numItems-1; index >= 0; index--) {
    addFront (L.getNth(index));
    // ASSERT: f = L.f(index),L.f(index+1),...,L.f(L.n-1)
    //         n = (L.n-1) - index + 1.
  }
  // ASSERT: f = L.f(0),...,L.f(L.n-1).
  //         n = L.n.
  return (*this);
}


// ======================================== 
// destructor
// ======================================== 

// PRE: This object is defined.
// POST: This object has no elements. f = NULL and n = 0.
//       All space allocated for this object is deallocated.
intList::~intList() {
  cerr << " Destructor called " << endl;
  for (int index = 0; index < numItems; index++) {
    deleteFront ();
    // ASSERT: f = (pre)f(index), (pre)f(index+1), ..., (pre)f(n-1)
  }
  // ASSERT: f is empty.
  numItems = 0;
  front = NULL;
}


/* COMMENTED OUT ALTERNATE DESTRUCTOR
// ======================================== 
// destructor
// ======================================== 

// PRE: This object is defined.
// POST: This object has no elements. f = NULL and n = 0.
//       All space allocated for this object is deallocated.
intList::~intList() {
   numItems = 0;
   delete (front);
   front = NULL;
}
  END OF ALTERNATE DESTRUCTOR COMMENT */


// ======================================== 
//       accessor functions
// ======================================== 

// PRE: This object is defined.
// POST: RV = n.
int intList::getSize () const {
  return (numItems);
}

// PRE: This object is defined and n > 0.
// POST: RV = the integer stored in f(0).
int intList::getFront () const {
  return (front->getData());
}

// PRE: N is defined. This object is defined and n > N.
// POST: RV = the integer stored in the node f(N).
int intList::getNth (int N) const {
  int count = 0;
  intNode * temp = front;  // temp is an alias for front.
  // ASSERT: temp points to the node f(0).
  while (count < N) {
    temp = temp->getNext(); 
    count++;
    // ASSERT: temp points to the node f(count).
  }
  // ASSERT: count = N. Therefore, temp points to the node f(N).
  return (temp->getData());
}

// ======================================== 
// modifier functions
// ======================================== 

// PRE: num = v is defined. This object is defined.
// POST: This object is defined with n = (pre)n + 1. An intNode
//       object t contains the integer data v.
//       f = t, (pre)f(0),(pre)f(1),...,(pre)f((pre)n).
//       NOTE: (pre) is an informal mechanism of referring to the
//             state of the variable in the PRE state of the function.
void intList::addFront (int num){
  intNode * tempNode = new intNode (num);
  // ASSERT: tempnode points to inNode object t containing v.
  tempNode->setNext (front);
  // ASSERT: The data object next in t points to f(0).
  front = tempNode;
  // ASSERT: This object has its first node as t.
  //         Thus, f = t, (pre)f(0),...,(pre)f(n).
  numItems++;
  // ASSERT: numItems = number of elements in this list object.
  //         Thus, f = t, (pre)f(0),...,(pre)f((pre)n)

}

// PRE: This object is defined. n > 0.
// POST: This object is defined and n = (pre)n - 1. 
//       f = (pre)f(1), (pre)f(2),..., (pre)f((pre)n-2).
void intList::deleteFront () {
  intNode * temp = front; // temp is an alias for the first node in this list. 
  front = front->getNext(); 
  // ASSERT: f = (pre)f(1),...,(pre)f(n-1).
  numItems--;
  // ASSERT: f = (pre)f(1),...,(pre)f((pre)n-2).
  delete (temp); // deallocate storage for the deleted node.
}

// PRE: N is defined. This object is defined. n > N.
// POST: This object is defined and n = (pre)n - 1.
//       f = (pre)f(0),...,(pre)f(N-1),(pre)f(N+1),...,(pre)f((pre)n - 2).
void deleteNth (int N) {

}

// ======================================== 
//     Input/Output
// ======================================== 

// PRE: L is defined.
// POST: str contains L.f(0),...,L.f(L.n-1).
//       NOTE: Here L.f refers to the elements of the intList object L.
ostream & operator<< (ostream & str, const intList L) {
  cerr << "L has " << L.numItems << " elements." << endl;
  
  for (int index = 0; index < L.numItems; index++) {
    str << L.getNth(index) << ", ";
    // ASSERT: str contains L.f(0), L.f(1), ..., L.f(index),
  }
  str << endl;
  return (str);  // The stream is modified by thie operation. So, we
		 // need to return the modified stream.
}
