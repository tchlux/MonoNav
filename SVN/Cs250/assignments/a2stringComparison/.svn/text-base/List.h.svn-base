#ifndef INCLUDED_List
#define INCLUDED_List

class List {
  
 private:
  
  int * theList;    // pointer to the space allocated for the array of
		    // numbers.
  int currentMax;   // the maximum number of numbers that can be
		    // currently accommodated in this List object.
  int currentSize;  // the number of numbers currently in this
		    // List object.

  // CI: theList points to space allocated for at least one
  //       number.
  //     currentMax >= 0. theList points to space allocated for
  //       currentMax numbers
  //     currentSize = 0. currentSize <= currentMax.
  //       theList[0]..theList[currentSize-1] is
  //       defined.

 public:

  // Default constructor
  // PRE:
  // POST: currentMax = 0. currentSize = 0. There is one space
  //         allocated for the object. theList[0] = '\0'. 
  //         CI is satisfied.
  List ();

  //Pre:  
  //Post: The current length of the list is returned as an integer
  int length() const;

  // PRE: This List object is defined and satisfies the CI.
  // POST: OS contains the integers in this list.
  void print () const;

  //Pre:  A location in memory to store the index of the min
  //Post: The index of the minimum of the list is given, if the list
  //      is empty, a print statement appears and the list will return
  //      a garbage value  The integer value passed is changed to
  //      hold the index of the min
  int min(int & index) const;

  //Pre:  The index to be returned
  //Post: The value stored at that index, or a warning before the seg fault
  int index(int index) const;

  // Modifiers

  // PRE: This List object is defined with values 
  //       currentMax = M, currentSize = S, and satisfies the CI.
  // POST: num is defined. 
  //       theList[0]..theList[S-1] are the same as before.
  //       theList[S] = ch
  //       theList[S+1] = '\0'
  //       The result object satisfies the CI.
  void add (int num);

  // PRE: This List object is defined.
  // POST: Free the memory allocated for the List.
  ~List();
};


#endif
