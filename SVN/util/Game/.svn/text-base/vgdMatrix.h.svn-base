#ifndef INCLUDED_VGDMATRIX
#define INCLUDED_VGDMATRIX

#include "Matrix.h"

template <class T>
class vgdMatrix : public Matrix{


  // Pre:  array is full of num elements
  // Post: The array is loaded in as the rightmost column
  vgdMatrix(const T & array, int num){
    Data = NULL; // Initialize Data
    Rows = Cols = num; // Set the dimensions of matrix
    initData(Rows, Cols); // Initialize all data slots
    for (int row=0; row<Rows; row++){
      Data[row][Cols-1] = array[row]; // Copy in provided values
    }
  }

  // Pre:  N/a
  // Post: A single dimensional array in row-major listing is returned
  // WARNING: This array is allocated with new and must be deleted
  T * array() const{
    T * array = new T[Rows*Cols];
    for (int row=0; row<Rows; row++)
      for (int col=0; col<Cols; col++)
	array[col*Rows + row] = Data[row][col]; // Extract Data
    return(array); // return the pointer to the new array
  };
  
}


#endif
