#include <iostream>
#include "icTuple.h"

using namespace std;
int main(int argc, char * argv[]){
  int status = 0;
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

  icTuple test0;
  icTuple test1(1);
  icTuple test2(s2);
  icTuple test3;
  cout << "Constructors complete." << endl;

  test0.set(0, s0);
  test1.setRight(s1);
  test2.setLeft(2);

  test3.set(3,s3);

  cout << "Test0: " << test0 << endl;
  cout << "Test1: " << test1 << endl;
  cout << "Test2: " << test2 << endl;
  cout << "Test3: " << test3 << endl;

  cout << "Test1 +" << endl;
  test1++;
  cout << "Test1: " << test1 << endl;

  icTuple test4 = test2+test0;
  cout << "Test2+Test0" << endl;
  cout << "Result (Test4): " << test4 << endl;

  cout << "Test2 > Test0: " << (test2 > test0) << endl;
  cout << "Test2 > Test2: " << (test2 > test2) << endl;
  cout << "Test2 >= Test4: " << (test2 >= test4) << endl;
  cout << "Test2 == Test4: " << (test2 == test4) << endl;

  cout << "Test0 += Test2: " << endl;
  test0 += test2;
  cout << "Result: " << test0 << endl;

  int getT3l;
  char * getT3r;

  test3[getT3l];
  test3[getT3r];

  cout << "Value retrieved from\n test3: [" << getT3l
       << "," << getT3r << "]" << endl;

  return (status);
}
