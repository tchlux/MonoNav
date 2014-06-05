
#include <iostream>      // Since we are using the type ostream.
#include "intTreeNode.h"     // Since we are using the intTreeNode class here.
#include "intBinTree.h"     

using namespace std;

// ======================================== 
// constructors
// ======================================== 

// default constructor
// PRE: 
// POST: This object is defined with r = NULL and n = 0.
intBinTree::intBinTree() {
  numItems = 0;
  root = NULL;
}


// copy constructor
// PRE: T is defined.
// POST: This object is defined and is a deep copy of T.
//       Thus, r = T.r, with all the intTreeNodes in this object being physically
//         distinct from the intTreeNodes of T.
//       n = T.n
//       Note here that T is being passed by reference to avoid the
//        shallow copy of the actual parameter being passed as T. We
//        indicate that T does not change with the keyword const.
intBinTree::intBinTree(const intBinTree & T) {
  numItems = T.getSize();
  intTreeNode * tempRoot = new intTreeNode(*T.getRoot());
  root = tempRoot;
}

// PRE: T is defined.
// POST: This object is defined and is a deep copy of T.
//       Thus, r = T.r, with all the intTreeNodes in r being physically
//         distinct from the intTreeNodes of T.
//       n = T.n
//       Note here that T is being passed by reference to avoid the
//        shallow copy of the actual parameter being passed as T. We
//        indicate that T does not change with the keyword const.
intBinTree & intBinTree::operator= (const intBinTree & T) {
  numItems = T.getSize();
  intTreeNode * tempRoot = new intTreeNode(*T.getRoot());
  root = tempRoot;
  // a copy of all things after it must be made as well
}

// ======================================== 
// destructor
// ======================================== 

// PRE: This object is defined.
// POST: This object has no elements. r = NULL and n = 0.
//       All space allocated for this object is deallocated.
intBinTree::~intBinTree() {
  delete (root);  // will recursively call the intTreeNode destructor
  root = NULL;
}

// ======================================== 
//       accessor functions
// ======================================== 

// PRE: This object is defined.
// POST: RV = n.
int intBinTree::getSize () const {
  return (numItems);
}

// PRE: This object is defined and n > 0.
// POST: RV = the integer stored at the root of the tree.
intTreeNode * intBinTree::getRoot () const {
  return (root);
  // Since the pre condition requires the tree object to have at least
  // one element, root-> will not give us a "de-referencing a null
  // pointer" error.
}

// ======================================== 
// modifier functions
// ======================================== 

// PRE: num = v is defined. This object is defined.
// POST: This object is defined with n = (pre)n + 1. An intTreeNode
//       object t contains the integer data v.
//       If this tree object is empty, then the new node is made the
//         root of the tree.
//       Otherwise: 
//       Let x be the first leftmost descendent (this could be the
//         root) of this intBinTree
//         object that does not have two children. If x does not have
//         a left child, then t is added as the left child of x;
//         otherwise, t is added as the right child of x.
void intBinTree::addLeft (int num) {
  intTreeNode * tempNode = new intTreeNode(num); //create the new Node
  if (numItems == 0){ //if there's nothing in the tree
    root = tempNode; //set the root
  }
  else{ //The tree is not empty
    intTreeNode * current = root; //get root node
    while ((current->getLeftChildPtr() != NULL) &&
	   (current->getRightChildPtr() != NULL)){ 
      //while there's data in both children
      current = current->getLeftChildPtr(); //move down one to the
      // right
    }
    if (current->getLeftChildPtr() == NULL){ //if the left is open
      current->setLeftPtr(tempNode); //set the left
    }
    else{ //the right was open
      current->setRightPtr(tempNode); //set the right
    }
  }
  numItems ++;
}

// PRE: num = v is defined. This object is defined.
// POST: This object is defined with n = (pre)n + 1. An intTreeNode
//       object t contains the integer data v.
//       If this tree object is empty, then the new node is made the
//         root of the tree.
//       Otherwise: 
//       Let x be the first rightmost descendent (this could be the
//         root) of this intBinTree
//         object that does not have both children. If x does not have
//         a right child, then t is added as the right child of x;
//         otherwise, t is added as the left child of x.
void intBinTree::addRight (int num) {
  intTreeNode * tempNode = new intTreeNode(num); //create the new Node
  if (numItems == 0){ //if there's nothing in the tree
    root = tempNode; //set the root
  }
  else{ //The tree is not empty
    intTreeNode * current = root; //get root node
    while ((current->getLeftChildPtr() != NULL) &&
	   (current->getRightChildPtr() != NULL)){ 
      //while there's data in both children
      current = current->getRightChildPtr(); //move down one to the
      // left
    }
    if (current->getRightChildPtr() == NULL){ //if the right is open
      current->setRightPtr(tempNode); //set the right
    }
    else{ //the left was open
      current->setLeftPtr(tempNode); //set the left
    }
  }
  numItems ++;
}

