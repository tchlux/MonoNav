#include "AVL.h"
#include "iostream"
#include "AVLTree.h"

using namespace std;

int main(){
  AVLTree<int> oldTree;
  AVL<int> intTree;
  int elem0 = 8; // create a new integer object
  int elem1 = 5; // create a new integer object
  int elem2 = 1; // create a new integer object
  int elem3 = 2; // create a new integer object
  int elem4 = 3; // create a new integer object
  int elem5 = 4; // create a new integer object
  int elem6 = 7; // create a new integer object
  int elem7 = 9; // create a new integer object
  int elem8 = 6; // create a new integer object
  intTree.add(elem0);
  oldTree.add(&elem0);
  cout << intTree << endl;
  cout << oldTree << endl;
  intTree.add(elem1);
  oldTree.add(&elem1);
  cout << intTree << endl;
  cout << oldTree << endl;
  intTree.add(elem2);
  oldTree.add(&elem2);
  cout << intTree << endl;
  cout << oldTree << endl;
  intTree.add(elem3);
  oldTree.add(&elem3);
  cout << intTree << endl;
  cout << oldTree << endl;
  intTree.add(elem4);
  oldTree.add(&elem4);
  cout << intTree << endl;
  cout << oldTree << endl;
  intTree.add(elem5);
  oldTree.add(&elem5);
  cout << intTree << endl;
  cout << oldTree << endl;
  intTree.add(elem6);
  oldTree.add(&elem6);
  cout << intTree << endl;
  cout << oldTree << endl;
  intTree.add(elem7);
  oldTree.add(&elem7);
  cout << intTree << endl;
  cout << oldTree << endl;
  intTree.add(elem8);
  oldTree.add(&elem8);
  cout << intTree << endl;
  cout << oldTree << endl;
  return(0);
}
