#ifndef INCLUDED_AVLTree
#define INCLUDED_AVLTree

#include <iostream>
#include "AVLnode.h"
#include "defs.h"

using namespace std;

// This is a templated AVLTree class that holds in its nodes pointers
// to defined objects of type T.

// CI: num is the number of elements in the AVLTree.
//     root = NULL iff num = 0.
//     If num > 0, then root points to the root node of the AVLTree.
//     ***********
//     This part of the CI is not yet implemented. Your addition of
//     the code to the function add should ensure this.
//     The elements in the tree are ordered according to the ordering
//     provided by the type T, and the tree is balanced.
//     ***********
template <class T>
class AVLTree{
 private:
  AVLnode<T> * root;  // pointer to the first node in the AVLTree.
  uint num;        // The number of elements in the AVLTree.

 public:
  // Default Constructor
  // PRE:
  // POST: This AVLTree object satisfies the CI.
  AVLTree<T> () {
    root = NULL;
    num = 0;
  };

  // Modifier


  // Pre:  toAdd points to defined AVLnode, left and foundCrit are
  //       defined booleans
  // Post: start is traversed (by reference) and the parent of the
  //       critical node pointer is returned, the boolean for
  //       foundCrit will be true if a critical node was found
  AVLnode<T> * avlInsert(AVLnode<T> * toAdd,
			 bool & left, bool & foundCrit){
    AVLnode<T> * start = root; //starting insert location
    bool done = false; //used to terminate insert

    AVLnode<T> * critNodePar = new AVLnode<T>(); //return value
    critNodePar->setLeft(root);
    left = true;
    if (start == NULL){ //special case, no elements
      root = toAdd;
      done = true;
    }
    else{
      if (start->getBalance() != 0){
	foundCrit = true;
      }
    }
    while (! done){
      if (start->getData() == toAdd->getData()){ //repeated value
	done = true;
	num --; //ten points from griffendor (only special case with
        	// no addition)
      }//end repeat check
      else{
	if (*(start->getData()) > *(toAdd->getData())){ //look left
	  if (start->getLeft() == NULL){ //no left child
	    start->setLeft(toAdd);
	    done = true;
	  }//end if start->getLeft
	  else{ //there is a left child
	    if ((start->getLeft() != NULL) &&
		(start->getLeft()->getBalance() != 0)){
	      //if the balance of the left child isn't 0	      
	      critNodePar = start; //it's a critical node
	      left = true; //it is left
	      foundCrit = true; //set the bool
	    }//end if start->getLeft
	    start = start->getLeft(); //traverse
	  }//end else
	}//end if start->getData
	else{ //need to look right
	  if (start->getRight() == NULL){ //no right child
	    start->setRight(toAdd);
	    done = true;
	  }//end if start->getRight
	  else{ //ther is a right child
	    if ((start->getRight() != NULL) &&
		(start->getRight()->getBalance() != 0)){
	      //if the balance of the right child isn't 0
	      critNodePar = start; //it's a critical node
	      left = false; //it is not left
	      foundCrit = true; //set the bool
	    }
	    start = start->getRight(); //traverse
	  }//end else
	}//end else
      }//end else
    }//end while
    num ++; //increment the number of elements
    return(critNodePar); //return the currently stored critNodePar
  }//end avlInsert
  
  // Pre:  cursor is the starting critical node, data is defined child
  //       will be the newest addition
  // Post: The child is returned given cursor as a start and
  //       data as a search, reBal is set to be the proper balance
  //       shift given the path taken
  AVLnode<T> * reBalance(AVLnode<T> * cursor, T * data, int & reBal){
    AVLnode<T> * child; //init return value
    if (*(cursor->getData()) > *data){ //if traveling left
      reBal -= 1; //balance shifts left by one
      child = cursor->getLeft(); //traverse and get child
    }
    else{ //traveling right
      reBal += 1; //balance shifts right
      child = cursor->getRight(); //traverse right & get child
    }
    return(child); //return child
  }

  // Pre:  parent is defined AVLnode, left is defined
  // Post: the appropriate child of parent is returned
  AVLnode<T> * get(AVLnode<T> * parent, bool left){
    AVLnode<T> * child; //init return value
    if (left){ //the left value is the node
      child = parent->getLeft(); //get the left child
    } 
    else{ //the right child is the node
      child = parent->getRight(); //get the right
    }
    return(child); //return the appropriate child
  }

