#ifndef INCLUDED_MATRIX
#define INCLUDED_MATRIX

#include <iostream>
#include <fstream>

#define INVERSE_FACTOR 2 // The growth factor for taking inverse
#define REDUCED_VALUE 1.0 // The desired value on row reduction
#define ROUND_AMOUNT 5 // How many digits to 
#define ROUND_UP_THRESHOLD .48 // Threshold for floating point error

// Pre:  num is some floating point number, truncate is the number of
//       significant bits to drop from the float
// Post: Remove 'truncate' number of significant bits from this number
float round(float num, int places){
  int digits = 1;  for (int i=0;i<places;i++){digits*=10;};
  int final = (int) (num * digits);
  if ((num*digits - final) > ROUND_UP_THRESHOLD) final ++;
  return(((float) final) / digits);
}

// ======================
//      Constructors     
// ======================

template <class T>
class Matrix{

  //CI: Matrix is a two dimensional array of type T, it is useful for
  //    mathematical operations on matrices.  
  //    rows and cols are integers > 0, size never changes

protected:

  T init;    //Initial value for slots in this matrix 
  T ** Data; //holder for the two-d array of Data
  int Cols, Rows;  //current size of matrix

public:


  // Pre:  initValue valid, y_x >= x_s > 0
  // Post: Data storage is initialized
  Matrix(T initValue, int y_s, int x_s){
    Data = NULL;
    init = initValue;
    Rows = y_s;
    Cols = x_s;     
    initData(Rows, Cols);
  };

  // Pre:  other is defined
  // Post: this is built as a copy of other
  Matrix(const Matrix<T> & other){
    Data = NULL;
    Rows = Cols = 0;
    (*this) = other;
  };

  // ====================
  //      Destructor     
  // ====================

  ~Matrix(){
    clearData();
  };

protected:

  // ==================================
  //     Protected member functions     
  // ==================================

  // Pre:  other is defined, 0 < rowCol < other.Cols
  // Post: The rows and columns != to rowCol are put into Data
  void exclude(const Matrix<T> & other, int rowCol){
    Rows = other.Rows -1;
    Cols = other.Cols -1;
    Data = new T*[Rows];
    for (int r=1; (r-1)<Rows; r++){
      Data[r-1] = new T[Cols];
      for (int c=(rowCol); (c-rowCol)<other.Cols; c++){
	Data[r-1][c-rowCol] = other.get(r,(c+1)%other.Cols);
      }
    }
  };

  // Post: If there is Data, it is cleared
  void clearData(){
    if (Data != NULL){
      for (int r=0; r<Rows; r++){
    	delete[](Data[r]);
      }
      delete[]Data;
      Data = NULL; // Reset Data to NULL
    }
  };

  // Pre:  cols >= rows > 0
  // Post: Data is initialized to this size
  void initData(int rows, int cols){
    clearData();
    Data = new T*[rows]; // Initialize new top level array
    for (int r=0; r<rows; r++){
      Data[r] = new T[cols]; // Initialize every row
      for (int c=0; c<cols; c++)
	Data[r][c] = init; //initialize every col in the row
    }    
  };

  // Pre:  0 <= row < Rows, factor is well-defined
  // Post: Each element in the given row index is multiplied by factor
  void multRow(int row, T factor){
    for (int col=0; col<Cols; col++)
      Data[row][col] = factor * Data[row][col];
  };

  // Pre:  0 <= with < toReduce;  multiple initialized
  // Post: toReduce is reduced by item by multiple*with
  void reduceRow(int toReduce, int with, T multiple){
    for (int col=0; col<Cols; col++)
      Data[toReduce][col] -= Data[with][col] * multiple;
  };

public:

  // ============================
  //      Accessor functions     
  // ============================

  // This is the const operator
  T get(int row, int col) const {return(Data[row][col]);};

  // Returns the current value of sizes
  int getRows() const {return(Rows);};
  int getCols() const {return(Cols);};

  // Return the current value of init
  T getInit() const {return(init);};

  // =================================
  //      Public member functions     
  // =================================

  // =======================
  //      Set operators     
  // =======================

  // The diagonal is set to the given value
  void setDiagonal(T value){
    for (int rc=0; rc<(Rows>Cols?Rows:Cols); rc++)
      Data[rc][rc] = value;
  };

