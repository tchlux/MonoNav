#include <iostream>
#include "Node.h"

using namespace std;

int main(int argc, char * argv[]){
  int status = 0;

  // ========================================
  //        Constructors & set methods
  // ========================================
  cerr << "testNode.cc Line 9: Testing constructors" << endl;
  Node<int> * test0 = new Node<int>;
  test0->setData(1); //set the data to 1
  Node<int> * test1 =  new Node<int>(4);

  test1->setPrevious(test0);
  test0->setNext(test1);  //build the ties for a new front

  test1->setNext(new Node<int>(5)); //tie test1 to another node with
  //        value 5
  test1->getNext()->setPrevious(test1);

  // ========================================
  //        Copy const. & get() methods
  // ========================================

  Node<int> * test2 =  new Node<int>(*test0); //get a copy of test0
  test2->setData(0);
  test2->getNext()->setData(2);
  test2->getNext()->getNext()->setData(3); //make this chain [0][2][3]
  cerr << "testNode.cc Line 14: Constructors complete" << endl;


  // ========================================
  //       operator= & traverse() method
  // ========================================

  //  Node<int> * test3 = new Node<int>(*(test1->traverse(1)));
  //^^ for testing the operator= method
  //  cout << *test3 << endl;

  // cout << "Removing the second element of test2\n";
  // cout << "The old test2:\n" << *test2 << endl;
  // test2->traverse(1)->remove();
  // cout << "The new test2:\n" << *test2 << endl;
  //^^ for testing the remove() method


  // ========================================
  //          swap() & merge() methods
  // ========================================

  // test3->swap(test1);
  // cout << "2 should be swapped with 1:\n" ;
  // cout << *test1 << endl;
  // cout << *test3 << endl;
  //^^ for testing the swap() method

  Node<int> * traverser = test2; //node for printing

  cout << "Merging test1 and test3:\n";
  test2->merge(test0);
  //  test0->merge(test2);
  //  test1->getPrevious()->merge(test2); //this also locks test2's destructor to test1's
  //  destructor, test1 should be deleted not test2

  cerr << "testNode.cc Line 65: Printing forwards from front" << endl;

  while (traverser->getNext() != NULL){
    //    traverser->debug(); //print debug info
    cout << *traverser << endl;
    traverser = traverser->getNext();
  }
  cerr << "testNode.cc Line 70: Printing backwards from back" << endl;
  while (traverser != NULL){
    cout << *traverser << endl;
    traverser = traverser->getPrevious();
  }

  // ========================================
  //             Operators
  // ========================================

  cout << "Comparing " << *test0 << " to " << *test2 << endl;
  cout << *test0 << " > " << *test2 << ": " << (*test0 > *test2) << endl; 
  cout << *test0 << " < " << *test2 << ": " << (*test0 < *test2) << endl; 
  cout << *test0 << " = " << *test2 << ": " << (*test0 == *test2) << endl; 
  cout << *test0 << " = " << *test0 << ": " << (*test0 == *test0) << endl; 

  // ========================================
  //              Destructors
  // ========================================
  delete(test0);
  delete(test1);
  //  delete(test2);
  //no need to call delete(test2) because it was merged with test1 and
  //              now  would point to garbage, given test1 was deleted
  return(status);
}
