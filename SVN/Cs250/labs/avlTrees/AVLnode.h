#ifndef INCLUDED_AVLnode
#define INCLUDED_AVLnode

#include "defs.h"

#include <iostream>

using namespace std;

// This is a templated AVLnode class that holds a pointer to an object of
// type T, and two pointers to the left and right children, if any, of this AVLnode.

// CI: If data != NULL, then data points to a defined object of type
//     T. 
//     If leftChild != NULL, then leftChild points to a defined AVLnode object
//     satisfying the AVLnode CI.
//     If rightChild != NULL, then rightChild points to a defined AVLnode object
//     satisfying the AVLnode CI.

template <class T>
class AVLnode{
 private:
  T * data;       // If not NULL, holds a pointer to a defined object
		  // of type T. 
  
  // The following two member data objects will be useful when creating AVL trees.
  uint height;    // The height of this AVLnode in a tree.
  int balance;    // The balance factor for this AVLnode in a tree.

  AVLnode<T> * leftChild;  // If not NULL, points to a defined AVLnode object
                           // satisfying the AVLnode CI.
  AVLnode<T> * rightChild; // If not NULL, points to a defined AVLnode object
                           // satisfying the AVLnode CI.

 public:

  // Default constructor

  // PRE:
  // POST: This AVLnode object is defined and satisfies the CI.
  AVLnode<T> () {
    data = NULL;
    leftChild = NULL;
    rightChild = NULL;
    height = 0;
    balance = 0;
  };

  // PRE: elemPtr points to a defined object of type T.
  // POST: This AVLnode object is defined, contains a pointer to a
  //       defined object of type T, and its leftChild and rightChild
  //       pointers are assigned the value NULL.
  //       This AVLnode object satsfies the CI.
  AVLnode<T> (T * elemPtr) { 
    data = elemPtr;
    leftChild = rightChild = NULL;
    height = balance = 0;
  };

  // Accessors

  // PRE: This AVLnode object is defined.
  // POST: RV is NULL or a pointer to a defined object of type T.
  T * getData() const {
    return (data);
  };
  
  // PRE: This AVLnode object is defined.
  // POST: RV is NULL or a pointer to a defined object, A, of type
  //       AVLnode<T> where A is the left child of this AVLnode.
  AVLnode<T> * getLeft() const {
    return (leftChild);
  };

  // PRE: This AVLnode object is defined.
  // POST: RV is NULL or a pointer to a defined object, A, of type
  //       AVLnode<T> where A is the right child of this AVLnode.
  AVLnode<T> * getRight() const {
    return (rightChild);
  };

  // Pre:  
  // Post: current height returned
  uint getHeight() const{return(height);};

  // Pre:  
  // Post: current balance returned
  int getBalance() const{return(balance);};

  // Pre:  
  // Post: returns a reference to balance
  int & getBalRef() {return(balance);};

  // Modifiers

  // Pre:  h is defined > 0
  // Post: height set
  void setHeight(uint h){
    height = h;
  }

  // Pre:  b is defined
  // Post: balance is set
  void setBalance(int b){
    balance = b;
  }

  // Pre:  newData is defined
  // Post: the data is saved to data
  void setData(T * newData){
    data = newData;
  }

  // PRE: This AVLnode object is defined.
  //      nodePtr is NULL or points to a defined object of type
  //      AVLnode<T>
  // POST: This AVLnode object's leftChild pointer is assigned the value of
  //       nextPtr. Thus this AVLnode object's leftChild pointer is NULL or
  //       points to a defined object of type AVLnode<T>.
  //       This AVLnode object satisfies the CI.
  void setLeft (AVLnode<T> * nodePtr) {
    leftChild = nodePtr;
  };

  // PRE: This AVLnode object is defined.
  //      nodePtr is NULL or points to a defined object of type
  //      AVLnode<T>
  // POST: This AVLnode object's rightChild pointer is assigned the value of
  //       nextPtr. Thus this AVLnode object's rightChild pointer is NULL or
  //       points to a defined object of type AVLnode<T>.
  //       This AVLnode object satisfies the CI.
  void setRight (AVLnode<T> * nodePtr) {
    rightChild = nodePtr;
  };

  // Predicates

  // PRE: This AVLnode object is defined.
  // POST: RV is true iff there is a left child of this AVLnode.
  bool hasLeft () {
    bool answer = (leftChild != NULL);
    return (answer);
  };

  // PRE: This AVLnode object is defined.
  // POST: RV is true iff there is a right child of this AVLnode.
  bool hasRight () {
    bool answer = (rightChild != NULL);
    return (answer);
  };

  // Output Operator

  // PRE: stream is a defined output stream.
  //      N points to a defined AVLnode object satisfying the AVLnode CI.
  // POST: OS contains the element, if any, stored in N.
  //       RV is the changed output stream.
  friend ostream & operator<< (ostream & stream, AVLnode<T> * N) {
    T * nodeDataPtr = N -> getData();
    if (nodeDataPtr != NULL) {
      // ASSERT: N contains a pointer to a defined object of type T.
      stream << *nodeDataPtr;  // using the overloaded operator
			      // provided by the user for the type T.
      stream << " (" << N->balance << ")";
    }
    return (stream);
  };
};
#endif
