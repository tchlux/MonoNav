#include <iostream>
#include "Stack.h"

using namespace std;

int main(int argc, char * argv[]){
  int num1 = 10;
  int num2 = 20;
  Stack<int> intStack1;
  intStack1.push(num1);
  intStack1.push(num2);

  int num3 = 30;
  int num4 = 40;
  Stack<int> intStack2;
  intStack2.push(num3);
  intStack2.push(num4);

  Stack<Stack<int> > metaStack;
  metaStack.push(intStack1);
  metaStack.push(intStack2);
  Stack<int> pop1 = metaStack.pop();
  Stack<int> pop2 = metaStack.pop();
  cout << "First Pop: " << pop1 << "\nSecond Pop: " 
       << pop2 << endl;

  return(0);
}