// PRE: This object is defined. n > 0.
// POST: This object is defined.
//       n = (pre)n  -1
//       Let x be the leftmost descendent of this intBinTree object.
//       If x is the root of this intBinTree object, then the right
//         child of x (possibly NULL) is made the root of this
//         object, and the node x is deleted.
//       If x is not the root of this object:
//         Suppose x does not have a right child. Then the node x is
//           deleted.
//         Suppose x has a right child, say y, and the parent of x is
//           p. Then node x is deleted and y is made the left child of p.
void intBinTree::deleteLeft () {
  if (root->getLeftChildPtr() == NULL){
    intTreeNode * oldRoot = root;
    root = root->getRightChildPtr();
    oldRoot->setRightPtr(NULL);
    delete(oldRoot);
  }
  intTreeNode * parent = root;
  intTreeNode * current = root;
  intTreeNode * child = NULL;
  while (current->getLeftChildPtr() != NULL){
    parent = current;
    current = current->getLeftChildPtr();
  }
  if (current->getRightChildPtr() != NULL){
    child = current->getRightChildPtr();
    current->setRightPtr(NULL);
  }
  delete(current);
  parent->setLeftPtr(child);
}

// PRE: This object is defined. n > 0.
// POST: This object is defined.
//       n = (pre)n  -1
//       Let x be the rightmost descendent of this intBinTree object.
//       If x is the root of this intBinTree object, then the left
//         child of x (possibly NULL) is made the root of this object.
//       If x is not the root of this object:
//         Suppose x does not have a left child. Then the node x is
//           deleted.
//         Suppose x has a left child, say y, and the parent of x is
//           p. Then node x is deleted and y is made the right child of p.
void intBinTree::deleteRight () {
  if (root->getRightChildPtr() == NULL){
    intTreeNode * oldRoot = root;
    root = root->getLeftChildPtr();
    oldRoot->setLeftPtr(NULL);
    delete(oldRoot);
  }
  intTreeNode * parent = root;
  intTreeNode * current = root;
  intTreeNode * child = NULL;
  while (current->getRightChildPtr() != NULL){
    parent = current;
    current = current->getRightChildPtr();
  }
  if (current->getLeftChildPtr() != NULL){
    child = current->getLeftChildPtr();
    current->setLeftPtr(NULL);
  }
  delete(current);
  parent->setRightPtr(child);
}


// PRE: This object is defined.
// POST: If the root is not NULL, then
//         one of the nodes of the tree, say x, is made the new root
//         of the tree and the parent/children relations are
//         revised, if necessary, so that 
//           for all nodes y not equal to x in the tree, 
//             any nodes in the left subtree of y before the deletion 
//               are still in the left subtree of y,
//             and 
//             any nodes in the right subtree of y before the deletion 
//               are still in the right subtree of y.
void intBinTree::deleteRoot () {
  intTreeNode * oldRoot = root;
  intTreeNode * attachPoint = NULL;
  if (root->getLeftChildPtr() != NULL){
    root = root->getLeftChildPtr();
    attachPoint = root;
    while (attachPoint->getRightChildPtr() != NULL){
      attachPoint = attachPoint->getRightChildPtr();
    }
    attachPoint->setRightPtr(oldRoot->getRightChildPtr());
  }
  else{
    if (root->getRightChildPtr() != NULL){
      root = root->getLeftChildPtr();
      attachPoint = root;
      while (attachPoint->getRightChildPtr() != NULL){
	attachPoint = attachPoint->getRightChildPtr();
      }
      attachPoint->setRightPtr(oldRoot->getRightChildPtr());    
    }
  }
  oldRoot->setRightPtr(NULL);
  oldRoot->setLeftPtr(NULL);
  delete(oldRoot);
}

// ======================================== 
//     Input/Output
// ======================================== 

// Pre:  stream is defined, current is defined or NULL
// Post: Left child, print current, right child order print
void inOrderTraversal(ostream & stream, const intTreeNode * current){
  intTreeNode * left = current->getLeftChildPtr();
  intTreeNode * right = current->getRightChildPtr();
  if (left != NULL){
    inOrderTraversal(stream, left);
    stream << ",";
  }
 stream << current->getData();
  if (right != NULL){
    stream << ",";
    inOrderTraversal(stream, right);
  }
}

// PRE: T is defined.
// POST: stream contains the contents of the nodes on one line of this
//       intBinTree object as visited in the inorder traversal of the
//       object. 
ostream & operator<< (ostream & stream, const intBinTree & T) {
  intTreeNode * current = T.root;
  inOrderTraversal (stream, current);
  return (stream);
}

// PRE: stream is a defined OS.
//      current is a defined pointer, possibly NULL, to an intTreeNode
//      object 
// POST: OS contains the elements in the left subtree of current
//      followed by the element at current, followed by the
//      elements in the right subtree of current.
void intBinTree::inOrderTraversal (ostream & stream, intTreeNode * current) {
  if (current != NULL) {
    inOrderTraversal (stream, current->getLeftChildPtr());
    stream << current->getData() << " ";
    inOrderTraversal (stream, current->getRightChildPtr());
  }
}
