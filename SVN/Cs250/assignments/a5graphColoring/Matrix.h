#include <iostream>

using namespace std;

template <class T>
class Matrix{

  //CI: Matrix is a two dimensional array of type T, it is useful for
  //    mathematical operations on matrices.  
  //    rows = cols currently implemented as square matrix only

private:

  T init;    //Initial value for slots in this matrix 
  T ** data; //holder for the two-d array of data
  int size;  //current size of matrix
  int max;   //current max size of matrix

public:

  // ======================
  //      Constructors     
  // ======================

  // Default constructor
  Matrix(){
    data = NULL;
    size = 0;
    max = 0;
  }

  // Pre: initValue is the value all slots in the matrix are
  //      initialized to
  Matrix(T initValue){
    init = initValue;
    data = NULL;
    size = 0;
    max = 0;
  };

  // Pre:  size is an integer > 0
  // Post: data storage is initialized
  Matrix(T initValue, int s){
    init = initValue;
    size = s;
    max = s;
    data = new T*[max];
    for (int i=0; i<max; i++){
      data[i] = new T[max];
      for (int s=0; s<max; s++){
	data[i][s] = init; //initialize every slot
      }
    }
  };

  // Pre:  other is defined
  // Post: this is built as a copy of other
  Matrix(Matrix<T> & other){
    data = NULL;
    size = 0;
    max = 0;
    (*this) = other;
  }

  // ====================
  //      Destructor     
  // ====================

  ~Matrix(){
    delete(data);
  };

  // ============================
  //      Accessor functions     
  // ============================

  // Returns the current value of size
  int getSize(){return(size);};

  // Returns the current value of max
  int getMax(){return(max);};

  // Return the current value of init
  T getInit(){return(init);};

  // =================================
  //      Public member functions     
  // =================================

  // Pre:  initValue is of type T and initialized
  // Post: init is set in this class
  void setInit(T initValue){
    init = initValue;
  }

  // Pre:  
  // Post: The size of this matrix is expanded by one
  void expand(){
    size ++;
    // If an expansion is in order
    if (size > max){
      int oldMax = max;
      max = (max+1)*2;
      // create space for a new array
      T ** newData = new T*[max];
      for (int i=0; i<max; i++){
	newData[i] = new T[max];
	for (int s=0; s<max; s++){
	  newData[i][s] = init; //initialize every slot
	}
      }
      //for element in old matrix (size-1)
      for (int row=0;row<(size-1);row++){
	for (int col=0;col<(size-1);col++){
	  // copy the element
	  newData[row][col] = data[row][col];
	}
      }
      // delete all of the old data
      for (int i=0; i<oldMax; i++){
	delete(data[i]);
      }
      delete(data);
      // set data to be the newly allocated and filled 2D array
      data = newData;
    }
  };


  // ===================
  //      Operators     
  // ===================

  // Pre:  other is defined
  // Post: This becomes a copy of other
  Matrix<T> & operator=(Matrix<T> & other){
    // If there is old data stored, delete it
    if (data != NULL){
      for (int i=0; i<max; i++){
	delete(data[i]);
      }
      delete(data);
    }
    size = other.size;
    max = other.max;
    init = other.init;
    // Initialize new data holds
    data = new T*[max];
    for (int i=0; i<max; i++){
      data[i] = new T[max];
      for (int s=0; s<max; s++){
	data[i][s] = init; //initialize every slot
      }
    }
    // Copy all values over
    for (int row=0; row<size; row++){
      for (int col=0; col<size; col++){
	data[row][col] = other[row][col];
      }// end col loop
    }//end row loop
  };

  // Pre:  0 < row < size 0 < col < size
  // Post: Given row is returned
  T * operator[](int row){
    return(data[row]);
  };

  // Pre:  other is defined and other.size == size
  // Post: The two matrices are multiplied, result is returned
  Matrix & operator*(Matrix<T> & other){
    Matrix<T> * temp = new Matrix(other.init, size);
    T slot; //temp holder for the current multiplication
    for (int row=0; row<size; row++){
      for (int col=0; col<size; col++){
	slot = data[row][0] * other.data[0][col]; //make slot
	// equivalent to the first operation for multiplication
	for (int curr=1; curr<size; curr++){ //finish the multipiation
	  slot += data[row][curr] * other.data[curr][col];
	}
	(*temp)[row][col] = slot;
      }
    }
    return (*temp);
  };  

  // Pre:  other is a defined matrix, other.size == this.size
  // Post: other is multiplied with this and stored in this
  Matrix & operator*=(Matrix<T> & other){
    (*this) = (*this) * other; //create a multiplied copy and store
    return(*this);
  }

  // Pre:  out and mat are defined
  // Post: ostream is modified with the contents of mat
  friend ostream & operator<<(ostream & out, Matrix & mat){
    out << " --";
    for (int i=0; i<mat.size; i++){
      out << "-";
    }
    out << "-" << endl;
    for (int row=0; row<mat.size; row++){
      out << "| ";
      for (int col=0; col<mat.size; col++){
	out << mat[row][col] << " ";
      }
      out << "|" << endl;
    }
    out << " --";
    for (int i=0; i<mat.size; i++){
      out << "-";
    }
    out << "-";
    return(out);
  };
};