  // Pre:  The length of values must be greater than or equal to the
  //       smallest dimension of this matrix
  // Post: The diagonal is set to the values in values
  void setDiagonal(T * values){
    for (int rc=0; rc<(Rows>Cols?Cols:Rows); rc++)
      Data[rc][rc] = values[rc];
  };

  // Pre:  value is defined, 0 <= row < Rows
  // Post: The elements in the given row are set to value
  void setRow(int row, T value){
    for (int col=0; col<Cols; col++)
      Data[row][col] = value;
  };

  // Pre:  values is of length Cols, 0<=row<Rows
  // Post: The elements in the given row are set to values
  void setRow(int row, T * values){
    for (int col=0; col<Cols; col++)
      Data[row][col] = values[col];
  };

  // Pre:  value is defined
  // Post: The elements in the given col are all set to value
  void setCol(int col, T value){
    for (int row=0; row<Rows; row++)
      Data[row][col] = value;
  };

  // Pre:  values is of length Rows, 0<=col<Cols
  // Post: The elements in the given col are set to values
  void setCol(int col, T * values){
    for (int row=0; row<Rows; row++)
      Data[row][col] = values[row];
  };

  // Pre:  initValue is of type T and initialized
  // Post: init is set in this class
  void setInit(T initValue){
    init = initValue;
  };

  // Pre:  other.Rows <= Rows and other.Cols <= Cols
  // Post: Data from other is copied into this
  void setMatrix(const Matrix & other){
    for (int row=0; row<other.Rows; row++)
      for (int col=0; col<other.Cols; col++)
	Data[row][col] = other.get(row,col);
  };

  // =========================
  //      File operations     
  // =========================

  // Pre:  filename is a terminated character array
  // Post: the file is written
  void write(const char fileName[]) const{
    std::ofstream outFile(fileName);	// Open outfile named filename
    outFile << Rows << " " << Cols << std::endl; // write size and max
    outFile << init << std::endl;       // write init value
    for (int i=0; i<Rows; i++){
      for (int s=0; s<Cols; s++){
	outFile << Data[i][s] << " ";	// write all Data to file
      }
      outFile << std::endl;		// New lines between rows
    }
    outFile.close();		// Close the outFile
  };

  // Pre:  fileName is a matrix file and properly formatted
  // Post: The file is read in to this matrix
  void read(char fileName[]){
    std::cerr << "This feature has not been created: Matrix.read()" 
	      << std::endl;
  };

  // ===========================
  //      Matrix operations     
  // ===========================

  // Pre:  Matrix has been initialized
  // Post: This Matrix is transposed in place
  void transpose(){
    int rows = Cols; // Temporary holder
    Cols = Rows;
    T ** newData = new T*[rows]; // Initialize new top level array
    for (int r=0; r<rows; r++){
      newData[r] = new T[Cols]; // Initialize every row
      for (int c=0; c<Cols; c++)
	newData[r][c] = Data[c][r]; //initialize every col in the row
    }
    clearData(); // Clear out old Data
    Rows = rows; // Set the rows variable appropriately
    Data = newData; // Set the new Data into this object
  };

  // Pre:  Rows >= Cols > 0
  // Post: The determinant of this matrix recursively
  T determinant() const{
    T sum_total; // Initialize sum
    if (Rows == Cols){
      if (Rows == 1) // Base case for too small matrix
	sum_total = Data[0][0];
      else if (Rows == 2) // Base case for determinant
	sum_total = Data[0][0]*Data[1][1] - Data[0][1]*Data[1][0];
      else if (Rows == 3){
	Matrix<T> temp;
	sum_total = Data[0][0] * ((Matrix<T>((*this), 0)).determinant());
	for(int col=1; col<Cols; col++)
	  sum_total += Data[0][col] * ((Matrix<T>((*this), col)).determinant());
      }
      else
	std::cerr << "Matrix: Cannot do determinant of Matrix larger than 3x3" << std::endl;
    }
    else
      std::cerr << "DETERMINANT ERROR: This function only works on square matrices."
		<< std::endl;
    return (sum_total); // Return the sum
  };

  // Pre:  1 <= Rows <= Cols
  // Post: The rows are reduced to having a diagonal of 1's
  void rowReduce(){
    for (int row=0; row<Rows; row++){      
      T multiple = REDUCED_VALUE / Data[row][row]; // Make the leading
      // entry the desired reduced value
      multRow(row, multiple); // Make the leading number REDUCED_VAL
      for (int next=(row+1); next<Rows; next++)
	reduceRow(next, row, Data[next][row]); // Reduce the next row
	// so that the entry below this leading REDUCED_VAL is a 0      
    }
  };

