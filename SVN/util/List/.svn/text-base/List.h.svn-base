#ifndef INCLUDED_LIST
#define INCLUDED_LIST

#include <iostream>

#define INITIAL_LIST_SIZE 4
#define LIST_GROWTH_FACTOR 2

template<class T>
class List{
  // This is an automatically resizing structure for holding arrays of
  //   the same data type
protected:
  T * Data; // Holds the data array
  int Max; // Max number of elements in current array
  int Size; // Number of elements currently in list

  // Copies data from first array to second in this List
  void copyData(T * oldData, T * newData){
    for (int index=0; index<Size; index++){
      newData[index] = oldData[index];
    }
  }

public:
  // Default constructor
  List(){
    Data = new T[INITIAL_LIST_SIZE]; // Create new array
    Max = INITIAL_LIST_SIZE; // Current Array size
    Size = 0; // No elements
  };

  // Copy constructor
  List(List<T> & other){
    Data = new T[0]; // Initialize data to nothing so that the
    //  delete in "operator=" does not free trash data (seg fault)
    (*this) = other;
  }

  // Pre:  other is well defined and Data has already been 
  // Post: 
  List<T> & operator=(List<T> & other){
    delete[]Data;
    Max = other.Max; Size = other.Size;
    Data = new T[Max];    
    copyData(other.Data, Data);
    return(*this);
  }

  // =============================
  //      Setters and Getters     
  // =============================

  // Pre:  0 <= index < Size, value is initialized
  // Post: Data[index] is set to be value
  void set(int index, const T value) { Data[index] = value; };

  // Pre:  0 <= index < Size
  // Post: A reference to the data in that location is returned
  T & operator[](int index) { return(Data[index]); };

  // Returns the number of elements in the list
  int length() const { return(Size); };
  int size() const { return(Size); };
  // Returns the last element in this list
  T back() const { return(Data[Size-1]); };

  // Pre:  0 <= index < Size
  // Post: A copy of the data in that location is returned
  T get(int index) const { return(Data[index]); };

  // ==================
  //      Removers     
  // ==================

  // Pre:  0 <= index < Size
  // Post: The value at index is returned, and removed from the list
  // Big O class: O(n)
  T pop(int index){
    T value = Data[index];
    remove(index);
    return(value);
  }

  // Pre:  0 <= index < Size
  // Post: The value at index is removed, all proceeding values are
  //       slid to lower indices ( O(n) )
  // Big O class: O(n)
  void remove(int index){
    for (int i=index; i<(Size-1); i++){
      Data[i] = Data[i+1];
    }
    Size--;
  }

  // Clears out all data from this list an reallocates new space
  void clear() { 
    delete[]Data;
    Data = new T[INITIAL_LIST_SIZE];
    Max = INITIAL_LIST_SIZE; Size = 0;
  };

  // ===================
  //      Appenders     
  // ===================

  // Pre:  data is of length size
  // Post: All of data is added to
  void append(const T * data, int size){
    for (int index=0; index<size; index++){
      append(data[index]); // Each element to this list
    }
  }

  // Pre:  data is valid
  // Post: data is added to storage
  void append(const T & data){
    if (Size >= Max){
      Max *= LIST_GROWTH_FACTOR;
      T * oldData = Data;
      Data = new T[Max];
      copyData(oldData, Data);
      delete[]oldData;
    }
    Data[Size] = data;
    Size++; // Increment the size    
  }

  // =====================
  //      Destructors     
  // =====================

  // Delete List data
  ~List(){ 
    delete[]Data;
  }

  // ===================
  //      Debuggers     
  // ===================

  // Prints all elements in list to cerr, primarilly for debugging
  void print() const{
    std::cerr << (*this) << std::endl;
  };

  // Pre:  out is well defined, list is initialized
  // Post: The contents of list are put into out
  friend std::ostream & operator<<(std::ostream & out, 
				   const List<T> & list){
    out << "[";
    for (int index=0; index<list.Size; index++){
      out << list.Data[index];
      if (index < (list.Size-1)) out << ", ";
    }
    out << "]";
    return(out);
  }

};

#endif
