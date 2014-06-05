#include <iostream>
#include "LinkedList.h"
#include "Node.h"

using namespace std;

// Pre:  
// Post: test linked list sorting and adding
int main(int argc, char * argv[]){
  int status = 0;
  Node<int> * node0 = new Node<int>(3);
  Node<int> * node1 = new Node<int>(2);
  Node<int> * node2 = new Node<int>(0);
  Node<int> * node3 = new Node<int>(1);
  Node<int> * node4 = new Node<int>(4);
  Node<int> * node5 = new Node<int>(5);

  LinkedList<int> test;
  cerr << "testLl.cc Line 12: created linked list" << endl;
  test.addFront(node0);
  test.addFront(node1);
  test.addFront(node2);
  test.addFront(node3);
  test.addFront(node4);
  test.addFront(node5);
  cerr << "testLl.cc Line 18: Added front six times" << endl;
  cerr << "\ntestLl.cc Line 16: Before sort\n" << test << endl;
  test.sort();
  cerr << "testLl.cc Line 16:   After sort\n" << test << endl;
  test.deleteFront();
  cerr << "\ntestLl.cc Line 32: After deleting front: "<<test<<endl;
  test.deleteBack();
  cerr << "testLl.cc Line 32: After deleting back: "<<test<<endl;

  cout << "The previous list has a node of value 1: " 
       << test.has(new Node<int>(4)) << endl;

  cout << "The previous list has a node of value 0: " 
       << test.has(new Node<int>(0)) << endl;

  test.addBack(new Node<int>(3));
  cerr << "testLl.cc Line 32: After adding 5 to back: \n"<<test<<endl;
  test.sort();
  cout << "After sorting: \n" << test<<endl;
  
  Node<int> * found = test.find(new Node<int>(3));
  cout << "Tried to find node with value 3: " << *found << endl;
  found = test.find(new Node<int>(5));
  cout << "Tried to find node with value 5: " << found << endl;

  return (status);
}
