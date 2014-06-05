#ifndef INCLUDED_LoopNode
#define INCLUDED_LoopNode

#include <iostream>
using namespace std;

template <class T>
class LoopNode {
  // Class Invariant (CI): This object contains a defined type T
  //                       and pointers to the next and previous nodes

private:
  T data; // Holder for this node's data
  LoopNode<T> * previous; //pointer to previous node
  LoopNode<T> * next;   // store the pointer to the next LoopNode
  // Pointers default to NULL, data should be set after init

public:
  
  // =====================================================
  //      Constructors: Default, Copy, and Given Data     
  // =====================================================

  // default constructor
  // PRE: 
  // POST: This object is defined with n = 0 and p = NULL.
  LoopNode(){
    previous = NULL;
    next = NULL;
  };

  // PRE: newData is defined
  // POST: data is set to equal new data
  LoopNode (const T newData){
    data = newData;
    previous = NULL;
    next = NULL;
  };

  //Pre:  Copy constructor N is defined
  //Post: shallow copy of N (just data)
  LoopNode (const LoopNode<T> & N){
    previous = NULL;
    next = NULL;
    (*this) = N;
  };

  // =======================================
  //          operators
  // =======================================

  //Pre:  N is defined
  //Post: shallow copy of N (just data)
  LoopNode & operator= (const LoopNode<T> & N){
    data = N.data;
  };

  //Pre:  N is defined
  //Post: bool if other.data == this.data
  bool operator== (const LoopNode<T> & N) const{
    return(data == N.data);
  };

  //Pre:  N is defined
  //Post: bool if other.data > this.data
  bool operator> (const LoopNode<T> & N) const{
    return(data > N.data);
  };

  //Pre:  N is defined
  //Post: bool if other.data < this.data
  bool operator< (const LoopNode<T> & N) const{
    return(data < N.data);
  };

  //Pre:  N is defined
  //Post: bool if other.data > this.data
  bool operator>= (const LoopNode<T> & N) const{
    return(data >= N.data);
  };

  //Pre:  N is defined
  //Post: bool if other.data < this.data
  bool operator<= (const LoopNode<T> & N) const{
    return(data <= N.data);
  };

  //Pre:  null integer, not used, just required
  //Post: This dereferenced is returned
  LoopNode<T> & operator++(int null){
    data++;
    return(*this);
  };

  // ================================
  //      Accessors and Traverse     
  // ================================

  // PRE: This object is defined.
  // POST: RV = n.
  T getData () const{
    return (data);
  };

  // PRE: This object is defined.
  // POST: RV = p.
  LoopNode<T> * getNext () const {
    return (next);
  };

  // PRE: This object is defined.
  // POST: RV = p.
  LoopNode<T> * getPrevious () const {
    return (previous);
  };

  //Pre:  amount is defined, every node in that range has children
  //Post: The node that many places away is returned
  LoopNode<T> * traverse(int amount) const{
    LoopNode<T> * temp = this;
    if (amount > 0){ // Forwards traversal
      for (int i=0; i<amount; i++){ // For Node in range amount
	temp = temp->getNext();	//Continue to traverse
      }
    }
    else{ // Backwards traversal
      for (int i=0; i<(-amount); i++){ // For Node in range amount
	temp = temp->getPrevious();    //Continue to traverse
      }
    }
    return (temp);
  };

  //========================================
  //        "set" modifiers & remove
  //========================================

  // PRE: This object is defined. num = v is defined.
  // POST: This object is defined and n = v.
  void setData (T newData){
    data = newData;
  };

  // PRE: This object is defined. next = x is defined.
  // POST: This object is defined and p = x.
  void setNext (LoopNode<T> * nextItem){
    next = nextItem;
  };

  //Pre:  newPrevious is defined or NULL
  //Post: previous is set
  void setPrevious(LoopNode<T> * newPrevious){
    previous = newPrevious;
  };

  //Pre:  called in order to remove this element
  //Post: The pointer to this is returned, so it can be immediately
  //      deleted 
  LoopNode<T> * remove(){
    //Call like this
    // delete(LoopNode<T>*->remove())
    if (previous != NULL){
      //if there was a previous, fill the gap
      previous->setNext(next);
    }
    if (next != NULL){
      //if there was a next, fill the gap
      next->setPrevious(previous);
    }
    next = NULL; //remove ties to make sure the destructor
    previous = NULL; //doesn't delete other nodes
    return(this);
  };

  //========================================
  //           friend fucntions
  //========================================

  //Pre:  ostr is defined, n is defined
  //Post: The data of n (opt. and it's children) is printed
  friend ostream & operator<<(ostream & out, const LoopNode<T> & N){
    out << N.data;
    return(out);
  };

  //========================================
  //               Destructor
  //========================================

  // PRE: This object is defined.
  // POST: The object that next pointed to is destroyed.
  ~LoopNode(){
    if (next != NULL){
      delete(next);
    }
  };

  // Debug print information, checking data, previous, next
  void debug(){
    cout << "Debug Print for LoopNode with data: " << data << endl;
    if (previous != NULL){
      cout << "Previous: " << *previous << endl;
    }
    if (next != NULL){
      cout << "Next:     " << *next     << endl;
    }
  };

};
#endif
