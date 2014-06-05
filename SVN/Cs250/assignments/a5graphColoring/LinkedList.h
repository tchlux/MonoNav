#ifndef INCLUDED_LinkedList
#define INCLUDED_LinkedList

#include <iostream>      // Since we are using the type ostream.
#include "Node.h"     // Since we are using the Node class here.

using namespace std;

template <class T>
class LinkedList {

  // Class Invariant (CI): This object contains a defined pointer f
  // that points to the first Node, if any, in this linked list
  // object. n is defined and contains the number of Node objects
  // in this linked list object. 

private:
  Node<T> * front; //The first node in the list
  Node<T> * back; //The back of the list
  int numItems;                // stores the number of items in the
			       // linked list.
                               // denoted by n.

  // NOTE: We will sometimes also refer to the elements of the list as
  // f(0), f(1),..., f(n-1), where f(0) is the Node at the front of
  // the list.


  //Pre:  
  //Post: front is set to NULL, this is only to be used to avoid
  //      deletions of subseuent nodes
  void setNull(){front=NULL;back=NULL;}

  // PRE: num = n > 0 is defined; 
  //      base = b > 0 is defined 
  // POST: RV = floor (log_b (n)).
  int floorLog (int num, int base){
    int power = 0;
    int raisedPower = 1;
    // ASSERT: raisedPower = base^power
    while (raisedPower <= num) {
      // ASSERT: raisedPower <= num
      raisedPower *= base;
      power++;
      // ASSERT: raisedPower = base^power    
    }
    // ASSERT: raisedPower > num and 
    //         base^(power-1) <= num.
    //         Thus, floor of log_b(n) = power-1.
    return (power-1);
  }

  // Pre:  number and the power to raise it to
  // Post: the number to that power
  int power(int num, int power){
    if (power == 0){
      num = 1;
    }
    for (int i=0; i<power; i++){
      num *= num;
    }
    return (num);
  }

  // Pre:  The current round number
  // Post: The according round is sorted
  void mergeSort(){
    if (numItems >= 2){ //if there are more than 2 items in this list
      back = ((*this)[numItems/2-1]); //split it up
      int remainder = numItems%2; //get the remained for final size
      numItems /= 2; //reset numItems to new size
      LinkedList secondHalf(back->getNext()); //get the second half
      back->setNext(NULL); //destroy the
      // extra link to the front of the other list
      mergeSort(); //call merge recursively
      secondHalf.mergeSort(); //call merge recursively

      //sort the two halves back together keeping in mind that Node's
      //merge method must be called from the smaller node
      if (front->getData() <= secondHalf.front->getData()){
	front->merge(secondHalf.front); //this front was smaller
      }
      else{ //the secondHalf.front was smaller
	secondHalf.front->merge(front);
	front = secondHalf.front; //and that should be the new front
      }

      numItems = numItems*2 + remainder; //we now have our original
      //items back and sorted! YAY!
      secondHalf.setNull(); //set the front and back of secondHalf to
      // NULL so that the destructor doesn't delete all of the nodes
    }
  };

 public:
  
  // ======================================== 
  // constructors
  // ======================================== 

  // default constructor
  // PRE: 
  // POST: This object is defined with f = NULL and n = 0.
  LinkedList(){
    front = NULL;
    back = NULL;
    numItems = 0;
  }

  // Pre:  newNode is defined
  // Post: Linked list is created, and size is found
  LinkedList(Node<T> * newNode){
    front = newNode; //set the front to this node
    back = newNode; //set the back to this node also
    newNode->setPrevious(NULL); //set the node's previous to null
    numItems = 1; //current number of items
    while (newNode->getNext() != NULL){ //until done
      newNode = newNode->getNext(); //traverse
      back = newNode; //set the back to this node
      numItems ++; //increment counter
    }
  }

  // copy constructor
  // PRE: L is defined.
  // POST: This object is defined and is a deep copy of L.
  //       Thus, f = L.f, with all the Nodes in f being physically
  //         distinct from the Nodes of L.
  //       n = L.n
  //       Note here that L is being passed by reference to avoid the
  //        shallow copy of the actual parameter being passed as L. We
  //        indicate that L does not change with the keyword const.
  LinkedList(LinkedList & L){
    front = NULL; //set front
    back = NULL; //set back
    numItems = 0; //set items
    Node<T> * temp = L.front; //get the first node of the other list
    for (int i=0; i<L.numItems; i++) { //for item in L
      addBack (temp); //add it to this list
      temp = temp->getNext(); //traverse L
    }
  }

  // PRE: L is defined. THIS MUST BE EMPTY
  // POST: This object is defined and is a deep copy of L.
  //       Thus, f = L.f, with all the Nodes in f being physically
  //         distinct from the Nodes of L.
  //       n = L.n
  //       Note here that L is being passed by reference to avoid the
  //        shallow copy of the actual parameter being passed as L. We
  //        indicate that L does not change with the keyword const.
  LinkedList & operator= (LinkedList & L){
    delete(front); //delete any old data
    delete(back);
    numItems = 0;  //and set size to 0
    Node<T> * temp = L.front; //get the first node of the other list
    for (int i=0; i<L.numItems; i++) { //for item in L
      addBack (temp); //add it to this list
      temp = temp->getNext(); //traverse L
    }
    return (*this); //return this object
  }

  // ======================================== 
  // destructor
  // ======================================== 
  
