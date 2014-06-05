#include <iostream>    // Here we need to include this only for the
		       // definition of NULL.
#include "intNode.h"

using namespace std;

// ======================================== 
// constructors
// ======================================== 

// default constructor
// PRE: 
// POST: This object is defined with n = 0 and p = NULL.
intNode::intNode () {
  data = 0;
  nextItem = NULL;
}

// PRE: num = v is defined.
// POST: This object is defined with n = v, and p = NULL.
intNode::intNode (int num) {
  data = num;
  nextItem = NULL;
}


// ======================================== 
//       accessor functions
// ======================================== 

// PRE: This object is defined.
// POST: RV = n.
int intNode::getData () const {
  return (data);
}

// PRE: This object is defined.
// POST: RV = p.
intNode * intNode::getNext () const {
  return (nextItem);
}

// ======================================== 
// modifier functions
// ======================================== 

// PRE: This object is defined. num = v is defined.
// POST: This object is defined and n = v.
void intNode::setData (int num) {
  data = num;
}

// PRE: This object is defined. next = x is defined.
// POST: This object is defined and p = x.
void intNode::setNext (intNode * next) {
  nextItem = next;
}

/* === COMMENTED OUT DESTRUCTOR
// PRE: This object is defined.
// POST: The object that next pointed to is destroyed.
intNode::~intNode() {
  cout << "Entering inNode destructor" << endl;
  delete (next);
  next = NULL;
}

   === COMMENTED OUT DESTRUCTOR */
