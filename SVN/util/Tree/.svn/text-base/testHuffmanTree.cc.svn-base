#include <iostream>
#include "huffmanTree.h"
#include "treeNode.h"
#include "icTuple.h"

using namespace std;

// Pre:  
// Post: 
int main(int argc, char * argv[]){
  int status = 0;

  treeNode<int> * n0 = new treeNode<int>(1);
  treeNode<int> * n1 = new treeNode<int>(1);
  treeNode<int> * n2 = new treeNode<int>(1);
  treeNode<int> * n3 = new treeNode<int>(1);

  huffmanTree<int> test0;
  huffmanTree<int> test1(n0);
  cout << "Test1 :" << test1 << endl;
  cout << "Constructors passed." << endl;

  test0.setRoot(n0);
  cout << "Test0 after setRoot: " << test0 << endl;

  test1.huffAdd(n1);
  test1.huffAdd(n2);
  test1.huffAdd(n3);

  cout << "Huffman adding 3 1's." << endl;
  cout << "test1 after huffman adds: " << test1 << endl;

  treeNode<int> * N0 = new treeNode<int>(1);
  treeNode<int> * N1 = new treeNode<int>(3);
  treeNode<int> * N2 = new treeNode<int>(4);
  treeNode<int> * N3 = new treeNode<int>(4);
  treeNode<int> * N4 = new treeNode<int>(5);
  treeNode<int> * N5 = new treeNode<int>(10);

  huffmanTree<int> test2;
  test2.huffAdd(N0);
  test2.huffAdd(N1);
  test2.huffAdd(N2);
  test2.huffAdd(N3);
  test2.huffAdd(N4);
  test2.huffAdd(N5);

  cout << "test2 after huffman adds: " << test2 << endl;
  cout << "Should be:                14384175942710" << endl;

  cout << "Setting up a huffTree with icTuples." << endl;


  //set up all of the strings for the icTuples
  char * s0 = new char[2];
  char * s1 = new char[2];
  char * s2 = new char[2];
  char * s3 = new char[2];
  s0[0] = 'a';
  s1[0] = 'b';
  s2[0] = 'c';
  s3[0] = 'd';
  s0[1] = '\0';
  s1[1] = '\0';
  s2[1] = '\0';
  s3[1] = '\0';
  //set up the icTuples
  icTuple t0;
  icTuple t1;
  icTuple t2;
  icTuple t3;
  t0.set(1, s0);
  t1.set(1, s1);
  t2.set(1, s2);
  t3.set(1, s3);
  //initialize the tree and then add all of the tuples
  huffmanTree<icTuple> test3;
  test3.huffAdd(t0);
  test3.huffAdd(t1);
  test3.huffAdd(t2);
  test3.huffAdd(t3);
  cout << "This should be the tree." << endl;
  cout << "The tree now looks like this: " << test3 << endl;

  unsigned int huffByte;
  int length;

  huffByte = 0;
  length = test3.getByte('a', huffByte);
  cout << "Size of a:   " << length << endl;
  cout << "Bytes for a: " << huffByte << endl << endl;

  huffByte = 0;
  length = test3.getByte('b', huffByte);
  cout << "Size of b:   " << length << endl;
  cout << "Bytes for b: " << huffByte << endl << endl;

  huffByte = 0;
  length = test3.getByte('c', huffByte);
  cout << "Size of c:   " << length << endl;
  cout << "Bytes for c: " << huffByte << endl << endl;

  huffByte = 0;
  length = test3.getByte('d', huffByte);
  cout << "Size of d:   " << length << endl;
  cout << "Bytes for d: " << huffByte << endl << endl;

  huffByte = 0;
  length = test3.getByte('e', huffByte);
  cout << "Size of e:   " << length << endl;
  cout << "Bytes for e: " << huffByte << endl << endl;

  cout << "Well, I guess it's time to continue on!" << endl;
  return(status);
}