  // PRE: This object is defined.
  // POST: This object has no elements. f = NULL and n = 0.
  //       All space allocated for this object is deallocated.
  ~LinkedList(){
    numItems = 0;
    delete (front); //this will recursively delete the list
    front = NULL;
    back = NULL;
  }

  // ======================================== 
  //       accessor functions
  // ======================================== 

  // PRE: This object is defined.
  // POST: RV = n.
  int getSize () const{return (numItems);};

  // PRE: This object is defined and n > 0.
  // POST: RV = the integer stored in f(0).
  Node<T> * getFront () const{return (front);};

  Node<T> * getBack () const{return (back);};

  // Pre:  index < numItems
  // Post: The pointer to the item at that index
  Node<T> * operator[](int index){
    Node<T> * temp = front;
    for (int i=0; i<index; i++){
      temp = temp->getNext();
    }
    return (temp);
  }

  // ======================================== 
  // modifier functions
  // ======================================== 

  //Pre:  newData is defined
  //Post: The new node is created and added
  void addFront(T newData){
    Node<T> * newNode = new Node<T>(newData);
    addFront(newNode);
  }

  // PRE: new is defined. This object is defined.
  // POST: This object is defined with n = (pre)n + 1. An Node
  //       object t contains the integer data v.
  //       f = t, (pre)f(0),(pre)f(1),...,(pre)f((pre)n).
  //       NOTE: (pre) is an informal mechanism of referring to the
  //       state of the variable in the PRE state of the
  //       function. 
  void addFront (Node<T> * newNode){
    if (numItems == 0){ //if no items are in the list
      front = newNode; //set the front to this node
      back = newNode; //set the back to this node as well
    }
    else{
      newNode->setNext(front); //set next of new front
      front->setPrevious(newNode); //set the previous of the old front
      front = newNode; //set new front
    }
    numItems++; //increment items
  }


  //Pre:  newData is defined
  //Post: The new node is created and added
  void addBack(T newData){
    Node<T> * newNode = new Node<T>(newData);
    addBack(newNode);
  }

  //Pre:  newNode is defined
  //Post: New back element is added
  void addBack (Node<T> * newNode){
    if (numItems == 0){ //if no items are in the list
      front = newNode; //set the front to this node
      back = newNode;
    }
    else{
      newNode->setPrevious(back); //set previous of new back
      back->setNext(newNode); //set next of old back to new node
      back = newNode; //set new back
    }
    numItems++; //increment items
  }

  // Pre:  hiddenNode is defined
  // Post: true false if nodes exists in list
  bool has(Node<T> * hiddenNode){
    T data = hiddenNode->getData();
    bool in = false;
    if (find(data) != NULL){
      in = true;
    }
    return(in);
  }

  // Pre:  hiddenNode is defined
  // Post: the node if it exists in list, otherwise NULL
  Node<T> * find(T & searchData){
    Node<T> * current = front; //get the front
    Node<T> * final = NULL;
    bool found = false;
    while ((current != NULL)&&(!found)){ //traverse the list
      if (current->getData() == searchData){ //if found
	found = true; //break the loop
	final = current; //set the final
      }
      current = current->getNext(); //traverse
    }
    return(final);
  }


  // PRE: This object is defined. n > 0.
  // POST: This object is defined and n = (pre)n - 1. 
  //       f = (pre)f(1), (pre)f(2),..., (pre)f((pre)n-2).
  void deleteFront (){
    Node<T> * temp = front->getNext(); //hold onto the new front
    delete(front->remove()); //get rid of the first element
    front = temp; //set the new front
    numItems --;
  }

  //Pre:  This list is defined with numItems > 0
  //Post: The back is set to it's previous, the old back is then
  //      deleted 
  void deleteBack(){
    Node<T> * temp = back->getPrevious(); //hold onto the new back
    delete(back->remove()); //get rid of the last element
    back = temp; //set the new front    
    numItems --;
  }

  // Pre: N is defined. This object is defined. n > N.
  // Post: The list is appropriately 
  void del (int N){
    delete((*this)[N]->remove()); //remove the nth element and then
    // delete the pointer to that node
    numItems--; //decrement num items
  };

  // Pre:  
  // Post: Linked list sorted with merge sort
  void sort(){
    mergeSort(); //call merge sort
    back = (*this)[numItems-1]; //get the new back, merge sort can't
    // handle this on it's own without exponentiall increasing runtime
  };


  // ======================================== 
  //     Input/Output
  // ======================================== 

  // PRE:  L is defined. and has more than one element
  // POST: str contains L.f(0),...,L.f(L.n-1).
  //       NOTE: Here L.f refers to the elements of the LinkedList
  //       object L. 
  friend ostream & operator<< (ostream & str, LinkedList & L){
    str << "LinkedList -" << L.numItems << " ";

    /* Node<T> * temp = L.back; */
    /* for (int index = L.numItems; index > 0; index--) { */
    /*   str << "[" << *temp << "] "; */
    /*   temp = temp->getPrevious(); */
    /* } */

    Node<T> * temp = L.front;
    for (int index = 0; index < L.numItems; index++) {
      str << "[" << *temp << "] ";
      temp = temp->getNext();
      // ASSERT: str contains L.f(0), L.f(1), ..., L.f(index),
    }
    return (str);  // The stream is modified by thie operation. So, we
    // need to return the modified stream.
  };

};

#endif
