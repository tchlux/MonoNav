#include <iostream>
#include "Graph.h"
#include "Tuple.h"
#include "defs.h"
#include "LinkedList.h"

// #include "Matrix.h"

using namespace std;


// used for testing the files
int main(int argc, char * argv[]){
  int status = 0;
  // return status set to normal state

  // ==================================
  //      Testing the Graph.h file     
  // ==================================


  // Generate a few vertices for testing
  Tuple<int,int> pair0(0,1);
  vertex v0(pair0, DEFAULT_COLOR);

  Tuple<int,int> pair1(1,0);
  vertex v1(pair1, DEFAULT_COLOR);

  Tuple<int,int> pair2(1,1);
  vertex v2(pair2, DEFAULT_COLOR);

  Tuple<int,int> pair3(2,2);
  vertex v3(pair3, DEFAULT_COLOR);

  // Tuple<int,int> pair4(1,1);
  // vertex v4(pair4, DEFAULT_COLOR);

  // add the vertices
  Graph<vertex> test;
  test.addVertex(v0);
  test.addVertex(v1);
  test.addVertex(v2);
  test.addVertex(v3);
  // test.addVertex(v4);

  // add a set of delta vectors
  int dv = 3;
  test.addDeltaVector(dv);
  // dv = 2;
  // test.addDeltaVector(dv);
  dv = 1;
  test.addDeltaVector(dv);

  // Set the threshold for adjacency
  test.setThreshold(2);

  cerr << "test.cc Line 62: " << endl;
  cout << "Number of colors required: " << test.color()<<endl; 
  //try  and color the graph 
  cout << "Final Graph: " << endl << test << endl;


  cerr << "Completed testing, no seg faults!" << endl;
  return(status);
}

//   // ===================================
//   //      Testing the Matrix.h file     
//   // ===================================


//   int size = 2;
//   Matrix<int> test(size);
//   for (int i=0; i<size; i++){
//     test[i][i] = 2;
//   }
//   cout << "Matrix: " << endl;
//   cout << test << endl;
//   cout << "Previous matrix squared." << endl;
//   cout << test * test << endl;
//   cout << "New matrix" << endl;
//   test[0][1] = 3;
//   test[1][0] = 1;
//   cout << test << endl;
//   cout << "new matrix squared." << endl;
//   cout << test * test << endl;
//   for (int row=0; row<size; row++){
//     for (int col=0; col<size; col++){
//       test[row][col] = row + col;
//     }
//   }
//   cout << "Final matrix:" << endl;
//   cout << test << endl;
//   cout << "final matrix squared." << endl;
//   cout << test * test << endl;

//   cout << "Now testing a boolean matrix." << endl;
//   Matrix<bool> test0(size);
//   for (int row=0; row<size; row++){
//     for (int col=0; col<size; col++){
//       test0[row][col] = (row+col) != 2;
//     }
//   }
//   //  test0[0][0] = true;
//   cout << test0 << endl;
//   cout << "Test 0 multiplied by itself" << endl;
//   cout << test0 * test0 << endl;

//   test.expand();
//   test[2][0] = test[2][1] = test[2][2] = 0;
//   test[0][2] = test[1][2] = 0;
  

//   cout << "Test after expansion." << endl;
//   cout << test << endl;

//   test0.expand();
//   test0[2][0] = test0[2][1] = test0[2][2] = false;
//   test0[0][2] = test0[1][2] = false;


//   cout << "Test2 after expansion." << endl;
//   cout << test0 << endl;

//   return(status);
// }
