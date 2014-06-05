#include <iostream>
#include "Tuple.h"

using namespace std;

int main(int argc, char * argv[]){
  int status = 0;

  Tuple<int, char> test0;
  Tuple<int, char> test1(1, '\0');
  Tuple<int, char> test2(0, 'c');
  Tuple<int, char> test3;

  cout << "Constructors complete." << endl;

  test0.set(0, 'a');
  test1.setRight('b');
  test2.setLeft(2);

  test3.set(3,'d');

  cout << "Test0: " << test0 << endl;
  cout << "Test1: " << test1 << endl;
  cout << "Test2: " << test2 << endl;
  cout << "Test3: " << test3 << endl;

  cout << "Test0 left: " << test0.left() << endl;
  cout << "Test1 left: " << test1.left() << endl;
  cout << "Modifying test0 left to test1 left" << endl;
  test0.left() = test1.left();
  cout << "Test0 left: " << test0.left() << endl;

  // cout << "Value retrieved from\n test3: [" << getT3l
  //      << "," << getT3r << "]" << endl;

  return (status);
}
