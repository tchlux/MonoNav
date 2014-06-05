#ifndef INCLUDED_Loop
#define INCLUDED_Loop

#include <iostream>      // Since we are using the type ostream.
#include "LoopNode.h"	 // Since we are using the LoopNode class.

using namespace std;

template <class T>
class Loop {

  // Class Invariant (CI): This object contains a defined pointer f
  // that points to the first LoopNode, if any, in this Loop list
  // object. n is defined and contains the number of LoopNode objects
  // in this linked list object. 

private:
  LoopNode<T> * front; //The first node in the list
  int n;	       // stores the number of items in the
		       // linked list. Denoted by n.

public:
  
  // ===============================================
  //      Constructors: Default, Given LoopNode     
  // ===============================================

  // default constructor
  Loop(){
    front = NULL;
    n = 0;
  }

  // Pre:  newNode is defined, 
  // Post: *(newNode) == *(front)
  Loop(LoopNode<T> * newNode){
    front = NULL; //set front
    n = 0; //set items
    add(newNode);
  };

  // ==============================================
  //      Copy Constructor and related methods     
  // ==============================================

  // Copy constructor, deep copy of L is made
  Loop(const Loop & L){
    (*this) = L;     // Call copy with the given Loop
  };

  // Pre:  L is defined with L.n > 0
  // Post: Deep copy of L is saved in *this
  Loop & operator= (const Loop & L){
    copy(L);
    return(*this);
  };

  // ==========================
  //      Deep Copy Method     
  // ==========================

  // Pre:  L is defined, L.n == num of nodes in L
  // Post: Deep copy of L is produced in *this
  void copy(const Loop & L){
    if (front != NULL){		// If there is still data present
      cerr << "WARNING: Loop: Possible memory leak." 
	   << " Delete data before using 'copy()'." << endl;
    }
    front = NULL;  // reset front to be NULL
    n = 0;  // and set size to 0

    LoopNode<T> * curr =  L.front; // Current node in L
    LoopNode<T> * toAdd;// copy of curr, to be added to this list 
    for (int i=0; i<L.n; i++) { //for item in L
      toAdd = new LoopNode<T>(*curr); // Create the copy of curr
      add(toAdd); //add it to this list
      curr = curr->getNext(); //traverse L
    }
  }
  
  // ====================
  //      Destructor     
  // ====================

  // PRE: This object is defined.
  // POST: This object has no elements. f = NULL and n = 0.
  //       All space allocated for this object is deallocated.
  ~Loop(){
    if (front != NULL){
      front->getPrevious()->setNext(NULL); // Break the loop so the
      // delete isn't infinitely recursive
      delete (front); //this will recursively delete the list
      front = NULL;
    }
  }

  // =================================
  //      Accessors and Operators     
  // =================================

  // PRE: This object is defined.
  // POST: RV = n.
  int getSize () const{return (n);};

  // PRE: This object is defined and n > 0.
  // POST: RV = the integer stored in f(0).
  LoopNode<T> * getFront () const{return (front);};

  // Pre:  index < n
  // Post: The pointer to the item at that index
  LoopNode<T> * operator[](int index){
    LoopNode<T> * temp = front;
    if (index > 0){ // Forwards traversal
      for (int i=0; i<index; i++){
	temp = temp->getNext();
      }
    }
    else{ // Backwards traversal
      for (int i=0; i<(-index); i++){
	temp = temp->getPrevious();
      }      
    }
    return (temp);
  }

  // PRE:  L is defined. and has more than one element
  // POST: out contains L.f(0),...,L.f(L.n-1).
  //       NOTE: Here L.f refers to the elements of the Loop
  //       object L. 
  friend ostream & operator<< (ostream & out, Loop<T> & L){
    out << "Loop -" << L.n << " "; // Header: "Loop -length"
    LoopNode<T> * curr = L.front;// Holder for current node
    for (int i = 0; i < L.n; i++) { // For node in loop
      out << "[" << *curr << "] "; // Output current node
      curr = curr->getNext();	   // traverse
    }
    return (out); // return the out stream
  };

  // =============================================
  //      Has and Find, informative methods
  // =============================================

  // Pre:  hiddenLoopNode is defined
  // Post: true false if nodes exists in list
  bool has(const LoopNode<T> * hiddenNode){
    return(find(hiddenNode->getData()) != NULL);
  }

  // Pre:  hiddenNode is defined
  // Post: the node if it exists in list, otherwise NULL
  LoopNode<T> * find(const T & searchData){
    LoopNode<T> * curr = front; // node for searching
    for (int i=0; ((i<n)&&(curr->getData()!=searchData)); i++){
      // While the whole loop hasn't been searched &&
      // searchData has not been found
      curr = curr->getNext(); // traverse to the next node
    }
    if (curr->getData() != searchData){	//if the search didn't succeed
      curr = NULL; // set curr to NULL, signifying nothing found
    }
    return(curr); // return the pointer
  }

  // ======================================================
  //      Modifier functions: add, remove(index), sort     
  // ======================================================

  //Pre:  newData is defined, & since there is no reason to copy, 
  //      loc >= 0
  //Post: The new node is created and inserted
  void insert(T & newData, int loc){
    LoopNode<T> * newNode = new LoopNode<T>(newData);
    insert(newNode, loc); // After creating a node from the data, insert it
  };

