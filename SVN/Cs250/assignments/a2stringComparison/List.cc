#include <iostream>
#include "List.h"

using namespace std;

// Default constructor
// PRE:
// POST: currentMax = 1. currentSize = 0. There is one space
//         allocated for 
//         CI is satisfied.
List::List () {
  currentMax = 1;
  theList = new int[currentMax];
  currentSize = 0;
}

//Pre:  
//Post: The current length of the list is returned as an integer
int List::length() const{
  return (currentSize);
}

// PRE: This List object is defined and satisfies the CI.
// POST: OS contains the intacters in this list.
void List::print () const{
  cout << "[";
  for (int i=0; i<currentSize; i++){
    cout << theList[i];
    if (i<currentSize-1){
      cout << ",";
    }
  }
  cout << "]\n";
}

//Pre:  A location in memory to store the index of the min
//Post: The index of the minimum of the list is given, if the list
//      is empty, a print statement appears and the list will return
//      a garbage value.  The integer value passed is changed to
//      hold the index of the min
int List::min (int & index) const{
  int min; //init minimum value storage
  if (currentSize == 0){
    cout << "\nERROR: Can't take .min() of empty list\n\n";
  }
  else{
    min = theList[0]; //get the first value as the min
    index = 0; //set index to the current min's index
    for (int i=0; i<currentSize; i++){
      if (theList[i] < min){
	index = i;
	min = theList[i];
      }
    }
  }
  return (min);
}

//Pre:  The index to be returned, assert this index is in the range of
//      the list or else segmentation fault
//Post: The value stored at that index, or a warning before the seg fault
int List::index(int index) const{
  if (index > currentSize-1){
    cout << "Warning:  Accessing index out of range in List\n";
  }
  return (theList[index]);
}


// PRE: This List object is defined with values 
//       currentMax = M, currentSize = S, and satisfies the CI.
// POST: num is defined. 
//       theList[0]..theList[S-1] are the same as before.
//       theList[S] = num
//       theList[S+1] = '\0'
//       The result object satisfies the CI.
void List::add (int num) {
  if ((currentMax - currentSize) <= 0){ //if the current array is full
    //       ( '<= 0' is used simply for safety but unnecessary)
    int * tempList = theList; //create a temp pointer to the old
    //       list
    theList = new int[(currentMax)*2]; //create a new arry twice as
    //       large for theList
    for (int i=0; i<currentSize; i++){ //Cycle through old list
      theList[i] = tempList[i]; //transfer values to new array
    }
    currentMax = (currentMax)*2; //Double the size of current max
    delete tempList; //Delete old useless array
  }
  theList[currentSize] = num; //Add new num
  currentSize ++; //increment currentSize
}

// PRE: This List object is defined.
// POST: Free the memory allocated for the List.
List::~List() {
  delete (theList);
  // You could also use
  //  free (theList); //for memory allocation involving c function malloc
}
