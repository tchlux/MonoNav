#include <iostream>
#include "Matrix.h"

#define DEFAULT_INT 0
#define DEFAULT_BOOL false
#define DEFAULT_FLOAT 0.0

using namespace std;


// used for testing the matrix class
int main(int argc, char * argv[]){
  int status = 0;
  // return status set to normal state

  // ===================================
  //      Testing the Matrix.h file     
  // ===================================

  Matrix<float> mvp(0.0, 4, 4);
  mvp.setDiagonal(1.0);
  mvp[0][0] = .75;
  mvp[2][2] = -1.0;
  mvp[3][2] = -1.0;
  Matrix<float> vector(0.0, 1, 4);
  float pos[4] = {.5, -.4, -.2, 0.0};
  vector.setRow(0, pos);
  std::cerr << "vector*mvp: " << vector*mvp << std::endl;
  return(status);
}
