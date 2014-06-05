#include "Loop.h"
#include "LoopNode.h"
#include <iostream>

using namespace std;

// Tests the Loop and LoopNode classes
int main(int argc, char *argv[]){
  int status = 0;

  // ================================
  //      Begin LoopNode testing     
  // ================================

  int ti0 = 0;
  char tc0 = 'a';

  LoopNode<int> * iTest0 = new LoopNode<int>();
  cout << "Pass:   LoopNode default constructor " << endl;

  iTest0->setData(ti0);
  if (iTest0->getData() == 0){
    cout << "Pass:   LoopNode setData" << endl;
  }
  else{
    cout << " -Fail: LoopNode setData" << endl;
  }

  LoopNode<char> * cTest0 = new LoopNode<char>(tc0);
  if (cTest0->getData() == 'a'){
    cout << "Pass:   LoopNode 'given data' constructor" << endl;
  }
  else{
    cout << " -Fail: LoopNode 'given data' constructor" << endl;
  }

  LoopNode<int> * iTest1 = new LoopNode<int>(*iTest0);
  if (iTest1->getData() == 0)
    cout << "Pass:   LoopNode copy constructor" << endl;
  else{
    cout << " -Fail: LoopNode copy constructor" << endl;    
  }

  (*iTest1)++;

  if ((*iTest0) < (*iTest1)){
    cout << "Pass:   LoopNode operator++, operator<"
	 << endl;
  }
  else{
    cout << " -Fail: LoopNode operator++, operator<"
	 << endl;
  }

  cout << "LoopNode ostream operator: cTest0: " << *cTest0 << endl;

  // ====================================================
  //      End LoopNode Testing :: Begin Loop Testing     
  // ====================================================

  Loop<int> intTest;
  Loop<char> charTest(cTest0);
  intTest.add(iTest0);
  intTest.add(iTest1);

  cout << "Loop ostream: intTest: "<< intTest << endl;
  cout << "Loop ostream: charTest: "<< charTest << endl;

  cout << "Loop traversals: ";

  for (int i=-5; i<6; i++){
    cout << "i = " << i << " : " << *(intTest[i]) << endl;
  }

  intTest.remove(0);
  cout << "intTest without the 0: " << intTest << endl;
  intTest.remove(0);
  cout << "intTest with nothing:  " << intTest << endl;

  intTest.add(ti0);
  (*(intTest[0]))++;
  intTest.add(ti0);
  (*(intTest[1]))++;
  (*(intTest[1]))++;
  intTest.add(ti0);
  cout << "intTest with 0->2:     " << intTest << endl;
  intTest[0]->debug();
  intTest[1]->debug();
  intTest[2]->debug();
  cout << "Debug on index(3) which is technically index(0)" << endl;
  intTest[3]->debug();
  cout << "Sorting" << endl;
  intTest.sort();
  cout << "intTest with 0->2:     " << intTest << endl;
  cout << "Four destructor calls ahead" << endl;
  return(status);
}
