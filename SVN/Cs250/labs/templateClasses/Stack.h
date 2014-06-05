#ifndef included_Stack
#define included_Stack
#define MAXSIZE 100

#include <iostream>

using namespace std;

template <class T>
class Stack
{ // Class Invariant: topPosition is the index of the next available
  //   position on this stack. 
  //   empty == true <==> topPosition == 0.
  //   full == true <==> topPosition == MAXSIZE
  
private:
  T Data[MAXSIZE];
  bool empty;
  bool full;
  int topPosition;

public:
  
  // Constructors
  Stack()
    {
      empty = true;
      full = false;
      topPosition = 0;
    };
  
  // Operations / Modifiers.
  // PRE: This stack is defined and is not full. 
  //       Element is defined = e.
  // POST: The new stack contains e as its top element.
  //         That is, after this function, top() == e.
  //         topPosition is modified, and full is updated.
  void push (T Element)
  {
    Data[topPosition] = Element;
    topPosition++;
    // ASSERT: topPosition is the index of the next available position
    // on the stack.
    if (topPosition == MAXSIZE)
      full = true;
    // ASSERT: full == true <==> topPosition == MAXSIZE

    if (empty)
      empty = false;
    // ASSERT: Stack is now not empty.
  };


  // PRE: This stack is defined and is not empty.
  // POST: topPosition is modified; empty is updated.
  T pop ()
  {
    topPosition--;
    T returnValue = Data[topPosition];
    if (topPosition == 0)
      empty = true;
    // ASSERT: empty == true <==> topPosition == 0

    if (full)
      full = false;
    // ASSERT: Stack is now not full.
    return (returnValue);
  };


  // Accessors
  // PRE: This stack is defined and is not empty.
  // POST: RV = e = the element at the top of the stack.
  //        The stack is not modified.
  T top () const
  {
    return (Data[topPosition-1]);
    // ASSERT: RV = e = the element at the top of the stack.
  };


  // Predicates
  
  // PRE: This stack is defined.
  // POST: RV = true <==> this stack is empty <==> topPosition == 0
  //        The stack is not modified.
  bool isEmpty() const {return (empty);};

  // PRE: This stack is defined.
  // POST: RV = true <==> this stack is full <==> topPosition == MAXSIZE
  //        The stack is not modified.
  bool isFull() const {return (full);};

  //Pre:  str is defined, stack is of correct type and defined
  //Post: Each element of stack is added to the ostream
  friend ostream & operator<<(ostream & str, Stack<T> stack)
  {
    str << "("; //open parenthesis
    for (int i=0; i<stack.topPosition; i++){ //for item in Data
      str << stack.Data[i]; //add item to ostream
      if (i < stack.topPosition-1){ //if not the last item
	str << ", ";  //add a comma and a space
      }
    }
    str << ")"; //add end parenthesis
    return (str); //return ostream object
  };


};

    

#endif
