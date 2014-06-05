#ifndef INCLUDED_intNode
#define INCLUDED_intNode

class intNode {

  // Class Invariant (CI): This object contains a defined integer n and 
  //                       a pointer p to the next intNode object.

 private:
  int data;             // stores the data item in this node
                        // denoted by n.
  intNode * nextItem;   // store the pointer to the next intNode, if
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
  intNode();

  // PRE: num = v is defined.
  // POST: This object is defined with n = v, and p = NULL.
  intNode (int num);


  // ======================================== 
  //       accessor functions
  // ======================================== 

  // PRE: This object is defined.
  // POST: RV = n.
  int getData () const;   // the keyword const indicates that this
                          // member function does not modify this
                          // object. 

  // PRE: This object is defined.
  // POST: RV = p.
  intNode * getNext () const;

  // ======================================== 
  // modifier functions
  // ======================================== 

  // PRE: This object is defined. num = v is defined.
  // POST: This object is defined and n = v.
  void setData (int num);

  // PRE: This object is defined. next = x is defined.
  // POST: This object is defined and p = x.
  void setNext (intNode * next);


  /* === COMMENTED OUT DESTRUCTOR
  // PRE: This object is defined.
  // POST: The object that next pointed to is destroyed.
  ~intNode();

  === COMMENTED OUT DESTRUCTOR */

};
#endif
