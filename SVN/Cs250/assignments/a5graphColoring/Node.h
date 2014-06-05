#ifndef INCLUDED_Node
#define INCLUDED_Node

#include <iostream>
using namespace std;

template <class T>
class Node {
  // Class Invariant (CI): This object contains a defined integer n
  //                       and a pointer p to the next Node object.

 private:
  T data;
  Node<T> * previous; //pointer to previous node
  Node<T> * next;   // store the pointer to the next Node, if
  // any. If there  is no next node, this
  // pointer has a value NULL
  // denoted by p.

 public:
  
  // ======================================== 
  // constructors
  // ======================================== 

  // default constructor
  // PRE: 
  // POST: This object is defined with n = 0 and p = NULL.
  Node(){
    previous = NULL;
    next = NULL;
  };

  // PRE: newData is defined
  // POST: data is set to equal new data
  Node (const T & newData){
    data = newData;
    previous = NULL;
    next = NULL;
  };

  //Pre:  Copy constructor N is defined
  //Post: shallow copy of N
  Node (const Node<T> & N){
    data = N.data;
    previous = NULL;
    next = NULL;
    if (N.next != NULL){
      next = new Node<T>(*N.next);
      next->setPrevious(this);
    }
  };

  // =======================================
  //          operators
  // =======================================

  //Pre:  N is defined
  //Post: copy of N
  Node operator= (const Node<T> & N){
    data = N.data;
    previous = NULL;
    next = NULL;
    if (N.next != NULL){
      next = new Node<T>(*N.next);
      next->setPrevious(this);
    }
  };

  //Pre:  N is defined
  //Post: bool if other.data == this.data
  bool operator== (const Node<T> & N){
    return(data == N.data);
  };

  //Pre:  N is defined
  //Post: bool if other.data > this.data
  bool operator> (const Node<T> & N){
    return(data > N.data);
  };

  //Pre:  N is defined
  //Post: bool if other.data < this.data
  bool operator< (const Node<T> & N){
    return(data < N.data);
  };

  //Pre:  N is defined
  //Post: bool if other.data > this.data
  bool operator>= (const Node<T> & N){
    return(data >= N.data);
  };

  //Pre:  N is defined
  //Post: bool if other.data < this.data
  bool operator<= (const Node<T> & N){
    return(data <= N.data);
  };

  //Pre:  
  //Post: This dereferenced is returned
  Node<T> & operator++(int null){
    data++;
    return(*this);
  };

  // ======================================== 
  //       accessor functions
  // ======================================== 

  // PRE: This object is defined.
  // POST: RV = n.
  T getData () const{
    return (data);
  };

  // PRE: This object is defined.
  // POST: RV = p.
  Node<T> * getNext () const {
    return (next);
  };

  // PRE: This object is defined.
  // POST: RV = p.
  Node<T> * getPrevious () const {
    return (previous);
  };

  //Pre:  amount is defined, every node in that range has children
  //Post: The node that many places away is returned
  Node<T> * traverse(int amount){ //should be const, but can't?
    Node<T> * temp = this;
    for (int i=0; i<amount; i++){
      temp = temp->getNext();	//if not at the end of the list
    }
    return (temp);
  };

  Node<T> * traverseCyclic(int amount, Node<T> * front){
    Node<T> * temp = this;
    for (int i=0; i<amount; i++){
      if (temp->getNext() != NULL){
	temp = temp->getNext();	//if not at the end of the list
      }
      else{//else start from the beginning
	temp = front;
      }
    }
    return (temp);    
  }

  //Pre:  
  //Post: Debug information is printed about this node and it's
  //      surrounding nodes if they exist
  Node<T> * debug(){
    cerr << "======Node.h Line 103: Debug Print=====" << endl;
    cerr << "\nthis.data: "<<data << endl;
    if (previous != NULL){
      cerr << "\nthis.previuos.data: "<<previous->data << endl;
      cerr << "this.previuos.next.data: "<<previous->next->data << endl;
    }
    if (next != NULL){
      cerr << "\nthis.next.data: "<<next->data << endl;
      cerr << "this.next.prvious.data: "<<next->previous->data << endl;
    }
    cerr << "=============DONE=============" << endl;
  };

  // ======================================== 
  //          modifier functions
  // ======================================== 

  //Pre:  other is defined
  //Post: This node and other is merged by recursively calling
  //      the children of each.
  //      WARNING:: other will now be deleted if this node is deleted,
  //      that means that delete will only have to be called on this
  //      Node
  void merge(Node<T> * other){
    if (other != NULL){ //valid merge is occuring
      if (other->data < data){ //if the other node was smaller
	if (previous != NULL){ //if there is a previous
	  previous->next = other; //point it at other (bc other<this)
	}
	other->merge(this); //call merge from the smaller node
      }
      else{
	Node<T> * thisNext = next; //hold onto this.next
	next = other; //link next to other
	previous = other->previous; //get other's previous
	other->previous = this; //link other.previous here
	other->merge(thisNext); //merge other with the next node in
	//sequence 
      }
    }
  }

  //Pre:  other is defined and has data of the same type as this
  //Post: The data values for the two are swapped
  void swap(Node<T> * other){
    //Swap data values
    T temp = data;
    data = other->data;
    other->setData(temp);
    //Swap next values
    Node<T> * n = next;
    next = other->next;
    other->next = n;
    //Swap previous values
    n = previous;
    previous = other->previous;
    other->previous = n;

    //Adjust appropriately the surrounding nodes
    if (previous != NULL){
      previous->next = this;
    }
    if (next != NULL){
      next->previous = this;
    }
    if (other->previous != NULL){
      other->previous->next = this;
    }
    if (other->next != NULL){
      other->next->previous = this;
    }
  }

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
  void setNext (Node<T> * nextItem){
    next = nextItem;
  };

  //Pre:  newPrevious is defined or NULL
  //Post: previous is set
  void setPrevious(Node<T> * newPrevious){
    previous = newPrevious;
  }

  //Pre:  called in order to remove this element
  //Post: The pointer to this is returned, so it can be immediately
  //      deleted 
  Node<T> * remove(){
    if (previous != NULL){
      //if there was a previous, fill the gap
      previous->setNext(next);
    }
    if (next != NULL){
      //if there was a next, fill the gap
      next->setPrevious(previous);
    }
    next = NULL; //remove ties to make sure the
    previous = NULL; //destructor works properly
    return(this);
  }

  //========================================
  //           friend fucntions
  //========================================

  //Pre:  ostr is defined, n is defined
  //Post: The data of n (opt. and it's children) is printed
  friend ostream & operator<<(ostream & out, Node<T> & n){
    out << n.data;
    return(out);
  }

  //========================================
  //               Destructor
  //========================================

  // PRE: This object is defined.
  // POST: The object that next pointed to is destroyed.
  ~Node(){
    delete(next);
  }

};
#endif
