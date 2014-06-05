#include <iostream>
#define ROWS 10
#define COLS 10

int * createMatrix (int rows, int cols){
  int * matrix = new int[rows][cols];
  for (int r=0; r<rows; r++){
    for (int c=0; c<cols;c++){
      matrix[r][c] = 1;
    }
  }
  return (matrix);
}


int main(int argc,  char * argv[]){
  int * matrix = createMatrix(ROWS, COLS);
}