  // Pre:  This matrix is invertable
  // Post: This matrix now equals its inverse
  void inverse(){
    Matrix<T> id(init, Rows, Cols); // Create a
    // matrix to hold the identity and later inverse
    id.setDiagonal(REDUCED_VALUE); // Default to 1.0
    for (int row=0; row<Rows; row++){      
      T multiple = REDUCED_VALUE / Data[row][row]; // Make the leading
      multRow(row, multiple); // entry the desired reduced value
      id.multRow(row, multiple); // Perform the operation on the id
      for (int next=(row+1); next<Rows; next++){
	id.reduceRow(next, row, Data[next][row]); // on id as well
	reduceRow(next, row, Data[next][row]); // Reduce the next row
	// so that the entry below this leading REDUCED_VAL is a 0
      }
    }
    // Go back up and make this matrix the identity (while
    // transforming id into the inverse
    for (int row=(Rows-1); row>=0; row--){
      for (int next=(row-1); next>=0; next--){
	id.reduceRow(next, row, Data[next][row]);
	reduceRow(next, row, Data[next][row]);
      }
    }
    (*this) = id; // Make the inverse this matrix
  };

  // Pre:  0 <= decimals <= 5
  // Post: All the values in the matrix are rounded to the given
  //       number of decimal places 
  void roundAll(int decimals){
    for (int row=0; row<Rows; row++)
      for (int col=0; col<Cols; col++)
	Data[row][col] = round(Data[row][col], decimals);
  };

  // ===================================
  //      Operator =, [], *, *=, <<     
  // ===================================

  // Pre:  other is defined
  // Post: This becomes a copy of other
  Matrix<T> & operator=(const Matrix<T> & other){
    // If there is old Data stored, delete it
    clearData();
    // Set member Data
    init = other.init; Rows = other.Rows; Cols = other.Cols;
    initData(other.Rows, other.Cols);
    // Copy all values over    
    for (int row=0; row<Rows; row++)
      for (int col=0; col<Cols; col++)
	Data[row][col] = other.get(row, col);
    return(*this);
  };

  // Pre:  0 < row < Rows
  // Post: Given row is returned as a reference without const for set
  T * operator[](int row){
    return(Data[row]);
  };

  // Pre:  other is defined and other.Rows == Cols
  // Post: The two matrices are multiplied, result is returned
  // WARNING: The return matrix is allocated with new and must be
  //          deleted
  Matrix & operator*(const Matrix<T> & other) const{
    Matrix<T> * temp = new Matrix(other.init, Rows, other.Cols);
    if (Cols != other.Rows)
      std::cerr << "MULTIPLICATION ERROR: other Matrix specs bad" 
		<< std::endl << "This:  " << (*this) << std::endl
		<< "Other: " << other << std::endl;
    else{
      T slot; //temp holder for the current multiplication
      for (int row=0; row<Rows; row++){
	for (int col=0; col<other.Cols; col++){
	  slot = Data[row][0] * other.Data[0][col]; //make slot
	  // equivalent to the first operation for multiplication
	  for (int ind=1; ind<other.Rows; ind++){
	    slot += Data[row][ind] * other.Data[ind][col];
	  }
	  (*temp)[row][col] = slot;
	}
      }
    }
    return (*temp); // Return the generated matrix
  };  

  // Pre:  other is a defined matrix, other.size == this.size
  // Post: other is multiplied with this and stored in this
  Matrix & operator*=(Matrix<T> & other){
    Matrix<T> result = (*this) * other; //create a multiplied copy
    (*this) = result;    delete(&result); // delete temporary  matrix
    return(*this);
  };

  // Pre:  out and mat are defined
  // Post: ostream is modified with the contents of mat
  friend  std::ostream & operator<<(std::ostream & out, const Matrix<T> & mat){
    out << std::endl << " --";
    for (int i=0; i<mat.Cols; i++) 
      out << "-";
    out << "-" << std::endl;
    for (int row=0; row<mat.Rows; row++){
      out << "| ";
      for (int col=0; col<mat.Cols; col++){
	out << mat.get(row,col) << " ";
      }
      out << "|" << std::endl;
    }
    out << " --";
    for (int i=0; i<mat.Cols; i++)
      out << "-";
    out << "-";
    return(out);
  };
};

#endif
