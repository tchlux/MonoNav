#include <iostream>
#include "intBinTree.h"

#define TREE_SIZE 10

using namespace std;


// Pre:  
// Post: The binary tree class is thoroughly tested
int main(int argc, char * argv[]){
  int returnCondition = 0;
  intBinTree test;

  for (int i=0; i<TREE_SIZE; i++){
    test.addLeft(i);    
  }
  cout << "The current root : " << test.getRoot() << endl;
  test.deleteRoot();
  cout << "The current root : " << test.getRoot() << endl;
  cout << "The final result for the tree:\n" << test << endl;

  return (returnCondition);
}