  //Pre:  newData is defined, & since there is no reason to copy
  //Post: The new node is created and added to the front
  void addFront(T & newData){
    LoopNode<T> * newNode = new LoopNode<T>(newData);
    addFront(newNode); // After creating a node from the data, add it
  };

  //Pre:  newData is defined, & since there is no reason to copy
  //Post: The new node is created and added
  void add(T & newData){
    LoopNode<T> * newNode = new LoopNode<T>(newData);
    add(newNode); // After creating a node from the data, add it
  };

  // Pre:  newNode is defined fully
  // Post: newNode is inserted into this loop
  void addFront(LoopNode<T> * newNode){
    add(newNode); // Add this node to the end of the loop
    front = newNode; // Set the front to be this newNode
  };

  // Pre:  newNode is defined fully
  // Post: newNode is inserted into this loop
  void add(LoopNode<T> * newNode){
    if (n == 0){		 // If there were no elements
      front = newNode;		 // Set this node to be front
      front->setNext(front);	 // Loop it into itself
      front->setPrevious(front); // same for going backwards
    }
    else{
      front->getPrevious()->setNext(newNode); // Insert at 'end'
      newNode->setPrevious(front->getPrevious()); // connect to Loop
      newNode->setNext(front); // connect 'end' to front
      front->setPrevious(newNode); // connect to new 'end'
    }
    n++; //increment items
  };

  // Pre:  newNode is defined fully
  // Post: newNode is inserted into this loop
  void insert(LoopNode<T> * newNode, int loc){
    if (loc % n == 0){ // If the element was the front
      add(newNode);
      front = newNode;		 // Set this node to be front
    }
    else{
      (*this)[loc]->getPrevious()->setNext(newNode); // Insert at 'end'
      newNode->setPrevious((*this)[loc]->getPrevious()); // connect to Loop
      newNode->setNext((*this)[loc]); // connect 'end' to front
      (*this)[loc]->setPrevious(newNode); // connect to new 'end'
    }
    n++; //increment items
  };

  // Pre: N is defined. This object is defined. n > N.
  // Post: The list is appropriately 
  void remove (int N){
    if (N % n == 0){ // If removing the front of the loop
      LoopNode<T> * temp = front; // Get a temporary holder on front
      if (n <= 1){ // If this is the last node in the loop
	front = NULL; // just set front to NULL
      }
      else{ // There is at least one more node
	front = front->getNext(); //it is now the front
      }
      delete(temp->remove());	// Delete the old front node
    }
    else{ // Not removing the front of the loop
      delete(((*this)[N])->remove()); //remove the nth element and then
      // delete that node (it is returned by it's remove method)
    }
    n--; //decrement num items
  };

  // Pre:  
  // Post: Linked list sorted with merge sort
  void sort(){
    mergeSort(); //call merge sort
  };

  // =======================================
  //      Private Sort Helper Functions     
  // =======================================

private:

  // Post: This list is set to be deleted without loss of nodes
  void setNull(){front=NULL; n=0;};

  // Pre:  first half and second half are defined
  // Post: All elements from fHalf and sHalf are put into this, and
  //       removed from fHalf and sHalf
  void combine(Loop<T> & fHalf, Loop<T> & sHalf){
    fHalf.front->getPrevious()->setNext(NULL); // break the loops for
    sHalf.front->getPrevious()->setNext(NULL); // simplicity
    LoopNode<T> * fCurr = fHalf.front; // Current node in firstHalf
    LoopNode<T> * sCurr = sHalf.front; // Current node in secondHalf
    LoopNode<T> * toAdd; // Holder for node to be added
    for (int i=0; i<(fHalf.n+sHalf.n); i++){ // for vertex in combined
      if ((sCurr!=NULL) && ((fCurr == NULL) || (sCurr > fCurr))){
	// ASSERT: fCurr = NULL or sCurr > fCurr
	toAdd = sCurr;		   // Hold the current
	sCurr = sCurr->getNext();  // traverse sCurr	
      } // End if ((sCurr!=NULL)...
      else{ //ASSERT: sCurr = NULL or fCurr >= sCurr
	toAdd = fCurr;		   // Hold the current
	fCurr = fCurr->getNext();  //traverse fCurr	
      } // End else
      add(toAdd); // add old element to this
    } // End for (int i=0...
  };

  // Post: This loop is sorted
  void mergeSort(){
    if (n >= 2){
      Loop<T> even;		  // Half of the loop
      Loop<T> odd;		  // The remaining half
      LoopNode<T> * curr = front; // Get the front of the loop
      LoopNode<T> * next;	  // Holder for the next node
      for (int i=0; i<n; i++){	  // for vertex in *this
	next = curr->getNext();	  // Get the next node
	if ((i % 2) == 0){	  // for every even vertex
	  even.add(curr);	  // Add it to the even loop
	}
	else{			  // for all odd vertices
	  odd.add(curr);          // Add to the odd loop
	}
	curr = next;
      }
      // ASSERT: even and odd contain all elements originally in this
      setNull();	  // Set this loop to be empty
      even.mergeSort();	  // Sort everything in even recursively
      odd.mergeSort();	  // Sort everything in odd recursivel
                          // ASSERT: all elements of even/odd sorted
      combine(even, odd); 
                          // ASSERT: All elements returned to this in
                          //         sorted order

      even.setNull();	  // Reset to null to prevent Node deletion
      odd.setNull();	  // Reset to null to prevent Node deletion
      // ASSERT: even.front = NULL && odd.front = NULL
    }    
  };

}; // End class Loop

#endif
