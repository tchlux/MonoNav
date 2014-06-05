#include <iostream>
#include "Tree.h"
#include "treeNode.h"

using namespace std;

// Pre:  
// Post: 
int main(int argc, char * argv[]){
  int status = 0;

  treeNode<int> * n0 = new treeNode<int>(0);
  treeNode<int> * n1 = new treeNode<int>(1);
  treeNode<int> * n2 = new treeNode<int>(2);
  treeNode<int> * n3 = new treeNode<int>(3);

  Tree<int> test0;
  Tree<int> test1(n1);
  cout << "Test1 :" << test1 << endl;
  cout << "Constructors passed." << endl;

  test0.setRoot(n0);
  cout << "Test0 after setRoot: " << test0 << endl;

  test1.add(0);
  test1.add(n2);
  test1.add(n3);

  cout << "Added 0, 2, 3 to Test1" << endl;
  cout << "test1 after adds: " << test1 << endl;

  treeNode<int> * N0 = new treeNode<int>(1);
  treeNode<int> * N1 = new treeNode<int>(3);
  treeNode<int> * N2 = new treeNode<int>(4);
  treeNode<int> * N3 = new treeNode<int>(4);
  treeNode<int> * N4 = new treeNode<int>(5);
  treeNode<int> * N5 = new treeNode<int>(10);

  Tree<int> test2;
  test2.add(N1);
  test2.add(N5);
  test2.add(N3);
  test2.add(N0);
  test2.add(N4);
  test2.add(N2);

  cout << "test2 after adds: " << test2 << endl;

  cout << "Deleting a 4." << endl;
  int x = 4;
  test2.deleteNode(x);
  test2.deleteNode(x);
  cout << "Result: " << test2 << endl;

  cout << "Well, I guess it's time to continue on!" << endl;

  return(status);
}
