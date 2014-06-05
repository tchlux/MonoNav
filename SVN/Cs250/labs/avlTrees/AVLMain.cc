#include <iostream>
#include "AVLTree.h"

using namespace std;

// Since we are using the AVLTree class to store pointers to integers
// (see main() below), we need to provide an overloaded output
// operator for pointers to integers.

// PRE: stream is a defined output stream.
//      intPtr points to a defined integer.
// POST: OS contains the value of the integer pointed to by intPtr
//       RV is the changed output stream.
ostream & operator<< (ostream & stream, int * intPtr) {
  stream << (*intPtr);
  return (stream);
}

int main () {
  AVLTree<int> intTree;       // intTree is an AVLTree whose nodes
			      // contain pointers to integers.
  int * elem0 = new int (8); // create a new integer object
  int * elem1 = new int (5); // create a new integer object
  int * elem2 = new int (1); // create a new integer object
  int * elem3 = new int (2); // create a new integer object
  int * elem4 = new int (3); // create a new integer object
  int * elem5 = new int (4); // create a new integer object
  int * elem6 = new int (7); // create a new integer object
  int * elem7 = new int (9); // create a new integer object
  int * elem8 = new int (6); // create a new integer object
  intTree.add(elem0);
  cout << intTree << endl;
  intTree.add(elem1);
  cout << intTree << endl;
  intTree.add(elem2);
  cout << intTree << endl;
  intTree.add(elem3);
  cout << intTree << endl;
  intTree.add(elem4);
  cout << intTree << endl;
  intTree.add(elem5);
  cout << intTree << endl;
  intTree.add(elem6);
  cout << intTree << endl;
  intTree.add(elem7);
  cout << intTree << endl;
  intTree.add(elem8);
  cout << intTree << endl;


  return (0);
}


  // intTree.addLeft (elem);   // Add the new integer object (its
  // 			    // pointer) as the leftmost child of intTree
  // cout << intTree << endl;          // Output intTree (using the overloaded
  // 			    // operator in the AVLTree class.
  // int * elem1 = new int (5); // create a new integer object and assign
  // 			    // the value 5 to it.
  // intTree.addRight (elem1);  // Add the new integer object (its
  // 			    // pointer) as the rightmost child of intTree
  // cout << intTree << endl;          // Output intTree (using the overloaded
  // 			    // operator in the AVLTree class.

  // int * elem2 = new int (7); // create a new integer object and assign
  // 			    // the value 7 to it.
  // intTree.addLeft (elem2);  // Add the new integer object (its
  // 			    // pointer) as the leftmost child of intTree
  // cout << intTree << endl;          // Output intTree (using the overloaded
  // 			    // operator in the AVLTree class.

  // /* COMMENT BLOCK
  //  *elem2 = 9;              // Reassign the value 9 to the integer
  //                           //  pointed to by elem2.
  // intTree.addRight (elem2);  // Add the integer object (its
  // 			    // pointer) as the rightmost child of intTree
  // cout << intTree << endl;          // Output intTree (using the overloaded
  // 			    // operator in the AVLTree class.
  // */

