#include <iostream>

#include "intTreeNode.h"

using namespace std;

// ======================================== 
// constructors
// ======================================== 

// default constructor
// PRE: 
// POST: This object is defined with n = 0 and p = NULL and q = NULL.
intTreeNode::intTreeNode () {
  data = 0;
  leftChildPtr = NULL;
  rightChildPtr = NULL;
}

// PRE: num = v is defined.
// POST: This object is defined with n = v, and p = NULL and q = NULL.
intTreeNode::intTreeNode (int num) {
  data = num;
  leftChildPtr = NULL;
  rightChildPtr = NULL;
}

// Pre:  node is defined
// Post: Deep copy of the node given
intTreeNode::intTreeNode(intTreeNode & node){
  data = node.getData();
  leftChildPtr = NULL;
  rightChildPtr = NULL;
  intTreeNode * left = node.getLeftChildPtr();
  intTreeNode * right = node.getRightChildPtr();
  if (left != NULL){
    leftChildPtr = new intTreeNode(*left);
  }
  if (right != NULL){
    rightChildPtr = new intTreeNode(*right);
  }
}

// ======================================== 
//       accessor functions
// ======================================== 

// PRE: This object is defined.
// POST: RV = n.
int intTreeNode::getData () const {
  return (data);
}

// PRE: This object is defined.
// POST: RV = p.
intTreeNode * intTreeNode::getLeftChildPtr () const {
  return (leftChildPtr);
}

 // PRE: This object is defined.
// POST: RV = q.
intTreeNode * intTreeNode::getRightChildPtr () const {
  return (rightChildPtr);
}


// ======================================== 
// modifier functions
// ======================================== 

// PRE: This object is defined. num = v is defined.
// POST: This object is defined and n = v.
void intTreeNode::setData (int num) {
  data = num;
}

// PRE: This object is defined. leftPtr = x is defined.
// POST: This object is defined and p = x.
void intTreeNode::setLeftPtr (intTreeNode * leftPtr) {
  leftChildPtr = leftPtr;
}

// PRE: This object is defined. rightPtr = x is defined.
// POST: This object is defined and p = x.
void intTreeNode::setRightPtr (intTreeNode * rightPtr) {
  rightChildPtr = rightPtr;
}

// ======================================== 
// I/O functions
// ======================================== 

// PRE: stream is a defined output stream. node is defined and is a
// pointer to an intTreeNode object.
// POST: Data from the node pointed to by nodePtr is on OS, and RV
// is the changed OS.
ostream & operator<< (ostream & stream, const intTreeNode * nodePtr) {
  stream << nodePtr->data;
  return (stream);
}

// PRE: stream is a defined output stream. node is defined and is an
// intTreeNode object.
// POST: Data from node is on OS, and RV
// is the changed OS.
ostream & operator<< (ostream & stream, const intTreeNode & node) {
  stream << node.data;
  return (stream);
}

// NOTE: The above two operators have different signatures: one
// gets a pointer to an intTreeNode object, while the other gets an
// intTreeNode object. Note the difference in the syntax to access
// the member data object "data" in the two cases.


// PRE: This object is defined.
// POST: The two children objects are destroyed.
intTreeNode::~intTreeNode() {
  cout << "Entering intTreeNode destructor" << endl;
  delete (leftChildPtr);
  leftChildPtr = NULL;
  delete (rightChildPtr);
  rightChildPtr = NULL;
}
