#ifndef INCLUDED_LINK
#define INCLUDED_LINK

#include "iostream" // For the ostream operator

#define DATA_NOT_FOUND -1 // Index for data not being found in Link

// ===================================================
//      This is a linked list class optimized for     
//       inserting and removing elements quickly      
// ===================================================

// ==========================
//      Member Functions     

// (constructor)
//   with no data and no elements, size of 0

// (destructor)
//   deep delete of all attached nodes

// int size()		- returns the current number of elements

// void spin()		- "spins" the list so current head goes to end
//                        and new
//			  head is the next element in the list

// int find(T&)         - Finds given "data" in the linked list with
//                        the equivilance operator, returns it's index
//                        or DATA_NOT_FOUND if it does not exist

// bool has(T&)         - Returns true an element exists in this list

// void clear()		- deletes and frees all memory and resets size

// void remove(int)	- removes this index from the list (uses modulus
//			  to wrap indices out of bounds back in range)

// void add(T&) 	- Adds given data into the list (constant time)

// Link<T>& operator+=(Link<T>&) - Cycles all elements of the given
//                                 Link and adds them to this list

// T& operator[](int)   - Returns data at that index (O(n/2)) uses
//                        modulus to wrap indices into bounds

// operator<<           - Returns the linked list illustrated in asci

// print                - Uses operator<< on standard out

//      End Functions     
// =======================


template <class T>
class Node{
public:
  T Data;  // Data holder
  Node<T> * Next; // Next node
  Node<T> * Prev; // Previous node

  // Default constructor
  Node(){ Next = Prev = Data = NULL; };

  // Constructor given data
  Node(const T & data){Data = data; Next = Prev = NULL; };

  // Destructor (linked to next)
  ~Node(){
    if (Next != NULL)
      delete(Next);    
  };
};


template <class T>
class Link{
protected:
  Node<T> * Head;  // Head of linked list  
  Node<T> * Tail;  // Tail of linked list
  int Size;	   // Number of elements in this list

  // Pre:  0 <= i < Size
  // Post: The node at that position is returned (optimized for either
  // first or last element retrieval) 
  // Big O class: O(n/2)
  Node<T> * getNode(int i){
    Node<T> * curr = i < Size / 2 ? Head : Tail;
    if (i < Size / 2)
      for (int n=0; n<i; n++)
	curr = curr->Next;
    else
      for (int n=0; n<(Size-1-i); n++)
	curr = curr->Prev;
    return(curr);
  };

public:
  // Default constructor
  Link(){ Head = Tail = NULL; Size = 0; };

  // Destructor: Deletes nodes from head using clear method
  ~Link(){ clear(); };

  // Returns the current size of this list
  int size() const{ return(Size); };

  // Pre:  If head != NULL then there are new allocated nodes in this
  // Post: All nodes are freed from memory, Member data is reset
  void clear(){  
    if (Head != NULL){
      delete(Head); // Call recursive delete through nodes
      Head = Tail = NULL; // Reset to NULL pointers
      Size = 0; // Set size to 0
    }
  };

  // Post: The elements in this list are spun, last comes to first,
  //       first goes to second etc
  void spin(){
    if (Head != NULL){
      Head->Prev = Tail;  Tail->Next = Head; 
      Head = Tail;        Tail = Tail->Prev;
      Tail->Next = Head->Prev = NULL;
    }
  };

  // Pre:  0 <= index < Size
  // Post: That Node is removed from this list
  void remove(int index){
    while (index < 0) index += Size; index = index % Size;
    Node<T> * toRemove = getNode(index);
    Node<T> * prev = toRemove->Prev;
    Node<T> * next = toRemove->Next;
    if (prev != NULL)  prev->Next = next;
    if (next != NULL)  next->Prev = prev;
    toRemove->Prev = toRemove->Next = NULL; // Set nodes to NULL
    delete(toRemove);    Size --; // One less element :(
    if (toRemove == Head) Head = next;
    if (toRemove == Tail) Tail = prev;
  };

  // Pre:  data is well defined
  // Post: A new node is created with data as its contents, size is
  //       incremented, Head and Tail are managed
  void add(const T & data){
    if ((Head == NULL) && (Tail == NULL))
      Head = Tail = new Node<T>(data);
    else{
      Tail->Next = new Node<T>(data); // Create new node
      Tail->Next->Prev = Tail; // Link back to current Tail
      Tail = Tail->Next; // Set the tail to be that new back node
    }
    Size++; // One more element!
  };

  // Pre:  other is well defined
  // Post: all nodes are shallow copied
  Link<T> & operator+=(const Link<T> &other){
    for (int n=0; n<other.size(); n++){
      add(other[0]); 
      other.spin();
    }
  }

  // Pre:  data is well defined and has an operator==
  // Post: the last occuring index of data if it exists in this Link
  int find(const T &data){
    int index = DATA_NOT_FOUND;
    for (int item=0; item<Size; item++){
      if (Head->Data == data)
	index = item;
      spin(); // Spin this list (to reduce big O to 'n')
    }
    return(index);
  }

  // Pre:  data is well defined and has an operator==
  // Post: true if data exists in this link
  bool has(const T &data){
    return(find(data) != DATA_NOT_FOUND);
  }

  // Pre:  0 <= index < Size
  // Post: The node at that position is returned
  T & operator[](int index){
    while (index < 0) index += Size; index = index % Size;
    return(getNode(index)->Data); // Return the data in that node
  };

  // Pre:  Called
  // Post: This data is sent to an ostream
  void print() const { std::cerr << (*this) << std::endl; };

  // Pre:  out is defined, link is well-defined
  // Post: All elements of link are sent to the ostream
  friend std::ostream & operator<<(std::ostream & out, 
				   const Link<T> & link){
    out << "(";
    Node<T> * curr = link.Head;
    for (int n=0; n<link.Size; n++){
      if (curr == link.Head)
	out << "H";
      if (curr == link.Tail)
	out << "T";
      out << curr->Data;
      curr = curr->Next;
      if (curr != NULL)
	out << ")-(";
    }
    out << ")";
    return(out);    
  };

};

#endif
