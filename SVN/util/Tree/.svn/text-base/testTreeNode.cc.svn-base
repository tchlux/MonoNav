#include <iostream>
#include "treeNode.h"

using namespace std;

int main(int argc, char * argv[]){
  int status = 0;

  treeNode<int> test0; //default constructor
  treeNode<int> test1(1); //con. given data
  treeNode<int> * test2 = new treeNode<int>(2);
  treeNode<int> * test3 = new treeNode<int>(3);
  treeNode<int> * test4 = new treeNode<int>(4);
  cout << "Constructors passed" << endl << endl;

  cout << test1 <<" > "<< *test2 <<" : "<< (test1>*test2) <<endl;
  cout << test1 <<" < "<< *test2 <<" : "<< (test1<*test2) <<endl;
  cout << test1 <<" == "<< *test2 <<" : "<< (test1==*test2) <<endl;
  cout << test1 <<" >= "<< *test2 <<" : "<< (test1>=*test2) <<endl;
  cout << test1 <<" <= "<< *test2 <<" : "<< (test1<=*test2) <<endl;
  cout << endl;

  test0.setData(0);
  test3->setLeft(test2);
  test3->setRight(test4);
  cout << "Set test0 to 0, test3.left = test2, test3.right = test4\n";
  cout << "Now test0 is : " << test0 << endl;
  cout << "Now test3 is : " << *test3 << endl;

  treeNode<int> * test5 = new treeNode<int>(1);
  treeNode<int> * test6 = new treeNode<int>(3);
  treeNode<int> * test7 = new treeNode<int>(4);

  cout << "Adding sorted 1, 3, 4." << endl;
  test3->addSorted(test5);
  test3->addSorted(test6);
  test3->addSorted(test7);
  cout << "Now 3 is: " << *test3 << endl;

  cout << "sumData of 3, new data should equal 8" << endl;
  test3->sumData();
  cout << test3->getData() << endl;
  cout << "New tree should be: 143844" << endl;
  cout << *test3 << endl;

  return (status);
}