  // Pre:  parent is the parent of the node to be rotated, left tells
  //       whether or not left child of parent  should be rotated, dir
  //       is -1 or +1 
  // Post: This position is rotated
  void rotate(AVLnode<T> * parent, bool left, int dir){
    AVLnode<T> * deepest; //holder for variable swap
    AVLnode<T> * P = get(parent, left); //holder for top of tree
    if (dir == -1){ //if left rotation
      deepest = P->getRight()->getLeft();
      //hold the deepest node
      P->getRight()->setLeft(P);
      //check special case, get(parent, left) == root
      if (*(get(parent,left)->getData()) == *(root->getData())){
	root = P->getRight();
      }
      if (left){ //setLeft method
	parent->setLeft(P->getRight());
      }
      else{ //use setRight method
	parent->setRight(P->getRight());
      }
      P->setRight(deepest);
    }
    else{ //right rotation
      deepest = P->getLeft()->getRight();
      P->getLeft()->setRight(get(parent, left));
      //check special case, get(parent, left) == root
      if (*(get(parent,left)->getData()) == *(root->getData())){
	root = P->getLeft();
      }
      if (left){ //use setLeft method
	parent->setLeft(P->getLeft());
      }
      else{ //use setRight method
	parent->setRight(P->getLeft());
      }
      P->setLeft(deepest);
    }
    //ASSERT: rotation complete, all pointers not changed are still
    //        valid arrangements in the avl tree
  }

  // PRE: This AVLTree object is defined.
  //      elemPtr points to a defined object of type T.
  // POST: num = (pre) num + 1.
  //       elemPtr is the element in a new node that is added to this
  //       tree so that the tree is in order (according to the
  //       ordering provided by the type T), and is balanced.
  //       This AVLTree object satisfies the CI.
  void add (T * newData) {
    AVLnode<T> * toAdd = new AVLnode<T>(newData); //to insert
    bool left; //holder for which child of critNodePar is te crit node
    bool foundCrit; //found a critical node
    AVLnode<T> * critNodeParent = avlInsert(toAdd, left, foundCrit);
    //get the deepst critNode's parent pointer
    AVLnode<T> * cursor; //used to point to where the top rotation
    //will occur if there is one, and for rebalancing afterwards
    if (! foundCrit){ //No critical node was found
      cursor = root;
    }
    else{ //a critical (imbalanced node) was found
      int reBal1 = 0; //holder for balance
      AVLnode<T> * child1 = reBalance(get(critNodeParent, left),
				      newData, reBal1); 
      if (reBal1 != get(critNodeParent, left)->getBalance()){ //the balance will be 0
	get(critNodeParent, left)->setBalance(0); //yay!
	cursor = toAdd; //cursor = newly added node
      }
      else{ //the balance will now have a magnitude of 2
	int reBal2 = 0; //holder for balance
	AVLnode<T> * child2 = reBalance(child1, newData, reBal2);
	if (reBal1 == reBal2){ //single rotation required
	  get(critNodeParent, left)->setBalance(0); //yay!
	  cursor = child2; //cursor goes to the child of child1
	  rotate(critNodeParent, left, -reBal1); //rotate the critical node the
	  //opposite of the direction it was off balanced
	}
	else{ //double rotation required
	  int reBal3 = 0; //holder for balance
	  cursor = reBalance(child2, newData, reBal3); //cursor is the
	  //     3rd child
	  if (reBal2 == reBal3){ //if the second two balances r equal
	    get(critNodeParent, left)->setBalance(0); //yay!
	    child1->setBalance(reBal1); //set balance for first child
	  }
	  else{//reBal2 and 3 are not equal
	    get(critNodeParent, left)->setBalance(reBal2); //set bal for critNode
	  }//end fourth else
	  rotate(get(critNodeParent, left),(reBal1 == -1), -reBal2); //rotate the bottom
	  rotate(critNodeParent, left, -reBal1); //rotate from the crit node
	}//end third else
      }//end second else
    }//end first else
    while (*(cursor->getData()) != *newData){ //from the top to the bottom
      cursor = reBalance(cursor, newData, cursor->getBalRef());
    }//end while
  } //end add


  // Output operator

  // PRE: stream is a defined output stream.
  //      Tree is a defined AVLTree object that satisfies the AVLTree CI.
  // POST: OS contains the elements of Tree in post-order.
  //       RV is the changed output stream.
  friend ostream & operator <<(ostream & stream, const AVLTree<T> & Tree) {
    AVLnode<T> * curr = Tree.root; 
    // Since the function printPostOrder is a member function of the
    // AVLTree class, it must be called for an AVLTree object. 
    Tree.printPostOrder (stream, curr);
    return (stream);
  };

private:
  // PRE: stream is a defined output stream.
  //      N is a defined AVLnode object that satisfies the AVLTree CI,
  //      or N is NULL.
  // POST: If N is not NULL, then OS contains the elements in the left
  //      subtree of N in post-order, followed by the elements in the
  //      right subtree of N in post-order, followed by the element in
  //      the AVNnode object pointed to by N.
  void printPostOrder (ostream & stream, AVLnode<T> * N) const {
    if (N != NULL) {
      printPostOrder (stream, N->getLeft());
      stream << N << " ";
      printPostOrder (stream, N->getRight());
    }
  }
};
#endif
